#include "myradio.h"
#include <QDebug>
MyRadio::MyRadio(int id,QString name,int count,int selectindex,int hov,int distance,bool isuseimg)
    :mid(id),mname(name),mradioCount(count),mselectIndex(selectindex),mdistance(distance),misuseimg(isuseimg),mhov(hov)
{


setObjectName(name);
}




void MyRadio::layout(){



    int btnw = 0;
    int btnh = 0;

    int parentw = this->width();
    int parenth = this->height();


    QString qssfg="",qssbg="";



    if(misuseimg){

        qssfg = "image:url("+foregroudImgPath+");";
        qssbg = "image:url("+backgroudImgPath+");";
    }else{
        qssbg =  "background-color:rgb("+QString::number(backgroudColor.red())+","+QString::number(backgroudColor.green())+","+QString::number(backgroudColor.blue())+");";
        qssfg =  "background-color:rgb("+QString::number(foregroudColor.red())+","+QString::number(foregroudColor.green())+","+QString::number(foregroudColor.blue())+");";

    }

    //间隔占据的像素
    int sumspace = (mradioCount-1)*mdistance;

    if(mhov == 1){//水平

        btnw = (parentw-sumspace)/mradioCount;
        btnh = parenth;

    }else{
        btnw = parentw;
        btnh = (parenth-sumspace)/mradioCount;
    }

   int width = btnw;

    QString qss = "QRadioButton {border-radius:"+QString::number(width/2)+"px;"+qssbg+"}"
            "QRadioButton::indicator{width:"+QString::number(width/2)+"px;height:"+QString::number(width/2)+"px;"
             "margin-left:"+QString::number(width/4)+"px;border-radius:"+QString::number(width/4)+";}"
            "QRadioButton::indicator::checked {"+qssfg+"}";

    QString qss1 = "QRadioButton {border-radius:"+QString::number(width/2)+"px;background-color:rgb(255,0,0);}"
                   "QRadioButton::indicator{width:"+QString::number(width/2)+"px;height:"+QString::number(width/2)+"px;"
           "margin-left:"+QString::number(width/4)+"px;border-radius:"+QString::number(width/4)+";}"
            "QRadioButton::indicator::checked {background-color:rgb(0,0,255);}";
    setStyleSheet(qss);

    qDebug()<<"MyRadio qss:"<<qss;
    qDebug()<<"MyRadio qss1:"<<qss1;
    qDebug()<<"mradioCount:"<<mradioCount;
    qDebug()<<"mhov:"<<mhov;
    qDebug()<<"mselectIndex:"<<mselectIndex;



    for (int i=0;i<mradioCount;i++) {

        QRadioButton *radiobtn = new QRadioButton(this);


        //radiobtn->setText("选项"+QString::number(i));
        if(mhov)
            radiobtn->setGeometry(i*(btnw+mdistance),0,btnw,btnh);
        else
            radiobtn->setGeometry(0,i*(btnh+mdistance),btnw,btnh);


        if(mselectIndex == i)
            radiobtn->setChecked(true);
        else
            radiobtn->setChecked(false);



        connect(radiobtn,&QRadioButton::pressed,this,[=](){

            qDebug()<<"click:"<<i<<","<<mselectIndex;

        });
        radiobtn->show();
    }


}


