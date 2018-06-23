#include "machinning_msg_module.h"

machinning_msg_module::machinning_msg_module(QWidget *parent)
    : base_public_widget(parent)
{
    QPalette gboxPalette = palette();
    gboxPalette.setColor(LABEL_TEXT_COLOR_BLUE);

    QPalette textPalette = palette();
    textPalette.setColor(LABEL_TEXT_COLOR_BLACK);

    // 状态信息组
    QGroupBox *statusParentBoxPtr = new QGroupBox(this);
    statusParentBoxPtr->setTitle(tr("状态信息"));
    statusParentBoxPtr->setGeometry(5,5,225,140);
    statusParentBoxPtr->setPalette(gboxPalette);

    // 加工信息组
    QGroupBox *msgParentBoxPtr = new QGroupBox(this);
    msgParentBoxPtr->setTitle(tr("加工信息"));
    msgParentBoxPtr->setGeometry(235,5,180,140);
    msgParentBoxPtr->setPalette(gboxPalette);

    for(int i = 0; i < AXIS_NUM; i++)
    {
        axisNameLabel[i] = new QLabel(statusParentBoxPtr);
        //axisNameLabel[i]->setFrameStyle(FRAME_SUNKEN_STYLE);
        axisNameLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        axisNameLabel[i]->setLineWidth(LINE_WIDTH_NORMAL);
        axisNameLabel[i]->setAutoFillBackground(true);
        axisNameLabel[i]->setScaledContents(true);
        axisNameLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        axisNameLabel[i]->setGeometry(77+i*30,10,25,25);
        axisNameLabel[i]->setPalette(textPalette);


    }
    axisNameLabel[0]->setText(tr("X1"));
    axisNameLabel[1]->setText(tr("X2"));
    axisNameLabel[2]->setText(tr("Y1"));
    axisNameLabel[3]->setText(tr("Y2"));
    axisNameLabel[4]->setText(tr("Z1"));

    for(int i = 0; i < STATUS_LABEL_NUM; i++)
    {
        statusNameLabel[i] = new QLabel(statusParentBoxPtr);
        statusNameLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        //statusNameLabel[i]->setFrameStyle(FRAME_SUNKEN_STYLE);
        statusNameLabel[i]->setLineWidth(LINE_WIDTH_NORMAL);
        statusNameLabel[i]->setAutoFillBackground(true);
        statusNameLabel[i]->setScaledContents(true);
        statusNameLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        statusNameLabel[i]->setGeometry(5,35 + i*25,65,25);
        statusNameLabel[i]->setPalette(textPalette);
    }
    statusNameLabel[0]->setText(tr("运动状态"));
    statusNameLabel[1]->setText(tr("原点捕获"));
    statusNameLabel[2]->setText(tr("极限警告"));
    statusNameLabel[3]->setText(tr("吸气状态"));

    for(int i = 0; i < MAX_VARIANTS_NUM; i++)
    {
        variantsLabel[i] = new QLabel(statusParentBoxPtr);
        //variantsLabel[i]->setFrameStyle(FRAME_SUNKEN_STYLE);
        variantsLabel[i]->setLineWidth(LINE_WIDTH_NORMAL);
        variantsLabel[i]->setAutoFillBackground(true);
        variantsLabel[i]->setScaledContents(true);
        variantsLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        variantsLabel[i]->setGeometry(75+30*(i/4),35+25*(i%4),25,25);
        variantsLabel[i]->setPalette(textPalette);
    }
    // 加工信息组
    for(int i = 0; i < MAX_MSG_NUM; i++)
    {
        msgNameLabel[i] = new QLabel(msgParentBoxPtr);
        msgNameLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        //msgNameLabel[i]->setFrameStyle(FRAME_SUNKEN_STYLE);
        msgNameLabel[i]->setLineWidth(LINE_WIDTH_NORMAL);
        msgNameLabel[i]->setAutoFillBackground(true);
        msgNameLabel[i]->setScaledContents(true);
        msgNameLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        msgNameLabel[i]->setGeometry(5,35 + i*25,65,25);
        msgNameLabel[i]->setPalette(textPalette);

        msgVariantsLabel[i] = new QLabel(msgParentBoxPtr);
        msgVariantsLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        //msgVariantsLabel[i]->setFrameStyle(FRAME_SUNKEN_STYLE);
        msgVariantsLabel[i]->setLineWidth(LINE_WIDTH_NORMAL);
        msgVariantsLabel[i]->setAutoFillBackground(true);
        msgVariantsLabel[i]->setScaledContents(true);
        msgVariantsLabel[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        msgVariantsLabel[i]->setGeometry(70,35 + i*25,80,25);
        msgVariantsLabel[i]->setPalette(textPalette);

    }
    msgNameLabel[0]->setText(tr("开机时间"));
    msgNameLabel[1]->setText(tr("加工时间"));
    msgNameLabel[2]->setText(tr("加工次数"));
    msgNameLabel[3]->setText(tr("激光时间"));

    QTime ctime = QTime::currentTime();
    msgVariantsLabel[0]->setText(ctime.toString(("hh:mm:ss")));
    msgVariantsLabel[1]->setText(ctime.toString(("hh:mm:ss")));
    msgVariantsLabel[2]->setText(ctime.toString(("hh:mm:ss")));
    msgVariantsLabel[3]->setText(ctime.toString(("hh:mm:ss")));

    for(int i = 0; i < RESET_BTN_NUM; i++)
    {
        msgResetButton[i] = new QPushButton(msgParentBoxPtr);
        msgResetButton[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        msgResetButton[i]->setGeometry(150,35 + i*25,25,25);
        msgResetButton[i]->setIcon(QIcon(":/icons/reset.png"));
        //msgResetButton[i]->setText(tr("重置"));

        // tmp for test data

    }
    UpdateMachinningFunction();
    resize(420,150);
}
void machinning_msg_module::UpdateData(void)
{
    //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
    //UpdateMachinningFunction();
}
void machinning_msg_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void machinning_msg_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void machinning_msg_module::UpdateMachinningFunction(void)
{
    variantsLabel[0]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[1]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[2]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[3]->setPixmap(QPixmap(":/icons/noready"));
    variantsLabel[4]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[5]->setPixmap(QPixmap(":/icons/noready"));
    variantsLabel[6]->setPixmap(QPixmap(":/icons/ready"));
    //variantsLabel[7]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[8]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[9]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[10]->setPixmap(QPixmap(":/icons/ready"));
    //variantsLabel[11]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[12]->setPixmap(QPixmap(":/icons/noready"));
    variantsLabel[13]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[14]->setPixmap(QPixmap(":/icons/ready"));
    //variantsLabel[15]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[16]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[17]->setPixmap(QPixmap(":/icons/ready"));
    variantsLabel[18]->setPixmap(QPixmap(":/icons/ready"));
    //variantsLabel[19]->setPixmap(QPixmap(":/icons/noready"));

}
