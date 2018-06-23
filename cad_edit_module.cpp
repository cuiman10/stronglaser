#include "cad_edit_module.h"

cad_edit_module::cad_edit_module(QWidget *parent)
    : base_public_widget(parent)
{
    // Init cad editor module data
    InitData();

    QPalette cadModulePalette = palette();
    cadModulePalette.setColor(QPalette::Text,Qt::green);
    cadModulePalette.setColor(QPalette::Window,Qt::black);


    setPalette(cadModulePalette);
}
void cad_edit_module::UpdateData(void)
{

}
void cad_edit_module::Respond_operate(int, bool)
{

}
void cad_edit_module::Refresh_button_text(int, const QString&)
{

}
void cad_edit_module::InitData(void)
{
    // current operate graph item
    highlightIndex = 0;
    list_start = 0;
    list_end = 0;
    list_cur = 0;
}
void cad_edit_module::paintEvent(QPaintEvent *)
{

}
/*!This is slots blew*/
void cad_edit_module::savePluse(void)
{

}
void cad_edit_module::saveBlast(void)
{

}
void cad_edit_module::inputCoordData(void)
{

}
void cad_edit_module::inputSlopeData(void)
{

}
void cad_edit_module::inputArcData(void)
{

}
void cad_edit_module::inputCenterData(void)
{

}
void cad_edit_module::inputCircleData(void)
{

}
void cad_edit_module::inputRadiusData(void)
{

}
/*！This is cad editor function blew*/
void cad_edit_module::setSizeSettings(const coordinate_scaling&)
{

}
void cad_edit_module::enlarge(void)
{

}
void cad_edit_module::reduce(void)
{

}
void cad_edit_module::refreshGraphic(void)
{

}
void cad_edit_module::drawCoordinate(QPainter*)
{

}
void cad_edit_module::drawWorkSpace(QPainter*)
{

}
void cad_edit_module::drawGraphic(QPainter*)
{

}
void cad_edit_module::drawHighlight(QPainter*)
{

}
void cad_edit_module::paintFirstPre(QPainter*, const GRAPH_PROPERTY&)
{

}
void cad_edit_module::paintLine(QPainter*, const GRAPH_PROPERTY&, const GRAPH_PROPERTY&, const QColor&)
{

}
void cad_edit_module::paintArc(QPainter*, const GRAPH_PROPERTY&, const GRAPH_PROPERTY&)
{

}
void cad_edit_module::paintPunch(QPainter*, const GRAPH_PROPERTY&)
{

}
void cad_edit_module::highlightLine(QPainter*, const GRAPH_PROPERTY&, const GRAPH_PROPERTY&, const QColor&)
{

}
void cad_edit_module::highlightArc(QPainter*, const GRAPH_PROPERTY&, const GRAPH_PROPERTY&)
{

}
void cad_edit_module::highlightPunch(QPainter*, const GRAPH_PROPERTY&)
{

}
void cad_edit_module::swithHighlight(void)
{

}
void cad_edit_module::antiSwithHighlight(void)
{

}
void cad_edit_module::selectLineMode(void)
{

}
void cad_edit_module::selectCircleMode(void)
{

}
void cad_edit_module::selectPunchMode(void)
{

}
void cad_edit_module::transCoordinate(QPainter*, double, double,double*, double*)
{

}
void cad_edit_module::computeCenter(double, double,double, double, double, double*, double*, double*, double*)
{

}
bool cad_edit_module::recomputeDatas(const GRAPH_PROPERTY&, const GRAPH_PROPERTY&)
{

}
void cad_edit_module::saveDatas(const GRAPH_PROPERTY&)
{

}
void cad_edit_module::deleteOneEvent(void)
{

}
void cad_edit_module::saveModifyData(const GRAPH_PROPERTY&)
{

}
void cad_edit_module::modifyOneEvent(void)
{

}
void cad_edit_module::saveDataToFile(void)
{

}
void cad_edit_module::saveProgramFile(double,double,double)
{

}
void cad_edit_module::isSaveData(void)
{

}
void cad_edit_module::getParameters(void)
{

}
void cad_edit_module::readDataFromFile(const QString&)
{

}
int cad_edit_module::errorMSG(const QString&)
{

}
void cad_edit_module::modifyGraphLine(const GRAPH_PROPERTY&)
{

}
void cad_edit_module::modifyGraphSlope(const GRAPH_PROPERTY&)
{

}
void cad_edit_module::modifyGraphPoints(const GRAPH_PROPERTY&)
{

}
void cad_edit_module::modifyGraphRadius(const GRAPH_PROPERTY&)
{

}
void cad_edit_module::modifyGraphCenter(const GRAPH_PROPERTY&)
{

}
void cad_edit_module::modifyGraphCircle(const GRAPH_PROPERTY&)
{

}
void cad_edit_module::revocationEvent(void)
{

}
void cad_edit_module::restorationEvent(void)
{

}
bool cad_edit_module::IsSaveCurFile(void)
{

}

