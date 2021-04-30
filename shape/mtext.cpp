#include "mtext.h"
//#include "util.h"
MText:: MText(float startx,float starty,float endx,float endy,QString text,QFont font,QColor fontcolor,int aligntype)
    :mstartx(startx),mstarty(starty),mendx(endx),mendy(endy),mtext(text),mfont(font),
      mfontcolor(fontcolor),maligntype(aligntype)
{

}


void MText::draw(QPainter *pt)
{

    pt->save();
    //文本所在限制区域
    QRectF textrectf(mstartx,mstarty,mendx-mstartx,mendy-mstarty);

//    pt->setPen(QPen(QColor(255,0,0)));
//    pt->drawRect(textrectf);


    pt->setFont(mfont);
    pt->setPen(QPen(mfontcolor));
    pt->drawText(textrectf, maligntype,mtext);

    pt->restore();

}

int MText::getMaligntype() const
{
    return maligntype;
}

void MText::setMaligntype(int value)
{
    maligntype = value;
}

QFont MText::getMfont() const
{
    return mfont;
}

void MText::setMfont(const QFont &value)
{
    mfont = value;
}

QColor MText::getMfontcolor() const
{
    return mfontcolor;
}

void MText::setMfontcolor(const QColor &value)
{
    mfontcolor = value;
}

int MText::getLetterSpacing() const
{
    return mfont.letterSpacing();
}

void MText::setLetterSpacing(qreal letterSpacing)
{
    mfont.setLetterSpacing(QFont::AbsoluteSpacing, letterSpacing);
}
