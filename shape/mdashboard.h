#ifndef MDASHBOARD_H
#define MDASHBOARD_H
#include "shape/Shape.h"

class MDashboard : public Shape
{
public:
    MDashboard();

    void draw(QPainter *pt) override;

private:

    void drawBg(QPainter *painter);
    void gradientArc(QPainter *painter, int radius, int startAngle, int angleLength, int arcHeight, QColor color);
    void drawIndicator(QPainter *painter);


    float m_centerX;
    float m_centerY;
    float maxAngle;
    float minAngle;
    int m_scaleNumber;
    bool m_isClockwise;

    float m_smallRadius,m_bigRadius;
    QString m_firstColor,m_sencondColor,m_thirdColor,m_indicatorColor,m_fontColor;

    float m_value,m_maxValue;
    float m_arcHeight;
    float m_scaleW;
};

#endif // MDASHBOARD_H
