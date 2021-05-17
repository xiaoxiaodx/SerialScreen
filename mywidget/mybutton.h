#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(int id,QString name);


    void updateStyle();

    void slot_clicked();
    void slot_pressed();
    void slot_released();

    int mid;
    QString mname;

    //0正常按钮，1双态按钮
    int btnType;

    QColor default_bgcolor_press;
    QColor default_bgcolor;


    //16位深565格式
    QString default_bgimg_press;//文件所在绝对路径
    QString default_bgimg;

    //是否使用图片
    bool isuseimgbg = false;

    QString qss_bg;
    QString qss_bg_press;
};

#endif // MYBUTTON_H
