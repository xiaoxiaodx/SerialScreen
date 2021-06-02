#include "myrolllabel.h"

#include <QTextCodec>
#include <QScrollBar>
MyRollLabel::MyRollLabel(int id,QString name):mid(id),mname(name)
{
setObjectName(name);
    //this->verticalScrollBar()->setVisible(false);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MyRollLabel::setText(QString txt)
{
    QTextEdit::setText(txt);
}

void MyRollLabel::setFont(QString family ,char* txt,QColor fontcolor,int Strdistance){

    QFont font(family);
    font.setWordSpacing(Strdistance);
    QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
    QString gbk_string = gbk_codec->toUnicode(txt);
    setText(gbk_string);
    QTextEdit::setFont(font);
    QTextEdit::setTextColor(fontcolor);
}

void MyRollLabel::addText(QString txt)
{
    //this->tex
}

void MyRollLabel::clearText(QString txt)
{

}

void MyRollLabel::setBackgroudImg(QString imgpath)
{

    QImage img(imgpath);
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Base,QBrush(img.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(pal);

}

void MyRollLabel::setBackgroudColor(QColor color)
{
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Base,color);
    this->setPalette(pal);
}

