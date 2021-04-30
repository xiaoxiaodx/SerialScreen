#include "mw_base.h"

MW_Base::MW_Base(int id,QString name,float x,float y,float width,float height,
                 bool ishiden ,bool isuseimg,
                 int radius ,int borderw,
                 QColor bgcolor,QColor bordercolor)
    :mid(id),mname(name),mx(x),my(y),mwidth(width),mheight(height),
      misHiden(ishiden),mradius(radius),mborderwidth(borderw),
      mbgcolor(bgcolor),mbordercolor(bordercolor)
{


}


//void MW_Base::drawBg(QPainter *pt){






//}

void MW_Base::drawbg_border(QPainter *pt)//边界
{

    if(mborderwidth > 0){

        if(mrectborder == nullptr){
            mrectborder = new MRect(mx,my,mx+mwidth,my+mheight,false,mbordercolor,mborderwidth);
        }
        mrectborder->setMcolor(mbordercolor);
        mrectborder->setMsize(mborderwidth);
        mrectborder->draw(pt);

    }

}
void MW_Base::drawbg_img(QPainter *pt)//内容填充
{

    if(mimg == nullptr )
        mimg = new MImage(mx,my,mx+mwidth,my+mheight,mradius,mbgimg);
    mimg->setMimg(mbgimg);
    mimg->draw(pt);


}

void MW_Base::drawbg_color(QPainter *pt)
{
    if(mrectfill == nullptr)
        mrectfill = new MRect(mx+mborderwidth,my+mborderwidth,mx+mwidth-mborderwidth,my+mheight-mborderwidth,true,mbgcolor,mborderwidth);
    mrectfill->setMcolor(mbgcolor);
    mrectfill->draw(pt);
}

QColor MW_Base::getMbordercolor() const
{
    return mbordercolor;
}

void MW_Base::setMbordercolor(const QColor &value)
{
    mbordercolor = value;
}

int MW_Base::getMborderwidth() const
{
    return mborderwidth;
}

void MW_Base::setMborderwidth(int value)
{
    mborderwidth = value;
}

bool MW_Base::getIsHiden() const
{
    return misHiden;
}

void MW_Base::setIsHiden(bool value)
{
    misHiden = value;
}

void MW_Base::setBackgroudColor(QColor color)
{

    mbgcolor = color;
}

void MW_Base::setBackgroudImage(QImage img)
{

    mbgimg = img;
}
