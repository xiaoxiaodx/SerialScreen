#include "mainwindow.h"
#include<QLabel>
#include "shape/mrect.h"
#include "shape/mline.h"
#include "shape/mpoint.h"
#include "shape/marc.h"
#include "shape/mimage.h"
#include "shape/mtext.h"
#include "shape/mdashboard.h"
#include <QTabWidget>
#include <mywidget/mypage.h>
#include <QPushButton>
#include <QDebug>


#include "mywidget/mybutton.h"
#include "mywidget/myprogressbar.h"
#include "mywidget/mysilder.h"
#include "mywidget/myrolllabel.h"
#include "mywidget/mygraph.h"
#include "mywidget/myradio.h"

#include <QMouseEvent>
#include <QApplication>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->resize(800, 600);
    //设置背景颜色
    QPalette palette = this->palette();  //获取调色板
    palette.setColor(QPalette::Window, QColor(255, 255, 255));  //设置为白色
    this->setPalette(palette);  //重新设置调色板
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏





    connect(&serialUtils,&SerialUtils::signal_addMWidget,this,&MainWindow::slot_addMWidget);
    connect(&serialUtils,&SerialUtils::signal_addPage,this,&MainWindow::slot_addPage);

    connect(&serialUtils,&SerialUtils::signal_switchPage,this,&MainWindow::slot_switchPage);
    connect(&serialUtils,&SerialUtils::signal_addShape,this,&MainWindow::slot_addShape);
    connect(&serialUtils,&SerialUtils::signal_process_cmd,this,&MainWindow::slot_process_cmd);


    init();
}


