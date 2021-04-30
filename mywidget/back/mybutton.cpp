#include "mybutton.h"
#include "util.h"
#include <QPalette>
MyButton::MyButton(int id,QString name,int x,int y,int w,int h,QWidget *parent):QPushButton(parent),
  id(id),name(name)
{

    connect(this,&QPushButton::click,this,&MyButton::slot_clicked);
    connect(this,&QPushButton::pressed,this,&MyButton::slot_pressed);
    connect(this,&QPushButton::released,this,&MyButton::slot_released);

    setGeometry(x,y,w,h);
    setbackgroud();
}


void MyButton::slot_clicked(){



    QWidget wh;

    if(btnType==1){


        if(isuseimgbg){
            QPalette palette = this->palette();
            palette.setColor(QPalette::Window,parse565(default_bgcolor));
            this->setPalette(palette);
        }else{


        }
    }

}


void MyButton::setbackgroud(){



    setStyleSheet("QPushButton{background-image: url(:/res/cloud_con.png);}"
    "QPushButton:hover{background-image: url(:/images/call_hov.bmp);}"
    "QPushButton:pressed{background-image: url(:/images/call_down.bmp);}");

}

void MyButton::slot_pressed(){

    if(btnType == 0){
        QPalette palette = this->palette();
        palette.setColor(QPalette::Window,parse565(default_bgcolor_press));
        this->setPalette(palette);
    }else{


    }

}

void MyButton::slot_released(){

    if(btnType == 0){
        QPalette palette = this->palette();
        palette.setColor(QPalette::Window,parse565(default_bgcolor));
        this->setPalette(palette);
    }
}

int MyButton::getBtnType() const
{
    return btnType;
}

void MyButton::setBtnType(int value)
{
    btnType = value;
}

