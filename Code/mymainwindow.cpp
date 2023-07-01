#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include<QMap>
#include<QDebug>
#include "navigation.h"
#include"location_direction.h"
#include<screenutil.h>
#include<QPainter>
#include<mylabel.h>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QEventLoop>

QString path="F:/Qt/weimin/weimin/img/";
extern QMap<location_direction,int> map;
QMap<QString,location_direction> guidemap;
extern location_direction nowlocation_direction;
extern QVector<QPair<int,int>> location;
extern int firstpoint,lastpoint;

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{

    //获取显示屏尺寸
    QSize screenSize=ScreenUtil::getScreenSize();
    int screenWidth,screenHeight;
    screenWidth = screenSize.width();
    screenHeight = screenSize.height();
    this->setMaximumSize(QSize(screenWidth, screenHeight));
    this->setMinimumSize(QSize(screenWidth, screenHeight));

    location.push_back(qMakePair(136*screenWidth/1280,381*screenHeight/720));
    location.push_back(qMakePair(386*screenWidth/1280,398*screenHeight/720));
    location.push_back(qMakePair(414*screenWidth/1280,248*screenHeight/720));
    location.push_back(qMakePair(542*screenWidth/1280,243*screenHeight/720));
    location.push_back(qMakePair(701*screenWidth/1280,235*screenHeight/720));
    location.push_back(qMakePair(727*screenWidth/1280,187*screenHeight/720));
    location.push_back(qMakePair(956*screenWidth/1280,148*screenHeight/720));
    location.push_back(qMakePair(1021*screenWidth/1280,225*screenHeight/720));
    location.push_back(qMakePair(1033*screenWidth/1280,440*screenHeight/720));
    location.push_back(qMakePair(949*screenWidth/1280,449*screenHeight/720));
    location.push_back(qMakePair(879*screenWidth/1280,423*screenHeight/720));
    location.push_back(qMakePair(761*screenWidth/1280,452*screenHeight/720));
    location.push_back(qMakePair(510*screenWidth/1280,420*screenHeight/720));
    location.push_back(qMakePair(542*screenWidth/1280,243*screenHeight/720));
    location.push_back(qMakePair(414*screenWidth/1280,248*screenHeight/720));
    location.push_back(qMakePair(386*screenWidth/1280,398*screenHeight/720));
    location.push_back(qMakePair(136*screenWidth/1280,381*screenHeight/720));

    qDebug()<<screenWidth<<' '<<screenHeight;  //输出窗口

    this->setWindowFlags(Qt::FramelessWindowHint); //设置无边框窗口，达到锁定页面的作用

    ui->setupUi(this);
    this->setWindowTitle(tr("PKU GUIDE"));
    action_Back=new QAction(tr("Back"),this);
    action_Exit=new QAction(tr("Exit"),this);
    action_Help=new QAction(tr("Help"),this);
    action_Back->setObjectName(QStringLiteral("action_Back"));
    action_Exit->setObjectName(QStringLiteral("action_Exit"));
    action_Help->setObjectName(QStringLiteral("action_Help"));
    QMenu *menu=new QMenu(tr("Menu"),this);
    QMenuBar *menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);
    menuBar->setStyleSheet("QMenuBar::icon { visibility: hidden; }");
    menuBar->addMenu(menu);
    menu->setTearOffEnabled(false);
    menu->setStyleSheet("QMenu::icon { width: 0px; }");
    menu->addAction(action_Back);
    menu->addAction(action_Exit);
    menu->addAction(action_Help);

    connect(action_Back,SIGNAL(triggered(bool)),this,SLOT(actionBack()));
    connect(action_Exit,SIGNAL(triggered(bool)),this,SLOT(actionExit()));
    connect(action_Help,SIGNAL(triggered(bool)),this,SLOT(actionHelp()));

    StackedWidget_mainfunctionpage=new QStackedWidget(ui->centralWidget);
    this->setCentralWidget(ui->centralWidget);
    Widget_startpage=new QWidget();
    Widget_startpage->setGeometry(QRect(0,0,screenWidth,screenHeight));

    StackedWidget_mainfunctionpage->addWidget(Widget_startpage);
    StackedWidget_mainfunctionpage->setObjectName(QStringLiteral("StackedWidget_mainfunctionpage"));
    StackedWidget_mainfunctionpage->setGeometry(QRect(0,0,screenWidth,screenHeight));
    StackedWidget_mainfunctionpage->setMaximumSize(screenWidth,screenHeight);
    StackedWidget_mainfunctionpage->setMinimumSize(screenWidth,screenHeight);

    //设置样式表
    QString stylesheet="QToolButton{"
                         "background-color: rgba(0, 0, 0, 0);"
                         "color:white;"
                         "}"
                         "QToolButton:hover{"
                         "background-color: rgba(0, 0, 0, 0);"
                         "color:yellow;"
                         "}";

    button_guide=new QToolButton(Widget_startpage) ;
    connect(button_guide,SIGNAL(clicked(bool)),this,SLOT(guideskip()));
    button_visitor=new QToolButton(Widget_startpage);
    connect(button_visitor,SIGNAL(clicked(bool)),this,SLOT(visitorskip()));
    label_startpageimg=new QLabel(Widget_startpage);
    button_guide->raise();
    button_visitor->raise();

    Widget_startpage->setObjectName(QStringLiteral("Widget_startpage"));
    button_guide->setObjectName(QStringLiteral("button_guide"));
    button_guide->setText(tr("Guide Mode"));
    button_guide->setGeometry(QRect(screenWidth/2-450,2*screenHeight/4 , 300, 150));

    QFont font;//设置字体
    font.setFamily(QStringLiteral("Kristen ITC"));
    font.setPointSize(28);
    font.setBold(true);
    font.setWeight(static_cast<QFont::Weight>(75));

    button_guide->setFont(font);
    button_guide->setStyleSheet(stylesheet);//透明背景
    button_visitor->setObjectName(QStringLiteral("button_visitor"));
    button_visitor->setText(tr("Visitor Mode"));
    button_visitor->setGeometry(QRect(screenWidth/2+150, screenHeight/2, 300, 150));
    button_visitor->setFont(font);
    button_visitor->setStyleSheet(stylesheet);

    label_startpageimg->setObjectName(QStringLiteral("label_startpageimg"));
    label_startpageimg->setGeometry(QRect(0, 0, screenWidth, screenHeight));
    label_startpageimg->setStyleSheet(QStringLiteral("background-color: transparent; border: 1px solid black;"));
    label_startpageimg->setPixmap(QPixmap(QString(path+"westgate.jpg")));
    label_startpageimg->setScaledContents(true);

    Widget_guidepage=new QWidget();
    StackedWidget_mainfunctionpage->addWidget(Widget_guidepage);
    Widget_guidepage->setObjectName(QStringLiteral("Widget_guidepage"));
    box_start = new QComboBox(Widget_guidepage);
    box_start->setObjectName(QStringLiteral("box_start"));
    //box_start->setGeometry(QRect(300, 100, 400, 40));
    box_start->setGeometry(QRect(screenWidth/8, screenHeight*3/4, screenWidth/8, screenHeight/16));
    box_start->setStyleSheet(QStringLiteral("font: 75 16pt \"Kristen ITC\";"));
    box_end = new QComboBox(Widget_guidepage);
    box_end->setObjectName(QStringLiteral("box_end"));
    //box_end->setGeometry(QRect(300, 200, 400, 40));
    box_end->setGeometry(QRect(screenWidth/2-screenWidth/16, screenHeight*3/4,screenWidth/8, screenHeight/16));
    box_end->setStyleSheet(QStringLiteral("font: 75 16pt \"Kristen ITC\";"));
    box_start->clear();
    box_start->insertItems(0, QStringList()
             << QApplication::translate("MyMainWindow", "westgate", Q_NULLPTR)
             << QApplication::translate("MyMainWindow", "boyatower", Q_NULLPTR)
             << QApplication::translate("MyMainWindow", "dezhai", Q_NULLPTR)
             << QApplication::translate("MyMainWindow", "yiti", Q_NULLPTR)
             << QApplication::translate("MyMainWindow", "huashenmiao", Q_NULLPTR)
            );
    box_end->clear();
    guidemap.insert("westgate",location_direction(0,0,0,0));
        guidemap.insert("boyatower",location_direction(230,600,0,0));
        guidemap.insert("dezhai",location_direction(0,270,0,0));
        guidemap.insert("yiti",location_direction(70,600,0,0));
        guidemap.insert("huashenmiao",location_direction(230,510,0,0));
    box_end->insertItems(0, QStringList()
             << QApplication::translate("MyMainWindow", "westgate", Q_NULLPTR)
             << QApplication::translate("MyMainWindow", "boyatower", Q_NULLPTR)
             << QApplication::translate("MyMainWindow", "dezhai", Q_NULLPTR)
             << QApplication::translate("MyMainWindow", "yiti", Q_NULLPTR)
             << QApplication::translate("MyMainWindow", "huashenmiao", Q_NULLPTR)
            );
    box_speed = new QComboBox(Widget_guidepage);
    box_speed->setObjectName(QStringLiteral("box_speed"));
    //box_speed->setGeometry(300,300,400,40);
    box_speed->setGeometry(QRect(screenWidth*3/4, screenHeight*3/4, screenWidth/8, screenHeight/16));
    box_speed->setStyleSheet(QStringLiteral("font: 75 16pt \"Kristen ITC\";"));
    box_speed->insertItems(0, QStringList()

            << QApplication::translate("MyMainWindow", "Fast", Q_NULLPTR)
            << QApplication::translate("MyMainWindow", "Normal", Q_NULLPTR)
            << QApplication::translate("MyMainWindow", "Slow", Q_NULLPTR)
            );

    QLabel *label_startpoint = new QLabel(Widget_guidepage);
    label_startpoint->setText(tr("Start from"));
    label_startpoint->setObjectName(QStringLiteral("label_startpoint"));
    //label_startpoint->setGeometry(QRect(80, 100, 200, 40));
    label_startpoint->setGeometry(QRect(screenWidth*1/8, screenHeight*2/3, screenWidth/8, screenHeight/16));
    label_startpoint->setStyleSheet(QStringLiteral("font: 75 16pt \"Kristen ITC\";"));
    label_startpoint->setScaledContents(true);
    QLabel *label_endpoint = new QLabel(Widget_guidepage);
    label_endpoint->setText(tr("End   at"));
    label_endpoint->setObjectName(QStringLiteral("endpoint"));
    //label_endpoint->setGeometry(QRect(80, 200, 200, 40));
    label_endpoint->setGeometry(QRect(screenWidth*1/2-screenWidth/16, screenHeight*2/3, screenWidth/8, screenHeight/16));
    label_endpoint->setStyleSheet(QStringLiteral("font: 75 16pt \"Kristen ITC\";"));
    label_endpoint->setTextFormat(Qt::AutoText);
    label_endpoint->setScaledContents(true);
    QLabel *label_speed=new QLabel(Widget_guidepage);
    label_speed->setText("Speed");
    label_speed->setObjectName(QStringLiteral("label_speed"));
    //label_speed->setGeometry(QRect(80, 300, 200, 40));
    label_speed->setGeometry(QRect(screenWidth*3/4, screenHeight*2/3, screenWidth/8, screenHeight/16));
    label_speed->setStyleSheet(QStringLiteral("font: 75 16pt \"Kristen ITC\";"));
    label_speed->setTextFormat(Qt::AutoText);
    label_speed->setScaledContents(true);
    QLabel *label_guidepageimg = new QLabel(Widget_guidepage);
    label_guidepageimg->lower();
    label_guidepageimg->setObjectName(QStringLiteral("guidepageimg"));
    label_guidepageimg->setGeometry(QRect(0, 0, screenWidth, screenHeight));
    label_guidepageimg->setPixmap(QPixmap((path+"guidemap")));
    label_guidepageimg->setScaledContents(true);

    QString stylesheet_start="QToolButton{"
                         "background-color: rgba(0, 0, 0, 0);"
                         "color:black;"
                         "font: 75 16pt \"Kristen ITC\";"
                         "}"
                         "QToolButton:hover{"
                         "background-color: rgba(0, 0, 0, 0);"
                         "color:red;"
                         "font: 75 16pt \"Kristen ITC\";"
                         "}";

    button_startguide = new QToolButton(Widget_guidepage);
    button_startguide->setObjectName(QStringLiteral("startguide"));
    button_startguide->setText(tr("Start"));
    button_startguide->setGeometry(QRect(screenWidth/2-screenWidth/12, screenHeight*4/5, screenWidth/6, screenHeight/6));
    button_startguide->setStyleSheet(stylesheet_start);

    button_drawline=new QToolButton(Widget_guidepage);
    button_drawline->setObjectName(QStringLiteral("drawline"));
    button_drawline->setText("Line");
    button_drawline->setGeometry(QRect(screenWidth*3/4, screenHeight*4/5, screenWidth/6, screenHeight/6));
    button_drawline->setStyleSheet(stylesheet_start);


    Widget_visitorpage=new widget_visitorpage();
    StackedWidget_mainfunctionpage->addWidget(Widget_visitorpage);
    connect(button_startguide,SIGNAL(clicked(bool)),this,SLOT(guide()) );   //槽函数关联

    connect(button_drawline,SIGNAL(clicked(bool)),this,SLOT(guideline()) );
    connect(Widget_visitorpage->button_endvisit,SIGNAL(clicked(bool)),this,SLOT(endvisit()) ) ;

    guidemap.insert("westgate",location_direction(0,0,0,0));
    guidemap.insert("boyatower",location_direction(230,600,0,0));
    guidemap.insert("dezhai",location_direction(0,270,0,0));
    guidemap.insert("yiti",location_direction(70,600,0,0));
    guidemap.insert("huashenmiao",location_direction(230,510,0,0));

    time =new QTimer(this);
    connect(time,&QTimer::timeout,this,&MyMainWindow::ontimeout);
    num_to_lo.insert(1,location_direction(0,0,0,0));
    num_to_lo.insert(2,location_direction(0,270,0,0));
    num_to_lo.insert(3,location_direction(70,600,0,0));
    num_to_lo.insert(4,location_direction(230,600,0,0));
    num_to_lo.insert(15,location_direction(230,270,0,0));
    num_to_lo.insert(17,location_direction(230,510,0,0));
    num_to_lo.insert(18,location_direction(0,600,0,0));
    lo_to_num.insert(location_direction(0,0,0,0),1);
    lo_to_num.insert(location_direction(0,270,0,0),2);
    lo_to_num.insert(location_direction(70,600,0,0),3);
    lo_to_num.insert(location_direction(230,600,0,0),4);
    lo_to_num.insert(location_direction(230,270,0,0),15);
    lo_to_num.insert(location_direction(230,510,0,0),17);
    lo_to_num.insert(location_direction(0,600,0,0),18);
    button_backguide=new QToolButton(Widget_visitorpage);
    connect(button_backguide,SIGNAL(clicked(bool)),this,SLOT(backguige()));
    button_backmenu=new QToolButton(Widget_visitorpage);
    connect(button_backmenu,SIGNAL(clicked(bool)),this,SLOT(backmenu()));
    button_backguide->setText("Back to guide");
    button_backmenu->setText("Back to menu");
    button_backguide->setFont(font);
    button_backguide->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0, 0)"));//透明背景
    button_backmenu->setFont(font);
    button_backmenu->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0, 0)"));//透明背景
    button_backguide->setGeometry(QRect(screenWidth/2-450,2*screenHeight/4 , 300, 150));
    button_backmenu->setGeometry(QRect(screenWidth/2+150, screenHeight/2, 300, 150));
    button_backguide->lower();
    button_backmenu->lower();

    label=new MyLabel(Widget_guidepage);


}
MyMainWindow::~MyMainWindow()
{
    delete ui;
}
void MyMainWindow::backguige()
{
    StackedWidget_mainfunctionpage->setCurrentIndex(1);
    button_backguide->lower();
    button_backmenu->lower();
    this->Widget_visitorpage->button_ahead->raise();
    this->Widget_visitorpage->button_left->raise();
    this->Widget_visitorpage->button_right->raise();
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
    Widget_guidepage->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(700);
    a->setStartValue(0.1);
    a->setEndValue(1);
    //a->setEasingCurve(QEasingCurve::InBack);
    a->setEasingCurve(QEasingCurve::Linear);
    QEventLoop loop;
    connect(a, SIGNAL(finished()), &loop, SLOT(quit()));
    a->start(QPropertyAnimation::DeleteWhenStopped);
    loop.exec();
}
void MyMainWindow::backmenu()
{
    StackedWidget_mainfunctionpage->setCurrentIndex(0);
    button_backguide->lower();
    button_backmenu->lower();
    this->Widget_visitorpage->button_ahead->raise();
    this->Widget_visitorpage->button_left->raise();
    this->Widget_visitorpage->button_right->raise();
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
    Widget_startpage->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(700);
    a->setStartValue(0.1);
    a->setEndValue(1);
    //a->setEasingCurve(QEasingCurve::InBack);
    a->setEasingCurve(QEasingCurve::Linear);
    QEventLoop loop;
    connect(a, SIGNAL(finished()), &loop, SLOT(quit()));
    a->start(QPropertyAnimation::DeleteWhenStopped);
    loop.exec();
}

