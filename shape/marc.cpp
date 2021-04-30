#include "marc.h"

MArc::MArc(float centerx,float centery,float radius,float startangle,float endangle,QColor color,bool isfill,float size)
    :mcenterx(centerx),mcentery(centery),mradius(radius),mstartangle(startangle),mendangle(endangle),mcolor(color),
      misfill(isfill),msize(size)
{

}


void MArc::draw(QPainter *pt)
{
    pt->save();

    float leftx = mcenterx - mradius;
    float lefty = mcentery - mradius;
    float rightx = mcenterx + mradius;
    float righty = mcentery + mradius;

    if(misfill){

        pt->setPen(QPen(QColor(0,0,0,0),msize,Qt::SolidLine,Qt::RoundCap));
        pt->setBrush(QBrush(mcolor,Qt::SolidPattern));
        pt->drawPie(leftx,lefty,rightx,righty,mstartangle*16,mendangle*16);

    }else{

        pt->setPen(QPen(mcolor,msize,Qt::SolidLine,Qt::RoundCap));
        pt->setBrush(QBrush(QColor(0,0,0,0),Qt::SolidPattern));
        pt->drawArc(leftx,lefty,rightx,righty,mstartangle*16,mendangle*16);
    }





    pt->restore();

}
