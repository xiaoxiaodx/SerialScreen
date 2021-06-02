#ifndef MYRADIO_H
#define MYRADIO_H

#include <QRadioButton>
//多选一
class MyRadio : public QWidget
{
public:
    MyRadio(int id,QString name,int count,int selectindex,int hov=1,int distance=2,bool isuseimg=false);



    void updateStyle();
    void layout();
    int mid;
    QString mname;
    int mradioCount;
    int mselectIndex;

    int mdistance;//控件间隔



    QString backgroudImgPath;
    QString foregroudImgPath;
    QColor backgroudColor;
    QColor foregroudColor;
    bool misuseimg = false;
    int mhov;
};

#endif // MYRADIO_H
