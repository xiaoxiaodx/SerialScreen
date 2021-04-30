#include "myradio.h"

MyRadio::MyRadio(int id,QString name,int count,int selectindex,int hov,int distance,bool isuseimg)
    :mid(id),mname(name),mradioCount(count),mselectIndex(selectindex),mdistance(distance),misuseimg(isuseimg),mhov(hov)
{



}



void MyRadio::layout(){



    int btnw = 0;
    int btnh = 0;

    int parentw = this->width();
    int parenth = this->height();

    //间隔占据的像素
    int sumspace = (mradioCount-1)*mdistance;

    if(mhov == 1){//水平

        btnw = (parentw-sumspace)/mradioCount;
        btnh = parenth;

    }else{
        btnw = parenth;
        btnh = (parenth-sumspace)/mradioCount;
    }

    for (int i=0;i<mradioCount;i++) {

        QRadioButton *radiobtn = new QRadioButton(this);

        radiobtn->setText("选项"+QString::number(i));
        if(mhov)
            radiobtn->setGeometry(i*(btnw+mdistance),0,btnw,btnh);
        else
            radiobtn->setGeometry(0,i*(btnh+mdistance),btnw,btnh);

        radiobtn->show();
    }


}


void MyRadio::setBackgroudImg(QString imgpath)
{

    QImage img(imgpath);
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Base,QBrush(img.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(pal);

}

void MyRadio::setBackgroudColor(QColor color)
{
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Base,color);
    this->setPalette(pal);
}
