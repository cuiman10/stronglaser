#include "axis_control_module.h"

axis_control_module::axis_control_module(QWidget *parent)
    : base_public_widget(parent)
{
    InitData();

    QFrame *mainFrame = new QFrame(this);
    mainFrame->resize(245,505);
    mainFrame->setFrameStyle(FRAME_BOX_SRAISED_STYLE);

    QPalette moveAxisPalette = palette();
    moveAxisPalette.setColor(LABEL_TEXT_COLOR_GREEN);
    moveAxisPalette.setColor(WIDGET_WINDOW_COLOR_BLACK);

    // stronglaser company logo
    companyLogoLabel = new QLabel(mainFrame);
    companyLogoLabel->setGeometry(10,10,225,60);
    companyLogoLabel->setPixmap(QPixmap(":/icons/stronglogo.jpg"));
    companyLogoLabel->setScaledContents(true);

    // chechbox for target position
    moveAxisBtnGrp = new QButtonGroup(mainFrame);
    // control axis function button group
    for(int i = 0; i < MAX_CONTROL_AXIS_NUM; i++)
    {
        axisBtnPtr[i] = new QPushButton(mainFrame);
        axisBtnPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_10));
        moveAxisBtnGrp->addButton(axisBtnPtr[i]);

    }
    // Axis X1-
    axisBtnPtr[0]->setText(tr("\342\206\220X1-"));
    axisBtnPtr[0]->setGeometry(10,75,110,40);
    // Axis X1+
    axisBtnPtr[1]->setText(tr("X1+\342\206\222"));
    axisBtnPtr[1]->setGeometry(125,75,110,40);
    // Axis X2-
    axisBtnPtr[2]->setText(tr("\342\206\220X2-"));
    axisBtnPtr[2]->setGeometry(10,120,110,40);
    // Axis X2+
    axisBtnPtr[3]->setText(tr("X2+\342\206\222"));
    axisBtnPtr[3]->setGeometry(125,120,110,40);
    // Axis Y1+
    axisBtnPtr[4]->setText(tr("\342\206\221\nY1+"));
    axisBtnPtr[4]->setGeometry(10,165,70,70);
    // Axis Y1-
    axisBtnPtr[5]->setText(tr("Y1-\n\342\206\223"));
    axisBtnPtr[5]->setGeometry(10,240,70,70);
    // Axis Y2+
    axisBtnPtr[6]->setText(tr("\342\206\221\nY2+"));
    axisBtnPtr[6]->setGeometry(87,165,70,70);
    // Axis Y2-
    axisBtnPtr[7]->setText(tr("Y2-\n\342\206\223"));
    axisBtnPtr[7]->setGeometry(87,240,70,70);
    // Axis Z+
    axisBtnPtr[8]->setText(tr("\342\206\221\nZ+"));
    axisBtnPtr[8]->setGeometry(164,165,70,70);
    // Axis Z-
    axisBtnPtr[9]->setText(tr("Z-\n\342\206\223"));
    axisBtnPtr[9]->setGeometry(164,240,70,70);

    connect(moveAxisBtnGrp, SIGNAL(buttonPressed(QAbstractButton*)), this, SLOT(sendMoveAxis(QAbstractButton*)));
    connect(moveAxisBtnGrp, SIGNAL(buttonReleased(QAbstractButton*)), this, SLOT(sendMoveAxis(QAbstractButton*)));

    for(int i = 0; i < CHECK_BTN_NUM; i++)
    {
        checkAxisPositionBtnPtr[i] = new QCheckBox(mainFrame);
        checkAxisPositionBtnPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        checkAxisPositionBtnPtr[i]->setGeometry(5,320 + i*25,45,23);


        // 目标位置输入框
        targetLineEditPtr[i] = new QLineEdit(mainFrame);
        targetLineEditPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        targetLineEditPtr[i]->setGeometry(60,320 + i*25,75,23);
        QDoubleValidator *positionValidator = new QDoubleValidator;
        positionValidator->setDecimals(9);
        positionValidator->setBottom(-9999.9999);
        positionValidator->setTop(9999.9999);
        targetLineEditPtr[i]->setValidator(positionValidator);
        targetLineEditPtr[i]->setText(QString::number(0.0000));

        // 轴移动目标位置单位
        unitLabel[i] = new QLabel(mainFrame);
        unitLabel[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        unitLabel[i]->setGeometry(135,320 + i*25,20,23);
        unitLabel[i]->setText(tr("mm"));

        // 轴参数配置按钮组
        setAxisParameterBtnPtr[i] = new QPushButton(mainFrame);
        setAxisParameterBtnPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
        setAxisParameterBtnPtr[i]->setGeometry(165,320 + i*25,70,23);

    }

    checkAxisPositionBtnPtr[0]->setText(tr("X1"));
    checkAxisPositionBtnPtr[1]->setText(tr("X2"));
    checkAxisPositionBtnPtr[2]->setText(tr("Y1"));
    checkAxisPositionBtnPtr[3]->setText(tr("Y2"));
    checkAxisPositionBtnPtr[4]->setText(tr("Z"));

    setAxisParameterBtnPtr[0]->setText(tr("X1轴参数"));
    setAxisParameterBtnPtr[1]->setText(tr("X2轴参数"));
    setAxisParameterBtnPtr[2]->setText(tr("Y1轴参数"));
    setAxisParameterBtnPtr[3]->setText(tr("Y2轴参数"));
    setAxisParameterBtnPtr[4]->setText(tr("Z轴参数"));

    // velocity ratio select group
    horslider = new QSlider(mainFrame);
    horslider->setGeometry(15,450,160,20);
    horslider->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
    horslider->setMaximum(100);
    horslider->setValue(currentAxisRate);
    horslider->setOrientation(Qt::Horizontal);

    sliderValueLabel = new QLabel(mainFrame);
    sliderValueLabel->setFont(QFont(HMI_COMMON_FONT_SIZE_8));
    sliderValueLabel->setGeometry(175,450,60,20);
    sliderValueLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    connect(horslider,SIGNAL(sliderMoved(int)),this,SLOT(slotGetCurrentRateFunction(int)));

    moveModeBtnGrp = new QButtonGroup(mainFrame);
    moveModeBtnGrp->setExclusive(true);

    for(int i = 0; i < 2; i++)
    {
        moveModeRadioBtnPtr[i] = new QRadioButton(mainFrame);
        moveModeRadioBtnPtr[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_6));
        moveModeRadioBtnPtr[i]->setGeometry(10 + i*80,480,80,20);
        //moveModeRadioBtnPtr[i]->setAutoExclusive(true);
    }
    moveModeRadioBtnPtr[0]->setText(tr("相对移动"));
    moveModeRadioBtnPtr[1]->setText(tr("绝对移动"));
    moveModeBtnGrp->addButton(moveModeRadioBtnPtr[0]);
    moveModeBtnGrp->addButton(moveModeRadioBtnPtr[1]);

    if(bIsAbsoluteFlag)
    {
        // 绝对移动方式
        moveModeRadioBtnPtr[0]->setChecked(false);
        moveModeRadioBtnPtr[1]->setChecked(true);
    }
    else
    {
        // 相对移动模式
        moveModeRadioBtnPtr[0]->setChecked(true);
        moveModeRadioBtnPtr[1]->setChecked(false);
    }
    connect(moveModeBtnGrp, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(modeSelectClicked(QAbstractButton*)));

    moveBtnPtr = new QPushButton(mainFrame);
    moveBtnPtr->setFont(QFont(HMI_COMMON_FONT_SIZE_10));
    moveBtnPtr->setGeometry(175,475,60,30);
    moveBtnPtr->setText(tr("移动"));


    slotGetCurrentRateFunction(currentAxisRate);
    resize(245,510);
}
void axis_control_module::UpdateData(void)
{
    //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
    UpdateAxisControlFunction();
}
void axis_control_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void axis_control_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void axis_control_module::InitData(void)
{
    qDebug()<<"[HMI](axis_control_module)--Init data!";
    currentAxisRate = 60;
    bIsAbsoluteFlag = true;
    curPressAxis = -1;
    bIsBtnDown = false;
    defaultVel = DEFAULT_CMD_VEL;

}
void axis_control_module::UpdateAxisControlFunction(void)
{
    if(bIsBtnDown && curPressAxis > -1)
    {
        switch (curPressAxis) {
        case 0:
            // X1-
            motionCmdPtr->axisCmd[0].axisCmdPostion = motionStatPtr->axisStat[0].axisCmdPostion - defaultVel;
            //qDebug()<<"[Axis control module]--Motion cmd position = "<<motionCmdPtr->axisCmd[0].axisCmdPostion;
            break;
        case 1:
            // X1+
            motionCmdPtr->axisCmd[0].axisCmdPostion = motionStatPtr->axisStat[0].axisCmdPostion + defaultVel;
            //qDebug()<<"[Axis control module]--Motion cmd position = "<<motionCmdPtr->axisCmd[0].axisCmdPostion;
            break;
        case 2:
            // X2-
            motionCmdPtr->axisCmd[1].axisCmdPostion = motionStatPtr->axisStat[1].axisCmdPostion - defaultVel;
            break;
        case 3:
            // X2+
            motionCmdPtr->axisCmd[1].axisCmdPostion = motionStatPtr->axisStat[1].axisCmdPostion + defaultVel;
            break;
        case 4:
            // Y1-
            motionCmdPtr->axisCmd[2].axisCmdPostion = motionStatPtr->axisStat[2].axisCmdPostion + defaultVel;
            break;
        case 5:
            // Y1+
            motionCmdPtr->axisCmd[2].axisCmdPostion = motionStatPtr->axisStat[2].axisCmdPostion - defaultVel;
            break;
        case 6:
            // Y2-
            motionCmdPtr->axisCmd[3].axisCmdPostion = motionStatPtr->axisStat[3].axisCmdPostion + defaultVel;
            break;
        case 7:
            // Y2+
            motionCmdPtr->axisCmd[3].axisCmdPostion = motionStatPtr->axisStat[3].axisCmdPostion - defaultVel;
            break;
        case 8:
            // Z-
            motionCmdPtr->axisCmd[4].axisCmdPostion = motionStatPtr->axisStat[4].axisCmdPostion + defaultVel;
            break;
        case 9:
            // Z+
            motionCmdPtr->axisCmd[4].axisCmdPostion = motionStatPtr->axisStat[4].axisCmdPostion - defaultVel;
            break;
        default:
            qDebug() << "[axis_control_module]--Error update axis position axisno!!!";
            break;
        }

    }
}
void axis_control_module::slotGetCurrentRateFunction(int val)
{
    currentAxisRate = val;
    defaultVel = (val/100.0)*DEFAULT_CMD_VEL;
    //qDebug() << QString("[axis_control_module](slotGetCurrentRateFunction)--current rate : %1").arg(QString::number(defaultVel));
    QString valStr;
    sliderValueLabel->setText(valStr.sprintf("%d%%",val));
}
void axis_control_module::modeSelectClicked(QAbstractButton *button)
{
    //qDebug() << QString("Clicked Button : %1").arg(button->text());
    if(!button->text().compare("相对移动"))
    {
        bIsAbsoluteFlag = false;
        qDebug() << QString("Current select mode : %1").arg("xiangduimode!");
    }
    else
    {
        bIsAbsoluteFlag = true;
        qDebug() << QString("Current select mode : %1").arg("abs mode!");
    }

    // 遍历按钮，获取选中状态
    /*
    QList<QAbstractButton*> list = moveModeBtnGrp->buttons();
    foreach (QAbstractButton *pButton, list)
    {
        QString strStatus = pButton->isChecked() ? "Checked" : "Unchecked";
        qDebug() << QString("Button : %1 is %2").arg(button->text()).arg(strStatus);
    }
    */

}
void axis_control_module::sendMoveAxis(QAbstractButton* btn)
{
    if(btn->isDown())
    {
        bIsBtnDown = true;
        //qDebug() << QString("X1- is pressed!");
    }
    else
    {
        bIsBtnDown = false;
        //qDebug() << QString("X1- is up!");
    }
    /*! allocate axis no*/
    if(!btn->text().compare("\342\206\220X1-"))
    {
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
        curPressAxis = 0;
    }
    else if(!btn->text().compare("X1+\342\206\222"))
    {
        curPressAxis = 1;
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
    }
    else if(!btn->text().compare("\342\206\220X2-"))
    {
        curPressAxis = 2;
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
    }
    else if(!btn->text().compare("X2+\342\206\222"))
    {
        curPressAxis = 3;
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
    }
    else if(!btn->text().compare("\342\206\221\nY1+"))
    {
        curPressAxis = 4;
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
    }
    else if(!btn->text().compare("Y1-\n\342\206\223"))
    {
        curPressAxis = 5;
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
    }
    else if(!btn->text().compare("\342\206\221\nY2+"))
    {
        curPressAxis = 6;
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
    }
    else if(!btn->text().compare("Y2-\n\342\206\223"))
    {
        curPressAxis = 7;
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
    }
    else if(!btn->text().compare("\342\206\221\nZ+"))
    {
        curPressAxis = 8;
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
    }
    else if(!btn->text().compare("Z-\n\342\206\223"))
    {
        curPressAxis = 9;
        //qDebug() << QString("Current select axis button is : %1").arg(btn->text());
    }
    else
    {
        curPressAxis = -1;
        qDebug() << QString("Error button select axis button is : %1").arg(btn->text());
    }
}
