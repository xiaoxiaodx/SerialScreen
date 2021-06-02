#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <QFile>
#include <QTextCodec>
bool onLoadFont(const QString& strPath)
{
    QFile dFontFile(strPath);
    if(!dFontFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"字体文件打开失败";
        return false;
    }

    int nFontId = QFontDatabase::addApplicationFontFromData(dFontFile.readAll());
    if(nFontId == -1)
    {
        //说明加载字体文件失败了，该字体不可用
        qDebug()<<"字体不可用";
        return false;
    }

    QStringList lFontFamily = QFontDatabase::applicationFontFamilies(nFontId);
    if(lFontFamily.empty())
    {
        //说明从字体中获取字体簇失败了
        qDebug()<<"获取字体簇失败";
        return false;
    }

//    QFont font(lFontFamily.at(0));
//    qApp->setFont(font);
    qDebug()<<"字体加载成功:"<<lFontFamily.at(0);
    return true;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForLocale(codec);


    //QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
       QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
       //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    onLoadFont("华文新魏1111.ttf");
    MainWindow w;
    w.show();
//    QFontDatabase database;
//    foreach (const QString &family, database.families())
//    {
//         qDebug()<<"family:"<<family;
//    }
    return a.exec();
}
