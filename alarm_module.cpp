#include "alarm_module.h"

alarm_module::alarm_module(QWidget *parent)
    : base_public_widget(parent)
{
    //-1-没有报警，
    //0-提示信息，不闪烁；
    //1-警告类，闪烁；
    //2-报警类手动，闪烁
    //3-报警自动类，闪烁；
    //4-报警自动类已经确认过的，不闪烁
    alarmTypeVal = NO_ALARM;
    countFlag = 0;// 计数器，报警显示时间用

    QPalette alarmPalette = palette();
    alarmPalette.setColor(LABEL_TEXT_COLOR_RED);
    alarmPalette.setColor(WIDGET_WINDOW_COLOR_BLUE);

    QPalette clearPalette = palette();
    clearPalette.setColor(LABEL_TEXT_COLOR_YELLOW);
    clearPalette.setColor(WIDGET_WINDOW_COLOR_BLUE);

    for(int i = 0; i<MAX_ALARM_MSG_NUM; i++)
    {
        alarmLabel[i] =  new QLabel(this);
        alarmLabel[i]->setGeometry(i*(HMI_SCREEN_WIDTH/2),0,HMI_SCREEN_WIDTH/2 - HMI_COMMON_WIDTH100,HMI_COMMON_HEIGH25);
        alarmLabel[i]->setAutoFillBackground(true);
        alarmLabel[i]->setPalette(alarmPalette);
        alarmLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_10));

        alarmClearBtn[i] = new QPushButton(this);
        alarmClearBtn[i]->setGeometry((HMI_SCREEN_WIDTH/2 - HMI_COMMON_WIDTH100)+i*(HMI_SCREEN_WIDTH/2),0,HMI_COMMON_WIDTH100,HMI_COMMON_HEIGH25);
        alarmClearBtn[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_10));
        alarmClearBtn[i]->setText(tr("清除报警"));
    }

    resize(HMI_SCREEN_WIDTH,HMI_COMMON_HEIGH25);
}
void alarm_module::UpdateData(void)
{
    //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
    UpdateAlarmFunction();
}
void alarm_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void alarm_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void alarm_module::UpdateAlarmFunction(void)
{
    int ltype = LanguageType();
    switch(ltype)
    {
        case SIMPLIFIED_CHINESE:
            alarmLabel[0]->setText(tr("12:21:33-alarm:"));
            alarmLabel[1]->setText(tr("12:21:33-alarm:"));
            break;
        case CHINESE_TRADITIONAL:
            alarmLabel[0]->setText(tr("12:21:33-alarm:"));
            alarmLabel[1]->setText(tr("12:21:33-alarm:"));
            break;
        case ENGLISH:
            alarmLabel[0]->setText(tr("12:21:33-alarm:"));
            alarmLabel[1]->setText(tr("12:21:33-alarm:"));
            break;
        case JAPANESE:
            alarmLabel[0]->setText(tr("12:21:33-alarm:"));
            alarmLabel[1]->setText(tr("12:21:33-alarm:"));
            break;
        default:
            break;
    }

}
