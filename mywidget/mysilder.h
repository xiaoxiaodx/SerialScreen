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

    QColor backgroud_color;
    QColor hander_color;

    QString hander_img;
    QString backgroud_img;


    int silderw;
    int silderh;
    bool isuseimg = false;
    int hov;
    int radius;

};

#endif // MYSILDER_H
