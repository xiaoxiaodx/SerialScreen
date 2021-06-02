#include "mygraph.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>
MyGraph::MyGraph(int id,QString name):mid(id),mname(name)
{
setObjectName(name);

    qDebug()<<"MyGraph";

    // 随机生成曲线第一条曲线的坐标
//    int x = 0, y = 0;
//    for (int i = 0; i < 10; ++i) {
//        x += qrand() % 30 + 20;
//        y = qrand() % 180 + 30;

//        //listpt1 <<x<<y;

//        addPoint(1,QPointF(x,y));
//    }

//    // 第二条星行曲线的坐标
//    listpt2 << QPointF(0, 150) << QPointF(50, 50) << QPointF(150, 0) << QPointF(50, -50)
//            << QPointF(0, -150) << QPointF(-50, -50) << QPointF(-150, 0) << QPointF(-50, 50);

//    smoothCurvePath1 = generateSmoothCurve(listpt1); // 第一条曲线不封闭
//    smoothCurvePath2 = generateSmoothCurve(listpt2, true); // 第二条曲线是封闭的
}


void MyGraph::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);


    drawBacgroud(&painter);

    drawGrid(&painter);
    drawCurve(&painter);


    //绘制点
    painter.setBrush(Qt::gray);
    for (int i = 0; i < listpt1.length() ; i += 2) {
        painter.drawEllipse(listpt1[i]-3, listpt1[i+1]-3, 6, 6);
    }
    for (int i = 0; i < listpt2.length() ; i += 2) {
        painter.drawEllipse(listpt2[i]-3, listpt2[i+1]-3, 6, 6);
    }
    for (int i = 0; i < listpt3.length() ; i += 2) {
        painter.drawEllipse(listpt3[i]-3, listpt3[i+1]-3, 6, 6);
    }
    for (int i = 0; i < listpt4.length() ; i += 2) {
        painter.drawEllipse(listpt4[i]-3, listpt4[i+1]-3, 6, 6);
    }

}
void MyGraph::drawBacgroud(QPainter *pt)
{

    pt->save();
    pt->setPen(Qt::NoPen);

    if(isuseimg){

        if(bgimg == nullptr)
            bgimg = new QImage(imgpath);
        pt->drawImage(rect(),*bgimg);

    }else{
        pt->setBrush(bgcolor);
        pt->drawRect(rect());
    }

    pt->restore();

}

void MyGraph::drawGrid(QPainter* pt)
{

    pt->save();
    pt->setPen(QPen(gridColor,2));


    //画竖线
    for (int i=0;i<width();i+=gridw) {

        pt->drawLine(i,0,i,height());

    }
    //画横线
    for (int i=0;i<height();i+=gridh) {

        pt->drawLine(0,i,width(),i);

    }

    pt->restore();


}


void MyGraph::drawCurve(QPainter*painter)
{

    painter->save();
    painter->setPen(QPen(color1, 2));
    painter->drawPath(smoothCurvePath1);

    painter->setPen(QPen(color2, 2));
    painter->drawPath(smoothCurvePath2);

    painter->setPen(QPen(color3, 2));
    painter->drawPath(smoothCurvePath3);

    painter->setPen(QPen(color4, 2));
    painter->drawPath(smoothCurvePath4);
    painter->restore();

}

void MyGraph::delCurve(int channel)
{
    switch(channel) {
    case 0:
        listpt1.clear();
        break;
    case 1:
        listpt2.clear();
        break;
    case 2:
        listpt3.clear();
        break;
    case 3:
        listpt4.clear();
        break;
    }
}

void MyGraph::addPoint(int channle,float data)
{
    int size = 0;
    switch(channle) {
    case 0:
        size = listpt1.size();
        break;
    case 1:
        size = listpt2.size();
        break;
    case 2:
        size = listpt3.size();
        break;
    case 3:
        size = listpt4.size();
        break;
    }

    addPoint(channle,QPointF(size,data));
}

void MyGraph::addPoint(int channle,QPointF pt){
    smoothPoint(channle,pt);
}

