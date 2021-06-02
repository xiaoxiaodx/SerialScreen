#ifndef MYCHECK_H
#define MYCHECK_H

#include <QCheckBox>
class MyCheck:public QCheckBox
{
public:
    MyCheck(int id,QString name);

    void layout();

    int mid;
    QString mname;
    bool misuseimg = false;
    QString foregroudImgPath;
    QString backgroudImgPath;

    QColor foregroudColor,backgroudColor;
};

#endif // MYCHECK_H
