#include "calendar.hh"
#include "ui_calendar.h"

Calendar::Calendar(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calendar)
{
    ui->setupUi(this);
    data.insert(std::pair<QDate,QString*>(*new QDate(2022, 11, 19), new QString("test")));
}

Calendar::~Calendar()
{
    delete ui;
}


void Calendar::on_calendarWidget_clicked(const QDate &date)
{
    ui->textBrowser->setText(*data.at(date));
}

