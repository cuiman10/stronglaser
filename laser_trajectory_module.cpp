#include "laser_trajectory_module.h"

laser_trajectory_module::laser_trajectory_module(QWidget *parent)
    : base_public_widget(parent)
{
    // Init cad editor module data

    resize(WORKING_AREA_MAX_X,WORKING_AREA_MAX_Y);
    // 注意，此处不是马虎，是定义画布定义为X和Y方向一样，为方形
    canvasPixmap = new QPixmap(WORKING_AREA_MAX_X,WORKING_AREA_MAX_X);
    canvasPixmap->fill(CM_COLOR_BLACK);

    InitData();
    initScaleList();
    //refreshPixmap();

    // 未加工图形颜色
    rawPalette = palette();
    rawPalette.setColor(QPalette::Text,Qt::green);
    rawPalette.setColor(QPalette::Window,CM_COLOR_BLACK);

    // 已加工图形颜色
    ripePalette = palette();
    ripePalette.setColor(QPalette::Text,Qt::darkYellow);
    ripePalette.setColor(QPalette::Window,CM_COLOR_BLACK);

    QPalette deepGreenPalette = palette();
    deepGreenPalette.setColor(QPalette::Text,Qt::darkGreen);
    deepGreenPalette.setColor(QPalette::Window,CM_COLOR_BLACK);

    QPalette labelPalette = palette();
    labelPalette.setColor(QPalette::WindowText,CM_COLOR_WHITE);
    labelPalette.setColor(QPalette::Window,CM_COLOR_BLACK);

    for(int i = 0; i < LED_MAX_NUM; i++)
    {
        ledLabel[i] = new QLabel(this);
        ledLabel[i]->setGeometry(15 + i*60,600,30,30);
        ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
        ledLabel[i]->setScaledContents(true);
        ledLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //ledLabel[i]->setAutoFillBackground(true);


        ledNameLabel[i] = new QLabel(this);
        ledNameLabel[i]->setGeometry(i*60,630,60,30);
        ledNameLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_10));
        ledNameLabel[i]->setPalette(labelPalette);
        ledNameLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //ledNameLabel[i]->setAutoFillBackground(true);

    }
    ledNameLabel[0]->setText(tr("光闸"));
    ledNameLabel[1]->setText(tr("红光"));
    ledNameLabel[2]->setText(tr("激光"));
    ledNameLabel[3]->setText(tr("跟随"));
    ledNameLabel[4]->setText(tr("吹气"));
    ledNameLabel[5]->setText(tr("空气"));
    ledNameLabel[6]->setText(tr("其他"));
    ledNameLabel[7]->setText(tr("其他"));
    ledNameLabel[8]->setText(tr("其他"));
    ledNameLabel[9]->setText(tr("其他"));

    setPalette(rawPalette);
    //setAutoFillBackground(true);

}
void laser_trajectory_module::UpdateData(void)
{
    refreshLed();
}
void laser_trajectory_module::Respond_operate(int, bool)
{

}
void laser_trajectory_module::Refresh_button_text(int, const QString&)
{

}
void laser_trajectory_module::InitData(void)
{
    // Init all variants
    // 是否已经读取加载完毕dxf数据
    bIsLoadedDxfFlag = false;
    // 在没有获取当前轴位置时，初始化x，y轴位置为0
    preX = motionStatPtr->axisStat[0].axisCmdPostion;
    preY = motionStatPtr->axisStat[2].axisCmdPostion;
    originalPreX = motionStatPtr->axisStat[0].axisCmdPostion;
    originalPreY = motionStatPtr->axisStat[2].axisCmdPostion;

}
void laser_trajectory_module::initScaleList(void)
{
    prePointX = motionStatPtr->axisStat[0].axisCmdPostion;
    prePointY = motionStatPtr->axisStat[2].axisCmdPostion;
    curPointX = motionStatPtr->axisStat[0].axisCmdPostion;
    curPointY = motionStatPtr->axisStat[2].axisCmdPostion;
    // 当前使用的缩放组为0
    //isPolylineFlag = false; // 开始绘制多段线标识，true-绘制,false-不绘制
    isCloedPolylineFlag = false; // 该多段线闭合标识，true-闭合，false-不闭合
    isFirstPointFlag = false; // 是否时多段线第一点，第一点保存该点，不绘制
    polylineVertisePointsNum = 0; // 初始无多段线
    // 情况初始化缩放系数队列
    zoomStack.clear();
    coordinate_scaling initScaling;
    // 坐标显示和绘图区域一直，长款相等
    initScaling.setLimitXY(0,0,WORKING_AREA_MAX_X,WORKING_AREA_MAX_X);
    zoomStack.append(initScaling);
    curZoom = 0;
    refreshPixmap();

}

