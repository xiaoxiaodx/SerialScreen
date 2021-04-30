#include "mydrawwidget.h"
#include <QDebug>
#include <QPushButton>
MyDrawWidget::MyDrawWidget(QWidget *parent) : QWidget(parent)
{


}

void MyDrawWidget::paintEvent(QPaintEvent *event){


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    for(int i=0;i<listShape.length();i++){

        Shape *shape = listShape.at(i);
        shape->draw(&painter);

    }

}






void MyDrawWidget::addShape(Shape *shape){

    listShape.append(shape);

}


void MyDrawWidget::mousePressEvent(QMouseEvent *event)        //按下
{

      qDebug()<<"mousePressEvent";
}
void MyDrawWidget::mouseReleaseEvent(QMouseEvent *event)      //抬起
{
qDebug()<<"mouseReleaseEvent";
}
void MyDrawWidget::mouseDoubleClickEvent(QMouseEvent *event)  //双击
{
    qDebug()<<"mouseDoubleClickEvent";
}
void MyDrawWidget::mouseMoveEvent(QMouseEvent *event)        //移动
{
    qDebug()<<"mouseMoveEvent";
}
void MyDrawWidget::wheelEvent(QWheelEvent *event)             //滑轮
{
    qDebug()<<"wheelEvent";
}
