#ifndef ENTITIESDATA_H
#define ENTITIESDATA_H

#include <QDebug>
#include <QList>
#include <QString>

#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "dl_attributes.h"
#include "dl_codes.h"
#include "dl_entities.h"
#include "dl_exception.h"
#include "dl_global.h"
#include "dl_writer.h"
#include "dl_writer_ascii.h"
#include "custom_constant.h"

typedef struct {
    /**
     * Constructor.
     * Parameters: see member variables.
     */
    LIMIT_COORD(double x1 = -1, double y1 = -1, double x2 = 1, double y2 = 1) {
        minX = x1;
        minY = y1;
        maxX = x2;
        maxY = y2;
    }
    double minX;
    double minY;
    double maxX;
    double maxY;

}LIMIT_COORD;
typedef struct{
    /**
     * Constructor.
     * Parameters: see member variables.
     */
    CM_data_type(int dtype = -1,int cflag = -1, void* cptr = NULL) {
        type = dtype;
        flag = cflag;
        cmPtr = cptr;
    }

    /*! current graph data type */
    int type;
    /*! current data position*/
    int flag;
    /*! void pointer. */
    void* cmPtr;
}CM_data_type;
class entitiesData : public DL_CreationAdapter
{
public:
    entitiesData();

    // 全部图形映射关系管理库
    QList<CM_data_type> topDataVectorPtr;
    void addPoint(const DL_PointData &);
    void addLine(const DL_LineData &);
    void addArc(const DL_ArcData &);
    void addCircle(const DL_CircleData &);
    void addEllipse(const DL_EllipseData &);
    void addText(const DL_TextData &);
    void addDimAngular(const DL_DimensionData &, const DL_DimAngularData &);
    void addDimLinear(const DL_DimensionData &, const DL_DimLinearData &);
    void addMText(const DL_MTextData &);
    void addXLine(const DL_XLineData &);
    void addRay(const DL_RayData &);
    void addPolyline(const DL_PolylineData &);
    void addSpline(const DL_SplineData &);
    void addComment(const std::string &);
    void addVertex(const DL_VertexData &);
    void addLayer(const DL_LayerData &);
    void addXDataString(int, const std::string &);
    void addXRecord(const std::string &);
    void addTrace(const DL_TraceData &);
    void endEntity();
    void endSequence();
    void setAttributes(const DL_Attributes &);
    void addHatch(const DL_HatchData &);
    void addHatchEdge(const DL_HatchEdgeData &);
    // set top data point fucntion
    void addTopDataFunction(int,int,void*);
    double getCoordMinX(void) const { return curLimitCoord.minX; }
    double getCoordMinY(void) const { return curLimitCoord.minY; }
    double getCoordMaxX(void) const { return curLimitCoord.maxX; }
    double getCoordMaxY(void) const { return curLimitCoord.maxY; }
    void initLimitPoint(void) { bIsInitLimitValFlag = false; }


    QList<DL_PointData> points;
    QList<DL_LineData> lines;//
    QList<DL_ArcData> arcs;
    QList<DL_CircleData> circles;//
    QList<DL_EllipseData> ellipses;
    QList<DL_TextData> texts;
    QList<DL_DimAngularData> dimangulars;
    QList<DL_DimLinearData> dimlines;
    QList<DL_DimRadialData> radias;
    QList<DL_VertexData> vertices;//
    QList<DL_PolylineData> polylines;//
    QList<DL_MTextData> mtexts;//
    QList<DL_HatchData> hatches;//
    QList<DL_HatchEdgeData> hatchedges;//
    QList<QString> hatchcolors;

private:
    void checkLimitCoord(double,double);

    LIMIT_COORD curLimitCoord;
    bool bIsInitLimitValFlag;
};

#endif // ENTITIESDATA_H
