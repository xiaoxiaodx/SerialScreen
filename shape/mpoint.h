#ifndef MPOINT_H
#define MPOINT_H

#include "Shape.h"

class MPoint : public Shape
{
public:
    MPoint(float,float,QColor color,int size = 2);
    void draw(QPainter *pt) override;
private:

    QColor mcolor;
    float mx;
    float my;
    int msize;
};

#endif // MPOINT_H
