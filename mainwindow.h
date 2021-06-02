#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QSerialPort>

#include "utils/cmdproc.h"
#include "utils/resourcesmanager.h"
#include "mywidget/mypage.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void addPage(int id,QString name);
    void addMWidget(QWidget *mwbase,int x,int y,int w,int h);



    void switchPage(int id);
    void switchPage(QString name);
    void switchPage();
    void deletePage();
public slots:
    void slot_serialRead();
    void slot_switchPage(int id);
    void slot_addShape(Shape *shpe);
    void slot_addPage(int id,QString name);
    void slot_changeWidgetState(bool isshow,QString name,int state);

    void slot_process_cmd(QString cmdtype,QString cmdstr);

    void slot_addMWidget(int pageid,QWidget *mwbase,int x,int y,int w,int h);


private:

    void msetProperty(QWidget *widget,QString proname,QVariant value);
    QVariant mgetProperty(QObject *obj,QString pname);

    void messageTip(QString str);
    void init();//初始化
    void initSerialPort(int baudrate);
    void btntest();
    MyPage *findPage(int id);
    QStackedWidget *rootWidget;



    //测试
    int test_page_index = 0;

    QSerialPort serialPort;
    SerialUtils serialUtils;
   // ResourcesManager resourcesManager;

};
#endif // MAINWINDOW_H
