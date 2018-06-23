#ifndef COORDINATE_SCALING_H
#define COORDINATE_SCALING_H

#include <custom_constant.h>

class coordinate_scaling
{
public:
    coordinate_scaling();

    // setting axis x and y offset fucntion
    void setScroll(int dx, int dy);
    // set axis x and y limit value to define the working area
    void setLimitXY(double,double,double,double);
    // get scaling factor functions below
    // 获取跨度值，实际上X轴的跨度也是Y轴的跨度,如果以后X轴和Y轴不是方形,就需要换算比例系数
    double getSpanXY(void) const { return maxX - minX; }
    int getNumXYTicks(void) const { return TICKS_XY_LEVEL; }
    double getMinX(void) const { return minX; }
    double getMinY(void) const { return minY; }
    double getMaxX(void) const { return maxX; }
    double getMaxY(void) const { return maxY; }

private:
    enum {TICKS_XY_LEVEL = 10};
    double minX;
    double maxX;
    double minY;
    double maxY;

};

#endif // COORDINATE_SCALING_H
