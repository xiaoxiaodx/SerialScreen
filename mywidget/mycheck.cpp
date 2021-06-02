#include "mycheck.h"
#include <QDebug>
MyCheck::MyCheck(int id,QString name):mid(id),mname(name)
{
    setObjectName(name);
}



void MyCheck::layout(){


    QString qssfg="",qssbg="";


    int width = this->width() < this->height() ? this->width():this->height();
    if(misuseimg){

        qssfg = "image:url("+foregroudImgPath+");";
        qssbg = "image:url("+backgroudImgPath+");";
    }else{
        qssbg =  "background-color:rgb("+QString::number(backgroudColor.red())+","+QString::number(backgroudColor.green())+","+QString::number(backgroudColor.blue())+");";
        qssfg =  "background-color:rgb("+QString::number(foregroudColor.red())+","+QString::number(foregroudColor.green())+","+QString::number(foregroudColor.blue())+");";

    }

    QString qss = "QCheckBox {"+qssbg+"}"
            "QCheckBox::indicator{width:"+QString::number(width/2)+"px;height:"+QString::number(width/2)+"px;"
             "margin-left:"+QString::number(width/4)+"px;}"
            "QCheckBox::indicator::checked {"+qssfg+"}"
            "QCheckBox::indicator::unchecked {background-color:rgba(0,0,0,0)}";

    setStyleSheet(qss);
}
