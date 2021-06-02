#ifndef MYDIAL_H
#define MYDIAL_H

#include <QWidget>

class MyDial: public QWidget
{
public:
    MyDial(int id,QString name);


    int mid;
    QString mname;
    bool isuseimg = false;
    QImage bgimg ;
    QColor bgcolor;
    QColor indicatorcolo;
    int indicatorW = 5;
    int indicatorAngle = 0;
protected:
    void paintEvent(QPaintEvent *event);

private:

    void drawBg(QPainter *painter);
    void drawIndicator(QPainter *painter);


};

#endif // MYDIAL_H
