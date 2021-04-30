#ifndef MTEXT_H
#define MTEXT_H
#include "shape/Shape.h"


class MText : public Shape
{
public:

    MText(float startx,float starty,float endx,float endy,QString text,QFont font,QColor fontcolor=QColor(0,0,0),int aligntype=(Qt::AlignHCenter | Qt::AlignVCenter));

    void draw(QPainter *pt) override;

    int getMaligntype() const;
    void setMaligntype(int value);

    QFont getMfont() const;
    void setMfont(const QFont &value);

    QColor getMfontcolor() const;
    void setMfontcolor(const QColor &value);

    int getLetterSpacing() const;
    void setLetterSpacing(qreal letterSpacing);

private:

    QColor mcolor;
    //左上
    float mstartx;
    float mstarty;
    //右下
    float mendx;
    float mendy;
    QString mtext;


    QFont mfont;
    QColor mfontcolor;
    int maligntype;
};

#endif // MTEXT_H
