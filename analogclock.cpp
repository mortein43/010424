
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
    setStyleSheet("background-color: black;");
}

void AnalogClock::paintEvent(QPaintEvent *)
{
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };
    static const QPoint secHand[3] = {
        QPoint(5, 7),
        QPoint(-5, 7),
        QPoint(0, -75)
    };
    QColor secColor(255, 0, 0);
    QColor hourColor(255, 212, 22);
    QColor minuteColor(50, 68, 255);
    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    painter.setPen(Qt::NoPen);
    painter.setBrush(secColor);
    QTime time = QTime::currentTime();
    painter.save();
    painter.rotate(6 * time.second());
    painter.drawConvexPolygon(secHand, 3);
    painter.restore();
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();
    painter.rotate(15.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();
    painter.setPen(hourColor);
    for (int i = 0; i < 24; ++i) {
        painter.drawLine(73, 0, 83, 0);
        painter.rotate(15.0);
    }
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
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
}


/*AnalogClock::~AnalogClock()
{
    delete ui;
}*/


