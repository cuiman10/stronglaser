#ifndef AUXILIARY_PLC_MODULE_H
#define AUXILIARY_PLC_MODULE_H

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QDoubleSpinBox>

#include "base_public_widget.h"

class auxiliary_PLC_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit auxiliary_PLC_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    // private function
    void UpdatePlcFunction(void);

    // private variants
    enum {MAX_SELECT_BTN_NUM = 3,MAX_PLC_BTN_NUM = 10};
    QGroupBox *parentGrpBoxPtr;
    QRadioButton *funcSelectBtn[MAX_SELECT_BTN_NUM];
    QPushButton *plcFunctionBtnPtr[MAX_PLC_BTN_NUM];
    QCheckBox *manuCuttingCheckBtnPtr;
    QLabel *powerLabel;
    QDoubleSpinBox *powerRatioSpinBoxPtr;


signals:

public slots:
};

#endif // AUXILIARY_PLC_MODULE_H
