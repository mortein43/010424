
#include "analogclock.h"
#include "./ui_analogclock.h"
#include <QPainter>
#include <QTime>
#include <QTimer>


AnalogClock::AnalogClock(QWidget *parent)
    : QWidget (parent)
{
    //ui->setupUi(this);
    QTimer *timer = new  QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
    timer->start(1000);
    setWindowTitle(tr("Стрілковий годинник"));
    resize(400, 400);
    setStyleSheet("background-color: black");
}

void AnalogClock::paintEvent(QPaintEvent *)
{
    static const QPoint hourHand[4] = {
        QPoint(3, -20),
        QPoint(0, 0),
        QPoint(-3, -20),
        QPoint(0, -35)

    };
    static const QPoint minuteHand[4] = {
        QPoint(4, -30),
        QPoint(0, 0),
        QPoint(-4, -30),
        QPoint(0, -55)
    };
    static const QPoint secHand[3] = {
        QPoint(1, 8),
        QPoint(-1, 8),
        QPoint(0, -60)
    };
    QColor secColor(255, 0, 0);
    QColor hourColor(255, 212, 22);
    QColor minuteColor(50, 68, 255);
    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    QTime time = QTime::currentTime();

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 4);
    painter.restore();
    painter.setPen(minuteColor);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) == 0)
        {
            painter.setPen(secColor);

            painter.drawLine(88, 0, 96, 0);
        } else
        {
            painter.setPen(minuteColor);
            painter.drawLine(92, 0, 96, 0);
        }
        painter.rotate(6.0);
    }
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();
    painter.rotate(15.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 4);
    painter.restore();
    painter.setPen(hourColor);
    for (int i = 0; i < 24; ++i) {
        painter.drawLine(73, 0, 83, 0);
        painter.rotate(15.0);
    }
    painter.drawText (int (13),int (-55), "1");
    painter.drawText (int (28),int (-50), "2");
    painter.drawText (int (43),int (-40), "3");
    painter.drawText (int (52),int (-27), "4");
    painter.drawText (int (60),int (-13), "5");
    painter.drawText (int (62),int (4), "6");
    painter.drawText (int (62),int (22), "7");
    painter.drawText (int (54),int (38), "8");
    painter.drawText (int (43),int (50), "9");
    painter.drawText (int (25),int (60), "10");
    painter.drawText (int (10),int (65), "11");
    painter.drawText (int (-6),int (68), "12");
    painter.drawText (int (-22),int (65), "13");
    painter.drawText (int (-40),int (58), "14");
    painter.drawText (int (-50),int (47), "15");
    painter.drawText (int (-62),int (35), "16");
    painter.drawText (int (-67),int (20), "17");
    painter.drawText (int (-67),int (4), "18");
    painter.drawText (int (-67),int (-13), "19");
    painter.drawText (int (-60),int (-29), "20");
    painter.drawText (int (-49),int (-41), "21");
    painter.drawText (int (-37),int (-50), "22");
    painter.drawText (int (-23),int (-56), "23");
    painter.drawText (int (-6),int (-58), "24");
    painter.setPen(Qt::NoPen);
    painter.setBrush(secColor);

    painter.save();
    painter.rotate(6 * time.second());
    painter.drawConvexPolygon(secHand, 3);
    painter.restore();
}



