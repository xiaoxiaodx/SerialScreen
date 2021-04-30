#ifndef MARC_H
#define MARC_H
#include "shape/Shape.h"


/*
 * 默认画圆弧
 * isfill 为true 就是饼图
 *
 * startangle = 0
 * endangle = 360 为圆
 *
*/
class MArc : public Shape
{
public:
    MArc(float centerx,float centery,float radius,float startangle,float endangle,QColor color,bool isfill=false,float size=2);
    void draw(QPainter *pt) override;



private:
    float mcenterx;
    float mcentery;
    float mradius;
    float mstartangle;
    float mendangle;
    QColor mcolor;
    bool misfill;
    float msize;
};

#endif // MARC_H
