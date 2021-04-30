#include "mysilder.h"
#include <QDebug>
/* 水平样式
QSlider::groove:horizontal {
border: 1px solid #4A708B;
background: #C0C0C0;
height: 5px;
border-radius: 1px;
padding-left:-1px;
padding-right:-1px;
}

QSlider::sub-page:horizontal {
background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
    stop:0 #B1B1B1, stop:1 #c4c4c4);
background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,
    stop: 0 #5DCCFF, stop: 1 #1874CD);
border: 1px solid #4A708B;
height: 10px;
border-radius: 2px;
}

QSlider::add-page:horizontal {
background: #575757;
border: 0px solid #777;
height: 10px;
border-radius: 2px;
}

QSlider::handle:horizontal
{
    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,
    stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));
    width: 11px;
    margin-top: -3px;
    margin-bottom: -3px;
    border-radius: 5px;
}

QSlider::handle:horizontal:hover {
    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA,
    stop:0.778409 rgba(255, 255, 255, 255));

    width: 11px;
    margin-top: -3px;
    margin-bottom: -3px;
    border-radius: 5px;
}

QSlider::sub-page:horizontal:disabled {
background: #00009C;
border-color: #999;
}

QSlider::add-page:horizontal:disabled {
background: #eee;
border-color: #999;
}

QSlider::handle:horizontal:disabled {
background: #eee;
border: 1px solid #aaa;
border-radius: 4px;
}
*/


/* 垂直样式
QSlider::groove:vertical {
border: 1px solid #4A708B;
background: #C0C0C0;
width: 5px;
border-radius: 1px;
padding-left:-1px;
padding-right:-1px;
padding-top:-1px;
padding-bottom:-1px;
}

QSlider::sub-page:vertical {
background: #575757;
border: 1px solid #4A708B;
border-radius: 2px;
}

QSlider::add-page:vertical {
background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
    stop:0 #c4c4c4, stop:1 #B1B1B1);
background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,
    stop: 0 #5DCCFF, stop: 1 #1874CD);
border: 0px solid #777;
width: 10px;
border-radius: 2px;
}

QSlider::handle:vertical
{
    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #45ADED,
<span style="white-space:pre">	</span>stop:0.778409 rgba(255, 255, 255, 255));

    height: 11px;
    margin-left: -3px;
    margin-right: -3px;
    border-radius: 5px;
}

QSlider::sub-page:vertical:disabled {
background: #00009C;
border-color: #999;
}

QSlider::add-page:vertical:disabled {
background: #eee;
border-color: #999;
}

QSlider::handle:vertical:disabled {
background: #eee;
border: 1px solid #aaa;
border-radius: 4px;
}
*/
MySilder::MySilder(int id,QString name)
    :mid(id),mname(name)
{




    //setStyleSheet("QSlider::groove:horizontal{border:1px solid #4A708B;background:#ff0000;height: 5px;border-radius: 1px;padding-left:-1px;padding-right:-1px;}");
    /* setStyleSheet("QSlider::groove:horizontal{"
                  "border:1px solid #4A708B;"
                  "background:#ff0000;"
                  "height: 5px;"
                  "border-radius: 1px;"
                  "padding-left:-1px;"
                  "padding-right:-1px;"
                  "}"

                 "QSlider::sub-page:horizontal {"
                  "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                  "    stop:0 #B1B1B1, stop:1 #c4c4c4);"
                  "background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,"
                      "stop: 0 #5DCCFF, stop: 1 #1874CD);"
                  "border: 1px solid #4A708B;"
                  "height: 10px;"
                  "border-radius: 2px;"
                  "}"

                  "QSlider::handle:horizontal"
                  "{"
                      "background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, "
                      "stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));"
                      "width: 11px;"
                      "margin-top: -3px;"
                      "margin-bottom: -3px;"
                      "border-radius: 5px;"
                  "}"

             );*/



}


void MySilder::updateStyle()
{
    QString qss,horstr,qssgroove,qsshandle,qsssubpage;

    if(hov>0){
        horstr ="vertical";
        setOrientation(Qt::Vertical);
    }else{
        horstr = "horizontal";
        setOrientation(Qt::Horizontal);
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
                "background:rgb("+QString::number(foregroud_color.red())+","+QString::number(foregroud_color.green())+","+QString::number(foregroud_color.blue())+");"+
                "height: "+QString::number(this->height())+";"+
                "border-radius: 2px;}";


    }else{


    }

    qDebug()<<"qss:"<<qssgroove+qsshandle+qsssubpage;
    setStyleSheet(qssgroove+qsshandle+qsssubpage);

}
