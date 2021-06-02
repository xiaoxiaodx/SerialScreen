#ifndef MYPIC_H
#define MYPIC_H

#include <QWidget>

class MyPic : public QWidget
{
    Q_OBJECT
public:
    explicit MyPic(int id,QString name);

    int mid;
    QString mname;
     QImage img;
protected:
    void paintEvent(QPaintEvent *event);
signals:

private:


};

#endif // MYPIC_H
