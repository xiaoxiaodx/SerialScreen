#include "mylabel.h"
#include <QTextCodec>
MyLabel::MyLabel(int id,QString name):mid(id),mname(name)
{
    setObjectName(name);
}

void MyLabel::setTextInfo(QColor fontcolor,char* txt,QString family,int Strdistance){


    QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
    QString gbk_string = gbk_codec->toUnicode(txt);

    mtxt = txt;
    QFont font(family);
    font.setWordSpacing(Strdistance);
    this->setFont(font);
    this->setText(gbk_string);

    mfontcolor = fontcolor;

    updateStyle();

}


void MyLabel::updateStyle(){



    QString qss_bg = "";

    if(misuseimg){
        qss_bg= "QLabel{border-image: url("+mimgpath+");"
                "color:rgb("+QString::number(mfontcolor.red())+","+QString::number(mfontcolor.green())+","+QString::number(mfontcolor.blue())+");}";
    }else
        qss_bg= "QLabel {"
                "color:rgb("+QString::number(mfontcolor.red())+","+QString::number(mfontcolor.green())+","+QString::number(mfontcolor.blue())+");"
                "background-color:rgba("+QString::number(mbgcolor.red())+","+QString::number(mbgcolor.green())+","+QString::number(mbgcolor.blue())+","+QString::number(mbgcolor.alpha())+");}";


    setStyleSheet(qss_bg);
}

#include <QDebug>
void MyLabel::setTxt(QString txt)
{
    qDebug()<<"setTxt:"<<txt;
    mtxt = txt;
    setText(mtxt);
}
QString MyLabel::txt(){

    return mtxt;
}
