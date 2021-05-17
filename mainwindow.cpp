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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->resize(800, 600);
    //设置背景颜色
    QPalette palette = this->palette();  //获取调色板
    palette.setColor(QPalette::Window, QColor(255, 255, 255));  //设置为白色
    this->setPalette(palette);  //重新设置调色板
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    init();




    connect(&serialUtils,&SerialUtils::signal_addMWidget,this,&MainWindow::slot_addMWidget);
    connect(&serialUtils,&SerialUtils::signal_addPage,this,&MainWindow::slot_addPage);

    serialUtils.analysisBin();
    //initSerialPort(115200);
}


void MainWindow::init(){



    //MyDrawWidget *mydrawWidget= new MyDrawWidget();
    //绘图测试
    //mydrawWidget->addShape(new MPoint(100,100,QColor(0,255,0),10));//点
    //mydrawWidget->addShape(new MLine(0,100,100,0,QColor(0,255,0)));//线
    //mydrawWidget->addShape(new MRect(0,0,50,50,false,QColor(255,0,0)));//边框矩形
    //mydrawWidget->addShape(new MRect(50,50,200,200,true,QColor(0,0,255)));//填充矩形
    //mydrawWidget->addShape(new MArc(110,110,50,0,360,QColor(0,0,255),false));
    //mydrawWidget->addShape(new MArc(200,200,100,0,360,QColor(0,255,0),true));

    //仪表盘
    //mydrawWidget->addShape(new MDashboard());

    //文本对齐测试
    //    mydrawWidget->addShape(new MText(0,0,100,100,"双方都撒即啦左上",QFont("Microsoft YaHei",10),QColor(0,255,0),true,QColor(0,0,0),ALIGN_TYPE_LEFT_TOP));
    //    mydrawWidget->addShape(new MText(110,0,210,100,"双方都撒即开始啦中上",QFont("Microsoft YaHei",10),QColor(0,255,0),true,QColor(0,0,0),ALIGN_TYPE_CENTER_TOP));
    //    mydrawWidget->addShape(new MText(220,0,320,100,"双方都始啦右上",QFont("Microsoft YaHei",10),QColor(0,0,255),true,QColor(0,0,0),ALIGN_TYPE_RIGHT_TOP));
    //    mydrawWidget->addShape(new MText(0,110,100,210,"双方都的开始啦左中",QFont("Microsoft YaHei",10),QColor(0,255,0),true,QColor(0,0,0),ALIGN_TYPE_LEFT_CENTER));
    //    mydrawWidget->addShape(new MText(110,110,210,210,"双方都撒开始啦中中",QFont("Microsoft YaHei",10),QColor(0,255,0),true,QColor(0,0,0),ALIGN_TYPE_CENTER_CENTER));
    //    mydrawWidget->addShape(new MText(220,110,320,210,"双方都撒即可附始啦右中",QFont("Microsoft YaHei",10),QColor(0,255,0),true,QColor(0,0,0),ALIGN_TYPE_RIGHT_CENTER));
    //    mydrawWidget->addShape(new MText(0,220,100,320,"双方都撒开始啦左下",QFont("Microsoft YaHei",10),QColor(0,255,0),true,QColor(0,0,0),ALIGN_TYPE_LEFT_BOTTOM));
    //    mydrawWidget->addShape(new MText(110,220,210,320,"双方都撒即可附中下",QFont("Microsoft YaHei",10),QColor(0,255,0),true,QColor(0,0,0),ALIGN_TYPE_CENTER_BOTTOM));
    //    mydrawWidget->addShape(new MText(220,220,320,320,"双方都撒即可始啦右下",QFont("Microsoft YaHei",10),QColor(0,255,0),true,QColor(0,0,0),ALIGN_TYPE_RIGHT_BOTTOM));

    //QImage img(":/res/cloud_con.png");
    //mydrawWidget->addShape(new MImage(0,0,100,100,5,img));
    //rootTabwidget->addTab(mydrawWidget,"");
    //QImage img("qrc:/res/cloud_con.png");


    rootWidget = new QStackedWidget(this);
    this->setCentralWidget(rootWidget);


    //btntest();


    //initSerialPort();

    btntest();
}
#include <QGuiApplication>
void MainWindow::btntest(){

    int btn_w = 80;
    int btn_h = 30;
    int w = this->width();
    int h = this->height();

    int btnindex = 1;
    QPushButton *btn_addpage = new QPushButton("添加页",this);


    //QGuiApplication::setFont(QFont("微软雅黑",10));
    btn_addpage->setFont(QFont("STXinwei",10));
    btn_addpage->setGeometry(10,h-btn_h-10,btn_w,btn_h);
    QFontInfo fontinfo = btn_addpage->fontInfo();
    qDebug() << fontinfo.family() + ":" + fontinfo.styleName();
    connect(btn_addpage,&QPushButton::clicked,this,[=] ()  {
        addPage(test_page_index,"test"+QString::number(test_page_index));
        test_page_index++;
    });

    QPushButton *btn_swichpage = new QPushButton("切换页",this);
    btn_swichpage->setGeometry((10+btn_w)*(btnindex++),h-btn_h-10,btn_w,btn_h);
    connect(btn_swichpage,&QPushButton::clicked,this,[=] ()  {
        switchPage();
    });

    QPushButton *btn_addbtn = new QPushButton("添加按钮",this);
    btn_addbtn->setGeometry((10+btn_w)*(btnindex++),h-btn_h-10,btn_w,btn_h);
    connect(btn_addbtn,&QPushButton::clicked,this,[=] ()  {

        MyButton *mbtn = new MyButton(15,"btn1");
        addMWidget(mbtn,10,10,50,50);
        //        mbtn->setDefault_bgimg("H:/dmjProgram/qtPro/SerialScreen/res/1111111.png");
        //        mbtn->setDefault_bgimg_press("H:/dmjProgram/qtPro/SerialScreen/res/whiteb.png");
        //        mbtn->setDefault_bgcolor(31);
        //        mbtn->setDefault_bgcolor_press(0);
        //        mbtn->setBtnType(1);
        mbtn->updateStyle();

    });

    QPushButton *btn_addprocessbar= new QPushButton("添加进度条",this);
    btn_addprocessbar->setGeometry((10+btn_w)*(btnindex++),h-btn_h-10,btn_w,btn_h);
    connect(btn_addprocessbar,&QPushButton::clicked,this,[=] ()  {

        MyProgressbar *processbar = new MyProgressbar(1,"进度条");

        processbar->setValue(10);

        processbar->setBackgroudImg("H:/dmjProgram/qtPro/SerialScreen/res/1111111.png");
        processbar->setForegroundImg("H:/dmjProgram/qtPro/SerialScreen/res/whiteb.png");
        processbar->setBackgroudColor(QColor(255,0,0));
        processbar->setForegroundColor(QColor(255,255,0));
        //processbar->isuseimg = true;
        processbar->radius = 5;
        processbar->hov = 0;
        processbar->updateStyle();

        addMWidget(processbar,60,60,100,30);

    });

    QPushButton *btn_addslider = new QPushButton("添加滑动控件",this);
    btn_addslider->setGeometry((10+btn_w)*(btnindex++),h-btn_h-10,btn_w,btn_h);
    connect(btn_addslider,&QPushButton::clicked,this,[=] ()  {

        MySilder *silder = new MySilder(1,"111");

        silder->foregroud_color= QColor("#ff0000");
        silder->backgroud_color = QColor("#00ff00");
        silder->hander_color = QColor("#0000ff");
        silder->hov = 0;
        silder->radius = 4;
        silder->silderw = 10;
        silder->silderh = 10;
        silder->isuseimg = false;


        silder->setOrientation(Qt::Horizontal);

        addMWidget(silder,90,90,100,10);
        silder->updateStyle();

    });

    QPushButton *btn_rolllabel = new QPushButton("添加滚动文本",this);
    btn_rolllabel->setGeometry((10+btn_w)*(btnindex++),h-btn_h-10,btn_w,btn_h);
    connect(btn_rolllabel,&QPushButton::clicked,this,[=] ()  {

        MyRollLabel *mrolllable = new MyRollLabel(1,"222");
        mrolllable->setReadOnly(true);

        // mrolllable->verticalScrollBar()
        mrolllable->setText("添加页德萨发111111111"
                            "几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份几点开始规范范德萨发生丰东股份股份"
                            "几点开始规范范德萨发生丰东股份"
                            "几点开始规范范德萨发生丰东股份大商股份dddd");


        QFont font("16",10);
        font.setWordSpacing(100);//字间距
        mrolllable->setFont(font,QColor(255,0,0));
        mrolllable->setLineWidth(5);



        addMWidget(mrolllable,200,200,100,100);

        mrolllable->setBackgroudImg("H:/dmjProgram/qtPro/SerialScreen/res/1111111.png");
        mrolllable->setBackgroudColor(QColor(255,255,255));
    });



    QPushButton *btn_cur = new QPushButton("添加曲线",this);
    btn_cur->setGeometry((10+btn_w)*(btnindex++),h-btn_h-10,btn_w,btn_h);
    connect(btn_cur,&QPushButton::clicked,this,[=] (){

        MyGraph *mg = new MyGraph;

        addMWidget(mg,0,0,600,400);

    });


    QPushButton *btn_radio = new QPushButton("添加radio",this);
    btn_radio->setGeometry((10+btn_w)*(btnindex++),h-btn_h-10,btn_w,btn_h);
    connect(btn_radio,&QPushButton::clicked,this,[=] (){

        MyRadio *mradio = new MyRadio(2,"111",4,0);

        addMWidget(mradio,100,100,600,100);
        mradio->layout();

    });


    //    QPushButton *btn_test11 = new QPushButton("test11",this);
    //    QPushButton *btn_test12 = new QPushButton("test12",this);
    //    btn_test11->setGeometry(300,300,300,100);
    //    btn_test12->setGeometry(400,300,300,100);
    //    btn_test11->raise();
    //    btn_test12->raise();
}

void MainWindow::addMWidget(QWidget *mwbase,int x,int y,int w,int h){

    MyPage *page = (MyPage*)rootWidget->currentWidget();

    mwbase->setParent(page);
    mwbase->setGeometry(x,y,w,h);
    mwbase->show();
}

void MainWindow::addPage(int id,QString name){


    MyPage *page = new MyPage(id,name);


    //QImage img(":/res/whiteb.png");
    // page->addShape(new MImage(0,0,100,100,10,img));
    // page->addShape( new MRect(50,50,70,70,true,QColor(0,0,255),10));
    //page->addShape(new MImage(0,0,100,100,5,img));
    rootWidget->addWidget(page);

}


void MainWindow::slot_addPage(int id,QString name){

    qDebug()<<"添加页";
    MyPage *page = new MyPage(id,name);
    rootWidget->addWidget(page);

}

void MainWindow::slot_addMWidget(int pageid,QWidget *mwbase,int x,int y,int w,int h)
{


    qDebug()<<"添加控件";
    MyPage *page =  (MyPage*)rootWidget->widget(pageid);

    mwbase->setParent(page);
    mwbase->setGeometry(x,y,w,h);
    mwbase->show();

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

MainWindow::~MainWindow()
{

}

