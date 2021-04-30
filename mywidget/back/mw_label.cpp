#include "mw_label.h"

MW_Label::MW_Label(int id,QString name,float x,float y,float w,float h,QString text,
                 QFont font,QColor fontcolor,int aligtype)
    :MW_Base(id,name,x,y,w,h),mfont(font),mstr(text),mfontcolor(fontcolor),maligntype(aligtype)
{

}
void MW_Label::drawself(QPainter *pt){


    if(misHiden)
        return;
    //drawBg(pt);

    if(mtext == nullptr)
        mtext = new MText(mx,my,mx+mwidth,my+mheight,mstr,mfont,mfontcolor,maligntype);

    mtext->draw(pt);

}
