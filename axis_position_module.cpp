#include "axis_position_module.h"

axis_position_module::axis_position_module(QWidget *parent)
    : base_public_widget(parent)
{
    QFrame *mainFrame = new QFrame(this);
    mainFrame->resize(AXIS_MODULE_WIDTH,AXIS_MODULE_HEIGH);
    mainFrame->setFrameStyle(FRAME_BOX_SRAISED_STYLE);

    QPalette moveAxisPalette = palette();
    moveAxisPalette.setColor(LABEL_TEXT_COLOR_GREEN);
    moveAxisPalette.setColor(WIDGET_WINDOW_COLOR_BLACK);

    QPalette staticAxisPalette = palette();
    staticAxisPalette.setColor(LABEL_TEXT_COLOR_YELLOW);
    staticAxisPalette.setColor(WIDGET_WINDOW_COLOR_BLACK);

    for(int i = 0; i<MAX_AXIS_NUM; i++)
    {
        axisNameLabel[i] =  new QLabel(mainFrame);
        //axisNameLabel[i]->setGeometry(i*(HMI_SCREEN_WIDTH/2),0,HMI_SCREEN_WIDTH/2 - HMI_COMMON_WIDTH100,HMI_COMMON_HEIGH25);
        //axisNameLabel[i]->setAutoFillBackground(true);
        //axisNameLabel[i]->setPalette(moveAxisPalette);
        axisNameLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_12));

        axisPositionLcdPtr[i] =  new QLCDNumber(mainFrame);
        //axisPositionLcdPtr[i]->setGeometry(i*(HMI_SCREEN_WIDTH/2),0,HMI_SCREEN_WIDTH/2 - HMI_COMMON_WIDTH100,HMI_COMMON_HEIGH25);
        axisPositionLcdPtr[i]->setAutoFillBackground(true);
        axisPositionLcdPtr[i]->setPalette(moveAxisPalette);
        axisPositionLcdPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_16));
        axisPositionLcdPtr[i]->setDigitCount(10);
        axisPositionLcdPtr[i]->setDecMode();
        axisPositionLcdPtr[i]->setSegmentStyle(QLCDNumber::Flat);
        axisPositionLcdPtr[i]->setFrameStyle(FRAME_BOX_SRAISED_STYLE);

    }
    // setting axis label position
    axisNameLabel[0]->setText(tr("X1"));
    axisNameLabel[0]->setGeometry(5,5,30,40);
    axisPositionLcdPtr[0]->display(8888.8888);
    axisPositionLcdPtr[0]->setGeometry(35,5,160,40);

    axisNameLabel[1]->setText(tr("X2"));
    axisNameLabel[1]->setGeometry(5,50,30,40);
    axisPositionLcdPtr[1]->display(8888.8888);
    axisPositionLcdPtr[1]->setGeometry(35,50,160,40);

    axisNameLabel[2]->setText(tr("Y1"));
    axisNameLabel[2]->setGeometry(205,5,30,40);
    axisPositionLcdPtr[2]->display(8888.8888);
    axisPositionLcdPtr[2]->setGeometry(235,5,160,40);

    axisNameLabel[3]->setText(tr("Y2"));
    axisNameLabel[3]->setGeometry(205,50,30,40);
    axisPositionLcdPtr[3]->display(8888.8888);
    axisPositionLcdPtr[3]->setGeometry(235,50,160,40);

    axisNameLabel[4]->setText(tr("Z1"));
    axisNameLabel[4]->setGeometry(405,5,30,40);
    axisPositionLcdPtr[4]->display(8888.8888);
    axisPositionLcdPtr[4]->setGeometry(435,5,160,40);

    axisNameLabel[5]->setText(tr("Z2"));
    axisNameLabel[5]->setGeometry(405,50,30,40);
    axisPositionLcdPtr[5]->display(8888.8888);
    axisPositionLcdPtr[5]->setGeometry(435,50,160,40);



    resize(AXIS_MODULE_WIDTH,AXIS_MODULE_HEIGH);
}
void axis_position_module::UpdateData(void)
{
    //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
    UpdateAxisPositionFunction();
}
void axis_position_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void axis_position_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void axis_position_module::UpdateAxisPositionFunction(void)
{
    int ltype = LanguageType();
    switch(ltype)
    {
        case SIMPLIFIED_CHINESE:

            break;
        case CHINESE_TRADITIONAL:

            break;
        case ENGLISH:

            break;
        case JAPANESE:

            break;
        default:
            break;
    }
    /*
    static double curposition = 0.0000;
    if(curposition < 10000)
    {
        curposition += 0.123;
    }
    else
    {
        curposition = -8888.0000;
    }
    */
    axisPositionLcdPtr[0]->display(motionStatPtr->axisStat[0].axisCmdPostion);
    axisPositionLcdPtr[1]->display(motionStatPtr->axisStat[1].axisCmdPostion);
    axisPositionLcdPtr[2]->display(motionStatPtr->axisStat[2].axisCmdPostion);
    axisPositionLcdPtr[3]->display(motionStatPtr->axisStat[3].axisCmdPostion);
    axisPositionLcdPtr[4]->display(motionStatPtr->axisStat[4].axisCmdPostion);
    axisPositionLcdPtr[5]->display(motionStatPtr->axisStat[5].axisCmdPostion);

}
