#ifndef MYPAGE_H
#define MYPAGE_H

#include <QWidget>
#include <shape/Shape.h>
class MyPage : public QWidget
{
    Q_OBJECT
public:
    explicit MyPage(int id,QString name);

    void addWidget(QWidget *widget);
    void addShape(Shape *shape);

    QString getName() const;
    void setName(const QString &value);

    int getId() const;
    void setId(int value);


    bool isusebgimg = false;
    QColor bgcolor;
    QString bgimgpath;
    QImage *img = nullptr;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);        //按下
    void mouseReleaseEvent(QMouseEvent *event);      //抬起
    void mouseDoubleClickEvent(QMouseEvent *event);  //双击
    void mouseMoveEvent(QMouseEvent *event);         //移动
    void wheelEvent(QWheelEvent *event);             //滑轮
signals:

private:
    int id;
    QString name;

    QList<Shape*> listShape;
};

#endif // MYPAGE_H
