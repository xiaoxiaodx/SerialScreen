#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QSerialPort>
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

private:

    void init();//初始化
    void initSerialPort(int baudrate);
    void btntest();
    QStackedWidget *rootWidget;



    //测试
    int test_page_index = 0;

    QSerialPort serialPort;

};
#endif // MAINWINDOW_H
