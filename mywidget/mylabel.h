#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT

    Q_PROPERTY(QString txt READ txt WRITE setTxt)


public:
    MyLabel(int id,QString name);

    void setTxt(QString);
    QString txt();


    void setBackgroudImg(QString imgpath);
    void setBackgroudColor(QColor color);
    void setTextInfo(QColor fontcolor,char* txt,QString family,int Strdistance);
    int mid;
    QString mname;
    QString mtxt;
};

#endif // MYLABEL_H
