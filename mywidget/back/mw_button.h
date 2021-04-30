#ifndef MW_BUTTON_H
#define MW_BUTTON_H

#include "mywidget/mw_base.h"
#include "shape/Shape.h"
class MW_Button: public MW_Base
{

public:
    MW_Button(int id,QString name,float x,float y,float w,float h,QString text);

   void drawself(QPainter *pt) override;

   void switchState();
protected:

    void drawBg(QPainter *pt);
private:
   MText *mtext = nullptr;

   QString showtext;

   //0正常按钮，1双态按钮
   int btnType;
   //鼠标按下抬起标志
   QColor bgcolor_state1;
   QColor bgcolor_state2;
   QImage bgimg_state1;
   QImage bgimg_state2;


   bool isuseimg;
   bool state;
};

#endif // MW_BUTTON_H
