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
        ui->textBrowser->setText(QString::fromStdString(it->second));
    }
    else{
        clear_text_browser();
    }
}


void Calendar::on_editButton_clicked()
{
    ui->dateLabel->setText("Now editing: " + ui->calendarWidget->selectedDate().toString("dd.MM.yyyy"));
    if(data.find(ui->calendarWidget->selectedDate()) != data.end()){
        if(create_confirmation_message("This date already has a note.\nAre you sure you want to edit it?")){
            ui->stackedWidget->setCurrentIndex(1);
        }
        return;
    }
    ui->stackedWidget->setCurrentIndex(1);
}


void Calendar::on_deleteButton_clicked()
{
    if(create_confirmation_message("Are you sure you want to delete the contents?")){
        const auto &it = data.find(ui->calendarWidget->selectedDate());
        if(it != data.end()){
            data.erase(it);
            clear_text_browser();
            write_to_file();
        }
    }
}


void Calendar::on_quitButton_clicked()
{
    if(create_confirmation_message("Are you sure you want to close the application?")){
        write_to_file();
        close();
    }
}


void Calendar::on_saveButton_clicked()
{
    const QDate &date = ui->calendarWidget->selectedDate();
    const QString &qstring = ui->plainTextEdit->toPlainText();
    add_entry(date, qstring);
    write_to_file();
    emit ui->calendarWidget->clicked(date);
    navigate_to_calendar();
}


void Calendar::on_cancelButton_clicked()
{
    if(create_confirmation_message("Are you sure you want to cancel?")){
        navigate_to_calendar();
    }
}


void Calendar::clear_text_browser(){
    ui->textBrowser->clear();
}


void Calendar::add_entry(QDate date, QString qstring)
{
    data.insert(std::pair<QDate,std::string>(date,qstring.toStdString()));
}


void Calendar::navigate_to_calendar()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->plainTextEdit->clear();
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
    const json &object = construct_json();
    if(auto fs = std::ofstream(DATAFILE)){
            try{
                std::string content = object.dump(4);
                fs.write(content.data(), content.size());
                std::cout << "File written." << std::endl;
            }  catch (const std::exception& e){
                std::cout << "An exception occurred when writing to file: " << e.what() << std::endl;
            }
        }
        else{
            std::cout << "Failed writing file." << std::endl;
    }
}


void Calendar::read_file()
{
    if(auto fs = std::ifstream(DATAFILE)){
            try{
                json object = json::parse(fs);
                for(const auto &pair : object){
                    add_entry(QDate::fromString(QString::fromStdString(pair.front()),"dd.MM.yyyy"), QString::fromStdString(pair.back()));
                }
                std::cout << "File read." << std::endl;
            }  catch (const std::exception& e){
                std::cout << "An exception occurred when reading file: " << e.what() << std::endl;
            }
        }
        else{
            std::cout << "Failed reading file." << std::endl;
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
