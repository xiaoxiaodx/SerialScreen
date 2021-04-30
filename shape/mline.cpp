#include "mline.h"

MLine::MLine(float startx,float starty,float endx,float endy,QColor color,int size)
    :mstartx(startx),mstarty(starty),mendx(endx),mendy(endy),mcolor(color),msize(size)
{

}

void MLine::draw(QPainter *pt){

    pt->save();

    pt->setPen(QPen(mcolor,msize,Qt::SolidLine,Qt::RoundCap));

    pt->drawLine(mstartx,mstarty,mendx,mendy);

    pt->restore();

}
