#ifndef CALENDAR_HH
#define CALENDAR_HH

#include <QMainWindow>
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

private:
    Ui::Calendar *ui;
    std::map<QDate,QString*> data;
};
#endif // CALENDAR_HH
