#ifndef WIDGET_VISITORPAGE_H
#define WIDGET_VISITORPAGE_H
#include<QStackedWidget>
#include <QWidget>
#include<QPushButton>
#include<QToolButton>
#include<QVBoxLayout>
#include<QFont>
#include<QLabel>
#include<QMovie>
#include<QMap>
#include"location_direction.h"
class widget_visitorpage : public QWidget
{
    Q_OBJECT
public:
    explicit widget_visitorpage(QWidget *parent = 0);
    QStackedWidget *StackedWidget_visitorview;
    QPushButton *button_left;
    QPushButton *button_ahead;
    QPushButton *button_right;

    QToolButton *button_endvisit;

    QVBoxLayout *Layout;
    QWidget *Widget_movie;
    QLabel *label_movie;
    QMovie *movie;
    QWidget *Widget_img;
    QLabel *label_img;

    QLabel *label_dezhai_h;
    QLabel *label_dezhai;
    QLabel *label_boya;
    QLabel *label_boya_h;
    QLabel *label_yiti;
    QLabel *label_yiti_h;
    QLabel *label_huashen;
    QLabel *label_huashen_h;
    QLabel *label_boya_p;

signals:

public slots:
    void Left();
    void Right();
    void Ahead();
    void shiftaftermove(const location_direction &b);
    void location_directionToimg(const location_direction &a);
};

#endif // WIDGET_VISITORPAGE_H
