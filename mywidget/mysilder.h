#ifndef MYSILDER_H
#define MYSILDER_H

#include <QSlider>

class MySilder : public QSlider
{
public:
    MySilder(int id,QString name);


    void updateStyle();
    int mid;
    QString mname;

    QColor foregroud_color;
    QColor backgroud_color;
    QColor hander_color;

    QString foregroud_img;//文件所在绝对路径
    QString backgroud_img;


    int silderw;
    int silderh;
    bool isuseimg = false;
    int hov;
    int radius;

};

#endif // MYSILDER_H
