#ifndef ALARM_MODULE_H
#define ALARM_MODULE_H

#include <QLabel>
#include <QPushButton>

#include "base_public_widget.h"

class alarm_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit alarm_module(QWidget *parent = nullptr);

    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    // private function
    void UpdateAlarmFunction(void);

    // private variants
    enum {MAX_ALARM_MSG_NUM = 2};
    /**********************************************************
    *1-没有报警，
    * 0-提示信息，不闪烁；
    * 1-警告类，闪烁；
    * 2-报警类手动，闪烁
    * 3-报警自动类，闪烁；
    * 4-报警自动类已经确认过的，不闪烁
    ***********************************************************/
    enum {
            NO_ALARM = -1,
            HINT_MSG_TYPE = 0,
            WARNING_MSG_TYPE,
            ALARM_MANU_TYPE,
            ALARM_AUTO_TYPE,
            ALARM_AUTO_CONFIRM
         };
    QLabel *alarmLabel[MAX_ALARM_MSG_NUM];
    QPushButton *alarmClearBtn[MAX_ALARM_MSG_NUM];
    int alarmTypeVal;
    int countFlag;

signals:

public slots:
};

#endif // ALARM_MODULE_H
