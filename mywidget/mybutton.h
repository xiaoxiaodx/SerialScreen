#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(int id,QString name);

    void setBtnType(int value);

    void setDefault_bgcolor_press(int value);

    void setDefault_bgcolor(int value);

    void setDefault_bgimg_press(QString imgfilepath);

    void setDefault_bgimg(QString imgfilepath);

    void updateStyle();
private slots:
    void slot_clicked();
    void slot_pressed();
    void slot_released();

private:
    int mid;
    QString mname;

    //0正常按钮，1双态按钮
    int btnType;

    int default_bgcolor_press;//16位深565格式
    int default_bgcolor;

    QString default_bgimg_press;//文件所在绝对路径
    QString default_bgimg;

    //是否使用图片
    bool isuseimgbg = false;

    QString qss_bg;
    QString qss_bg_press;
};

#endif // MYBUTTON_H
