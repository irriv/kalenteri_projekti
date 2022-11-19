#ifndef CALENDAR_HH
#define CALENDAR_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calendar; }
QT_END_NAMESPACE

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = nullptr);
    ~Calendar();

private:
    Ui::Calendar *ui;
};
#endif // CALENDAR_HH
