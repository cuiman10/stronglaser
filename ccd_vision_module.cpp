#include "ccd_vision_module.h"

ccd_vision_module::ccd_vision_module(QWidget *parent)
    : base_public_widget(parent)
{
    QPalette ccdModulePalette = palette();
    ccdModulePalette.setColor(LABEL_TEXT_COLOR_BLUE);

    ccdParentBoxPtr = new QGroupBox(this);
    ccdParentBoxPtr->setTitle(tr("CCD视觉区"));
    ccdParentBoxPtr->setGeometry(5,5,410,320);
    ccdParentBoxPtr->setPalette(ccdModulePalette);

    QLabel *visionLabel = new QLabel(ccdParentBoxPtr);
    visionLabel->setGeometry(5,15,400,300);
    visionLabel->setPixmap(QPixmap(":/icons/ccdposition.png"));
    visionLabel->setAutoFillBackground(true);
    visionLabel->setScaledContents(true);

    resize(420,330);
}
void ccd_vision_module::UpdateData(void)
{
    //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
    UpdateCcdFunction();
}
void ccd_vision_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void ccd_vision_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void ccd_vision_module::UpdateCcdFunction(void)
{

}
