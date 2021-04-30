#include "mimage.h"

MImage:: MImage(float startx,float starty,float endx,float endy,int radius,QImage img)
    :mstartx(startx),mstarty(starty),mendx(endx),mendy(endy),mradius(radius),mimg(img)
{



}


void MImage::draw(QPainter *pt)
{

    pt->save();


    QRectF rectf(mstartx,mstarty,mendx-mstartx,mendy-mstarty);

    QPainterPath path;
    path.addRoundedRect(rectf,mradius,mradius);
    pt->setClipPath(path);
    pt->drawImage(rectf,mimg);

    pt->restore();

}

QImage MImage::getMimg() const
{
    return mimg;
}

void MImage::setMimg(const QImage &value)
{
    mimg = value;
}
