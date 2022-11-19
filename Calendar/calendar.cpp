#include "calendar.hh"
#include "ui_calendar.h"

Calendar::Calendar(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calendar)
{
    ui->setupUi(this);
    //read data from file
    emit ui->calendarWidget->clicked(QDate::currentDate());
}

Calendar::~Calendar()
{
    delete ui;
}


void Calendar::on_calendarWidget_clicked(const QDate &date)
{
    auto it = data.find(date);
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
    ui->stackedWidget->setCurrentIndex(1);
}


void Calendar::on_deleteButton_clicked()
{
    if(!create_confirmation_message("Are you sure you want to delete the contents?")){
        clear_text_browser();
        data.erase(data.find(ui->calendarWidget->selectedDate()));
        //add write to file
    }
}


void Calendar::on_quitButton_clicked()
{
    if(create_confirmation_message("Are you sure you want to quit?")){
        close();
    }
}


void Calendar::on_saveButton_clicked()
{
    QDate date = ui->calendarWidget->selectedDate();
    QString qstring = ui->plainTextEdit->toPlainText();
    add_entry(date, qstring);
    emit ui->calendarWidget->clicked(date);
    navigate_to_calendar();
    //add write to file
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
    auto reply = QMessageBox::question(ui->stackedWidget->currentWidget(),"",QString::fromStdString(text));
    if(reply == QMessageBox::Yes){
        return true;
    }
    return false;
}

