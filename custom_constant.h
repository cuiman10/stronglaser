#ifndef CUSTOM_CONSTANT_H
#define CUSTOM_CONSTANT_H

enum
{
    SIMPLIFIED_CHINESE = 0,
    CHINESE_TRADITIONAL,
    ENGLISH,
    JAPANESE
};
// 全部图形索引
enum {
    POINT_TYPE = 0,
    LINE_TYPE,
    ARC_TYPE,
    CIRCLE_TYPE,
    ELLIPSE_TYPE,
    TEXT_TYPE,
    DIMANGULAR_TYPE,
    DIMLINEAR_TYPE,
    VERTEX_TYPE,
    POLYLINE_TYPE,
    MTEXT_TYPE,
    HATCH_TYPE,
    HATCH_EDGE_TYPE,
    QSTRING_HATCHCOLOR_TYPE
};
typedef struct{
    /**
     * Constructor.
     * Parameters: see member variables.
     */
    LASER_PARAM_TYPE(int lpower = 0,int lfreq = 0, double lduty = 0) {
        power = lpower;
        freq = lfreq;
        duty = lduty;
    }

    /*! current laser power. */
    int power;
    /*! current laser frequency.*/
    int freq;
    /*! current laser dutyfactor. */
    double duty;

}LASER_PARAM_GRP;

#define MAX_AXIS_NUMBER 8

typedef struct
{
    // axis command postion
    double axisCmdPostion;
    // axis actual postion
    double axisActPostion;
    // axis velocity
    double cmdVel;
    double actVel;
    double followErr;

    // 状态位标识0000 0000 从右到左，正限位，负限位，，使能，回零点，清零
    // 0000 0001 正限位
    // 0000 0010 负限位
    // 0000 0100 轴使能
    // 0000 1000 回零点
    // 0001 0000 清零
    // 0010 0000
    // 0100 0000
    // 1000 0000
    unsigned char statusFlag;
    // 轴类型，0-直线轴，1-旋转轴
    int type;

}AXIS_TYPE;
// 激光参数类型
typedef struct
{
    // 激光功率
    double power;
    // 激光频率
    int frequence;
    // 占空比
    double ocupy;

}LASER_STATUS_TYPE;
// 视觉参数类型
typedef struct
{
    //定位状态，0-空闲 1-正在定位
    int positonStat;
    /// axis x 定位点
    double px;
    // axis y 定位点
    double py;
    // 是否已标定
    bool markFlag;

}VISION_STATUS_TYPE;
// 轴参数类型
typedef struct{

    /*! Axis cmd positon array. */
    AXIS_TYPE axisStat[MAX_AXIS_NUMBER];
    /*!system had ready.*/
    int sysReady;

}MOTION_STATUS_GRP;
typedef struct
{
    // 报警号
    int index;
    // 报警类型
    int type;

}ALARM_TYPE;
typedef struct
{
    AXIS_TYPE axisCmd[MAX_AXIS_NUMBER];
    int jok;

}MOTION_CMD_TYPE;

#define LABEL_TEXT_COLOR_BLACK QPalette::WindowText,QColor(33,40,48)
#define LABEL_TEXT_COLOR_YELLOW QPalette::WindowText,Qt::yellow
#define LABEL_TEXT_COLOR_RED QPalette::WindowText,QColor(222,0,0)
#define LABEL_TEXT_COLOR_BLUE QPalette::WindowText,QColor(0,0,127)
#define LABEL_TEXT_COLOR_GREEN QPalette::WindowText,QColor(0,188,0)
#define WIDGET_WINDOW_COLOR_BLUE QPalette::Window,QColor(0,64,128)
#define WIDGET_WINDOW_COLOR_GREEN QPalette::Window,QColor(0,188,0)
#define WIDGET_WINDOW_COLOR_BLACK QPalette::Window,QColor(33,40,48)

#define CM_COLOR_BLACK QColor(33,40,48)
//#define CM_COLOR_BLACK2 QColor(46,47,48)
#define CM_COLOR_WHITE QColor(190,192,194)
#define CM_COLOR_DEEPBLUE QColor(51,57,73)
#define CM_COLOR_DARKBLUE QColor(43,43,62)
#define CM_COLOR_DEEPGREEN QColor(35,110,38)
#define CM_COLOR_DARKRED QColor(109,36,38)

#define FRAME_SUNKEN_STYLE QFrame::Sunken|QFrame::Panel
#define FRAME_RAISED_STYLE QFrame::Raised|QFrame::Panel
#define FRAME_BOX_SUNKEN_STYLE QFrame::Sunken|QFrame::Box
#define FRAME_BOX_SRAISED_STYLE QFrame::Raised|QFrame::Box

#define TIMESFONT_BOLT(x) "Times",(x),QFont::Bold
#define TIMESFONT_NORMAL(x) "Times",(x),QFont::Normal
#define HMI_COMMON_FONT_SIZE_6 "Times",6,QFont::Normal
#define HMI_COMMON_FONT_SIZE_8 "Times",8,QFont::Normal
#define HMI_COMMON_FONT_SIZE_10 "Times",10,QFont::Normal
#define HMI_COMMON_FONT_SIZE_12 "Times",12,QFont::Normal
#define HMI_COMMON_FONT_SIZE_16 "Times",16,QFont::Normal

#define LINE_WIDTH_NORMAL 1
#define LINE_WIDTH_WIDEN 2
#define HMI_SCREEN_WIDTH 1280
#define HMI_SCREEN_HEIGH 1024
#define HMI_COMMON_HEIGH25 25
#define HMI_COMMON_WIDTH100 100
#define AXIS_MODULE_WIDTH 600
#define AXIS_MODULE_HEIGH 95
#define SEMICIRCLE_DEGREES 180
#define DEGREE_FACTOR 16

/*!机床幅面初始值，以后可在参数中设置*/
#define WORKING_AREA_MAX_X 600
#define WORKING_AREA_MAX_Y 660

#endif // CUSTOM_CONSTANT_H
