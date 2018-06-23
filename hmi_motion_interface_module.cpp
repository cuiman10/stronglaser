#include "hmi_motion_interface_module.h"

hmi_motion_interface_module *hmi_motion_interface_module::theOnlyInstance=0;
int hmi_motion_interface_module::commandSerialNumber = 0;
int hmi_motion_interface_module::lastCommandSerialNumber=0;

hmi_motion_interface_module::hmi_motion_interface_module()
{
    InitData();
}
void hmi_motion_interface_module::InitData(void)
{
    // laser data init
    laserStat.duty = 0.5;
    laserStat.freq = 10; // KHZ
    laserStat.power = 5; //KW

    // vision data init
    visionStat.markFlag = false;
    visionStat.positonStat = 0;
    visionStat.px = 0.0;
    visionStat.py = 0.0;

    // motion status init
    for(int i = 0; i < MAX_AXIS_NUMBER; i++)
    {
        motionCmd.axisCmd[i].axisActPostion = 0.0;
        motionCmd.axisCmd[i].axisCmdPostion = 0.0;
        motionCmd.axisCmd[i].statusFlag = 0;
        motionCmd.axisCmd[i].cmdVel = 0.0;
        motionCmd.axisCmd[i].actVel = 0.0;
        motionCmd.axisCmd[i].followErr = 0.0;

        // init linear axis or rotation axis
        if(i < 3 || i >5)
        {
            motionCmd.axisCmd[i].type = 0;
        }
        else
        {
            motionCmd.axisCmd[i].type = 1;
        }
    }
    motionCmd.jok = 0;

    // motion status init
    for(int i = 0; i < MAX_AXIS_NUMBER; i++)
    {
        motionStat.axisStat[i].axisActPostion = 0.0;
        motionStat.axisStat[i].axisCmdPostion = 0.0;
        motionStat.axisStat[i].statusFlag = 0;
        motionStat.axisStat[i].cmdVel = 0.0;
        motionStat.axisStat[i].actVel = 0.0;
        motionStat.axisStat[i].followErr = 0.0;

        // init linear axis or rotation axis
        if(i < 3 || i >5)
        {
            motionStat.axisStat[i].type = 0;
        }
        else
        {
            motionStat.axisStat[i].type = 1;
        }
    }
    motionStat.sysReady = 0;

    systemAlarm.clear();

    commandSerialNumber = 0;
    lastCommandSerialNumber = 0;

    // alarm list init

}
void hmi_motion_interface_module::updateData(void)
{
    //printf("[UI]000000000000000000000000000000000000000000000\n");
    for(int i = 0; i < MAX_AXIS_NUMBER; i++)
    {
        //printf("[UI]11111111111111111111111111111111111111111111111\n");
        motionStat.axisStat[i].axisActPostion = motionCmd.axisCmd[i].axisActPostion;
        motionStat.axisStat[i].axisCmdPostion = motionCmd.axisCmd[i].axisCmdPostion;
        motionStat.axisStat[i].statusFlag = motionCmd.axisCmd[i].statusFlag;
        motionStat.axisStat[i].cmdVel = motionCmd.axisCmd[i].cmdVel;
        motionStat.axisStat[i].actVel = motionCmd.axisCmd[i].actVel;
        motionStat.axisStat[i].followErr = motionCmd.axisCmd[i].followErr;
    }
    //printf("[UI]22222222222222222222222222222222222222222222222222\n");
    motionStat.sysReady = 1;
}
const MOTION_STATUS_GRP* hmi_motion_interface_module::GetMotionStatus(void)
{

    return &motionStat;
}
const ALARM_TYPE* hmi_motion_interface_module::GetMotionError(void)
{
    ALARM_TYPE tmpAlarm;
    tmpAlarm.index = 1001;
    tmpAlarm.type = MSG_HINT;

    systemAlarm.append(tmpAlarm);

    return &systemAlarm[0];
}
MOTION_CMD_TYPE* hmi_motion_interface_module::SendHmiCommand(void)
{
    return &motionCmd;
}
