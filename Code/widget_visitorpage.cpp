#include "widget_visitorpage.h"
#include"location_direction.h"
#include<QMap>
#include<QMovie>
#include<QDebug>
#include<QStringList>
#include<screenutil.h>

extern QString path;
extern QMap<location_direction,int> map;
extern location_direction nowlocation_direction;
widget_visitorpage::widget_visitorpage(QWidget *parent) : QWidget(parent)
{
    //获取显示屏尺寸
    QSize screenSize=ScreenUtil::getScreenSize();
    int screenWidth,screenHeight;
    screenWidth = screenSize.width();
    screenHeight = screenSize.height();
    this->setMaximumSize(QSize(screenWidth, screenHeight));
    this->setMinimumSize(QSize(screenWidth, screenHeight));

     StackedWidget_visitorview=new QStackedWidget(this);
     StackedWidget_visitorview->setGeometry(0,0,screenWidth,screenHeight);
     StackedWidget_visitorview->setObjectName(QStringLiteral("StackedWidget_visitor"));
     Widget_movie = new QWidget(StackedWidget_visitorview);
     StackedWidget_visitorview->addWidget(Widget_movie);//编号为0的一页专门播放动画
     Widget_img = new QWidget(StackedWidget_visitorview);
     StackedWidget_visitorview->addWidget(Widget_img);
     label_movie= new QLabel(Widget_movie);
     label_movie->setGeometry(0,0,screenWidth,screenHeight);
     label_img=new QLabel(Widget_img);
     label_img->setGeometry(0,0,screenWidth,screenHeight);

     QString stylesheet_button_rightleft="QPushButton{"
                                              "border-radius: 50px;"
                                              "background-color: rgba(0, 0, 0, 0);"
                                              "color: white;"
                                              "border: 5px solid white;"
                                              "font-size:125px;"
                                              "}"
                                              "QPushButton:hover{"
                                              "border-radius: 50px;"
                                              "background-color: rgba(0, 0, 0, 0);"
                                              "color: grey;"
                                              "border: 8px solid grey;"
                                              "font-size:125px;"
                                              "}";

         QString stylesheet_button_ahead="QPushButton{"
                                          "border-radius: 50px;"
                                          "background-color: rgba(0, 0, 0, 0);"
                                          "color:white;"
                                          "border: 5px solid white;"
                                          "font-size:125px;"
                                          "}"
                                          "QPushButton:hover{"
                                          "border-radius: 50px;"
                                          "background-color: rgba(0, 0, 0, 0);"
                                          "color: blue;"
                                          "border: 8px solid blue;"
                                          "font-size:125px;"
                                          "}";

          button_left = new QPushButton(this);
          button_left->setObjectName(QStringLiteral("button_left"));
          button_left->setText("⭅");
          //button_left->setGeometry(600, 750, 100, 100);
          button_left->setStyleSheet(stylesheet_button_rightleft);
          button_left->setGeometry(screenWidth/2-150,screenHeight*3/5+100,100,100);


          button_ahead = new QPushButton(this);
          button_ahead->setObjectName(QStringLiteral("button_ahead"));
          button_ahead->setText("⟰");
          button_ahead->setStyleSheet(stylesheet_button_ahead);
          //button_ahead->setGeometry(700, 650, 100, 100);
          button_ahead->setGeometry(screenWidth/2-50,screenHeight*3/5-100+100,100,100);

          button_right = new QPushButton(this);
          button_right->setObjectName(QStringLiteral("button_right"));
          button_right->setText("⭆");
          //button_right->setGeometry(800, 750, 100, 100);
          button_right->setGeometry(screenWidth/2+50,screenHeight*3/5+100,100,100);
          button_right->setStyleSheet(stylesheet_button_rightleft);

     QFont font;//设置字体
     QFont Fonth("SimHei",30);

     font.setFamily(QStringLiteral("Kristen ITC"));
     font.setPointSize(28);
     font.setBold(true);
     font.setWeight(static_cast<QFont::Weight>(75));
     button_ahead->setFont(font);
     button_left->setFont(font);
     button_right->setFont(font);
     connect(button_left,SIGNAL(clicked(bool)),this,SLOT(Left()));
     connect(button_ahead,SIGNAL(clicked(bool)),this,SLOT(Ahead()));
     connect(button_right,SIGNAL(clicked(bool)),this,SLOT(Right()));
     movie = new QMovie();
     label_movie->setMovie(movie);
     StackedWidget_visitorview->setCurrentIndex(1);
     label_img->setPixmap(QPixmap(path+"img0_0_0_1.jpg"));
     label_img->setScaledContents(true);
     int k=1;
     for(int i=0;i<=60;i++)
         map.insert(location_direction(0,i*10,0,1),k++);

     for(int i=0;i<=23;i++)
         map.insert(location_direction(i*10,600,1,0),k++);

     for(int i=60;i>=27;i--)
         map.insert(location_direction(230,i*10,0,-1),k++);

     for(int i=23;i>=0;i--)
         map.insert(location_direction(i*10,270,-1,0),k++);

     for(int i=27;i>=0;i--)
         map.insert(location_direction(0,i*10,0,-1),k++);
     for(int i=0;i<=23;i++)
         map.insert(location_direction(i*10,270,1,0),k++);
     for(int i=27;i<=60;i++)
         map.insert(location_direction(230,i*10,0,1),k++);
     for(int i=23;i>=0;i--)
         map.insert(location_direction(i*10,600,-1,0),k++);
     for(int i=60;i>=28;i--)
         map.insert(location_direction(0,10*i,0,-1),k++);

     label_dezhai_h=new QLabel(StackedWidget_visitorview);
     label_dezhai=new QLabel(StackedWidget_visitorview);
     label_boya=new QLabel(StackedWidget_visitorview);
     label_boya_h=new QLabel(StackedWidget_visitorview);
     label_boya_p=new QLabel(StackedWidget_visitorview);
     label_yiti=new QLabel(StackedWidget_visitorview);
     label_yiti_h=new QLabel(StackedWidget_visitorview);
     label_huashen=new QLabel(StackedWidget_visitorview);
     label_huashen_h=new QLabel(StackedWidget_visitorview);

     label_dezhai_h->setAlignment(Qt::AlignCenter);
     label_dezhai_h->setText("德斋");
     label_dezhai_h->setGeometry(2*screenWidth/3,0,screenWidth/3,screenHeight/12);
     label_dezhai_h->setFont(Fonth);
     label_dezhai_h->setStyleSheet("background-color:rgba(0,153,0,30);color:rgb(255,255,128)");
     label_dezhai_h->setWordWrap(true);
     label_dezhai->setAlignment(Qt::AlignTop);
     label_dezhai->setIndent(1);
     label_dezhai->setText("德才均备体健全斋在未名湖北岸，是一个由七个宅院组成的仿明清式古典建筑群，"
                           "由西向东依次为德斋、才斋、均斋、备斋、体斋、健斋、全斋。"
                           "德斋、才斋、均斋、备斋与西面的民主楼平行，在未名湖北岸呈直线排列。"
                           "德才均备体健斋建于1929年，其中德才均备四斋（人称“红四楼”）原来都是燕京大学的男生宿舍。");
     label_dezhai->setGeometry(2*screenWidth/3,screenHeight/12,screenWidth/3,(screenHeight*2)/3);
     label_dezhai->setFont(Fonth);
     label_dezhai->setStyleSheet("background-color:rgba(0,153,0,30);color:rgb(255,255,128)");
     label_dezhai->setWordWrap(true);
     label_dezhai->setFrameStyle(QFrame::Panel | QFrame::Sunken);
     label_yiti_h->setAlignment(Qt::AlignCenter);
     label_yiti_h->setText("第一体育馆");
     label_yiti_h->setGeometry(2*screenWidth/3,0,screenWidth/3,screenHeight/12);
     label_yiti_h->setFont(Fonth);
     label_yiti_h->setStyleSheet("background-color:rgba(128,111,77,60);color:rgb(255,221,153);");
     label_yiti_h->setWordWrap(true);
     label_yiti->setAlignment(Qt::AlignTop);
     label_yiti->setText("第一体育馆位于风景秀丽的未名湖畔，处于古文物保护区内。"
                         "一种说法里，第一体育馆是“一塔湖图”中的一字。"
                         "室内场馆有方正乒乓球俱乐部、力量训练房及理论课教室。"
                         "有2个足球场兼做棒垒球、橄榄球场，1个高尔夫打习场兼做田径投掷场。"
                         "体育馆北侧是一个攀岩和拓展训练场地。");

     label_yiti->setGeometry(2*screenWidth/3,screenHeight/12,screenWidth/3,(screenHeight*1)/2);
     label_yiti->setFont(Fonth);
     label_yiti->setStyleSheet("background-color:rgba(128,111,77,60);color:rgb(255,221,153);");
     label_yiti->setWordWrap(true);
     label_boya_h->setAlignment(Qt::AlignCenter);
     label_boya_h->setText("博雅塔");
     label_boya_h->setGeometry(0,0,screenWidth/3,screenHeight/12);
     label_boya_h->setFont(Fonth);
     label_boya_h->setStyleSheet("background-color:rgba(0,128,43,0);color:rgb(255,242,179);");
     label_boya_h->setWordWrap(true);
     label_boya->setAlignment(Qt::AlignTop);
     label_boya->setText("1924年，燕京大学为解决全校师生用水问题，在未名湖东南的小土丘处掘水井一口。"
                         "水塔是当时为深水井专造的塔式水楼建筑，仿通州燃灯塔。"
                         "因系燕大哲学系教授博晨光的叔父（James W. Porter）捐资兴建，故又称“博雅塔”。"
                         "1952年院系调整中，燕京大学被撤销，北京大学迁入燕京大学校园。"
                         "博雅塔逐渐成为了北大的精神象征。");

     label_boya->setGeometry(0,screenHeight/10,screenWidth/3,(screenHeight*1)/1);
     label_boya->setFont(Fonth);
     label_boya->setStyleSheet("background-color:rgba(0,128,43,0);color:rgb(255,242,179);");
     label_boya->setWordWrap(true);
     QPixmap picture;

     picture.load("F:/Qt/weimin/weimin/img/boyatower.jpg");
     label_boya_p->setPixmap(picture);
     label_boya_p->setScaledContents(true);
     label_boya_p->move(2*screenWidth/3,0);
     label_boya_p->resize(screenWidth/3,5*screenHeight/12);
     label_huashen_h->setAlignment(Qt::AlignCenter);
     label_huashen_h->setText("花神庙");
     label_huashen_h->setGeometry(0,0,screenWidth/3,screenHeight/12);
     label_huashen_h->setFont(Fonth);
     label_huashen_h->setStyleSheet("background-color:rgb(0,128,43,0);color:rgb(255,242,179);");
     label_huashen_h->setWordWrap(true);
     label_huashen->setAlignment(Qt::AlignTop);
     label_huashen->setText("慈济寺建于清代，在古时候曾用来祭祀花神，所以被大家称为“花神庙”。"
                            "现在仅存山门门洞，是未名湖畔的一处重要景观。"
                            "之前，花神庙曾惨遭各种涂鸦，成了高考生的“许愿墙”。"
                            "后来，北大将花神庙重新修缮了一番，并在周围围起了栏杆。");
     label_huashen->setGeometry(0,screenHeight/12,screenWidth/3,(screenHeight*1)/1);
     label_huashen->setFont(Fonth);
     label_huashen->setStyleSheet("background-color:rgba(0,128,43,0);color:rgb(255,242,179);");
     label_huashen->setWordWrap(true);

     button_endvisit=new QToolButton(this);
     button_endvisit->setText("Back to menu");
     button_endvisit->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0, 0)"));//透明背景
     button_endvisit->setGeometry(QRect(screenWidth/2-150,2*screenHeight/4 , 300, 150));
     button_endvisit->setFont(font);
     button_endvisit->lower();

}
void widget_visitorpage::location_directionToimg(const location_direction &a)
{
    QString imgpath=path+"img";
    imgpath+=QString::number(a.x)+"_"+QString::number(a.y)+"_";
    imgpath=imgpath+QString::number(a.dx).replace("-","i")+"_"+QString::number(a.dy).replace("-","i");
    this->StackedWidget_visitorview->setCurrentIndex(1);
    label_img->setPixmap(QPixmap(imgpath));
    label_img->setScaledContents(true);
}

