#include "vision_marker_module.h"

vision_marker_module::vision_marker_module(QWidget *parent)
    : base_public_widget(parent)
{
    QPalette visionMarkerModulePalette = palette();
    visionMarkerModulePalette.setColor(LABEL_TEXT_COLOR_BLUE);

    for(int i = 0; i < MAX_MARKER_NUM; i++)
    {
        markerParentBoxPtr[i] = new QGroupBox(this);
        markerParentBoxPtr[i]->setGeometry(5 + i*210,5,200,155);
        markerParentBoxPtr[i]->setPalette(visionMarkerModulePalette);

        markerLabel[i] = new QLabel(markerParentBoxPtr[i]);
        markerLabel[i]->setGeometry(5,15,190,135);
        markerLabel[i]->setPixmap(QPixmap(":/icons/ccdposition.png"));
        markerLabel[i]->setAutoFillBackground(true);
        markerLabel[i]->setScaledContents(true);
    }
    markerParentBoxPtr[0]->setTitle(tr("第一标靶"));
    markerParentBoxPtr[1]->setTitle(tr("第二标靶"));

    resize(420,165);
}
void vision_marker_module::UpdateData(void)
{
    //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
    UpdateCcdFunction();
}
void vision_marker_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void vision_marker_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void vision_marker_module::UpdateCcdFunction(void)
{

}
