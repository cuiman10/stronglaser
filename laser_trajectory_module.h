#ifndef LASER_TRAJECTORY_MODULE_H
#define LASER_TRAJECTORY_MODULE_H

#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QTime>

#include "base_public_widget.h"
#include "coordinate_scaling.h"
#include "entitiesdata.h"

class laser_trajectory_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit laser_trajectory_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString&);
    void InitData(void);
    // 绘制导入的dxf数据图形
    void paintDxfTraj(const QList<CM_data_type>&);
   // 设置导入dxf格式数据状态，导入完成， 赋值为真
    void setImportDxfFlag(bool v){ bIsLoadedDxfFlag = v; }
    void frameTraj(double, double, double, double);

protected:
    void paintEvent(QPaintEvent *);

private:
    // private function below
    void refreshPixmap(void);
    // 实际位置与显示位置的映射变换
    void translateData(QPainter*, double, double, double&, double&);
    // 绘制参考标尺
    void drawGrid(QPainter*);
    // 绘制切割轨迹直线
    void paintLine(DL_LineData*, QPainter*, const QColor&);
    // 绘制多段线
    void paintLine(DL_VertexData*, QPainter*, const QColor&);
    // 绘制圆弧
    void paintArc(DL_ArcData*, QPainter*,const QColor&);
    // 绘制圆
    void paintCircle(DL_CircleData*, QPainter*,const QColor&);
    // 绘制点
    void paintPoint(DL_PointData*, QPainter*,const QColor&);
    // 绘制椭圆
    void paintEllipse(DL_EllipseData*, QPainter*,const QColor&);
    // 实时切割轨迹
    void paintCuttingTraj(QPainter*);
    // 激光切割头示意符号
    void paintLaserCutter(QPainter*);
    void zoomIn(void);
    void zoomOut(void);
    void loadAxisValue(void);
    void initScaleList(void);
    void refreshLed(void);


    /*********************************/
    enum {TRAJ_SPACE = 5,
            MARGIN = 40,
            PHOTO_LENGTH = 50,
            TEXT_LENGTH = 80,
            TEXT_HIGHT = 20
         };
    enum {LASER_CUTTER = 10,POINT_SIZE = 5};
    // variants below
    // 已读取完毕dxf文件
    bool bIsLoadedDxfFlag;
    // 加载图文数据提示字符信息
    QString loadingStatusStr;
    // 未加工色料板
    QPalette rawPalette;
    // 已加工色料板
    QPalette ripePalette;
    // 图形缩放比例队列
    QVector<coordinate_scaling> zoomStack;
    int curZoom;
    // current canvas
    QPixmap *canvasPixmap;
    double preX;
    double preY;
    double originalPreX;
    double originalPreY;
    QRect frameRect;

    double prePointX;
    double prePointY;
    double curPointX;
    double curPointY;

    // 用于绘制多段线控制变量
    //bool isPolylineFlag; // 开始绘制多段线标识，true-绘制,false-不绘制
    bool isCloedPolylineFlag; // 该多段线闭合标识，true-闭合，false-不闭合
    bool isFirstPointFlag; // 是否时多段线第一点，第一点保存该点，不绘制
    int polylineVertisePointsNum; // 多段线顶点数,不封闭，线段数=顶点数-1；封闭线段数=顶点数

    // 设备工作状态指示灯控件
    enum {LED_MAX_NUM = 10};
    QLabel *ledLabel[LED_MAX_NUM];
    QLabel *ledNameLabel[LED_MAX_NUM];

signals:

public slots:
};

#endif // LASER_TRAJECTORY_MODULE_H
