#include "base_public_widget.h"

base_public_widget::base_public_widget(QWidget *parent)
    :QWidget(parent)
{
    gbkCodec = QTextCodec::codecForName("GBK");
    //qDebug()<<"[HMI]--This is base_public_widget model!"<<"[Constructor]";
}
void base_public_widget::UpdateData(void)
{
    //qDebug()<<"[HMI]--This is base_public_widget model!"<<"[UpdaeData()]";
}
void base_public_widget::Respond_operate(int, bool)
{
    qDebug()<<"[HMI]--This is base_public_widget model!"<<"[Respond_operate(int, bool)]";
}
void base_public_widget::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI]--This is base_public_widget model!"<<"[Refresh_button_text(int, const QString &)]";
}
void base_public_widget::InitData(void)
{
    //qDebug()<<"[HMI]--This is base_public_widget model!"<<"[InitData()]";
}
int base_public_widget::LanguageType(void)
{
    //qDebug()<<"[HMI]--This is base_public_widget model!"<<"[BisEnglish(void)]";
    return languageFlag;
}
bool base_public_widget::BisInch(void)
{
    //qDebug()<<"[HMI]--This is base_public_widget model!"<<"[BisEnglish(void)]";
    return unitIsInchFlag;
}
