#ifndef MW_TEXT_H
#define MW_TEXT_H

#include "mywidget/mw_base.h"

class MW_Label : public MW_Base
{
public:
    MW_Label(int id,QString name,float x,float y,float w,float h,QString text,QFont font=QFont("Microsoft YaHei",10),QColor fontcolor=QColor(0,255,0),int aligtype = Qt::AlignLeft|Qt::AlignVCenter);

    void drawself(QPainter *pt) override;

private:
    MText *mtext = nullptr;
    QString mstr;
    QFont mfont;
    QColor mfontcolor;
    int maligntype;

};

#endif // MW_TEXT_H
