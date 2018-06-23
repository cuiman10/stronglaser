#ifndef MACHINNING_MSG_MODULE_H
#define MACHINNING_MSG_MODULE_H

#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QTime>

#include "base_public_widget.h"

class machinning_msg_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit machinning_msg_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    // private function
    void UpdateMachinningFunction(void);

    // private variants
    // 状态信息组
    enum {AXIS_NUM = 5,STATUS_LABEL_NUM = 4,MAX_VARIANTS_NUM = 20};
    QLabel *axisNameLabel[AXIS_NUM];
    QLabel *statusNameLabel[STATUS_LABEL_NUM];
    QLabel *variantsLabel[MAX_VARIANTS_NUM];
    // 加工信息组
    enum {MAX_MSG_NUM = 4,RESET_BTN_NUM = 3};
    QLabel *msgNameLabel[MAX_MSG_NUM];
    QLabel *msgVariantsLabel[MAX_MSG_NUM];
    QPushButton *msgResetButton[RESET_BTN_NUM];

signals:

public slots:
};

#endif // MACHINNING_MSG_MODULE_H
