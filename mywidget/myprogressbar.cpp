#include "myprogressbar.h"
#include <QDebug>
MyProgressbar::MyProgressbar(int id,QString name):mid(id),mname(name)
{

setObjectName(name);

}

void MyProgressbar::updateStyle()
{
    //水平样式
    //    "QProgressBar{"
    //                                        "border-radius:5px;"
    //                                        "background-color:darkgray;"
    //                                        "text-align:center"
    //                                        "}"
    //                                        "QProgressBar::chunk{"
    //                                        "background-color:#FF0000;"
    //                                        "width:6px;"
    //                                        "margin:2px;"
    //                                        "}");
    //垂直样式
    /* "QProgressBar:vertical{"
                                        "border-radius:5px;"
                                        "background-color:darkgray;"
                                        "text-align:center"
                                        "}"
                                      "QProgressBar::chunk:vertical{"
                                        "background-color:#00FF00;"
                                        "margin:1px;"
                                        //"height:2px;"
                                        "}"*/


    QString qss,horstr;


    if(hov>0){
        horstr ="horizontal";
        setOrientation(Qt::Horizontal);
    }else{
        horstr = "vertical";
        setOrientation(Qt::Vertical);
    }
    if(!isuseimg){
        QString qssbackgroud = "QProgressBar:"+horstr+"{"+
                "border-radius:"+QString::number(radius)+"px;"+
                "background-color:rgb("+QString::number(backgroud_color.red())+","+QString::number(backgroud_color.green())+","+QString::number(backgroud_color.blue())+");"+
                "text-align:center;"
                "}";

        QString qssforegroud = "QProgressBar::chunk:"+horstr+"{"
                                "background-color:rgb("+QString::number(foregroud_color.red())+","+QString::number(foregroud_color.green())+","+QString::number(foregroud_color.blue())+")"
                                "}";

        qss = qssbackgroud + qssforegroud;
    }else{

        QString qssbackgroud = "QProgressBar:"+horstr+"{"+
                "border-image:url("+backgroud_img+");"+
                "text-align:center;"
                "}";

        QString qssforegroud = "QProgressBar::chunk:"+horstr+"{"
                                "border-image:url("+foregroud_img+");}";

        qss = qssbackgroud + qssforegroud;

    }

    qDebug()<<"MyProgressbar qss:"<<qss;
    setStyleSheet(qss);

}

void MyProgressbar::setLayoutDirection(int hov)
{
    this->hov = hov;
}


void MyProgressbar::setForegroundColor(QColor v)
{
foregroud_color = v;
}

void MyProgressbar::setBackgroudColor(QColor v)
{
backgroud_color = v;
}

void MyProgressbar::setForegroundImg(QString v)
{
    foregroud_img = v;
}

void MyProgressbar::setBackgroudImg(QString v)
{
    backgroud_img = v;
}
