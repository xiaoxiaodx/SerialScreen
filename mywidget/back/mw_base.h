#ifndef MW_BASE_H
#define MW_BASE_H

#include <QString>
#include <QList>
#include <QColor>
#include <QImage>
#include "shape/mrect.h"
#include "shape/mimage.h"
#include "shape/mtext.h"
/*
 * 控件基类，提供抽象接口
 * MW 是 MyWidget缩写
*/
class MW_Base
{
public:
   MW_Base(int id,QString name,float x,float y,float width,float height,
           bool ishiden = false,bool isuseimg = false,
           int radius = 0,int borderw=1,
           QColor bgcolor= QColor(255,255,255),QColor bordercolor=QColor(0,0,0));

  virtual void drawself(QPainter *pt)=0;


   bool getIsHiden() const;
   void setIsHiden(bool value);
   void setBackgroudColor(QColor color);
   void setBackgroudImage(QImage img);
   int getMborderwidth() const;
   void setMborderwidth(int value);

   QColor getMbordercolor() const;
   void setMbordercolor(const QColor &value);

protected:
   void drawbg_border(QPainter *pt);//边界
   void drawbg_img(QPainter *pt);//内容填充
   void drawbg_color(QPainter *pt);//内容填充


   int mid;
   QString mname;

   float mx;
   float my;
   float mwidth;
   float mheight;

   bool misHiden;

   int mradius;

   int mborderwidth;
   QColor mbordercolor;

   QColor mbgcolor;
   QImage mbgimg;


   MImage *mimg;
   MRect *mrectborder = nullptr;
   MRect *mrectfill = nullptr;


    QList<MW_Base*> children;
};

#endif // MW_BASE_H
