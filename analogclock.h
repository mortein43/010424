
#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>



QT_BEGIN_NAMESPACE
namespace Ui { class AnalogClock; }
QT_END_NAMESPACE

class AnalogClock : public QWidget

{
    Q_OBJECT

public:
    AnalogClock(QWidget *parent = nullptr);


private:
    Ui::AnalogClock *ui;
    void paintEvent(QPaintEvent *event) override;
};

#endif // ANALOGCLOCK_H
