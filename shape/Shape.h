#ifndef SHAP_H
#define SHAP_H

#include <QPainter>

class Shape{

public:
    //Shape();
    virtual void draw(QPainter *pt) = 0;

};

#endif
