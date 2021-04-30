#ifndef MIMAGE_H
#define MIMAGE_H
#include "shape/Shape.h"

class MImage : public Shape
{
public:
    MImage(float startx,float starty,float endx,float endy,int radius,QImage img);

    void draw(QPainter *pt) override;
    QImage getMimg() const;
    void setMimg(const QImage &value);

private:


    QColor mcolor;
    //左上
    float mstartx;
    float mstarty;
    //右下
    float mendx;
    float mendy;

    int mradius;
    QImage mimg;
};

#endif // MIMAGE_H