void widget_visitorpage::Left()
{
    this->StackedWidget_visitorview->setCurrentIndex(0);
    int xx,yy;
    xx=-nowlocation_direction.dy;
    yy=nowlocation_direction.dx;
    //qDebug()<<yy<<-xx<<"  "<<xx<<yy;
    QString moviepath=path+"left"+QString::number(nowlocation_direction.x)+"_"+QString::number(nowlocation_direction.y)+"_";
    moviepath=moviepath+QString::number(nowlocation_direction.dx).replace("-","i")+"_"+QString::number(nowlocation_direction.dy).replace("-","i");
    moviepath=moviepath+"to"+QString::number(xx).replace("-","i")+"_"+QString::number(yy).replace("-","i")+".gif";
    nowlocation_direction.dx=xx;
    nowlocation_direction.dy=yy;

    this->movie->setFileName(moviepath);
    this->label_movie->setScaledContents(true);
    this->movie->start();

    this->button_ahead->lower();
    this->button_left->lower();
    this->button_right->lower();
    connect(this->movie, &QMovie::frameChanged, [=](int frameNumber) {
        if (frameNumber == movie->frameCount() - 1) {
            movie->stop();
            if(map.contains(location_direction(nowlocation_direction.x+10*nowlocation_direction.dx,nowlocation_direction.y+10*nowlocation_direction.dy,nowlocation_direction.dx,nowlocation_direction.dy)))
                this->button_ahead->raise(); //setEnabled(true);
            else this->button_ahead->lower();//setEnabled(false);
            if(map.contains(location_direction(nowlocation_direction.x,nowlocation_direction.y,nowlocation_direction.dy,-nowlocation_direction.dx)))
                this->button_right->raise();  //setEnabled(true);
            else this->button_right->lower();    //setEnabled(false);
            if(map.contains(location_direction(nowlocation_direction.x,nowlocation_direction.y,-nowlocation_direction.dy,nowlocation_direction.dx)))
                this->button_left->raise(); //setEnabled(true);
            else this->button_left->lower();//setEnabled(false);

        }
    });

}
void widget_visitorpage::shiftaftermove(const location_direction &b)
{
    this->location_directionToimg(b);
}

