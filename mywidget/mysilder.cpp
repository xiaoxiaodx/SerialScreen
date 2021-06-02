#include "mysilder.h"
#include <QDebug>

MySilder::MySilder(int id,QString name)
    :mid(id),mname(name)
{



    setObjectName(name);


}


void MySilder::updateStyle()
{
    QString qss,horstr,qssgroove,qsshandle,qsssubpage;

    if(hov>0){
        horstr ="horizontal";
        setOrientation(Qt::Horizontal);
    }else{
        horstr = "vertical";
        setOrientation(Qt::Vertical);
    }


    if(!isuseimg){

        qssgroove = "QSlider::groove:"+horstr+"{"+
                "background:rgb("+QString::number(backgroud_color.red())+","+QString::number(backgroud_color.green())+","+QString::number(backgroud_color.blue())+");"+
                "height:"+QString::number(this->height())+";"+
                "border-radius: 1px;"+
                "padding-left:-1px;"+
                "padding-right:-1px;"+
                "}";

        qsshandle = "QSlider::handle:"+horstr+"{"+
                "background:rgb("+QString::number(hander_color.red())+","+QString::number(hander_color.green())+","+QString::number(hander_color.blue())+");"+
                "width:"+QString::number(silderw)+";"+
                "height:"+QString::number(silderh)+";"+
                "margin-top: -3px;"+
                "margin-bottom: -3px;"+
                "border-radius: 5px;}";
        qsssubpage = "QSlider::sub-page:"+horstr+"{"+
                "background:rgb("+QString::number(backgroud_color.red())+","+QString::number(backgroud_color.green())+","+QString::number(backgroud_color.blue())+");"+
                "height: "+QString::number(this->height())+";"+
                "border-radius: 2px;}";


    }else{

        qssgroove = "QSlider::groove:"+horstr+"{"+
                "border-image: url("+backgroud_img+");"+
                "height:"+QString::number(this->height())+";"+
                "border-radius: 1px;"+
                "padding-left:-1px;"+
                "padding-right:-1px;"+
                "}";

        qsshandle = "QSlider::handle:"+horstr+"{"+
                "border-image: url("+hander_img+");"+
                "width:"+QString::number(silderw)+";"+
                "height:"+QString::number(silderh)+";"+
                "margin-top: -3px;"+
                "margin-bottom: -3px;"+
                "border-radius: 5px;}";
        qsssubpage = "QSlider::sub-page:"+horstr+"{"+
                "border-image: url("+backgroud_img+");"+
                "height: "+QString::number(this->height())+";"+
                "border-radius: 2px;}";
    }

    qDebug()<<"qss:"<<qssgroove+qsshandle+qsssubpage;
    setStyleSheet(qssgroove+qsshandle+qsssubpage);

}
