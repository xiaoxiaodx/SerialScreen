#include "mypic.h"
#include <QPainter>
#include <QDebug>
MyPic::MyPic(int id,QString name):mid(id),mname(name)
{
setObjectName(name);
}


void MyPic::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawImage(QRect(0,0,width(),height()),img);
}