void widget_visitorpage::Right()
{
    this->StackedWidget_visitorview->setCurrentIndex(0);
    int xx,yy;
    xx=nowlocation_direction.dy;
    yy=-nowlocation_direction.dx;
    //qDebug()<<-yy<<xx<<"  "<<xx<<yy;
    QString moviepath=path+"right"+QString::number(nowlocation_direction.x)+"_"+QString::number(nowlocation_direction.y)+"_";
    moviepath=moviepath+QString::number(nowlocation_direction.dx).replace("-","i")+"_"+QString::number(nowlocation_direction.dy).replace("-","i");
    moviepath=moviepath+"to"+QString::number(xx).replace("-","i")+"_"+QString::number(yy).replace("-","i")+".gif";
    nowlocation_direction.dx=xx;
    nowlocation_direction.dy=yy;
    button_ahead->lower();
    button_left->lower();
    button_right->lower();
    this->movie->setFileName(moviepath);
    this->label_movie->setScaledContents(true);
    this->movie->start();
    connect(this->movie, &QMovie::frameChanged, [=](int frameNumber) {
        if (frameNumber == movie->frameCount() - 1) {
            movie->stop();
            this->location_directionToimg(nowlocation_direction);
            if(map.contains(location_direction(nowlocation_direction.x+10*nowlocation_direction.dx,nowlocation_direction.y+10*nowlocation_direction.dy,nowlocation_direction.dx,nowlocation_direction.dy)))
                this->button_ahead->raise(); //setEnabled(true);
            else this->button_ahead->lower();//setEnabled(false);
            if(map.contains(location_direction(nowlocation_direction.x,nowlocation_direction.y,nowlocation_direction.dy,-nowlocation_direction.dx)))
                this->button_right->raise();  //setEnabled(true);
            else this->button_right->lower();    //setEnabled(false);
            if(map.contains(location_direction(nowlocation_direction.x,nowlocation_direction.y,-nowlocation_direction.dy,nowlocation_direction.dx)))
                this->button_left->raise(); //setEnabled(true);
            else this->button_left->lower();//setEnabled(false);
        }
    });

}
void widget_visitorpage::Ahead()
{


    nowlocation_direction.x+=nowlocation_direction.dx*10;
    nowlocation_direction.y+=nowlocation_direction.dy*10;

    if(nowlocation_direction.x==0&&nowlocation_direction.y==240)
    {
         this->label_dezhai->raise();
         this->label_dezhai_h->raise();
    }
    else
    {
         this->label_dezhai->lower();
         this->label_dezhai_h->lower();
    }
    if(nowlocation_direction.x==70&&nowlocation_direction.y==600)
    {
         this->label_yiti->raise();
         this->label_yiti_h->raise();
    }
    else
    {
         this->label_yiti->lower();
         this->label_yiti_h->lower();
    }
    if(nowlocation_direction.x==230&&nowlocation_direction.y==600)
    {
         this->label_boya->raise();
         this->label_boya_h->raise();
         this->label_boya_p->raise();
    }
    else
    {
         this->label_boya->lower();
         this->label_boya_h->lower();
         this->label_boya_p->lower();
    }
    if(nowlocation_direction.x==230&&nowlocation_direction.y==510)
    {
         this->label_huashen->raise();
         this->label_huashen_h->raise();
    }
    else
    {
         this->label_huashen->lower();
         this->label_huashen_h->lower();
    }

    this->location_directionToimg(nowlocation_direction);
    if(map.contains(location_direction(nowlocation_direction.x+10*nowlocation_direction.dx,nowlocation_direction.y+10*nowlocation_direction.dy,nowlocation_direction.dx,nowlocation_direction.dy)))
       {

        this->button_ahead->raise();// setEnabled(true);

    }
    else this->button_ahead->lower();// setEnabled(false);
    if(map.contains(location_direction(nowlocation_direction.x,nowlocation_direction.y,nowlocation_direction.dy,-nowlocation_direction.dx)))
        this->button_right->raise();// setEnabled(true);
    else this->button_right->lower();// setEnabled(false);
    if(map.contains(location_direction(nowlocation_direction.x,nowlocation_direction.y,-nowlocation_direction.dy,nowlocation_direction.dx)))
        this->button_left->raise(); //setEnabled(true);
    else this->button_left->lower();//setEnabled(false);
     //qDebug()<<nowlocation_direction.x<<nowlocation_direction.y<<nowlocation_direction.dx<<nowlocation_direction.dy;

    if(nowlocation_direction.x==0&&nowlocation_direction.y==0&&nowlocation_direction.dy==-1)
    {
        button_endvisit->raise();
    }
    else button_endvisit->lower();
}