void MyGraph::smoothPoint(int channle,QPointF pt){


    double tension = 0.5;
    int numberOfSegments = 16;
    double x, y;
    double t1x, t2x, t1y, t2y;
    double c1, c2, c3, c4;
    double st;

    QPainterPath *path;
    QList<double> *tmpps;
    switch(channle) {
    case 0:
        tmpps = &listpt1;
        path = &smoothCurvePath1;
        break;
    case 1:
        tmpps = &listpt1;
        path = &smoothCurvePath1;
        break;
    case 2:
        tmpps = &listpt2;
        path = &smoothCurvePath2;
        break;
    case 3:
        tmpps = &listpt3;
        path = &smoothCurvePath3;
        break;
    case 4:
        tmpps = &listpt4;
        path = &smoothCurvePath4;
        break;
    }

    if(tmpps->size() == 0){
        path->moveTo(pt);
        tmpps->append(pt.x());
        tmpps->append(pt.y());
    }
    tmpps->append(pt.x());
    tmpps->append(pt.y());

    qDebug()<<"ps:"<<tmpps->size();
    if(tmpps->size() < 8){
        return;
    }

    qDebug()<<"ps1:"<<tmpps->size();
    //int i = tmpps->size()-5;
    QList<double> ps;

    for(int i=tmpps->size()-8;i<tmpps->size();i++){
        ps.append(tmpps->at(i));
    }
    int i=2;
    // calculate tension vectors
    t1x = (ps[i + 2] - ps[i - 2]) * tension;
    t2x = (ps[i + 4] - ps[i - 0]) * tension;
    t1y = (ps[i + 3] - ps[i - 1]) * tension;
    t2y = (ps[i + 5] - ps[i + 1]) * tension;

    for (int t = 0; t <= numberOfSegments; t++) {
        // calculate step
        st = (double)t / (double)numberOfSegments;

        // calculate cardinals
        c1 =  2 * qPow(st, 3) - 3 * qPow(st, 2) + 1;
        c2 = -2 * qPow(st, 3) + 3 * qPow(st, 2);
        c3 = qPow(st, 3) - 2 * qPow(st, 2) + st;
        c4 = qPow(st, 3) - qPow(st, 2);

        // calculate x and y cords with common control vectors
        x = c1 * ps[i] + c2 * ps[i + 2] + c3 * t1x + c4 * t2x;
        y = c1 * ps[i + 1] + c2 * ps[i + 3] + c3 * t1y + c4 * t2y;

        //store points in array
       // result << x << y;

        path->lineTo(x, y);

    }

    // 使用的平滑曲线的坐标创建 QPainterPath
//    QPainterPath path;
//    path.moveTo(result[0], result[1]);
//    for (int i = 2; i < result.length() - 2; i += 2) {
//        path.lineTo(result[i+0], result[i+1]);
//    }
}



QPainterPath MyGraph::generateSmoothCurve(QList<QPointF> points, bool closed, double tension, int numberOfSegments) {
    QList<double> ps;

    foreach (QPointF p, points) {
        ps << p.x() << p.y();
    }

    return generateSmoothCurve(ps, closed, tension, numberOfSegments);
}

QPainterPath MyGraph::generateSmoothCurve(QList<double> points, bool closed, double tension, int numberOfSegments) {
    QList<double> ps(points); // clone array so we don't change the original points
    QList<double> result; // generated smooth curve coordinates
    double x, y;
    double t1x, t2x, t1y, t2y;
    double c1, c2, c3, c4;
    double st;

    // The algorithm require a previous and next point to the actual point array.
    // Check if we will draw closed or open curve.
    // If closed, copy end points to beginning and first points to end
    // If open, duplicate first points to befinning, end points to end
    if (closed) {
        ps.prepend(points[points.length() - 1]);
        ps.prepend(points[points.length() - 2]);
        ps.prepend(points[points.length() - 1]);
        ps.prepend(points[points.length() - 2]);
        ps.append(points[0]);
        ps.append(points[1]);
    } else {
        ps.prepend(points[1]); // copy 1st point and insert at beginning
        ps.prepend(points[0]);
        ps.append(points[points.length() - 2]); // copy last point and append
        ps.append(points[points.length() - 1]);
    }

    // 1. loop goes through point array
    // 2. loop goes through each segment between the 2 points + 1e point before and after
    for (int i = 2; i < (ps.length() - 4); i += 2) {
        // calculate tension vectors
        t1x = (ps[i + 2] - ps[i - 2]) * tension;
        t2x = (ps[i + 4] - ps[i - 0]) * tension;
        t1y = (ps[i + 3] - ps[i - 1]) * tension;
        t2y = (ps[i + 5] - ps[i + 1]) * tension;

        for (int t = 0; t <= numberOfSegments; t++) {
            // calculate step
            st = (double)t / (double)numberOfSegments;

            // calculate cardinals
            c1 =  2 * qPow(st, 3) - 3 * qPow(st, 2) + 1;
            c2 = -2 * qPow(st, 3) + 3 * qPow(st, 2);
            c3 = qPow(st, 3) - 2 * qPow(st, 2) + st;
            c4 = qPow(st, 3) - qPow(st, 2);

            // calculate x and y cords with common control vectors
            x = c1 * ps[i] + c2 * ps[i + 2] + c3 * t1x + c4 * t2x;
            y = c1 * ps[i + 1] + c2 * ps[i + 3] + c3 * t1y + c4 * t2y;

            //store points in array
            result << x << y;
        }
    }

    // 使用的平滑曲线的坐标创建 QPainterPath
    QPainterPath path;
    path.moveTo(result[0], result[1]);
    for (int i = 2; i < result.length() - 2; i += 2) {
        path.lineTo(result[i+0], result[i+1]);
    }

    if (closed) {
        path.closeSubpath();
    }

    return path;
}
