#ifndef CAD_EDIT_MODULE_H
#define CAD_EDIT_MODULE_H

#include <QLabel>

#include "base_public_widget.h"
#include "coordinate_scaling.h"

#define FIRST_mode 0
#define COORD_mode 11
#define SLOPE_mode 12
#define THREEPOINTS_mode 21
#define RADIUS_mode 22
#define CENTER_mode 23
#define CIRCLE_mode 24
#define PLUSE_mode 31
#define BLAST_mode 32

#define FIRST 0
#define LINETRAVEL 100
#define LINEFEED 101
#define CLOCKWISE 202
#define COUNTERCLOCKWISE 203
#define PUNCH 300

#define INSERT_PRI 1000
#define MODIFY_PRI 2000
#define DELETE_PRI 3000
#define MAX_LIST_LENGTH 11

typedef struct{
    double offset_endx;
    double offset_endy;
}LINE_COORD;
typedef struct{
    double length;
    double slope;
}LINE_SLOPE;
typedef struct{
    double offset_endx;
    double offset_endy;
    double offset_inx;
    double offset_iny;
    double centerx;
    double centery;
}CIRCLE_THREEPOINTS;
typedef struct{
    double offset_endx;
    double offset_endy;
    double centerx;
    double centery;  //(centerx,centery)only for painting,so it is a coordinate
    double radius;
}CIRCLE_RADIUS;
typedef struct{
    double offset_centerx;
    double offset_centery;
}CIRCLE_CIRCLE;
typedef struct{
    double offset_endx;
    double offset_endy;
    double offset_centerx;
    double offset_centery;
}CIRCLE_CENTER;
typedef struct{
    double offset_prix;
    double offset_priy;
    double width;
    double length;
}FIRST_PRI;
typedef struct{
    int mode;
}PUNCH_PROERTY;
typedef union{
    LINE_COORD linecoord_data;
    LINE_SLOPE lineslope_data;
    CIRCLE_THREEPOINTS circlepoints_data;
    CIRCLE_RADIUS circleradius_data;
    CIRCLE_CIRCLE circle_data;
    CIRCLE_CENTER circlecenter_data;
    FIRST_PRI firstPri_data;
    PUNCH_PROERTY punch_data;
}GRAPH_DATA;
typedef struct {
    int mode_type;  //input mode
    int type;  //primitive type
    double endX;
    double endY;
    GRAPH_DATA  data;
}GRAPH_PROPERTY;

typedef struct{
    int operating_type;
    int position;
    GRAPH_PROPERTY pri_data;
}GRAPH_PROPERTY_LIST;

class cad_edit_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit cad_edit_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString&);
    void InitData(void);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void savePluse(void);
    void saveBlast(void);
    void inputCoordData(void);
    void inputSlopeData(void);
    void inputArcData(void);
    void inputCenterData(void);
    void inputCircleData(void);
    void inputRadiusData(void);

private:
    // private functions
    void setSizeSettings(const coordinate_scaling&);
    void enlarge(void);
    void reduce(void);
    void refreshGraphic(void);
    void drawCoordinate(QPainter*);
    void drawWorkSpace(QPainter*);
    void drawGraphic(QPainter*);
    void drawHighlight(QPainter*);
    void paintFirstPre(QPainter*, const GRAPH_PROPERTY&);
    void paintLine(QPainter*, const GRAPH_PROPERTY&, const GRAPH_PROPERTY&, const QColor&);
    void paintArc(QPainter*, const GRAPH_PROPERTY&, const GRAPH_PROPERTY&);
    void paintPunch(QPainter*, const GRAPH_PROPERTY&);
    void highlightLine(QPainter*, const GRAPH_PROPERTY&, const GRAPH_PROPERTY&, const QColor&);
    void highlightArc(QPainter*, const GRAPH_PROPERTY&, const GRAPH_PROPERTY&);
    void highlightPunch(QPainter*, const GRAPH_PROPERTY&);
    void swithHighlight(void);
    void antiSwithHighlight(void);
    void selectLineMode(void);
    void selectCircleMode(void);
    void selectPunchMode(void);
    void transCoordinate(QPainter*, double, double,double*, double*);
    void computeCenter(double, double,double, double, double, double*, double*, double*, double*);
    bool recomputeDatas(const GRAPH_PROPERTY&, const GRAPH_PROPERTY&);
    void saveDatas(const GRAPH_PROPERTY&);
    void deleteOneEvent(void);
    void saveModifyData(const GRAPH_PROPERTY&);
    void modifyOneEvent(void);
    void saveDataToFile(void);
    void saveProgramFile(double,double,double);
    void isSaveData(void);
    void getParameters(void);
    void readDataFromFile(const QString&);
    int errorMSG(const QString&);
    void modifyGraphLine(const GRAPH_PROPERTY&);
    void modifyGraphSlope(const GRAPH_PROPERTY&);
    void modifyGraphPoints(const GRAPH_PROPERTY&);
    void modifyGraphRadius(const GRAPH_PROPERTY&);
    void modifyGraphCenter(const GRAPH_PROPERTY&);
    void modifyGraphCircle(const GRAPH_PROPERTY&);
    void revocationEvent(void);
    void restorationEvent(void);
    bool IsSaveCurFile(void);
    // variants
    QLabel *titleLabel;
    QList<GRAPH_PROPERTY> graphDatas;
    QVector<coordinate_scaling> zoomStack;
    int curZoom;
    QPixmap cadPixmap;
    int highlightIndex;
    QString programFileName;
    GRAPH_PROPERTY_LIST priList[MAX_LIST_LENGTH];
    int list_start;
    int list_end;
    int list_cur;
};

#endif // CAD_EDIT_MODULE_H
