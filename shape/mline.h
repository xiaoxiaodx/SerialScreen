#ifndef MLINE_H
#define MLINE_H

#include "shape/Shape.h"

class MLine: public Shape
{

public:
    MLine(float startx,float starty,float endx,float endy,QColor color,int size = 2);
    void draw(QPainter *pt) override;

private:
    float mstartx;
    float mstarty;
    float mendx;
    float mendy;
    QColor mcolor;

    int msize;
};

#endif // MLINE_H
