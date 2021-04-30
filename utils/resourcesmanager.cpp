#include "resourcesmanager.h"
#include <QDir>
#include <QCoreApplication>
#include "debuglog.h"
#include <QFile>
#include <QDebug>
#include <QFontDatabase>
ResourcesManager::ResourcesManager()
{

}


QImage ResourcesManager::getImage(int index)
{
    if(mapImage.contains(index)){


        QString imgpath = mapImage.value(index);
        return QImage(imgpath);
    }

    return QImage();
}
QString ResourcesManager::getImageAbsolutePath(int index)
{

    if(mapImage.contains(index)){

        return mapImage.value(index);
    }

    return "";
}

QString ResourcesManager::getFontFamily(int index)
{

    if(mapFont.contains(index)){

        QString fontfilepath = mapFont.value(index);
        QString familyname;
        if(onLoadFont(fontfilepath,familyname)){


            return familyname;
        }
    }
    return "";
}
QString ResourcesManager::getFontAbsolutePath(int index)
{
    if(mapFont.contains(index)){

        return mapFont.value(index);
    }

    return "";
}
void ResourcesManager::saveImage(int index,int w,int h,int format,unsigned char *data)
{



    QString runfilepath = QCoreApplication::applicationDirPath();

    QString desFileDir = runfilepath+"/resources/image";
    QDir dir;
    if (!dir.exists(desFileDir)){
        bool res = dir.mkpath(desFileDir);
        if(res)
            DebugLog::getInstance()->writeLog("create new save image dir is succ");
        else
            DebugLog::getInstance()->writeLog("create new save image dir  is fail");
    }
    //切换当前相对路径
    if(!QDir::setCurrent(desFileDir)){
        DebugLog::getInstance()->writeLog("set save image relative dir is false");
        return ;
    }


    QImage img(data,w,h,QImage::Format_RGB16);
    QString filename = QString::number(index)+".png";
    if(img.save(filename,"PNG")){

        mapImage.insert(index,desFileDir+QString::number(index)+".png");
    }else{

        DebugLog::getInstance()->writeLog("image save is fail,filedir:"+desFileDir+",filename:"+filename);

    }


}
void ResourcesManager::saveFont(int index,char *data,int len)
{

    QString runfilepath = QCoreApplication::applicationDirPath();
    QString desFileDir = runfilepath+"/resources/font";

    QDir dir;
    if (!dir.exists(desFileDir)){
        bool res = dir.mkpath(desFileDir);
        if(res)
            DebugLog::getInstance()->writeLog("create new save font dir is succ");
        else
            DebugLog::getInstance()->writeLog("create new save font dir  is fail");
    }
    QString desFilePath = desFileDir+"/"+QString::number(index)+".ttf";

    QFile fontfile(desFilePath);
    if(fontfile.open(QIODevice::WriteOnly)){

        int writelen = fontfile.write(data,len);

        DebugLog::getInstance()->writeLog("save font file is succ,writelen:"+QString::number(writelen)+",datelen:"+QString::number(len));

    }else {
        DebugLog::getInstance()->writeLog("save font file is fail,open file fail,filepath:"+desFilePath);

    }

}


bool ResourcesManager::onLoadFont(const QString& fontPath,QString &fontfamilyname)
{
    QFile dFontFile(fontPath);
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

    fontfamilyname = lFontFamily.at(0);
   // QFont font(lFontFamily.at(0));
    //qApp->setFont(font);
    qDebug()<<"字体加载成功";
    return true;
}
