#ifndef LASER_CUTTING_MODULE_H
#define LASER_CUTTING_MODULE_H

#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
// json head file for write and read json format file
//#include <QJsonArray>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonValue>
#include <QtXml>


#include "base_public_widget.h"
#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "entitiesdata.h"
#include "laser_trajectory_module.h"

class laser_cutting_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit laser_cutting_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);
    void InitData(void);

private:
    // private function
    void UpdateCuttingFunction(void);
    // read import dxf format file and creat machinning cutting list
    void ReadDxfFile(char*);
    // write dxf file and draw graph on the screen,user can edit it and product cutting cutting.pgm(G_code file)
    void WriteDxfFile(void);
    //*********************************************************************************************
    // read and write dxf function blew
    //line
    int getLineLength(void);
    double getLinex1(int);
    double getLinex2(int);
    double getLiney1(int);
    double getLiney2(int);

    //circle
    int getCircleLength(void);
    double getCirclex(int);
    double getCircley(int);
    double getCircleRadius(int);

    //mtext
    int getMTextLength(void);
    double getMTextx(int);
    double getMTexty(int);
    QString getMTextStr(int);
    double getMTextSize(int);

    //ploy line
    int getPolyLineLength(void);
    double getVertex1x(int);
    double getVertex2x(int);
    double getVertex3x(int);
    double getVertex4x(int);
    double getVertex1y(int);
    double getVertex2y(int);
    double getVertex3y(int);
    double getVertex4y(int);

    //hatch edge and hatch color
    int getHatchLength(void);
    QString getHatchColor(int);
    double getHatchx(int);
    double getHatchy(int);
    double getHatchRadius(int);

    // write and read xml file
    void WriteXml(const QString &);
    void ReadXml(const QString &);
    void AddXml(const QString &);
    void RemoveXml(const QString &);
    void UpdateXml(const QString &);
    void TechList(void);




    // private variants
    enum {MAX_FUNC_BTN_NUM = 6};
    // max laser technology grp
    enum {MAX_LASER_GRP_NUM = 10};
    enum {CUTTING_MODE = 0,VISION_MARKING_MODE,MACHIN_SET_MODE,OFFSET_ADJUST,GALVO_ADJUST,CAMERA_ADJUST};
    QPushButton *funcBtn[MAX_FUNC_BTN_NUM];
    QButtonGroup *funcBtnGrp;
    int curFuncFlag; // current mode flag

    // read and write dxf blew
    entitiesData entityGraph;
    //DL_Dxf *laserCuttingDxf;
    LASER_PARAM_GRP laserGrp[MAX_LASER_GRP_NUM];

    // current laser cutting trajectory path
    laser_trajectory_module *laserTrajModePtr;

signals:

public slots:
    void SlotBtnFunction(QAbstractButton*);

};

#endif // LASER_CUTTING_MODULE_H
