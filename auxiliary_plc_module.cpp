#include "auxiliary_plc_module.h"

auxiliary_PLC_module::auxiliary_PLC_module(QWidget *parent)
    : base_public_widget(parent)
{

    QPalette importModulePalette = palette();
    importModulePalette.setColor(LABEL_TEXT_COLOR_BLUE);

    QPalette textPalette = palette();
    textPalette.setColor(LABEL_TEXT_COLOR_BLACK);

    parentGrpBoxPtr = new QGroupBox(this);
    parentGrpBoxPtr->setGeometry(5,10,405,150);
    parentGrpBoxPtr->setPalette(importModulePalette);
    parentGrpBoxPtr->setTitle(tr("切割执行组"));

    for(int i = 0; i < MAX_SELECT_BTN_NUM; i++)
    {
        funcSelectBtn[i] = new QRadioButton(parentGrpBoxPtr);
        funcSelectBtn[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        funcSelectBtn[i]->setGeometry(5,20 + i*25,95,25);
        funcSelectBtn[i]->setPalette(textPalette);
    }
    funcSelectBtn[0]->setText(tr("画面缩放"));
    funcSelectBtn[1]->setText(tr("选择物体"));
    funcSelectBtn[2]->setText(tr("选择分区"));

    manuCuttingCheckBtnPtr = new QCheckBox(parentGrpBoxPtr);
    manuCuttingCheckBtnPtr->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
    manuCuttingCheckBtnPtr->setGeometry(5,95,95,25);
    manuCuttingCheckBtnPtr->setText(tr("点动切割"));
    manuCuttingCheckBtnPtr->setPalette(textPalette);

    powerLabel = new QLabel(parentGrpBoxPtr);
    powerLabel->setPalette(textPalette);
    powerLabel->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
    powerLabel->setGeometry(5,120,35,25);
    powerLabel->setText(tr("功率"));

    powerRatioSpinBoxPtr = new QDoubleSpinBox(parentGrpBoxPtr);
    powerRatioSpinBoxPtr->setPalette(textPalette);
    powerRatioSpinBoxPtr->setFont(QFont(HMI_COMMON_FONT_SIZE_6));
    powerRatioSpinBoxPtr->setGeometry(40,120,55,25);
    powerRatioSpinBoxPtr->setValue(10.0);
    powerLabel->setBuddy(powerRatioSpinBoxPtr);

    for(int i = 0; i < MAX_PLC_BTN_NUM; i++)
    {
        plcFunctionBtnPtr[i] = new QPushButton(parentGrpBoxPtr);
        plcFunctionBtnPtr[i]->setPalette(textPalette);
        plcFunctionBtnPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        plcFunctionBtnPtr[i]->setGeometry(100+(i/2)*60,20 + (i%2)*60,60,60);
    }

    plcFunctionBtnPtr[0]->setText(tr("Y1\n启动"));
    plcFunctionBtnPtr[1]->setText(tr("Y1\n进料点"));
    plcFunctionBtnPtr[2]->setText(tr("Y2\n启动"));
    plcFunctionBtnPtr[3]->setText(tr("Y2\n进料点"));
    plcFunctionBtnPtr[4]->setText(tr("真空\n吸附"));
    plcFunctionBtnPtr[5]->setText(tr("升降门"));
    plcFunctionBtnPtr[6]->setText(tr("暂停"));
    plcFunctionBtnPtr[7]->setText(tr("回原点"));
    plcFunctionBtnPtr[8]->setText(tr("停止"));
    plcFunctionBtnPtr[9]->setText(tr("退出"));

    resize(415,160);
}
void auxiliary_PLC_module::UpdateData(void)
{
    //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
    UpdatePlcFunction();
}
void auxiliary_PLC_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void auxiliary_PLC_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void auxiliary_PLC_module::UpdatePlcFunction(void)
{

}
