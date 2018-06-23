/********************************************************************
*	Description:   strongMainWin.cpp
*   Stronglaser cnc main window
*
*	Author:  CM
*	License: StrongLaser soft Version 1.0
*	System: Windows7
*
*	Date: 2018/05/20
********************************************************************/

#include "strongMainWin.h"

hmi_motion_interface_module *motionInterfacePtr = 0;

// globe variant for other object to access
//
int languageFlag = SIMPLIFIED_CHINESE;
bool unitIsInchFlag = false;

hmi_motion_interface_module *motionBuffPtr = hmi_motion_interface_module::getInstance();
const MOTION_STATUS_GRP* motionStatPtr = motionBuffPtr->GetMotionStatus();
MOTION_CMD_TYPE* motionCmdPtr = motionBuffPtr->SendHmiCommand();

MainWin::MainWin(QWidget *parent)
    :QWidget(parent)
{
    qDebug()<<"[HMI](MainWindow)--MainWindow constructor!";

    systemStatusModulePtr = new system_status_module(this);
    systemStatusModulePtr->setGeometry(0,0,HMI_SCREEN_WIDTH,HMI_SCREEN_HEIGH);

    alarmModulePtr = new alarm_module(this);
    alarmModulePtr->setGeometry(0,HMI_SCREEN_HEIGH - HMI_COMMON_HEIGH25,HMI_SCREEN_WIDTH,HMI_COMMON_HEIGH25);

    axisPositionModulePtr = new axis_position_module(this);
    axisPositionModulePtr->setGeometry(420,35,600,95);

    cuttingGraphModulePtr = new laser_cutting_module(this);
    cuttingGraphModulePtr->setGeometry(420,135,600,660 + 5 + 40);

    ccdVisionModulePtr = new ccd_vision_module(this);
    ccdVisionModulePtr->setGeometry(0,25,420,330);

    machinningMsgModulePtr = new machinning_msg_module(this);
    machinningMsgModulePtr->setGeometry(0,355,420,150);

    worKStationModulePtr = new work_station_module(this);
    worKStationModulePtr->setGeometry(0,490,420,355);

    visionMarkerModulePtr = new vision_marker_module(this);
    visionMarkerModulePtr->setGeometry(0,835,420,165);

    importCadModulePtr = new import_cuttingfile_module(this);
    importCadModulePtr->setGeometry(415,835,450,160);

    auxiliaryPlcModulePtr = new auxiliary_PLC_module(this);
    auxiliaryPlcModulePtr->setGeometry(865,835,415,160);

    axisControlModulePtr = new axis_control_module(this);
    axisControlModulePtr->setGeometry(1025,35,245,505);

    processMsgModulePtr = new process_msg_module(this);
    processMsgModulePtr->setGeometry(1025,540,245,300);

    QTimer *mainTimer = new QTimer(this);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(TimeoutCB()));
    mainTimer->start(100);

    setWindowIcon(QIcon(":/icons/stronglogo.png"));
    resize(1280,1024);
}

MainWin::~MainWin()
{
    qDebug()<<"[HMI](destroy)--Default destroy function!";
}
void MainWin::TimeoutCB(void)
{
    //qDebug()<<"[HMI](TimeoutCB)--Main timeout cycle loop function!";
    if(nullptr == motionBuffPtr)
    {
        qDebug()<<"[MainWin]--motionBuffPtr is null!";
    }
    else {
        //qDebug()<<"[MainWin]--motionBuffPtr is not null!";
        motionBuffPtr->updateData();
        //qDebug()<<"[MainWin]--motionBuffPtr is not null 222!";
    }

    systemStatusModulePtr->UpdateData();
    alarmModulePtr->UpdateData();
    axisPositionModulePtr->UpdateData();
    axisControlModulePtr->UpdateData();
    cuttingGraphModulePtr->UpdateData();
}
void MainWin::ExitHmi(void)
{
    qDebug()<<"[HMI](ExitHmi)--Main window quit function!";
}
