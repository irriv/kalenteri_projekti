#ifndef CALENDAR_HH
#define CALENDAR_HH

#include <QMainWindow>
#include <QMessageBox>
#include <map>
#include "libs/nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <QListWidgetItem>

using json = nlohmann::json;

QT_BEGIN_NAMESPACE
namespace Ui { class Calendar; }
QT_END_NAMESPACE

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = nullptr);
    ~Calendar();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_quitButton_clicked();

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    bool create_confirmation_message(std::string text);
    void write_to_file();
    void read_file();
    json construct_json();
    void closeEvent (QCloseEvent *event);

    Ui::Calendar *ui;
    std::map<QDate,std::string> data;
};
#endif // CALENDAR_HH
