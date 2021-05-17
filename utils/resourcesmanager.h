#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <QFont>
#include <QImage>
#include <QMap>
class ResourcesManager
{


public:
    ResourcesManager();
    static ResourcesManager *resmanager;
    static ResourcesManager *getInstance();

    QImage getImage(int index);
    QString getImageAbsolutePath(int index);
    QString getFontFamily(int index);
    QString getFontAbsolutePath(int index);
    void saveImage(int index,int w,int h,int format,char *data);
    void saveFont(int index,char *data,int datalen);



private:
    bool onLoadFont(const QString& fontPath,QString &fontfamilyname);
    //字体，图片键值对， 键为资源索引，值为资源绝对路径
    QMap<int,QString> mapFont;
    QMap<int,QString> mapImage;

};

#endif // RESOURCESMANAGER_H
