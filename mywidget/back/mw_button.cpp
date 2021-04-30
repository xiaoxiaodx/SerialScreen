#include "mw_button.h"
#include "util.h"
MW_Button::MW_Button(int id,QString name,float x,float y,float w,float h,QString text)
    :MW_Base(id,name,x,y,w,h),showtext(text)
{

}

void MW_Button::drawself(QPainter *pt){



    if(state){

        setBackgroudImage(bgimg_state1);
        setBackgroudColor(bgcolor_state1);

    }else{
        setBackgroudImage(bgimg_state2);
        setBackgroudColor(bgcolor_state2);
    }

    drawBg(pt);


    if(mtext == nullptr)
        mtext = new MText(mx,my,mx+mwidth,my+mheight,showtext,QFont("Microsoft YaHei",10));

    mtext->draw(pt);

}

void MW_Button::drawBg(QPainter *pt){


    if(isuseimg)
        drawbg_img(pt);
    else
        drawbg_color(pt);

}

void MW_Button::switchState(){

    state = !state;
}



