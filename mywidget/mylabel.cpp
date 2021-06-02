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
    QPalette pe;
    pe.setColor(QPalette::WindowText,fontcolor);
    this->setPalette(pe);



}

void MyLabel::setBackgroudImg(QString imgpath)
{

    QImage img(imgpath);
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Base,QBrush(img.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(pal);

}

void MyLabel::setBackgroudColor(QColor color)
{
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Base,color);
    this->setPalette(pal);
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
