#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <QWidget>

class MyGraph : public QWidget
{
    Q_OBJECT
public:
    explicit MyGraph(int id,QString name);


    void addPoint(int channle,float data);
    void addPoint(int channle,QPointF pt);
    void smoothPoint(int channle,QPointF pt);
    void delCurve(int channel);
    bool isuseimg;
    //0左到右  1右到左
    int flushdirection;

    int mid;
    QString mname;
    QString imgpath;
    QImage *bgimg = nullptr;
    QColor bgcolor;
    QColor gridColor;
    int gridw;
    int gridh;
    int scalew;//水平刻度
    int scaleh;//垂直刻度
    QColor color1;
    QColor color2;
    QColor color3;
    QColor color4;


protected:
    void paintEvent(QPaintEvent *event);
signals:


private:
    QPainterPath generateSmoothCurve(QList<QPointF> points, bool closed = false, double tension = 0.5, int numberOfSegments = 16);

       /**
        * @brief 使用传入的曲线顶点坐标创建平滑曲线。
        *
        * @param points 曲线顶点坐标数组，
        *               points[i+0] 是第 i 个点的 x 坐标，
        *               points[i+1] 是第 i 个点的 y 坐标
        * @param closed 曲线是否封闭，默认不封闭
        * @param tension 密集程度，默认为 0.5
        * @param numberOfSegments 平滑曲线 2 个顶点间的线段数，默认为 16
        * @return 平滑曲线的 QPainterPath
        */
    QPainterPath generateSmoothCurve(QList<double>points, bool closed = false, double tension = 0.5, int numberOfSegments = 16);

    void drawBacgroud(QPainter*);
    void drawGrid(QPainter*);
    void drawCurve(QPainter*);


    QList<double> listpt1;
    QList<double> listpt2;
    QList<double> listpt3;
    QList<double> listpt4;

    QPainterPath smoothCurvePath1,smoothCurvePath2,smoothCurvePath3,smoothCurvePath4;

};

#endif // MYGRAPH_H
