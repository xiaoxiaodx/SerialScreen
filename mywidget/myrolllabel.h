#ifndef MYROLLLABEL_H
#define MYROLLLABEL_H

#include <QTextEdit>

class MyRollLabel : public QTextEdit
{
public:
    MyRollLabel(int id,QString name);


    void setBackgroudImg(QString imgpath);
    void setBackgroudColor(QColor color);
    void setFont(QFont font,QColor fontcolor);
    void setText(QString txt);
    void addText(QString txt);
    void clearText(QString txt);

    int mid;
    QString mname;


    bool isuseimg;
    QColor backgroud_color;
    QColor fontcolor;
    QString backgroud_img;

private:
    QString mtext;


};

#endif // MYROLLLABEL_H
