#include "mybutton.h"

#include <QPalette>
#include <QDebug>
MyButton::MyButton(int id,QString name):mid(id),mname(name)
{

    setObjectName(name);
}


void MyButton::updateStyle(){



    QString qssfontcolor = "color:rgb("+QString::number(mfontcolor.red())+","+QString::number(mfontcolor.green())+","+QString::number(mfontcolor.blue())+");";

    if(isuseimgbg){
        qss_bg_press = "border-image: url("+default_bgimg_press+");";
        qss_bg = "border-image: url("+default_bgimg+");";
    }else{

        QColor press_color = default_bgcolor_press;
        QColor color = default_bgcolor;
        qss_bg_press = "background-color:rgba("+QString::number(press_color.red())+","+QString::number(press_color.green())+","+QString::number(press_color.blue())+","+QString::number(press_color.alpha())+");";
        qss_bg= "background-color:rgba("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+","+QString::number(color.alpha())+");";

    }





    QString qss = "QPushButton{"+qssfontcolor+qss_bg+"}QPushButton:pressed{"+qssfontcolor+qss_bg_press+"}";




    setStyleSheet(qss);

   // qDebug()<<"qss:"<<qss;
}


void MyButton::slot_clicked(){

    qDebug()<<"slot_clicked";

}


void MyButton::slot_pressed(){


}

void MyButton::slot_released(){


}


