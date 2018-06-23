/********************************************************************
*	Description:   work_station_module.cpp
*   Stronglaser cnc work station module
*
*	Author:  CM
*	License: StrongLaser soft Version 1.0
*	System: Windows7
*
*	Date: 2018/05/30
********************************************************************/
#include "work_station_module.h"

work_station_module::work_station_module(QWidget *parent)
    : base_public_widget(parent)
{
    QPalette gboxPalette = palette();
    gboxPalette.setColor(LABEL_TEXT_COLOR_BLUE);

    QPalette textPalette = palette();
    textPalette.setColor(LABEL_TEXT_COLOR_BLACK);

    // 工位设定组
    QGroupBox *parentGrpBoxPtr = new QGroupBox(this);
    parentGrpBoxPtr->setTitle(tr("工位设定区"));
    parentGrpBoxPtr->setGeometry(5,5,410,345);
    parentGrpBoxPtr->setPalette(gboxPalette);

    // 工位设定表格
    setStationTabPtr = new QTableWidget(parentGrpBoxPtr);
    setStationTabPtr->setGeometry(5,20,325,260);

    for(int i = 0; i < Function_BTN_NUM; i++)
    {
        setTechButton[i] = new QPushButton(parentGrpBoxPtr);
        setTechButton[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        setTechButton[i]->setGeometry(335,20 + i*(25+5),70,25);
    }
    setTechButton[0]->setText(tr("新增工位"));
    setTechButton[1]->setText(tr("删除工位"));
    setTechButton[2]->setText(tr("删除全部"));
    setTechButton[3]->setText(tr("新增矩阵"));
    setTechButton[4]->setText(tr("复制矩阵"));
    setTechButton[5]->setText(tr("全部加工"));
    setTechButton[6]->setText(tr("全部停止"));
    setTechButton[7]->setText(tr("偏位设定"));

    QDoubleValidator *positionValidator = new QDoubleValidator;
    positionValidator->setDecimals(6);
    positionValidator->setBottom(-99.999);
    positionValidator->setTop(99.999);

    for(int i = 0; i < NAME_LABEL_NUM; i++)
    {
        // 图层及标靶福选按钮
        checkBtnPtr[i] = new QCheckBox(parentGrpBoxPtr);
        checkBtnPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_6));
        checkBtnPtr[i]->setGeometry(5,285 + i*25,110,23);
        checkBtnPtr[i]->setPalette(textPalette);


        // 板厚输入框
        thicknessLineEdit[i] = new QLineEdit(parentGrpBoxPtr);
        thicknessLineEdit[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        thicknessLineEdit[i]->setGeometry(200,285 + i*25,70,23);
        thicknessLineEdit[i]->setPalette(textPalette);
        thicknessLineEdit[i]->setValidator(positionValidator);
        thicknessLineEdit[i]->setText(QString::number(0.000));

        // 板厚名称标签
        thicknessNameLabel[i] = new QLabel(parentGrpBoxPtr);
        thicknessNameLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_6));
        thicknessNameLabel[i]->setGeometry(125,285 + i*25,70,23);
        thicknessNameLabel[i]->setBuddy(thicknessLineEdit[i]);
        thicknessNameLabel[i]->setPalette(textPalette);

        // 更多功能选择按钮
        moreFunctionBtnPtr[i] = new QPushButton(parentGrpBoxPtr);
        moreFunctionBtnPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        moreFunctionBtnPtr[i]->setGeometry(270,285 + i*25,30,23);
        moreFunctionBtnPtr[i]->setText(tr("..."));

        // 长度单位标签
        unitLabel[i] = new QLabel(parentGrpBoxPtr);
        unitLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        unitLabel[i]->setGeometry(300,285 + i*25,60,23);
        unitLabel[i]->setText(tr("mm"));
        unitLabel[i]->setPalette(textPalette);

    }
    checkBtnPtr[0]->setText(tr("显示单一图层"));
    checkBtnPtr[1]->setText(tr("标靶在底部"));

    thicknessNameLabel[0]->setText(tr("基础板厚:"));
    thicknessNameLabel[1]->setText(tr("当前板厚:"));

    setPositionBtn = new QPushButton(parentGrpBoxPtr);
    setPositionBtn->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
    setPositionBtn->setGeometry(335,285,70,50);
    setPositionBtn->setText(tr("位置设定"));

    UpdateWorkStationFunction();
    resize(420,355);
}
void work_station_module::UpdateData(void)
{
    //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
    //UpdateMachinningFunction();
}
void work_station_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void work_station_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void work_station_module::UpdateWorkStationFunction(void)
{

}
