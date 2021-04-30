#include "mpoint.h"

#include <QDebug>

MPoint::MPoint(float x,float y,QColor color,int size):mx(x),my(y),mcolor(color),msize(size)
{
}

void MPoint::draw(QPainter *painter){

    painter->save();
    painter->setPen(QPen(mcolor,msize,Qt::SolidLine,Qt::RoundCap));
    painter->drawPoint(QPointF(mx,my));
    painter->restore();

}
