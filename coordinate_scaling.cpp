/*!This class function is coordinate scaling for edit draw CAD*/
#include "coordinate_scaling.h"

coordinate_scaling::coordinate_scaling()
{
    // 方形显示区域
    // 最小最大x轴值，用于显示幅面
    minX = 0;
    maxX = WORKING_AREA_MAX_X;
    // 最小最大y轴值，用于显示幅面
    minY = 0;
    maxY = WORKING_AREA_MAX_X;
}
/*！平移系数计算*/
void coordinate_scaling::setScroll(int dx, int dy)
{
    double stepX = getSpanXY()/TICKS_XY_LEVEL;
    minX += dx * stepX;
    maxX += dx * stepX;

    double stepY = getSpanXY()/TICKS_XY_LEVEL;
    minY += dy * stepY;
    maxY += dy * stepY;
}
void coordinate_scaling::setLimitXY(double x1,double y1,double x2,double y2)
{
    // 以长度长的为基准
    if((x2 - x1) < (y2 - y1))
    {
        minX = x1;
        maxX = x1 + (y2 - y1);

        minY = y1;
        maxY = y2;
    }
    else
    {

        minX = x1;
        maxX = x2;

        minY = y1;
        maxY = y1 + (x2 - x1);
    }

}

