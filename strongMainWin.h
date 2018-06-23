#ifndef STRONGMAINWIN_H
#define STRONGMAINWIN_H

#include <QWidget>
#include <QTimer>
#include "base_public_widget.h"
#include "system_status_module.h"
#include "alarm_module.h"
#include "axis_position_module.h"
#include "laser_cutting_module.h"
#include "ccd_vision_module.h"
#include "machinning_msg_module.h"
#include "work_station_module.h"
#include "vision_marker_module.h"
#include "import_cuttingfile_module.h"
#include "auxiliary_plc_module.h"
#include "axis_control_module.h"
#include "process_msg_module.h"
#include "hmi_motion_interface_module.h"


class MainWin : public QWidget
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = 0);
    ~MainWin();


private:
    // private function
    void ExitHmi(void);
    // private variant
    system_status_module *systemStatusModulePtr;
    alarm_module *alarmModulePtr;
    axis_position_module *axisPositionModulePtr;
    laser_cutting_module *cuttingGraphModulePtr;
    ccd_vision_module *ccdVisionModulePtr;
    machinning_msg_module *machinningMsgModulePtr;
    work_station_module *worKStationModulePtr;
    vision_marker_module *visionMarkerModulePtr;
    import_cuttingfile_module *importCadModulePtr;
    auxiliary_PLC_module *auxiliaryPlcModulePtr;
    axis_control_module *axisControlModulePtr;
    process_msg_module *processMsgModulePtr;

private slots:
    void TimeoutCB(void);

};

#endif // STRONGMAINWIN_H
