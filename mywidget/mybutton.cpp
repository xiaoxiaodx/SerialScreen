#include "mybutton.h"

#include <QPalette>
#include <QDebug>
MyButton::MyButton(int id,QString name):mid(id),mname(name)
{

    setObjectName(name);
}


void MyButton::updateStyle(){


    if(btnType == 0){

        setChecked(false);

        if(isuseimgbg){
            qss_bg_press = "QPushButton:pressed{border-image: url("+default_bgimg_press+");}";
            qss_bg = "QPushButton{border-image: url("+default_bgimg+");}";
        }else{

            QColor press_color = default_bgcolor_press;
            QColor color = default_bgcolor;
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


