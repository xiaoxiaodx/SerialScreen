#include "mybutton.h"
#include "util.h"
#include <QPalette>
#include <QDebug>
MyButton::MyButton(int id,QString name):mid(id),mname(name)
{

    connect(this,SIGNAL(clicked()),this,SLOT(slot_clicked()));
    connect(this,SIGNAL(pressed()),this,SLOT(slot_pressed()));
    connect(this,SIGNAL(released()),this,SLOT(slot_released()));


   /* setStyleSheet("QPushButton{border-image: url(H:/dmjProgram/qtPro/SerialScreen/res/1111111.png);}"
    "QPushButton:pressed{border-image: url(:/res/localnet.png);}");*/

    /*setStyleSheet("QPushButton{background-color: rgb(255, 0, 0);}"
    "QPushButton:pressed{background-color: rgb(0, 255, 0);}");*/
}


void MyButton::updateStyle(){


    if(btnType == 0){

        setChecked(false);

        if(isuseimgbg){
            qss_bg_press = "QPushButton:pressed{border-image: url("+default_bgimg_press+");}";
            qss_bg = "QPushButton{border-image: url("+default_bgimg+");}";
        }else{

            QColor press_color = parse565(default_bgcolor_press);
            QColor color = parse565(default_bgcolor);
            qss_bg_press = "QPushButton:pressed{background-color:rgb("+QString::number(press_color.red())+","+QString::number(press_color.green())+","+QString::number(press_color.blue())+");}";
            qss_bg= "QPushButton{background-color:rgb("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+");}";

        }

    }else{


        setCheckable(true);
        qss_bg_press = "QPushButton:checked{border-image: url("+default_bgimg_press+");}";
        qss_bg = "QPushButton{border-image: url("+default_bgimg+");}";


    }

    qDebug()<<"qss:"<<qss_bg+qss_bg_press;

    setStyleSheet(qss_bg+qss_bg_press);


}


void MyButton::slot_clicked(){

    qDebug()<<"slot_clicked";

}


void MyButton::slot_pressed(){


}

void MyButton::slot_released(){


}



void MyButton::setDefault_bgimg(QString imgfilepath)
{
    default_bgimg = imgfilepath;
}


void MyButton::setDefault_bgimg_press(QString imgfilepath)
{
    default_bgimg_press = imgfilepath;
}



void MyButton::setDefault_bgcolor(int value)
{
    default_bgcolor = value;
}


void MyButton::setDefault_bgcolor_press(int value)
{
    default_bgcolor_press = value;
}

void MyButton::setBtnType(int value)
{
    btnType = value;
}

