#ifndef MYHOTSPOT_H
#define MYHOTSPOT_H

#include <QObject>
#include <QWidget>

class MyHotSpot : public QWidget
{
    Q_OBJECT
public:
    explicit MyHotSpot(int id,QString name);
    int mid;
    QString mname;
signals:

};

#endif // MYHOTSPOT_H
