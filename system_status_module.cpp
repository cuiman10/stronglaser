#include "system_status_module.h"

system_status_module::system_status_module(QWidget *parent)
    : base_public_widget(parent)
{
    qDebug()<<"[HMI]--This is system_status_module!"<<"[Constructor]";
    oldState = -1;
    oldMode = -1;

    QPalette sysHintModulePalette = palette();
    sysHintModulePalette.setColor(LABEL_TEXT_COLOR_YELLOW);
    sysHintModulePalette.setColor(WIDGET_WINDOW_COLOR_BLUE);

    QPalette timeLabelPalette = palette();
    timeLabelPalette.setColor(LABEL_TEXT_COLOR_GREEN);
    timeLabelPalette.setColor(WIDGET_WINDOW_COLOR_BLUE);

    for(int i = 0;i < SYSTEM_LABEL_MAX_NUM; i++)
    {
        subLabel[i] = new QLabel(this);
        subLabel[i]->setFrameStyle(FRAME_SUNKEN_STYLE);
        subLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_10));
        subLabel[i]->setLineWidth(LINE_WIDTH_NORMAL);
        subLabel[i]->setPalette(sysHintModulePalette);
        subLabel[i]->setAutoFillBackground(true);
        subLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        if(i < 11)
        {
            subLabel[i]->setGeometry(i*80,0,80,25);
        }
        else
        {
            subLabel[i]->setGeometry(880 + (i-11)*100,0,100,25);
        }

    }

    /***********************************************************************
    *subLabel[0]-LOGO
    *subLabel[1]-当前工作模式
    *subLabel[2]-
    *subLabel[3]-
    *subLabel[4]-
    *subLabel[5]-
    *subLabel[6]-
    *subLabel[7]-
    *subLabel[8]-
    *subLabel[9]-
    *subLabel[10]-公英制提示
    *subLabel[11]-激光状态
    *subLabel[12]-机床状态
    *subLabel[13]-报警提示
    *subLabel[14]-当前时间
    ************************************************************************/
    subLabel[0]->setPixmap(QPixmap(":/icons/logo.png"));
    subLabel[0]->setScaledContents(true);

    // alarm flash hint
    alarmHintLabel = new flash_label(subLabel[13]);
    alarmHintLabel->setGeometry(1,1,100-2,25 - 2);

    // display current time
    timeLcdPtr = new QLCDNumber(subLabel[14]);
    timeLcdPtr->setDigitCount(9);
    timeLcdPtr->setDecMode();
    timeLcdPtr->setSegmentStyle(QLCDNumber::Flat);
    timeLcdPtr->setFrameStyle(FRAME_SUNKEN_STYLE);
    timeLcdPtr->setGeometry(0,0,100,25);
    //timeLcdPtr->setPalette(timeLabelPalette);

    resize(1280,25);
}
void system_status_module::UpdateData(void)
{
    //qDebug()<<"[HMI](system_status_module)--UpdateData()!";
    UpdateModeFunction();
}
void system_status_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](system_status_module)--Respond_operate()!";
}
void system_status_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](system_status_module)--Refresh_button_text()!";
}
void system_status_module::UpdateModeFunction(void)
{
    //char strText[10];
    int curModeFlag = 0;

    int ltype = LanguageType();
    switch (curModeFlag)
    {
        case 0:
            {
                switch(ltype)
                {
                    case SIMPLIFIED_CHINESE:
                        subLabel[1]->setText(tr("加工模式"));
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
            }
            break;
        default:
            break;
    }

    QTime time = QTime::currentTime();
    timeLcdPtr->display(time.toString(("hh:mm:ss")));

}
