#include "import_cuttingfile_module.h"

import_cuttingfile_module::import_cuttingfile_module(QWidget *parent)
    : base_public_widget(parent)
{
    QPalette importModulePalette = palette();
    importModulePalette.setColor(LABEL_TEXT_COLOR_BLUE);

    QPalette textPalette = palette();
    textPalette.setColor(LABEL_TEXT_COLOR_BLACK);

    parentGrpBoxPtr = new QGroupBox(this);
    parentGrpBoxPtr->setGeometry(5,10,445,150);
    parentGrpBoxPtr->setPalette(importModulePalette);
    parentGrpBoxPtr->setTitle(tr("文件编辑组"));

    importFileNameLabel = new QLabel(parentGrpBoxPtr);
    importFileNameLabel->setGeometry(10,25,70,25);
    importFileNameLabel->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
    importFileNameLabel->setText(tr("文件路径:"));
    importFileNameLabel->setPalette(textPalette);

    importFilePathLineEdit = new QLineEdit(parentGrpBoxPtr);
    importFilePathLineEdit->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
    importFilePathLineEdit->setGeometry(80,25,360,25);
    importFilePathLineEdit->setPalette(textPalette);
    importFileNameLabel->setBuddy(importFilePathLineEdit);

    for(int i = 0; i < MAX_FUNCBTN_NUM; i++)
    {
        functionBtnPtr[i] = new QPushButton(parentGrpBoxPtr);
        functionBtnPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        functionBtnPtr[i]->setGeometry(5+i*60,55,60,30);
    }
    functionBtnPtr[6]->setGeometry(365,55,75,30);

    functionBtnPtr[0]->setText(tr("新建"));
    functionBtnPtr[1]->setText(tr("打开"));
    functionBtnPtr[2]->setText(tr("保存"));
    functionBtnPtr[3]->setText(tr("编辑"));
    functionBtnPtr[4]->setText(tr("待定..."));
    functionBtnPtr[5]->setText(tr("待定..."));
    functionBtnPtr[6]->setText(tr("待定..."));

    QLabel *techLogoLabelPtr = new QLabel(parentGrpBoxPtr);
    techLogoLabelPtr->setGeometry(10,90,20,20);
    techLogoLabelPtr->setPixmap(QPixmap(":/icons/techLogo.png"));
    techLogoLabelPtr->setScaledContents(true);
    techLogoLabelPtr->setPalette(textPalette);

    techNameLabel = new QLabel(parentGrpBoxPtr);
    techNameLabel->setGeometry(30,90,35,20);
    techNameLabel->setText(tr("工艺"));
    techNameLabel->setPalette(textPalette);
    techNameLabel->setFont(QFont(HMI_COMMON_FONT_SIZE_8));

    for(int i = 0; i < MAX_TECH_LAYOUT_NUM; i++)
    {
        techLayoutBtnPtr[i] = new QPushButton(parentGrpBoxPtr);
        techLayoutBtnPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        techLayoutBtnPtr[i]->setGeometry(65+i*25,90,20,20);
        techLayoutBtnPtr[i]->setPalette(textPalette);
    }

    techLayoutBtnPtr[0]->setIcon(QIcon(":/icons/layout1.png"));
    techLayoutBtnPtr[1]->setIcon(QIcon(":/icons/layout2.png"));
    techLayoutBtnPtr[2]->setIcon(QIcon(":/icons/layout3.png"));
    techLayoutBtnPtr[3]->setIcon(QIcon(":/icons/layout4.png"));
    techLayoutBtnPtr[4]->setIcon(QIcon(":/icons/layout5.png"));
    techLayoutBtnPtr[5]->setIcon(QIcon(":/icons/layout6.png"));
    techLayoutBtnPtr[6]->setIcon(QIcon(":/icons/layout7.png"));
    techLayoutBtnPtr[7]->setIcon(QIcon(":/icons/layout8.png"));
    techLayoutBtnPtr[8]->setIcon(QIcon(":/icons/layout9.png"));
    techLayoutBtnPtr[9]->setIcon(QIcon(":/icons/layout10.png"));
    techLayoutBtnPtr[10]->setIcon(QIcon(":/icons/layout11.png"));
    techLayoutBtnPtr[11]->setIcon(QIcon(":/icons/layout12.png"));
    techLayoutBtnPtr[12]->setIcon(QIcon(":/icons/layout13.png"));
    techLayoutBtnPtr[13]->setGeometry(395,90,20,20);
    techLayoutBtnPtr[13]->setIcon(QIcon(":/icons/layoutTop.png"));
    techLayoutBtnPtr[14]->setGeometry(420,90,20,20);
    techLayoutBtnPtr[14]->setIcon(QIcon(":/icons/layoutBottom.png"));

    for(int i = 0; i < MAX_TECH_PARAM_BTN_NUM; i++)
    {
        techParamComboBtnPtr[i] = new QComboBox(parentGrpBoxPtr);
        techParamComboBtnPtr[i]->setGeometry(5 + i*55,115,50,25);
        techParamComboBtnPtr[i]->setPalette(textPalette);
    }

    resize(450,160);
}
void import_cuttingfile_module::UpdateData(void)
{
  //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
  UpdateFileImportFunction();
}
void import_cuttingfile_module::Respond_operate(int, bool)
{
  qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void import_cuttingfile_module::Refresh_button_text(int, const QString &)
{
  qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void import_cuttingfile_module::UpdateFileImportFunction(void)
{

}
