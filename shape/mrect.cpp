#include "mrect.h"

MRect:: MRect(float startx,float starty,float endx,float endy,bool isfill,QColor color,int radius,int size)
    :mstartx(startx),mstarty(starty),mendx(endx),mendy(endy),mcolor(color),isFill(isfill),msize(size),mradius(radius)
{



}

void MRect::draw(QPainter *pt){

    pt->save();

    if(!isFill){
        pt->setPen(QPen(mcolor,msize,Qt::SolidLine,Qt::RoundCap));
        pt->setBrush(QBrush(QColor(0,0,0,0),Qt::SolidPattern));

    }else{
        pt->setPen(QPen(QColor(0,0,0,0),msize,Qt::SolidLine,Qt::RoundCap));
        pt->setBrush(QBrush(mcolor,Qt::SolidPattern));
    }

    pt->drawRoundedRect(mstartx,mstarty,mendx-mstartx,mendy-mstarty,mradius,mradius);
    pt->restore();

}

QColor MRect::getMcolor() const
{
    return mcolor;
}

void MRect::setMcolor(const QColor &value)
{
    mcolor = value;
}

int MRect::getMsize() const
{
    return msize;
}

void MRect::setMsize(int value)
{
    msize = value;
}