void MyMainWindow::actionExit()
{
    this->close();
}
void MyMainWindow::actionBack()
{
    this->StackedWidget_mainfunctionpage->setCurrentIndex(0);

}
void MyMainWindow::actionHelp()
{

}
void MyMainWindow::visitorskip()
{
    this->Widget_visitorpage->label_img->setPixmap(QPixmap(path+"img0_0_0_1.jpg"));
    nowlocation_direction=location_direction(0,0,0,1);
    this->Widget_visitorpage->button_left->lower();
    this->Widget_visitorpage->button_right->lower();
    this->Widget_visitorpage->button_ahead->raise();
    this->StackedWidget_mainfunctionpage->setCurrentIndex(2);

    this->Widget_visitorpage->label_dezhai->lower();
    this->Widget_visitorpage->label_dezhai_h->lower();
    this->Widget_visitorpage->label_boya->lower();
    this->Widget_visitorpage->label_boya_h->lower();
    this->Widget_visitorpage->label_boya_p->lower();
    this->Widget_visitorpage->label_yiti->lower();
    this->Widget_visitorpage->label_yiti_h->lower();
    this->Widget_visitorpage->label_huashen->lower();
    this->Widget_visitorpage->label_huashen_h->lower();

    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
    Widget_visitorpage->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(700);
    a->setStartValue(0.1);
    a->setEndValue(1);
    //a->setEasingCurve(QEasingCurve::InBack);
    a->setEasingCurve(QEasingCurve::Linear);
    QEventLoop loop;
    connect(a, SIGNAL(finished()), &loop, SLOT(quit()));
    a->start(QPropertyAnimation::DeleteWhenStopped);
    loop.exec();
    this->Widget_visitorpage->StackedWidget_visitorview->setCurrentIndex(2);

    Widget_visitorpage->button_endvisit->lower();
}
void MyMainWindow::guideskip()
{
    button_drawline->raise();
    button_startguide->raise();

    box_end->raise();
    box_speed->raise();
    box_start->raise();

    this->StackedWidget_mainfunctionpage->setCurrentIndex(1);
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
    Widget_guidepage->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(700);
    a->setStartValue(0.1);
    a->setEndValue(1);
    //a->setEasingCurve(QEasingCurve::InBack);
    a->setEasingCurve(QEasingCurve::Linear);
    QEventLoop loop;
    connect(a, SIGNAL(finished()), &loop, SLOT(quit()));
    a->start(QPropertyAnimation::DeleteWhenStopped);
    loop.exec();
    //this->StackedWidget_mainfunctionpage->setCurrentIndex(1);
}
void MyMainWindow::ontimeout()
{
    if(!(timeoutlocation_direction==timeoutlocation_directionmid))
    {
        timeoutlocation_direction.x+=10*timeoutdx;
        timeoutlocation_direction.y+=10*timeoutdy;
        timeoutlocation_direction.dx=timeoutdx;
        timeoutlocation_direction.dy=timeoutdy;
        //qDebug()<<timeoutlocation_direction.x<<timeoutlocation_direction.y<<"  "<<timeoutdx<<timeoutdy;
        this->Widget_visitorpage->location_directionToimg(timeoutlocation_direction);
    }
    else
    {
        time->stop();
        timestop=true;
    }
}

