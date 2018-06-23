#ifndef WORK_STATION_MODULE_H
#define WORK_STATION_MODULE_H

#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QTableWidget>
#include <QCheckBox>

#include "base_public_widget.h"

class work_station_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit work_station_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    // private function
    void UpdateWorkStationFunction(void);

    // private variants

    enum {NAME_LABEL_NUM = 2, Function_BTN_NUM = 8};
    // 工位设定表格
    QTableWidget *setStationTabPtr;
    // 工位设定功能按钮组
    QPushButton *setTechButton[Function_BTN_NUM];
    // 工艺设定复选框组
    QCheckBox *checkBtnPtr[NAME_LABEL_NUM];
    // 板厚设定组
    QLabel *thicknessNameLabel[NAME_LABEL_NUM];
    QLineEdit *thicknessLineEdit[NAME_LABEL_NUM];
    QPushButton *moreFunctionBtnPtr[NAME_LABEL_NUM];
    QLabel *unitLabel[NAME_LABEL_NUM];
    // 位置设定按钮
    QPushButton *setPositionBtn;


signals:

public slots:
};

#endif // WORK_STATION_MODULE_H
