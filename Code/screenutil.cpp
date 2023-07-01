
#include"screenutil.h"

QSize ScreenUtil::getScreenSize()
{
    QScreen* screen=QGuiApplication::primaryScreen();
    return screen->size();
}
//在对应的源文件内在具体定义函数
