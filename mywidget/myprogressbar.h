#ifndef MYPROGRESSBAR_H
#define MYPROGRESSBAR_H


#include <QProgressBar>
#include <QDebug>
class MyProgressbar:public QProgressBar
{
public:
    MyProgressbar(int id,QString name);


    void setForegroundColor(QColor v);
    void setBackgroudColor(QColor v);

    void setForegroundImg(QString v);
    void setBackgroudImg(QString v);

    void updateStyle();

    //0 垂直 1 水平
    void setLayoutDirection(int hov);
    int mid;
    QString mname;




    QColor foregroud_color;
    QColor backgroud_color;

    QString foregroud_img;//文件所在绝对路径
    QString backgroud_img;


    bool isuseimg = false;
    int hov;
    int radius;
};

#endif // MYPROGRESSBAR_H
