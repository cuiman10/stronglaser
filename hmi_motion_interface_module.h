#ifndef HMI_MOTION_INTERFACE_MODULE_H
#define HMI_MOTION_INTERFACE_MODULE_H

#include "custom_constant.h"
#include <QList>

class hmi_motion_interface_module
{
public:
    static hmi_motion_interface_module *getInstance()
    {
        if(!theOnlyInstance)
        {
            theOnlyInstance = new hmi_motion_interface_module;
        }
        return theOnlyInstance;

    }

    void InitData(void);
    void updateData(void);
    // get data from motion or interp data queue list
    const MOTION_STATUS_GRP* GetMotionStatus(void);
    const ALARM_TYPE* GetMotionError(void);
    MOTION_CMD_TYPE* SendHmiCommand(void);

private:
    static hmi_motion_interface_module *theOnlyInstance;
    hmi_motion_interface_module();

    enum {MSG_HINT = 0,
         ALARM_MSG,
         ERROR_MSG,
         FATAL_MSG
         };
    // 激光状态变量
    LASER_PARAM_GRP laserStat;
    VISION_STATUS_TYPE visionStat;
    MOTION_STATUS_GRP motionStat;
    MOTION_CMD_TYPE motionCmd;
    QList<ALARM_TYPE> systemAlarm;

    static int commandSerialNumber ;
    static int lastCommandSerialNumber;

signals:

public slots:
};

#endif // HMI_MOTION_INTERFACE_MODULE_H
