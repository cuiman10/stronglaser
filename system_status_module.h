#ifndef SYSTEM_STATUS_MODULE_H
#define SYSTEM_STATUS_MODULE_H

#include <QWidget>
#include <QLabel>
#include <QTime>
#include <QLCDNumber>

#include "base_public_widget.h"
#include "flash_label.h"


class system_status_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit system_status_module(QWidget *parent = nullptr);

    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    // private function
    void UpdateModeFunction(void);

    // private variant
    enum {SYSTEM_LABEL_MAX_NUM = 15};
    QLabel *subLabel[SYSTEM_LABEL_MAX_NUM];
    flash_label *alarmHintLabel;
    QLCDNumber *timeLcdPtr;
    int oldState;
    int oldMode;

};

#endif // SYSTEM_STATUS_MODULE_H
