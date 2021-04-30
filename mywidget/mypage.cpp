#include "mypage.h"
#include <QDebug>
MyPage::MyPage(int id,QString name):id(id),name(name)
{

}


void MyPage::addShape(Shape *shape){

    if(shape != nullptr)
        listShape.append(shape);

}

void MyPage::addWidget(QWidget *wd){


    wd->setParent(this);


}

void MyPage::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    for(int i=0;i<listShape.length();i++){

        Shape *shape = listShape.at(i);
        shape->draw(&painter);

    }

}

void MyPage::mousePressEvent(QMouseEvent *event)        //按下
{

    qDebug()<<"mousePressEvent";
}
void MyPage::mouseReleaseEvent(QMouseEvent *event)      //抬起
{
    qDebug()<<"mouseReleaseEvent";
}
void MyPage::mouseDoubleClickEvent(QMouseEvent *event)  //双击
{
    qDebug()<<"mouseDoubleClickEvent";
}
void MyPage::mouseMoveEvent(QMouseEvent *event)        //移动
{
    qDebug()<<"mouseMoveEvent";
}
void MyPage::wheelEvent(QWheelEvent *event)             //滑轮
{
    qDebug()<<"wheelEvent";
}

int MyPage::getId() const
{
    return id;
}

void MyPage::setId(int value)
{
    id = value;
}


QString MyPage::getName() const
{
    return name;
}

void MyPage::setName(const QString &value)
{
    name = value;
}
