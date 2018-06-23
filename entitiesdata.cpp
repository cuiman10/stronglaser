#include "entitiesdata.h"

entitiesData::entitiesData()
{
    // constructor
    // 初始值未初始化，由第一个得到的点初始化，以后的点与该点依次比较
    bIsInitLimitValFlag = false;

}
// 添加点
void entitiesData::addPoint(const DL_PointData &d)
{
    points.append(d);
    //qDebug()<<"1111111111111111111111111111111"<<"point size ="<<points.size();
    int t = points.size();
    if(t>0)
    {
        addTopDataFunction(POINT_TYPE,t,(void*)(&points[t-1]));
    }
}
// 添加直线
void entitiesData::addLine(const DL_LineData &d)
{
    lines.append(d);
    //qDebug()<<"222222222222222222222222222222add line"<<"line size ="<<lines.size();
    int t = lines.size();
    if(t>0)
    {
        addTopDataFunction(LINE_TYPE,t,(void*)(&lines[t-1]));
    }
}
// 添加圆弧
void entitiesData::addArc(const DL_ArcData &d)
{
    arcs.append(d);
    //qDebug()<<"333333333333333333333333333333add arc"<<"arc size ="<<arcs.size();
    int t = arcs.size();
    if(t>0)
    {
        addTopDataFunction(ARC_TYPE,t,(void*)(&arcs[t-1]));
    }
}
// 添加圆
void entitiesData::addCircle(const DL_CircleData &d)
{
    circles.append(d);
    int t = circles.size();
    //qDebug()<<"4444444444444444444444444444444add circle"<<"circle size ="<<circles.size();
    if(t>0)
    {
        addTopDataFunction(CIRCLE_TYPE,t,(void*)(&circles[t-1]));
    }
}
// 添加椭圆
void entitiesData::addEllipse(const DL_EllipseData &d)
{
    ellipses.append(d);
    //qDebug()<<"555555555555555555555555555555add ellipses"<<"ellipses size ="<<ellipses.size();
    int t = ellipses.size();
    if(t>0)
    {
        addTopDataFunction(ELLIPSE_TYPE,t,(void*)(&ellipses[t-1]));
    }
}
// 添加文本
void entitiesData::addText(const DL_TextData &d)
{
    texts.append(d);
    //qDebug()<<"666666666666666666666666666666add texts"<<"texts size ="<<texts.size();
    int t = texts.size();
    if(t>0)
    {
        addTopDataFunction(TEXT_TYPE,t,(void*)(&texts[t-1]));
    }
}
// 添加多段线
void entitiesData::addPolyline(const DL_PolylineData &d)
{
    polylines.append(d);
    //qDebug()<<"7777777777777777777777777777777 add polyline";
    int t = polylines.size();
    if(t>0)
    {
        addTopDataFunction(POLYLINE_TYPE,t,(void*)(&polylines[t-1]));
    }
}
// 添加到多段线这个容器内
void entitiesData::addVertex(const DL_VertexData &d)
{
    vertices.append(d);
    //qDebug()<<"888888888888888888888888888888888 add vertex";
    int t = vertices.size();
    if(t>0)
    {
        addTopDataFunction(VERTEX_TYPE,t,(void*)(&vertices[t-1]));
    }
}
// 添加多行文本
void entitiesData::addMText(const DL_MTextData &d)
{
    mtexts.append(d);
    //qDebug()<<"999999999999999999999999999999999 add mtexts";
    int t = mtexts.size();
    if(t>0)
    {
        addTopDataFunction(MTEXT_TYPE,t,(void*)(&mtexts[t-1]));
    }
}
// 添加角度标注
void entitiesData::addDimAngular(const DL_DimensionData &, const DL_DimAngularData &)
{
    //qDebug()<<"***********add angular";
}
// 添加线性标注
void entitiesData::addDimLinear(const DL_DimensionData &, const DL_DimLinearData &)
{
    //qDebug()<<"___________________________add deim linear";
}

// 添加参考线
void entitiesData::addXLine(const DL_XLineData &)
{
    //qDebug()<<"++++++++++++++add xline";
}
// 添加射线
void entitiesData::addRay(const DL_RayData &)
{
    //qDebug()<<"/////////////////////////////add ray";
}

