#ifndef AXIS_CONTROL_MODULE_H
#define AXIS_CONTROL_MODULE_H

#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QCheckBox>
#include <QSlider>
#include <QString>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>

#include <QDoubleValidator>

#include "base_public_widget.h"

#define DEFAULT_CMD_VEL 16.6667

class axis_control_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit axis_control_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);
    void InitData(void);

private:
    // private function
    void UpdateAxisControlFunction(void);

    // private variants
    enum {CHECK_BTN_NUM = 5,MAX_CONTROL_AXIS_NUM = 10};
    // stronglaser logo label
    QLabel *companyLogoLabel;
    // move axis command button group
    QButtonGroup *moveAxisBtnGrp;
    // axis move control button
    QPushButton *axisBtnPtr[MAX_CONTROL_AXIS_NUM];
    // exactly position target group
    QCheckBox *checkAxisPositionBtnPtr[CHECK_BTN_NUM];
    QLineEdit *targetLineEditPtr[CHECK_BTN_NUM];
    QLabel *unitLabel[CHECK_BTN_NUM];
    QPushButton *setAxisParameterBtnPtr[CHECK_BTN_NUM];
    // axis move ratio group
    QSlider *horslider;
    QLabel *sliderValueLabel;
    // axis move style select group
    QButtonGroup *moveModeBtnGrp;
    QRadioButton *moveModeRadioBtnPtr[2];
    QPushButton *moveBtnPtr;

    // control variants
    int currentAxisRate; // 当前轴移动倍率
    bool bIsAbsoluteFlag; // 默认绝对移动方式

    double defaultVel; // 默认速度1mm/s

    int curPressAxis; // 当前按下的轴号，对应相应数组下标
    bool bIsBtnDown; // 移动轴按钮是否按下
signals:

public slots:
    void slotGetCurrentRateFunction(int);
    void modeSelectClicked(QAbstractButton*);
    void sendMoveAxis(QAbstractButton*);
};

#endif // AXIS_CONTROL_MODULE_H
