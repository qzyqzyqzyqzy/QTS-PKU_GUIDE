
#include "mylabel.h"
#include<QDebug>
extern int firstpoint,lastpoint;
extern QVector<QPair<int,int>> location;

MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent)
{
}

void MyLabel::paintEvent(QPaintEvent *event)
{
    qDebug()<<"line0";
    QLabel::paintEvent(event);
    qDebug()<<"line";
    QPainter painter(this);
    //painter.setPen(Qt::blue);
    painter.setPen(QPen(Qt::red, 10));

    this->setGeometry(0,0,1280,720);
    //painter.drawLine(0, 0, width(), height());

    for (int i = firstpoint; i + 1 <= lastpoint; i++)
    {
        int x1 = location[i].first;
        int y1 = location[i].second;
        QPoint point1(x1, y1);

        int x2 = location[i + 1].first;
        int y2 = location[i + 1].second;
        QPoint point2(x2, y2);

        painter.drawLine(point1, point2);
    }
}