// 添加样条曲线
void entitiesData::addSpline(const DL_SplineData &)
{
    //qDebug()<<".....................................add spline data";
}
// 添加注释
void entitiesData::addComment(const std::string &)
{
    //qDebug()<<",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,add comment";
}
// 添加顶点
// 添加图层
void entitiesData::addLayer(const DL_LayerData &d)
{
    //qDebug()<<"ggggggggggggggggggg add layer";
    //qDebug()<<QString::fromStdString(d.name);
}
// 添加xdata扩展数据字符
void entitiesData::addXDataString(int, const std::string &)
{
    //qDebug()<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>add xdata string";
}
// 添加X扩展记录
void entitiesData::addXRecord(const std::string &)
{
    //qDebug()<<",.,.,.,.,.,.,.,.,.,.,.,.,.,.,add repcord";
}
// 添加轨迹
void entitiesData::addTrace(const DL_TraceData &)
{
    //qDebug()<<"mmmmmmmmmmmmmm add trace";
}
// 结束实体
void entitiesData::endEntity()
{
    //qDebug()<<"end entity***********************";
    //qDebug()<<"attribute           ***************** "<<this->getAttributes().getColor();
}
// 结束序列
void entitiesData::endSequence()
{
    //qDebug()<<"end sequence +++++++++++++++++++++";
}
// 设置属性
void entitiesData::setAttributes(const DL_Attributes &attrib)
{
    //qDebug()<<"set attribute ()()()()()()()()()()()()()()()";
}
// 添加填充
void entitiesData::addHatch(const DL_HatchData &d)
{
    //qDebug()<<"nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn add hatch";
    hatches.append(d);
}
// 添加填充边缘
void entitiesData::addHatchEdge(const DL_HatchEdgeData &d)
{
    //qDebug()<<"MMMMMMMMMMMMMMMMKMMMMM add hat edge data";
    hatchedges.append(d);
    if(this->getAttributes().getColor()==1)
    {
        QString color="#ef3312";
        hatchcolors.append(color);
    }
    else if(this->getAttributes().getColor()==2)
    {
        QString color="#efef33";
        hatchcolors.append(color);
    }
    else if(this->getAttributes().getColor()==3)
    {
        QString color="#12ef33";
        hatchcolors.append(color);
    }
    else
    {
        QString color="#efefef";
        hatchcolors.append(color);
    }
}
void entitiesData::addTopDataFunction(int type, int flag, void* ptr)
{
    CM_data_type tmpData;
    tmpData.type = type;
    tmpData.flag = flag;
    tmpData.cmPtr = ptr;
    topDataVectorPtr.append(tmpData);
    //qDebug()<<"The top dxf array ="<<topDataVectorPtr.length();
    int curt = topDataVectorPtr.length() - 1;
    switch (type) {
    case POINT_TYPE:
        checkLimitCoord(((DL_PointData*)(topDataVectorPtr[curt].cmPtr))->x,((DL_PointData*)(topDataVectorPtr[curt].cmPtr))->y);
        break;
    case LINE_TYPE:
        checkLimitCoord(((DL_LineData*)(topDataVectorPtr[curt].cmPtr))->x1,((DL_LineData*)(topDataVectorPtr[curt].cmPtr))->y1);
        checkLimitCoord(((DL_LineData*)(topDataVectorPtr[curt].cmPtr))->x2,((DL_LineData*)(topDataVectorPtr[curt].cmPtr))->y2);
        /*
        qDebug()<<"The data type = "<<"LINE_TYPE"
               <<"from("
               <<((DL_LineData*)(topDataVectorPtr[curt].cmPtr))->x1
               <<","
               <<((DL_LineData*)(topDataVectorPtr[curt].cmPtr))->y1
               <<")"
               <<"to("
               <<((DL_LineData*)(topDataVectorPtr[curt].cmPtr))->x2
               <<","
               <<((DL_LineData*)(topDataVectorPtr[curt].cmPtr))->y2
               <<")";
               */
        break;
    case ARC_TYPE:
        checkLimitCoord(((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->cx - ((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->radius,
                        ((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->cy - ((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->radius);
        checkLimitCoord(((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->cx + ((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->radius,
                        ((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->cy + ((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->radius);
       /*
        qDebug()<<"The data type = "<<"ARC_TYPE"
               <<"Center("
               <<((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->cx
               <<","
               <<((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->cy
               <<","
               <<((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->cz
               <<")"
               <<"radius="
               <<((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->radius
               <<"angle1="
               <<((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->angle1
               <<"angle2="
               <<((DL_ArcData*)(topDataVectorPtr[curt].cmPtr))->angle2
                 ;
        */
        break;
    case CIRCLE_TYPE:
        checkLimitCoord(((DL_CircleData*)(topDataVectorPtr[curt].cmPtr))->cx - ((DL_CircleData*)(topDataVectorPtr[curt].cmPtr))->radius,
                        ((DL_CircleData*)(topDataVectorPtr[curt].cmPtr))->cy - ((DL_CircleData*)(topDataVectorPtr[curt].cmPtr))->radius);
        checkLimitCoord(((DL_CircleData*)(topDataVectorPtr[curt].cmPtr))->cx + ((DL_CircleData*)(topDataVectorPtr[curt].cmPtr))->radius,
                        ((DL_CircleData*)(topDataVectorPtr[curt].cmPtr))->cy + ((DL_CircleData*)(topDataVectorPtr[curt].cmPtr))->radius);

        break;
    case ELLIPSE_TYPE:
        checkLimitCoord(((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->cx - ((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->mx,
                        ((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->cy - ((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->mx*((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->ratio);
        checkLimitCoord(((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->cx + ((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->mx,
                        ((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->cy + ((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->mx*((DL_EllipseData*)(topDataVectorPtr[curt].cmPtr))->ratio);

        break;
    case TEXT_TYPE:
        /*
        qDebug()<<"The data type = "<<"TEXT_TYPE"
               <<"ipx="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->ipx
               <<"ipy="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->ipy
               <<"ipz="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->ipz
               <<"apx="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->apx
               <<"apy="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->apy
               <<"apz="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->apz
               <<"height="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->height
               <<"xScaleFactor="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->xScaleFactor
               <<"textGenerationFlags="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->textGenerationFlags
               <<"hJustification="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->hJustification
               <<"vJustification="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->vJustification
               <<"angle="
               <<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->angle
                 ;
        */
               std::cout<<"text="<<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->text
               <<"style="<<((DL_TextData*)(topDataVectorPtr[curt].cmPtr))->style;
        break;
    case DIMANGULAR_TYPE:
        break;
    case VERTEX_TYPE:
        checkLimitCoord(((DL_VertexData*)(topDataVectorPtr[curt].cmPtr))->x, ((DL_VertexData*)(topDataVectorPtr[curt].cmPtr))->y);
        /*
        qDebug()<<"The data type = "<<"VERTEX_TYPE"
                <<"x="
                <<((DL_VertexData*)(topDataVectorPtr[curt].cmPtr))->x
                <<"y="
                <<((DL_VertexData*)(topDataVectorPtr[curt].cmPtr))->y
                <<"z="
                <<((DL_VertexData*)(topDataVectorPtr[curt].cmPtr))->z
                <<"bulge="
                <<((DL_VertexData*)(topDataVectorPtr[curt].cmPtr))->bulge
                  ;
              */
        break;
    case POLYLINE_TYPE:
        /*
        qDebug()<<"The data type = "<<"POLYLINE_TYPE"
                <<"vertice number="
                <<((DL_PolylineData*)(topDataVectorPtr[curt].cmPtr))->number
                <<"m="
                <<((DL_PolylineData*)(topDataVectorPtr[curt].cmPtr))->m
                <<"n="
                <<((DL_PolylineData*)(topDataVectorPtr[curt].cmPtr))->n
                <<"elevation="
                <<((DL_PolylineData*)(topDataVectorPtr[curt].cmPtr))->elevation
                <<"flags="
                <<((DL_PolylineData*)(topDataVectorPtr[curt].cmPtr))->flags
                  ;
                  */
        break;
    case MTEXT_TYPE:
        checkLimitCoord(((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->ipx, ((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->ipy);
        checkLimitCoord(((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->ipx + ((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->width,
                        ((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->ipy + ((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->height);
        /*
        qDebug()<<"The data type = "<<"MTEXT_TYPE"
               <<"ipx="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->ipx
               <<"ipy="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->ipy
               <<"ipz="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->ipz
               <<"dirx="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->dirx
               <<"diry="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->diry
               <<"dirz="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->dirz
               <<"height="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->height
               <<"width="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->width
               <<"attachmentPoint="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->attachmentPoint
               <<"drawingDirection="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->drawingDirection
               <<"lineSpacingStyle="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->lineSpacingStyle
               <<"lineSpacingFactor="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->lineSpacingFactor
               <<"angle="
               <<((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->angle
               <<"text="
               <<QString::fromStdString(((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->text)
               <<"style="
               <<QString::fromStdString(((DL_MTextData*)(topDataVectorPtr[curt].cmPtr))->style)
                 ;
                 */
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
// 左上角xy，右下角xy
void entitiesData::checkLimitCoord(double x,double y)
{
    if(!bIsInitLimitValFlag)
    {
        curLimitCoord.minX = x - 1;
        curLimitCoord.maxX = x + 1;

        curLimitCoord.minY = y - 1;
        curLimitCoord.maxY = y + 1;

        bIsInitLimitValFlag = true;
    }
    // 判断x是否超越极限值
    if(x < curLimitCoord.minX)
    {
        //qDebug()<<"[Check x,y limit value]---minX,x = "<<curLimitCoord.minX<<","<<x;
        curLimitCoord.minX = x;

    }
    else if(x > curLimitCoord.maxX)
    {
        //qDebug()<<"[Check x,y limit value]---maxX,x = "<<curLimitCoord.maxX<<","<<x;
        curLimitCoord.maxX = x;
    }
    else
    {
        // to do nothing,noly for the soft Reliability and stability
    }
    // 判断y是否超越极限值
    if(y < curLimitCoord.minY)
    {
        //qDebug()<<"[Check x,y limit value]---minY,y = "<<curLimitCoord.minY<<","<<y;
        curLimitCoord.minY = y;
    }
    else if(y > curLimitCoord.maxY)
    {
        //qDebug()<<"[Check x,y limit value]---maxY,y = "<<curLimitCoord.maxY<<","<<y;
        curLimitCoord.maxY = y;
    }
    else
    {
        // to do nothing,noly for the soft Reliability and stability
    }

}
