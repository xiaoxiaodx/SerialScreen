#include "mdashboard.h"
#include "math.h"
MDashboard::MDashboard()
{

    m_centerX = 400;
    m_centerY = 400;

    maxAngle = 60;
    minAngle = -240;

    m_scaleNumber = 10;
    m_isClockwise = false;

    m_smallRadius = 340;
    m_bigRadius = 360;

    m_firstColor = "#ff0000";
    m_sencondColor = "#00ff00";
    m_thirdColor = "#0000ff";
    m_fontColor = "#aaaaaa";
    m_indicatorColor = "#ffff00";
    m_value = 60;
    m_maxValue = 100;

    m_arcHeight = 5;
    m_scaleW = 4;

}


void MDashboard::draw(QPainter *pt)
{
    drawBg(pt);
    drawIndicator(pt);
}

//以中心为原点，水平正方向为正轴，且X轴为0度，逆时针反向为角度增加的反向
void MDashboard::drawBg(QPainter *painter)
{

    painter->translate(m_centerX,m_centerY);
    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);


    int degreeNum = (maxAngle - minAngle)/3;//每段的弧度数  单位：度
    qreal scaleAngle = (maxAngle - minAngle)/m_scaleNumber;

    QPainterPath circlePath;


    //绘制圆环
    int firstStart = 360- maxAngle;
    QString tmpFirstColor,tmpthirdColor,tmpSecondColor;
    if(m_isClockwise){
        tmpFirstColor = m_firstColor;
        tmpSecondColor = m_sencondColor;
        tmpthirdColor = m_thirdColor;
    }else {
        tmpFirstColor = m_thirdColor;
        tmpSecondColor = m_sencondColor;
        tmpthirdColor = m_firstColor;
    }
    gradientArc(painter,m_bigRadius,firstStart,degreeNum,m_arcHeight,tmpthirdColor);
    gradientArc(painter,m_bigRadius,firstStart + degreeNum,degreeNum,m_arcHeight,tmpSecondColor);
    gradientArc(painter,m_bigRadius,firstStart + degreeNum*2,degreeNum,m_arcHeight,tmpFirstColor);

    //画刻度
    qreal valuePerAngle = m_maxValue/(maxAngle - minAngle);

    for (int deAngle = 0;deAngle<=(maxAngle-minAngle);deAngle+=scaleAngle) {

        int angle ;
        if(m_isClockwise)
            angle = minAngle + deAngle;
        else
            angle = maxAngle - deAngle;

        if(deAngle >= degreeNum*2)
            painter->setPen(QPen(QBrush(QColor(m_thirdColor)),m_scaleW));
        else if(deAngle >= degreeNum)
            painter->setPen(QPen(QBrush(QColor(m_sencondColor)),m_scaleW));
        else if(deAngle >= 0)
            painter->setPen(QPen(QBrush(QColor(m_firstColor)),m_scaleW));

        qreal anglePi = 3.1415926*angle/180;
        qreal x1 = (m_smallRadius)*cos(anglePi);
        qreal y1 = (m_smallRadius)*sin(anglePi);
        qreal x2 = (m_smallRadius-4)*cos(anglePi);
        qreal y2 = (m_smallRadius-4)*sin(anglePi);

        painter->drawLine(QPointF(x1,y1),QPointF(x2,y2));

        int num = deAngle *valuePerAngle;
        QFontMetrics fm(font);
        QRect rect = fm.boundingRect(QString::number(num));
        qreal x3 = (m_smallRadius-20)*cos(anglePi);
        qreal y3 = (m_smallRadius-20)*sin(anglePi);
        painter->setPen(QPen(QBrush(QColor(m_fontColor)),m_scaleW));
        painter->drawText(x3-rect.width()/2,y3+rect.height()/2,QString::number(num));
    }
}


void MDashboard::gradientArc(QPainter *painter, int radius, int startAngle, int angleLength, int arcHeight, QColor color)
{
    // 渐变色
    QRadialGradient gradient(0, 0, radius);
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1.0, color);

    painter->setBrush(gradient);

    // << 1（左移1位）相当于radius*2 即：150*2=300
    //QRectF(-150, -150, 300, 300)
    QRectF rect(-radius, -radius, radius << 1, radius << 1);
    QPainterPath path;
    path.arcTo(rect, startAngle, angleLength);

    // QRectF(-120, -120, 240, 240)
    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));

    // path为扇形 subPath为椭圆
    path -= subPath;

    painter->setPen(Qt::NoPen);
    painter->drawPath(path);
}

void MDashboard::drawIndicator(QPainter *painter)
{
    painter->setBrush(QBrush(QColor(m_indicatorColor)));
    painter->setPen(Qt::NoPen);

    qreal mValueAngle ;
    if(m_isClockwise)
        mValueAngle = minAngle+ (maxAngle-minAngle)*m_value/m_maxValue ;
    else
        mValueAngle = maxAngle - (maxAngle-minAngle)*m_value/m_maxValue ;

    QPainterPath painterPath;


    //三角形3个点 假设为等边
    int triangleLen = 10;//三角形边长
    qreal zhongxianLen = triangleLen*sin(3.1415926*60/180);
    qreal point1X = (triangleLen/2) * sin(3.1415926*mValueAngle/180);
    qreal point1Y = - (triangleLen/2) * cos(3.1415926*mValueAngle/180);

    qreal point2X = - (triangleLen/2) * sin(3.1415926*mValueAngle/180);
    qreal point2Y =  (triangleLen/2) * cos(3.1415926*mValueAngle/180);

    //指示器尾端（短的一端）
    qreal point3X = -zhongxianLen * cos(3.1415926*mValueAngle/180);
    qreal point3Y = -zhongxianLen * sin(3.1415926*mValueAngle/180);

    //指示器尾端（长的一端）
    qreal pointTipX = (m_smallRadius-30) * cos(3.1415926*mValueAngle/180);
    qreal pointTipY = (m_smallRadius-30) * sin(3.1415926*mValueAngle/180);

    painterPath.moveTo(point1X,point1Y);
    painterPath.lineTo(pointTipX,pointTipY);
    painterPath.lineTo(point2X,point2Y);
    painterPath.lineTo(point3X,point3Y);
    painterPath.moveTo(point1X,point1Y);

    painter->drawPath(painterPath);
}
