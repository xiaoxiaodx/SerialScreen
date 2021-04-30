#ifndef MRECT_H
#define MRECT_H

#include "shape/Shape.h"

class MRect : public Shape
{
public:
    MRect(float startx,float starty,float endx,float endy,bool isfill,QColor color,int radius =0,int size = 2);
    void draw(QPainter *pt) override;
    QColor getMcolor() const;
    void setMcolor(const QColor &value);

    int getMsize() const;
    void setMsize(int value);

private:
    bool isFill;
    int msize;


    QColor mcolor;

    //左上
    float mstartx;
    float mstarty;
    //右下
    float mendx;
    float mendy;

    int mradius;
};

#endif // MRECT_H
