#ifndef AXIS_POSITION_MODULE_H
#define AXIS_POSITION_MODULE_H

#include <QLabel>
#include <QFrame>
#include <QLCDNumber>

#include "base_public_widget.h"


class axis_position_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit axis_position_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    void UpdateAxisPositionFunction();
    enum {MAX_AXIS_NUM = 6};

    QLabel *axisNameLabel[MAX_AXIS_NUM];
    QLCDNumber *axisPositionLcdPtr[MAX_AXIS_NUM];

signals:

public slots:

};

#endif // AXIS_POSITION_MODULE_H
