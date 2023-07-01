
/*#ifndef MYLABEL_H
#define MYLABEL_H

//#include <QLabel>
#include<QWidget>
#include <QPainter>
#include <QPaintEvent>


class MyLabel : public QWidget
{
    Q_OBJECT

public:
    //MyLabel(QWidget*);
    MyLabel(QWidget *parent = nullptr):QWidget(parent){}
protected:
    void paintEvent(QPaintEvent *event) ;
};

#endif // MYLABEL_H*/

#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QPainter>
class MyLabel : public QLabel
{
public:
    MyLabel(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // MYLABEL_H
