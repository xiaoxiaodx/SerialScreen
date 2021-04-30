#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <shape/Shape.h>
#include <QPaintEvent>

class MyDrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyDrawWidget(QWidget *parent = nullptr);
    void addShape(Shape *shape);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);        //按下
    void mouseReleaseEvent(QMouseEvent *event);      //抬起
    void mouseDoubleClickEvent(QMouseEvent *event);  //双击
    void mouseMoveEvent(QMouseEvent *event);         //移动
    void wheelEvent(QWheelEvent *event);             //滑轮
signals:


private:
    QList<Shape*> listShape;
};

#endif // MYWIDGET_H
