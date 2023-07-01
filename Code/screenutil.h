
#ifndef SCREENUTIL_H
#define SCREENUTIL_H

#include<QScreen>
#include<QGuiApplication>
class ScreenUtil
{
public:
    static QSize getScreenSize();
};
//头文件内只声明函数，不进行定义，避免函数在多次引入头文件时发生重复定义的问题

#endif // SCREENUTIL_H

