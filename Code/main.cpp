#include "mymainwindow.h"
#include <QApplication>
#include"location_direction.h"
//#include"navigation.h"
#include<QMap>
#include<QDebug>
#include<QVector>
#include<QPair>

QMap<location_direction,int> map;
location_direction nowlocation_direction(0,0,0,1);//定义一个现在位置方向状态的对象，不需要父对象

QVector<QPair<int,int>> location;

int firstpoint,lastpoint;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MyMainWindow w;

    w.show();

    return a.exec();
}