void laser_trajectory_module::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, *canvasPixmap);
    paintCuttingTraj(&painter);
    paintLaserCutter(&painter);
}
void laser_trajectory_module::refreshPixmap(void)
{
    if(nullptr != canvasPixmap)
    {
        delete canvasPixmap;
        canvasPixmap = nullptr;
    }

    canvasPixmap = new QPixmap(WORKING_AREA_MAX_X,WORKING_AREA_MAX_X);
    canvasPixmap->fill(CM_COLOR_BLACK);

    QPainter painter(canvasPixmap);
    painter.initFrom(this);

    drawGrid(&painter);

    preX = originalPreX;
    preY = originalPreY;

    update();

}
void laser_trajectory_module::drawGrid(QPainter *painter)
{
    //qDebug()<<"[drawGrid]--width()="<<width()<<"height()"<<height();
    QRect rect(MARGIN, MARGIN,WORKING_AREA_MAX_X - 2*MARGIN, WORKING_AREA_MAX_X - 2*MARGIN);
    if (!rect.isValid())
    {
        qDebug()<<"[HMI]--Creat drawGrid rect failure!";
        return;
    }

    // get current canvas scaling factor
    coordinate_scaling settings = zoomStack[curZoom];

    for (int i = 0; i <= settings.getNumXYTicks(); ++i)
    {
        int x = rect.left() + (i*(rect.width() - 1)/settings.getNumXYTicks());// 画布上每个刻度的横轴像素点值
        double label = settings.getMinX() + (i*settings.getSpanXY()/settings.getNumXYTicks());// 每个刻度的X坐标值
        painter->setPen(QPen(CM_COLOR_DEEPBLUE, 1, Qt::SolidLine, Qt::RoundCap));
        painter->drawLine(x, rect.bottom(), x, rect.top());
        painter->setPen(QPen(CM_COLOR_WHITE, 1, Qt::SolidLine, Qt::RoundCap));
        painter->drawText(x - 50, rect.bottom() + 5, 100, 20,
                          Qt::AlignHCenter|Qt::AlignTop,
                          QString::number(int(label)));

        if(i < settings.getNumXYTicks())
        {
            int unitWidth = ((rect.width() - 1)/settings.getNumXYTicks())/5;
            painter->setPen(QPen(CM_COLOR_DARKBLUE, 1, Qt::SolidLine, Qt::RoundCap));
            for (int p = 0; p < 4; ++p)
            {
                // 将每个格子细分为5份
                painter->drawLine(x + 1 + (p+1)*unitWidth, rect.bottom(), x + (p+1)*unitWidth, rect.top());
            }
        }

    }

    for (int j = 0; j <= settings.getNumXYTicks(); ++j)
    {
        int y = rect.bottom() - (j*(rect.height() - 1)/settings.getNumXYTicks());// 画布上每个刻度的纵轴像素点值
        double label = settings.getMinY() + (j * settings.getSpanXY()/settings.getNumXYTicks());// 每个刻度的Y坐标值
        painter->setPen(QPen(CM_COLOR_DEEPBLUE, 1, Qt::SolidLine, Qt::RoundCap));
        painter->drawLine(rect.right(), y, rect.left(), y);
        painter->setPen(QPen(CM_COLOR_WHITE, 1, Qt::SolidLine, Qt::RoundCap));
        painter->drawText(rect.left() - MARGIN, y - 10, MARGIN - 5, 20,
                          Qt::AlignRight|Qt::AlignVCenter,
                          QString::number(int(label)));

        if(j < settings.getNumXYTicks())
        {
            int unitHeight = ((rect.height() - 1)/settings.getNumXYTicks())/5;
            painter->setPen(QPen(CM_COLOR_DARKBLUE, 1, Qt::SolidLine, Qt::RoundCap));
            for (int p = 0; p < 4; ++p)
            {
                // 将每个格子细分为5份
                painter->drawLine(rect.right(), y - 1 - (p+1)*unitHeight, rect.left(), y - (p+1)*unitHeight);
            }
        }

    }

    //painter->drawRect(rect.adjusted(0, 0, -1, -1));
    // draw Axis X name and Axis Y
    // x
    painter->setPen(CM_COLOR_DARKRED);
    painter->drawText(rect.right()+10,rect.bottom()-10 + 1,20,20,Qt::AlignLeft|Qt::AlignHCenter,"X");
    painter->drawLine(rect.left(), rect.bottom(), rect.right() + 10, rect.bottom());

    // y
    painter->setPen(CM_COLOR_DEEPGREEN);
    painter->drawText(rect.left()-10 + 1,rect.top()-30,20,20,Qt::AlignLeft|Qt::AlignHCenter,"Y");
    painter->drawLine(rect.left(), rect.top() - 10, rect.left(), rect.bottom());

    //show the explain
    /*
    painter->setPen(Qt::yellow);
    painter->drawLine(rect.left(), rect.bottom()+40, rect.left()+PHOTO_LENGTH, rect.bottom()+40);
    painter->drawText(rect.left() + PHOTO_LENGTH + TRAJ_SPACE,rect.bottom()+30,TEXT_LENGTH,TEXT_HIGHT,
                       Qt::AlignLeft | Qt::AlignHCenter,"快移");
    painter->setPen(Qt::green);
    painter->drawLine(rect.left() + PHOTO_LENGTH + TEXT_LENGTH + 2*TRAJ_SPACE, rect.bottom()+40,
                      rect.left() + 2*PHOTO_LENGTH + TEXT_LENGTH + 2*TRAJ_SPACE, rect.bottom()+40);
    painter->drawText(rect.left() + 2*PHOTO_LENGTH + TEXT_LENGTH + 3*TRAJ_SPACE,rect.bottom()+30,TEXT_LENGTH,TEXT_HIGHT,
                       Qt::AlignLeft | Qt::AlignHCenter,"进给");
    // laser_cutting position
    painter->setPen(Qt::red);
    painter->drawLine(rect.left() + 2*PHOTO_LENGTH + 2*TEXT_LENGTH + 4*TRAJ_SPACE, rect.bottom()+40,
                      rect.left() + 3*PHOTO_LENGTH + 2*TEXT_LENGTH + 4*TRAJ_SPACE, rect.bottom()+40);
    painter->drawText(rect.left() + 3*PHOTO_LENGTH + 2*TEXT_LENGTH + 5*TRAJ_SPACE, rect.bottom()+30,TEXT_LENGTH,TEXT_HIGHT,
                       Qt::AlignLeft | Qt::AlignHCenter,"切割");

    painter->setPen(Qt::cyan);
    painter->drawLine(rect.left() + 3*PHOTO_LENGTH + 3*TEXT_LENGTH + 6*TRAJ_SPACE, rect.bottom()+40,
                      rect.left() + 4*PHOTO_LENGTH + 3*TEXT_LENGTH + 6*TRAJ_SPACE, rect.bottom()+40);
    painter->drawText(rect.left() + 4*PHOTO_LENGTH + 3*TEXT_LENGTH + 7*TRAJ_SPACE, rect.bottom()+30,TEXT_LENGTH,TEXT_HIGHT,
                       Qt::AlignLeft | Qt::AlignHCenter,tr("未切割"));

    */

}
// 绘制导入的dxf格式文件，即切割轮廓
void laser_trajectory_module::paintDxfTraj(const QList<CM_data_type> &dxfT)
{

    QPainter painter(canvasPixmap);
    for(int i = 0; i < dxfT.length(); i++)
    {
        switch (dxfT[i].type) {
        case POINT_TYPE:
            paintPoint((DL_PointData*)(dxfT[i].cmPtr), &painter, Qt::yellow);
            break;
        case LINE_TYPE:
            paintLine((DL_LineData*)(dxfT[i].cmPtr), &painter, Qt::green);
            break;
        case ARC_TYPE:
            paintArc((DL_ArcData*)(dxfT[i].cmPtr), &painter,Qt::green);
            break;
        case CIRCLE_TYPE:
            paintCircle((DL_CircleData*)(dxfT[i].cmPtr), &painter,Qt::green);
            break;
        case ELLIPSE_TYPE:
            paintEllipse((DL_EllipseData*)(dxfT[i].cmPtr), &painter,Qt::green);
            break;
        case TEXT_TYPE:

            break;
        case DIMANGULAR_TYPE:

            break;
        case DIMLINEAR_TYPE:

            break;
        case VERTEX_TYPE:
            paintLine((DL_VertexData*)(dxfT[i].cmPtr), &painter, Qt::green);
            break;
        case POLYLINE_TYPE:
            // 启动绘制多段线标识
            //isPolylineFlag = true;
            isFirstPointFlag = true;
            if(1 == ((DL_PolylineData*)(dxfT[i].cmPtr))->flags)
            {
                // flag=1为多段线封闭标识
                isCloedPolylineFlag = true;
            }
            else
            {
                isCloedPolylineFlag = false;
            }
            polylineVertisePointsNum = ((DL_PolylineData*)(dxfT[i].cmPtr))->number;
            break;
        case MTEXT_TYPE:

            break;
        case HATCH_TYPE:

            break;
        case HATCH_EDGE_TYPE:

            break;
        case QSTRING_HATCHCOLOR_TYPE:

            break;
        default:
            break;
        }
    }
}
// 转换位置数据
void laser_trajectory_module::translateData(QPainter *painter, double inx, double iny,double &outx, double &outy)
{
    // 位置变换，不是长度变换，全部转换为位置后，再换算回去
    coordinate_scaling settings = zoomStack[curZoom];
    QRect rect(MARGIN, MARGIN, WORKING_AREA_MAX_X - 2*MARGIN, WORKING_AREA_MAX_X - 2*MARGIN);
    if (!rect.isValid())
    {
        qDebug()<<"[HMI]--Laser_trajectory_module translateData error!";
        return;
    }
    painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

    double dx = inx - settings.getMinX();
    double dy = iny - settings.getMinY();

    outx = rect.left() + (dx*(rect.width() - 1)/settings.getSpanXY());
    outy = rect.bottom() - (dy*(rect.height() - 1)/settings.getSpanXY());
}
// 绘制切割轨迹直线
void laser_trajectory_module::paintLine(DL_LineData *dataPtr, QPainter *painter, const QColor &color)
{
    double s_prex, s_prey, s_x, s_y;    //screen x and y
    translateData(painter, dataPtr->x1, dataPtr->y1, s_prex, s_prey);
    translateData(painter, dataPtr->x2, dataPtr->y2, s_x, s_y);

    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(s_prex, s_prey, s_x, s_y);
    painter->setRenderHint(QPainter::Antialiasing, true);
}
// 绘制多段线
void laser_trajectory_module::paintLine(DL_VertexData *dataPtr, QPainter *painter, const QColor &color)
{
    // 定义多段线第一点和上一点
    static double firstPolyX, firstPolyY, prePolyX, proPolyY;
    double s_prex, s_prey, s_x, s_y;    //screen x and y
    // 调用一次绘制多段线函数，顶点数减少1
    if(polylineVertisePointsNum > 0)
    {
        polylineVertisePointsNum--;
    }
    else
    {
        return;
    }

    // 如果时第一次调用，则记录第一点位置后返回
    if(isFirstPointFlag)
    {
        firstPolyX = dataPtr->x;
        firstPolyY = dataPtr->y;
        prePolyX = dataPtr->x;
        proPolyY = dataPtr->y;
        isFirstPointFlag = !isFirstPointFlag;
        return;
    }

    translateData(painter, prePolyX, proPolyY, s_prex, s_prey);
    translateData(painter, dataPtr->x, dataPtr->y, s_x, s_y);

    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(s_prex, s_prey, s_x, s_y);
    painter->setRenderHint(QPainter::Antialiasing, true);

    prePolyX = dataPtr->x;
    proPolyY = dataPtr->y;

    // 如果该多段线时封闭的，到最后一点时，与第一点连线
    if(isCloedPolylineFlag && (0 == polylineVertisePointsNum))
    {
        translateData(painter, prePolyX, proPolyY, s_prex, s_prey);
        translateData(painter, firstPolyX, firstPolyY, s_x, s_y);

        painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap));
        painter->drawLine(s_prex, s_prey, s_x, s_y);
        painter->setRenderHint(QPainter::Antialiasing, true);
    }

}
// 绘制圆弧
void laser_trajectory_module::paintArc(DL_ArcData *dataPtr, QPainter *painter,const QColor &color)
{
    // calculate radius in tool coordinate
    double radius = dataPtr->radius;
    // calculate start angle and span angle
    double angle1 = dataPtr->angle1;
    double angle2 = dataPtr->angle2;
    double startAngle = angle1*DEGREE_FACTOR;
    double spanAngle = 0;
    if((angle2 - angle1)<0)
    {
        spanAngle = (angle2 - angle1 + 360)*DEGREE_FACTOR;
    }
    else
    {
        spanAngle = (angle2 - angle1)*DEGREE_FACTOR;
    }
    qDebug()<<"[laser_trajectory_module::paintArc](startangel,endangel)";
    qDebug()<<angle1;
    qDebug()<<angle2;


    // get left-top screen coordinate and right-bottom screen coordinate
    double topleftX = dataPtr->cx - radius;
    double topleftY = dataPtr->cy - radius;
    double bottomrightX = dataPtr->cx + radius;
    double bottomrightY = dataPtr->cy + radius;

    double stlx, stly, sbrx, sbry;
    translateData(painter, topleftX, topleftY, stlx, stly);
    translateData(painter, bottomrightX, bottomrightY, sbrx, sbry);

    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(stlx,  stly, sbrx - stlx, sbry - stly, startAngle, spanAngle);
    painter->setRenderHint(QPainter::Antialiasing, true);

}
// 绘制圆
void laser_trajectory_module::paintCircle(DL_CircleData *dataPtr, QPainter *painter,const QColor &color)
{
    // calculate radius in tool coordinate
    double radius = dataPtr->radius;
    double startAngle = 0;
    double spanAngle = 2*SEMICIRCLE_DEGREES*DEGREE_FACTOR; //whole circle

    // get left-top screen coordinate and right-bottom screen coordinate
    double topleftX = dataPtr->cx - radius;
    double topleftY = dataPtr->cy - radius;
    double bottomrightX = dataPtr->cx + radius;
    double bottomrightY = dataPtr->cy + radius;

    double stlx, stly, sbrx, sbry;
    translateData(painter, topleftX, topleftY, stlx, stly);
    translateData(painter, bottomrightX, bottomrightY, sbrx, sbry);

    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(stlx,  stly, sbrx-stlx, sbry-stly, startAngle, spanAngle);
    painter->setRenderHint(QPainter::Antialiasing, true);

}
void laser_trajectory_module::paintPoint(DL_PointData *dataPtr, QPainter *painter,const QColor &color)
{
    double xposition, yposition;
    translateData(painter, dataPtr->x, dataPtr->y, xposition, yposition);

    painter->setPen(QPen(color, 3, Qt::SolidLine, Qt::RoundCap));
    painter->drawPoint(xposition, yposition);
    painter->setRenderHint(QPainter::Antialiasing, true);
}
// 绘制圆弧
void laser_trajectory_module::paintEllipse(DL_EllipseData *dataPtr, QPainter *painter,const QColor &color)
{
    // calculate radius in tool coordinate

    // 计算椭圆长短轴
    double lradius = sqrt(pow(dataPtr->mx, 2) + pow(dataPtr->my, 2));
    double sradius = lradius*dataPtr->ratio;
    // 椭圆中心点
    double topleftX = dataPtr->cx - lradius;
    double topleftY = dataPtr->cy + sradius;
    // 椭圆对应矩形长度和宽度
    double bottomrightX = topleftX + 2*lradius;
    double bottomrightY = topleftY - 2*sradius;
    // 计算椭圆偏转角度
    double rotateAngle = atan2(dataPtr->my, dataPtr->mx)/M_PI * SEMICIRCLE_DEGREES;
    //qDebug()<<"$$$$$$The ellipse angel ="<<rotateAngle;
    /*
    qDebug()<<"[DXF]--------------------------------->Draw dxf ellipse!"
            <<"cx="
            <<dataPtr->cx
            <<"cy="
            <<dataPtr->cy
            <<"mx"
            <<dataPtr->mx
            <<"lradius"
            <<lradius
            <<"my"
            <<dataPtr->my
            <<"sradius"
            <<sradius
            <<"ratio"
            <<dataPtr->ratio
            <<"topleftX"
            <<topleftX
            <<"heightY"
            <<topleftY
            <<"ellipse width"
            <<2*dataPtr->mx
            <<"ellipse height"
            <<2*dataPtr->mx*dataPtr->ratio;

    */
    double stlx, stly, sbrx, sbry, centerX, centerY;
    translateData(painter, topleftX, topleftY, stlx, stly);
    translateData(painter, bottomrightX, bottomrightY, sbrx, sbry);
    translateData(painter, dataPtr->cx, dataPtr->cy, centerX, centerY);
    //qDebug()<<"********************->The ellipse display cx"<<centerX<<"cy"<<centerY;

    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->save();
    painter->translate(centerX,centerY);
    painter->rotate(-rotateAngle);
    painter->translate(-centerX,-centerY);
    painter->drawEllipse(QRect(QPoint(stlx,  stly),QPoint(sbrx, sbry)));
    painter->restore();

}
void laser_trajectory_module::paintCuttingTraj(QPainter *painter)
{
    double s_prex, s_prey, s_x, s_y;
    // Fix todo 实时更新当前轨迹点,等有实时数据后再用实时数据替换

    //simulate data by timer

    curPointX = motionStatPtr->axisStat[0].axisCmdPostion;
    curPointY = motionStatPtr->axisStat[2].axisCmdPostion;


    translateData(painter, prePointX, prePointY, s_prex, s_prey);
    translateData(painter, curPointX, curPointY, s_x, s_y);
    /*
    painter->setPen(QPen(Qt::cyan, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(s_prex, s_prey, s_x, s_y);
    painter->setRenderHint(QPainter::Antialiasing, true);
    */

    prePointX = curPointX;
    prePointY = curPointY;

}
void laser_trajectory_module::paintLaserCutter(QPainter *painter)
{
    double s_x, s_y;
    translateData(painter, curPointX, curPointY, s_x, s_y);

    // 绘制一个叉叉，叉叉的焦点代表激光切割点
    painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
    QLineF line(s_x - LASER_CUTTER, s_y + LASER_CUTTER, s_x + LASER_CUTTER, s_y - LASER_CUTTER);
    painter->drawLine(line);
    line.setLine(s_x - LASER_CUTTER, s_y - LASER_CUTTER, s_x + LASER_CUTTER, s_y + LASER_CUTTER);
    painter->drawLine(line);

    update();
}
// 根据输入的轴位置区域显示图形,可以创建一个对话框获取轴范围
void laser_trajectory_module::loadAxisValue(void)
{
    // fixed todo
}
void laser_trajectory_module::frameTraj(double minx, double miny, double maxx, double maxy)
{
    // 比较之后取小的，防止比例失调
    /*
    qDebug()<<"[laser_trajectory_module::frameTraj]{before}--(minx,miny,maxx,maxy)";
    qDebug()<<minx;
    qDebug()<<miny;
    qDebug()<<maxx;
    qDebug()<<maxy;
    */

    if((maxx - minx) < (maxy - miny))
    {
        maxx = minx + (maxy - miny);
    }
    else
    {
        maxy = miny + (maxx - minx);
    }
    /*
    qDebug()<<"[laser_trajectory_module::frameTraj]{after}--(minx,miny,maxx,maxy)";
    qDebug()<<minx;
    qDebug()<<miny;
    qDebug()<<maxx;
    qDebug()<<maxy;
    */

    QPoint point1, point2;
    point1.setX(minx);point1.setY(miny);
    point2.setX(maxx);point2.setY(maxy);
    frameRect.setTopLeft(point1);
    frameRect.setBottomRight(point2);

    //qDebug()<<"[laser_trajectory_module::frameTraj]{point1}"<<point1;
    //qDebug()<<"[laser_trajectory_module::frameTraj]{point2}"<<point2;

    QRect rect = frameRect.normalized();
    if (rect.width() < 4 || rect.height() < 4)
    {
        qDebug()<<"[HMI]--Creat frameTraj rect failure!";
        return;
    }

    //coordinate_scaling prevSettings = zoomStack[curZoom];
    coordinate_scaling settings;

    double width = (maxx - minx);
    double height = (maxy - miny);
    double centerX = (maxx + minx)/2.0;
    double centerY = (maxy + miny)/2.0;

    settings.setLimitXY(centerX - width/2.0, centerY - height/2.0, centerX + width/2.0, centerY + height/2.0);
    /*
    qDebug()<<"[laser_trajectory_module::frameTraj]{dealed}--(minX,minY,maxX,maxY,spanxy)";
    qDebug()<<settings.getMinX();
    qDebug()<<settings.getMinY();
    qDebug()<<settings.getMaxX();
    qDebug()<<settings.getMaxY();
    qDebug()<<settings.getSpanXY();
    */
    //zoomStack.resize(curZoom + 1);
    zoomStack.append(settings);
    ++curZoom;

    refreshPixmap();
}
// 放大
void laser_trajectory_module::zoomOut(void)
{
    if (curZoom > 0)
    {
        --curZoom;
        refreshPixmap();
    }
}
// 缩小
void laser_trajectory_module::zoomIn(void)
{
    coordinate_scaling prevSettings = zoomStack[curZoom];
    coordinate_scaling settings;

    double width = (prevSettings.getMaxX()-prevSettings.getMinX())*0.8;
    double height = (prevSettings.getMaxY()-prevSettings.getMinY())*0.8;
    double centerX = (prevSettings.getMaxX()+prevSettings.getMinX())/2.0;
    double centerY = (prevSettings.getMaxY()+prevSettings.getMinY())/2.0;
    settings.setLimitXY(centerX - width/2.0, centerY - height/2.0, centerX + width/2.0, centerY + height/2.0);

    //zoomStack.resize(curZoom + 1);
    zoomStack.append(settings);
    ++curZoom;

    refreshPixmap();
}
void laser_trajectory_module::refreshLed(void)
{
    static int ctrlV = 0;
    //qDebug()<<"[Led]-------------------------------ctrlv------------------------------------^_^!"<<ctrlV;
    if(ctrlV > 100)
    {
        ctrlV = 0;
    }
    ctrlV++;
    if(ctrlV == 10)
    {
        //qDebug()<<"[Led]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~green------------------------------------^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");

        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(0 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    if(ctrlV == 20)
    {
        //qDebug()<<"[Led]$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$yellow$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");
        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(1 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    if(ctrlV == 30)
    {
        //qDebug()<<"[Led]#################################red######################################^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");
        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(2 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    if(ctrlV == 40)
    {
        //qDebug()<<"[Led]#################################red######################################^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");
        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(3 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    if(ctrlV == 50)
    {
        //qDebug()<<"[Led]#################################red######################################^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");
        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(4 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    if(ctrlV == 60)
    {
        //qDebug()<<"[Led]#################################red######################################^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");
        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(5 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    if(ctrlV == 70)
    {
        //qDebug()<<"[Led]#################################red######################################^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");
        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(6 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    if(ctrlV == 80)
    {
        //qDebug()<<"[Led]#################################red######################################^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");
        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(7 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    if(ctrlV == 90)
    {
        //qDebug()<<"[Led]#################################red######################################^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");
        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(8 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    if(ctrlV == 100)
    {
        //qDebug()<<"[Led]#################################red######################################^_^ctrlV="<<ctrlV;
        //QTime time = QTime::currentTime();
        //qDebug()<<"[Time]--Current time = "<<time.toString("hh:mm:ss");
        for(int i = 0; i < LED_MAX_NUM; i++)
        {
            if(9 == i)
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledred.png"));
            }
            else
            {
                ledLabel[i]->setPixmap(QPixmap(":/icons/ledgreen.png"));
            }

        }
    }
    update();

}
