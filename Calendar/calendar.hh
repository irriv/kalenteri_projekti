#ifndef CALENDAR_HH
#define CALENDAR_HH

#include <QMainWindow>
#include <QMessageBox>
#include <map>

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

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_quitButton_clicked();

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    void clear_text_browser();
    void add_entry(QDate date, QString qstring);
    void navigate_to_calendar();
    bool create_confirmation_message(std::string text);

    Ui::Calendar *ui;
    std::map<QDate,std::string> data;
};
#endif // CALENDAR_HH
