#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QStackedWidget>
#include<QToolButton>
#include<QLabel>
#include <QFont>
#include<QComboBox>
#include <QMainWindow>
#include"widget_visitorpage.h"
#include<QTimer>
#include<QMouseEvent>

#include<QVector>
#include<QPainter>
#include<QPair>
#include"mylabel.h"

namespace Ui {
class MyMainWindow;
}


class MyMainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        QPoint pos = event->pos();
        qDebug() << "Mouse Pressed at position: " << pos;
    }


public:
    explicit MyMainWindow(QWidget *parent = 0);
    ~MyMainWindow();
    QAction *action_Back;
    QAction *action_Exit;
    QAction *action_Help;
    QWidget *Widget_central;
    QStackedWidget *StackedWidget_mainfunctionpage;
    QWidget *Widget_startpage;
    QWidget *Widget_guidepage;
    QToolButton *button_guide;
    QToolButton *button_visitor;
    QLabel *label_startpageimg;
    QComboBox *box_start;
    QComboBox *box_end;
    QComboBox *box_speed;
    QToolButton *button_startguide;
    QToolButton *button_backguide;
    QToolButton *button_backmenu;

    QToolButton *button_drawline;   //添加

    widget_visitorpage *Widget_visitorpage;
    QTimer *time;
    location_direction timeoutlocation_direction;
    location_direction timeoutlocation_directionmid;
    location_direction timeoutlocation_directionend;
    int timeoutdx;
    int timeoutdy;
    bool timestop=false;
    int guide_speed;

    MyLabel* label;

private:
    Ui::MyMainWindow *ui;
private slots:
    void actionBack();
    void actionExit();
    void actionHelp();
    void visitorskip();
    void guideskip();
    void guide();
    void ontimeout();
    void backguige();
    void backmenu();

    void guideline();
    void endvisit();

protected:


};

#endif // MYMAINWINDOW_H