void MyMainWindow::guide()
{
    this->Widget_visitorpage->label_dezhai_h->lower();
    this->Widget_visitorpage->label_dezhai->lower();
    this->Widget_visitorpage->label_boya->lower();
    this->Widget_visitorpage->label_boya_h->lower();
    this->Widget_visitorpage->label_yiti->lower();
    this->Widget_visitorpage->label_yiti_h->lower();
    this->Widget_visitorpage->label_huashen->lower();
    this->Widget_visitorpage->label_huashen_h->lower();
    this->Widget_visitorpage->label_boya_p->lower();


    timestop=false;
    QString start=this->box_start->currentText();
    QString end=this->box_end->currentText();
    QString speed=this->box_speed->currentText();
    if(speed=="Fast")
        guide_speed=100;
    else if(speed=="Normal")
        guide_speed=1000;
    else guide_speed=2000;

    if(start==end)return;

    this->StackedWidget_mainfunctionpage->setCurrentIndex(2);
    this->Widget_visitorpage->label_img->setPixmap(QPixmap(path+"imgstartguide.jpg"));
    this->Widget_visitorpage->label_img->setScaledContents(true);
    this->Widget_visitorpage->StackedWidget_visitorview->setCurrentIndex(1);
    this->Widget_visitorpage->button_ahead->lower();
    this->Widget_visitorpage->button_left->lower();
    this->Widget_visitorpage->button_right->lower();

    this->timeoutlocation_direction=location_direction(guidemap[start]);
    this->timeoutlocation_directionend=location_direction(guidemap[end]);

    qDebug()<<lo_to_num[timeoutlocation_direction]<<" "<<lo_to_num[timeoutlocation_directionend];

    dijkstra(lo_to_num[timeoutlocation_directionend],lo_to_num[timeoutlocation_direction]);

    printpath(lo_to_num[timeoutlocation_directionend], lo_to_num[timeoutlocation_direction]);
    //把这两个location_dirction输入后得到一个QVector，依次是经过的结点，并且保证两个相邻节点都是以直线连接的
    //这里以头尾在一条直线上为例子
    //实际上，应该用timeoutlocation_direction 与vector中的元素一一进行下述操作。
    //qDebug()<<"LLLLL"<<dest.size();
    for(int i=dest.size()-1;i>0;i--)
    {
        qDebug()<<dest[i].x<<" "<<dest[i].y;
    }
    for(int i=dest.size()-1;i>=0;i--)
    {
        time->start(guide_speed);
        this->timeoutlocation_directionmid=dest[i];
        int lx=timeoutlocation_directionmid.x-timeoutlocation_direction.x;
        if(lx==0)timeoutdx=0;
        else if(lx>0)timeoutdx=1;
        else timeoutdx=-1;
        int ly=timeoutlocation_directionmid.y-timeoutlocation_direction.y;
        if(ly==0)timeoutdy=0;
        else if(ly>0)timeoutdy=1;
        else timeoutdy=-1;
        time->start();
        while(!timestop)
        {
            QCoreApplication::processEvents();
        }
        //qDebug()<<"HHHHH";
        timestop=false;
    }

    this->button_backguide->raise();
    this->button_backmenu->raise();
}

