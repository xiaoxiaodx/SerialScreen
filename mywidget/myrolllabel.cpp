#include "myrolllabel.h"


#include <QScrollBar>
MyRollLabel::MyRollLabel(int id,QString name):mid(id),mname(name)
{

    //this->verticalScrollBar()->setVisible(false);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MyRollLabel::setText(QString txt)
{
    QTextEdit::setText(txt);
}

void MyRollLabel::setFont(QFont font,QColor fontcolor){

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

