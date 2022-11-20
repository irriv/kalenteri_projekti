#include "calendar.hh"
#include "ui_calendar.h"

const std::string &DATAFILE = "calendarData.json";


Calendar::Calendar(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calendar)
{
    ui->setupUi(this);
    read_file();
    emit ui->calendarWidget->clicked(QDate::currentDate());
}

Calendar::~Calendar()
{
    delete ui;
}


void Calendar::on_calendarWidget_clicked(const QDate &date)
{
    const auto &it = data.find(date);
    if(it != data.end()){
        ui->listWidget->setCurrentItem(ui->listWidget->findItems(it->first.toString("dd.MM.yyyy"), Qt::MatchExactly).at(0));
        ui->textBrowser->setText(QString::fromStdString(it->second));
        ui->deleteButton->setEnabled(true);
    }
    else{
        ui->textBrowser->clear();
        ui->listWidget->clearSelection();
        ui->deleteButton->setDisabled(true);
    }
}


void Calendar::on_listWidget_itemClicked(QListWidgetItem *item)
{
    const auto &it = data.find(QDate::fromString(item->text(), "dd.MM.yyyy"));
    ui->calendarWidget->setSelectedDate(it->first);
    ui->textBrowser->setText(QString::fromStdString(it->second));
    ui->deleteButton->setEnabled(true);
}


void Calendar::on_editButton_clicked()
{
    ui->dateLabel->setText("Now editing: " + ui->calendarWidget->selectedDate().toString("dd.MM.yyyy"));
    const auto &it = data.find(ui->calendarWidget->selectedDate());
    ui->plainTextEdit->setFocus();
    if(it != data.end()){
        ui->plainTextEdit->setPlainText(QString::fromStdString(it->second));
        QTextCursor newCursor = ui->plainTextEdit->textCursor();
        newCursor.movePosition(QTextCursor::End);
        ui->plainTextEdit->setTextCursor(newCursor);
    }
    else{
        ui->plainTextEdit->clear();
    }
    ui->stackedWidget->setCurrentIndex(1);
}


void Calendar::on_deleteButton_clicked()
{
    if(create_confirmation_message("Are you sure you want to delete\nthe contents of " + ui->calendarWidget->selectedDate().toString("dd.MM.yyyy").toStdString() + "?")){
        ui->listWidget->takeItem(ui->listWidget->currentRow());
        ui->listWidget->clearSelection();
        data.erase(data.find(ui->calendarWidget->selectedDate()));
        ui->textBrowser->clear();
        ui->deleteButton->setDisabled(true);
    }
}


void Calendar::on_quitButton_clicked()
{
    close();
}


void Calendar::on_saveButton_clicked()
{
    const QString &qstring = ui->plainTextEdit->toPlainText();
    if(qstring.isEmpty()){
        ui->stackedWidget->setCurrentIndex(0);
        return;
    }
    const QDate &date = ui->calendarWidget->selectedDate();
    const auto &it = data.find(date);
    if(it != data.end()){
        data.erase(it);
    }
    data.insert(std::pair<QDate,std::string>(date,qstring.toStdString()));
    ui->listWidget->clear();
    for(auto it = data.rbegin(); it != data.rend(); it++){
        ui->listWidget->addItem(it->first.toString("dd.MM.yyyy"));
    }
    emit ui->calendarWidget->clicked(date);
    ui->stackedWidget->setCurrentIndex(0);
}


void Calendar::on_cancelButton_clicked()
{
    if(create_confirmation_message("Are you sure you want to cancel\nediting the contents of " + ui->calendarWidget->selectedDate().toString("dd.MM.yyyy").toStdString() + "?")){
        ui->stackedWidget->setCurrentIndex(0);
    }
}


bool Calendar::create_confirmation_message(std::string text)
{
    const auto &reply = QMessageBox::question(ui->stackedWidget->currentWidget(),"",QString::fromStdString(text));
    if(reply == QMessageBox::Yes){
        return true;
    }
    return false;
}


void Calendar::write_to_file()
{
    if(auto fs = std::ofstream(DATAFILE)){
            try{
                std::string content = construct_json().dump();
                fs.write(content.data(), content.size());
            }  catch (const std::exception& e){
            }
        }
        else{
    }
}


void Calendar::read_file()
{
    if(auto fs = std::ifstream(DATAFILE)){
            try{
                json object = json::parse(fs);
                for(const auto &pair : object){
                    data.insert(std::pair<QDate,std::string>(QDate::fromString(QString::fromStdString(pair.front()),"dd.MM.yyyy"),pair.back()));
                }
                for(auto it = data.rbegin(); it != data.rend(); it++){
                    ui->listWidget->addItem(it->first.toString("dd.MM.yyyy"));
                }
            }  catch (const std::exception& e){
            }
        }
        else{
        }
}


json Calendar::construct_json()
{
    json object;
    for(const auto &date_string_pair : data){
        object.push_back({date_string_pair.first.toString("dd.MM.yyyy").toStdString(), date_string_pair.second});
    }
    return object;
}


void Calendar::closeEvent(QCloseEvent *event)
{
    write_to_file();
    event->accept();
}