void MyMainWindow::guideline()
{
    QString start=this->box_start->currentText();
    QString end=this->box_end->currentText();

    if(start=="westgate")
    {
        firstpoint=0;
        if(end=="dezhai")lastpoint=3;
        else if(end=="yiti")lastpoint=7;
        else if(end=="boyatower")lastpoint=8;
        else if(end=="huashenmiao"){firstpoint=10;lastpoint=16;}
    }
    else if(start=="dezhai")
    {
        if(end=="westgate"){firstpoint=0;lastpoint=3;}
        else if(end=="yiti"){firstpoint=3;lastpoint=7;}
        else if(end=="boyatower"){firstpoint=3;lastpoint=8;}
        else if(end=="huashenmiao"){firstpoint=10;lastpoint=13;}
    }
    else if(start=="yiti")
    {
        if(end=="westgate"){firstpoint=0;lastpoint=7;}
        else if(end=="dezhai"){firstpoint=3;lastpoint=7;}
        else if(end=="boyatower"){firstpoint=7;lastpoint=8;}
        else if(end=="huashenmiao"){firstpoint=7;lastpoint=10;}
    }
    else if(start=="boyatower")
    {
        if(end=="westgate"){firstpoint=0;lastpoint=8;}
        else if(end=="yiti"){firstpoint=7;lastpoint=8;}
        else if(end=="dezhai"){firstpoint=3;lastpoint=8;}
        else if(end=="huashenmiao"){firstpoint=8;lastpoint=10;}
    }
    else if(start=="huashenmiao")
    {
        if(end=="westgate"){firstpoint=10;lastpoint=16;}
        else if(end=="yiti"){firstpoint=7;lastpoint=10;}
        else if(end=="boyatower"){firstpoint=8;lastpoint=10;}
        else if(end=="dezhai"){firstpoint=10;lastpoint=13;}
    }

    label->update();
}

void MyMainWindow::endvisit()
{
    StackedWidget_mainfunctionpage->setCurrentIndex(0);
    qDebug()<<"&&&&&&";
    Widget_visitorpage->button_endvisit->lower();
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
    Widget_startpage->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(700);
    a->setStartValue(0.1);
    a->setEndValue(1);
    //a->setEasingCurve(QEasingCurve::InBack);
    a->setEasingCurve(QEasingCurve::Linear);
    QEventLoop loop;
    connect(a, SIGNAL(finished()), &loop, SLOT(quit()));
    a->start(QPropertyAnimation::DeleteWhenStopped);
    loop.exec();
    StackedWidget_mainfunctionpage->setCurrentIndex(0);
}
