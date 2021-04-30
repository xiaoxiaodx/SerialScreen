#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT

public:
    MyLabel(int id,QString name);


    int mid;
    QString mname;
};

#endif // MYLABEL_H
