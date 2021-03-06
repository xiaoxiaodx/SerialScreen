#include "resourcesmanager.h"
#include <QDir>
#include <QCoreApplication>
#include "debuglog.h"
#include <QFile>
#include <QDebug>
#include <QFontDatabase>


ResourcesManager* ResourcesManager::resmanager = NULL;


ResourcesManager* ResourcesManager::getInstance()
{
    if(resmanager == NULL){
        resmanager = new ResourcesManager();
        return resmanager;
    }else {
        return resmanager;
    }
}

ResourcesManager::ResourcesManager()
{

}

QFont ResourcesManager::getFont(int index){

    //onLoadFont()
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
void ResourcesManager::saveImage(int index,int w,int h,int format,char *data)
{


    qDebug()<<"saveImage:"<<index;

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


    short *rgb565 = new short[w*h];

    memset(rgb565,0,w*h*2);

    for (int i=0;i<w*h;i++) {

        unsigned short h =  0x00ff & data[i*2+1];
        unsigned short l =  0x00ff & data[i*2];
        unsigned short bgr565value = h*256+ l;

        unsigned int r_565 = bgr565value & 0x0000001f;
        unsigned int g_565 = bgr565value & 0x000007f0;
        unsigned int b_565 = bgr565value & 0x0000f800;


        int tmpv = 0;

        tmpv |= g_565;
        tmpv |= r_565<<11;
        tmpv |= b_565>>11;

        rgb565[i] =  tmpv;
    }

    //格式是bgr565
    //QImage img((unsigned char*)rgb565,w,h,QImage::Format_RGB16);
    //格式是rbg565
    QImage img((unsigned char*)data,w,h,QImage::Format_RGB16);

    QString filename = QString::number(index)+".png";
    if(img.save(filename,"PNG")){

        mapImage.insert(index,desFileDir+"/"+QString::number(index)+".png");
    }else{

        DebugLog::getInstance()->writeLog("image save is fail,filedir:"+desFileDir+",filename:"+filename);

    }

     delete[] rgb565;



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

    if(fontfile.isOpen())
        fontfile.close();


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
