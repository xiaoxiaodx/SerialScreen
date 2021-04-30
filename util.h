#ifndef UTIL_H
#define UTIL_H

#include <QColor>
//对齐方式
#define ALIGN_TYPE_LEFT_TOP 0
#define ALIGN_TYPE_CENTER_TOP 1
#define ALIGN_TYPE_RIGHT_TOP 2
#define ALIGN_TYPE_LEFT_CENTER 4
#define ALIGN_TYPE_CENTER_CENTER 5
#define ALIGN_TYPE_RIGHT_CENTER 6
#define ALIGN_TYPE_LEFT_BOTTOM 8
#define ALIGN_TYPE_CENTER_BOTTOM 9
#define ALIGN_TYPE_RIGHT_BOTTOM 10


QColor parse565(int rgb565value){

    float r_565 = (rgb565value>>11) & 0x0000001f;
    float g_565 = (rgb565value>>5) & 0x0000003f;
    float b_565 = (rgb565value) & 0x0000001f;


    float percentage_r = r_565 / (1*16 + 15);
    float percentage_g = g_565 / (3*16 + 15);
    float percentage_b = b_565 / (1*16 + 15);

    return QColor(255*percentage_r,255*percentage_g,255*percentage_b);
}



#endif // UTIL_H