void MainWindow::init(){

    rootWidget = new QStackedWidget(this);
    this->setCentralWidget(rootWidget);

    serialUtils.analysisBin();


    int nCount = rootWidget->count();
    for (int i=0;i<nCount;i++) {

        MyPage *curpage = (MyPage*)(rootWidget->widget(i));


    }

    serialUtils.ParseSerialInt();
    initSerialPort(115200);

    btntest();
}
#include <QGuiApplication>
void MainWindow::btntest(){

    int btn_w = 80;
    int btn_h = 30;
    int w = this->width();
    int h = this->height();

    int btnindex = 1;


    QPushButton *btn_addbtn = new QPushButton("测试",this);
    btn_addbtn->setGeometry((10+btn_w)*(btnindex++),h-btn_h-10,btn_w,btn_h);

    connect(btn_addbtn,&QPushButton::pressed,this,[=] ()  {

        qDebug()<<"add btn";


        switchPage();


    });

    QPushButton *btn_cur = new QPushButton("添加曲线",this);
    btn_cur->setGeometry((10+btn_w)*(btnindex++),h-btn_h-10,btn_w,btn_h);
    connect(btn_cur,&QPushButton::clicked,this,[=] (){

        qDebug()<<"添加曲线"<<btn_addbtn->x()<<","<<btn_addbtn->y();

        QMouseEvent event1(QEvent::MouseButtonPress, QPointF(2,2), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(btn_addbtn, &event1);

        MyPage *curpage = (MyPage *)rootWidget->currentWidget();

        QList<QWidget*> listwidget = curpage->findChildren<QWidget*>();

        for(int i=0;i<listwidget.size();i++)
            qDebug()<<"objectName:"<<listwidget.at(i)->objectName();
    });

}

void MainWindow::addMWidget(QWidget *mwbase,int x,int y,int w,int h){

    MyPage *page = (MyPage*)rootWidget->currentWidget();

    mwbase->setParent(page);
    mwbase->setGeometry(x,y,w,h);
    mwbase->show();
}

void MainWindow::addPage(int id,QString name,bool isuseimg,QString imgpaht,QColor color){


    MyPage *page = new MyPage(id,name);
    page->isusebgimg = isuseimg;
    if(isuseimg){
        page->bgimgpath = imgpaht;
    }else{
        page->bgcolor = color;
    }
    rootWidget->addWidget(page);

}
void MainWindow::slot_changeWidgetState(bool isshow,QString name,int state){


    MyPage *curpage = (MyPage *)rootWidget->currentWidget();


    QWidget *widget = curpage->findChild<QWidget *>(name);


    if(widget == nullptr)
        return;


    if(state == 2){

        widget->setVisible(isshow);

    }else if(state == 1){

        widget->setEnabled(isshow);

    }else if(state == 3){

        widget->setVisible(isshow);
        widget->setEnabled(isshow);
    }

}

void MainWindow::slot_addPage(int id,QString name,bool isuseimg,QString imgpaht,QColor color){


    MyPage *page = new MyPage(id,name);
    page->isusebgimg = isuseimg;
    if(isuseimg){
        page->bgimgpath = imgpaht;
    }else{
        page->bgcolor = color;
    }
    rootWidget->addWidget(page);

    qDebug()<<"add page succ";
}

void MainWindow::slot_addMWidget(int pageid,QWidget *mwbase,int x,int y,int w,int h)
{


   // qDebug()<<"添加控件";
    MyPage *page =  (MyPage*)rootWidget->widget(pageid);

    mwbase->setParent(page);
    mwbase->setGeometry(x,y,w,h);
    mwbase->show();

}


void MainWindow::slot_switchPage(int id)
{
    switchPage(id);
}

void MainWindow::slot_addShape(Shape *shpe)
{

    MyPage *curpage = (MyPage *)rootWidget->currentWidget();

    curpage->addShape(shpe);

    curpage->update();
}


MyPage* MainWindow::findPage(int id)
{
    int nCount = rootWidget->count();
    for (int i=0;i<nCount;i++) {

        MyPage *curpage = (MyPage*)(rootWidget->widget(i));
        if(curpage->getId()==id){

            return curpage;
        }
    }
    return nullptr;
}

void MainWindow::switchPage(int id)
{
    int nCount = rootWidget->count();
    for (int i=0;i<nCount;i++) {

        MyPage *curpage = (MyPage*)(rootWidget->widget(i));
        if(curpage->getId()==id){
            qDebug()<<"curpage info:"<<curpage->getId()<<","<<curpage->getName();
            rootWidget->setCurrentWidget(curpage);
        }
    }
}

void MainWindow::switchPage(QString name)
{

    int nCount = rootWidget->count();
    for (int i=0;i<nCount;i++) {

        MyPage *curpage = (MyPage*)(rootWidget->widget(i));
        if(curpage->getName().compare(name)==0){
            qDebug()<<"curpage info:"<<curpage->getId()<<","<<curpage->getName();

            rootWidget->setCurrentWidget(curpage);
        }
    }
}

void MainWindow::switchPage(){

    int nCount = rootWidget->count();
    int nIndex = rootWidget->currentIndex();

    // 获取下一个需要显示的页面索引
    ++nIndex;

    // 当需要显示的页面索引大于等于总页面时，切换至首页
    if (nIndex >= nCount)
        nIndex = 0;

    MyPage *curpage = (MyPage*)rootWidget->currentWidget();
    qDebug()<<"curpage info:"<<curpage->getId()<<","<<curpage->getName();
    rootWidget->setCurrentIndex(nIndex);

}


void MainWindow::slot_process_cmd(QString cmdtype,QString cmdstr){


    qDebug()<<"cmdtype:"<<cmdtype<<"    cmdstr:"<<cmdstr;

    QStringList cmdlist = cmdstr.split(" ");

    QString type = cmdtype;
    QString validstr = cmdstr;


    MyPage *curpage = (MyPage*)rootWidget->currentWidget();

    if(type.compare("page")==0){

        bool isok = false;
        int pageid = validstr.toUInt(&isok);

        if(isok)
            switchPage(pageid);
        else
            switchPage(validstr);

    }else if(type.compare("ref")==0){


        QWidget *widget = curpage->findChild<QWidget*>(validstr);

        widget->update();

    }else if(type.compare("click")==0){

        QStringList cmdcontent = cmdstr.split(",");
        if(cmdcontent.size() <= 2){

            QString name = cmdcontent[0];
            int state = cmdcontent[1].toInt();

            QWidget *widget = curpage->findChild<QWidget*>(name);

            if(state == 1){


                QMouseEvent me(QEvent::MouseButtonPress,QPointF(1,1),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
                QApplication::sendEvent(widget, &me);

            }else if(state == 2){
                QMouseEvent me(QEvent::MouseButtonRelease,QPointF(1,1),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
                QApplication::sendEvent(widget, &me);

            }else{

                messageTip("click state:"+cmdcontent[1]);

            }



        }else{

            messageTip("error:"+type+"---"+cmdstr);
        }



    }else if(type.compare("hide")==0){


        QStringList cmdcontent = cmdstr.split(",");
        qDebug()<<"cmdcontent:"<<cmdcontent.size();
        if(cmdcontent.size() <= 2){

            QString name = cmdcontent[0];
            int state = cmdcontent[1].toInt();

            slot_changeWidgetState(false,name,state);

        }else{

            messageTip("error:"+type+"---"+cmdstr);
        }


    }else if(type.compare("show")==0){

        QStringList cmdcontent = cmdstr.split(",");

        if(cmdcontent.size() <= 2){

            QString name = cmdcontent[0];
            int state = cmdcontent[1].toInt();

            slot_changeWidgetState(true,name,state);

        }else{

            messageTip("error:"+type+"---"+cmdstr);
        }

    }else if(type.compare("re")==0){




    }else if(type.compare("add")==0){

        QStringList cmdcontent = cmdstr.split(",");

        if(cmdcontent.size() <= 3){

            QString name = cmdcontent[0];
            int channel = cmdcontent[1].toInt();
            float data = cmdcontent[2].toFloat();
            MyGraph *mygraph = curpage->findChild<MyGraph*>(name);

            mygraph->addPoint(channel,data);

        }else{

            messageTip("error:"+type+"---"+cmdstr);

        }


    }else if(type.compare("addn")==0){




    }else if(type.compare("del")==0){

        QStringList cmdcontent = cmdstr.split(",");

        if(cmdcontent.size() <= 2){

            QString name = cmdcontent[0];
            int channel = cmdcontent[1].toInt();

            MyGraph *mygraph = curpage->findChild<MyGraph*>(name);

            mygraph->delCurve(channel);

        }else{

            messageTip("error:"+type+"---"+cmdstr);

        }


    }else if(type.compare("cal")==0){//触摸校准




    }else if(type.compare("reset")==0){//屏幕重启




    }else if(type.compare("baud")==0){//修改波特率




    }else if(type.compare("dim")==0){//屏幕亮度调节


        int dim = validstr.toInt();


    }else if(type.compare("rand")==0){





    }else if(type.compare("strLen")==0){


        QStringList cmdcontent = cmdstr.split(",");

        if(cmdcontent.size() <= 2){

            QStringList tmpstr = cmdcontent[0].split(".");
            QStringList tmpstr1 = cmdcontent[1].split(".");

            QString w_name = tmpstr[0];
            QString p_name = tmpstr[1];

            QString w_name1 = tmpstr1[0];
            QString p_name1 = tmpstr1[1];

            QWidget *mwt = curpage->findChild<QWidget*>(w_name);
            QWidget *mwt1 = curpage->findChild<QWidget*>(w_name1);


            //第一个控件的属性 的字符串长度值给第二个控件
            QString str = mgetProperty(mwt,p_name).toString();
            msetProperty(mwt1,p_name1,str.length());

        }else{

            messageTip("error:"+type+"---"+cmdstr);

        }



    }else if(type.compare("strCopy")==0){

        QStringList cmdcontent = cmdstr.split(",");

        if(cmdcontent.size() <= 2){

            QStringList tmpstr = cmdcontent[0].split(".");
            QStringList tmpstr1 = cmdcontent[1].split(".");

            QString w_name = tmpstr[0];
            QString p_name = tmpstr[1];

            QString w_name1 = tmpstr1[0];
            QString p_name1 = tmpstr1[1];

            QWidget *mwt = curpage->findChild<QWidget*>(w_name);
            QWidget *mwt1 = curpage->findChild<QWidget*>(w_name1);


            //第二个控件的属性 的字符串值给第一个控件
            //QString str = mgetProperty(mwt1,p_name1).toString();
             QString str = mwt1->property(p_name1.toLatin1()).toString();
             mwt->setProperty(p_name1.toLatin1(),str);


        }else{

            messageTip("error:"+type+"---"+cmdstr);

        }


    }else if(type.compare("sncpy")==0){


    }else if(type.compare("ecoh")==0){






    }

}

QVariant MainWindow::mgetProperty(QObject *obj,QString pname){


    if(pname.compare("txt")==0){

        return obj->property("text");
    }else
        return obj->property(pname.toLatin1());
}
void MainWindow::msetProperty(QWidget *widget,QString proname,QVariant value)
{

    int x = widget->x();
    int y = widget->y();
    int width = widget->width();
    int height = widget->height();

    if(proname.compare("x")==0){

        x = value.toInt();
        widget->setGeometry(x,y,width,height);
    }else if(proname.compare("y")==0){
        y = value.toInt();
        widget->setGeometry(x,y,width,height);
    }else if(proname.compare("width")==0){
        width = value.toInt();
        widget->setGeometry(x,y,width,height);
    }else if(proname.compare("height")==0){
        height = value.toInt();
        widget->setGeometry(x,y,width,height);
    }else if(proname.compare("txt")==0){

         widget->setProperty("text",value);
    }else{

        widget->setProperty(proname.toLatin1(),value);
    }
}
void MainWindow::initSerialPort(int baudrate){



    serialPort.setPortName("COM2");
    serialPort.setBaudRate(baudrate,QSerialPort::AllDirections);//设置波特率和读写方向
    serialPort.setDataBits(QSerialPort::Data8);      //数据位为8位
    serialPort.setFlowControl(QSerialPort::NoFlowControl);//无流控制
    serialPort.setParity(QSerialPort::NoParity); //无校验位
    serialPort.setStopBits(QSerialPort::OneStop); //一位停止位


    connect(&serialPort,&QSerialPort::readyRead,this,&MainWindow::slot_serialRead);

    if(!serialPort.open(QIODevice::ReadWrite))
    {
        qDebug()<<"无法打开串口！";
        return;
    }
}

void MainWindow::slot_serialRead(){

    QByteArray arr = serialPort.readAll();
    //arr.data();

    qDebug()<<"slot_serialRead:"<<arr.toHex();

    serialUtils.ParseSerialComm(arr.data(),arr.length());
}

#include <QMessageBox>
void MainWindow::messageTip(QString str)
{
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
}
MainWindow::~MainWindow()
{

}

