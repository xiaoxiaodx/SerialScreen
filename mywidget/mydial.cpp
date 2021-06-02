#include "mydial.h"
#include <QPainter>

MyDial::MyDial(int id,QString name):mid(id),mname(name)
{
    setObjectName(name);
}



void MyDial::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    drawBg(&painter);
    drawIndicator(&painter);
}

void MyDial::drawBg(QPainter *painter)
{

    if(isuseimg){


        painter->drawImage(QRect(0,0,this->width(),this->height()),bgimg);
    }else{

        painter->setPen(Qt::NoPen);

        painter->fillRect(QRect(0,0,this->width(),this->height()),QBrush(bgcolor));
    }


}

#include <QDebug>
void MyDial::drawIndicator(QPainter *painter)
{

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(indicatorcolo));

    float radius = (this->width() < this->height()?this->width():this->height())/2;

    painter->translate(this->width()/2,this->height()/2);
    painter->rotate(indicatorAngle);
    painter->fillRect(QRect(-indicatorW/2,-radius,indicatorW,radius),QBrush(indicatorcolo));

    painter->restore();
}
