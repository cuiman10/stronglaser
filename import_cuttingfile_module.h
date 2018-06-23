#ifndef IMPORT_CUTTINGFILE_MODULE_H
#define IMPORT_CUTTINGFILE_MODULE_H

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "base_public_widget.h"

class import_cuttingfile_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit import_cuttingfile_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    // private function
    void UpdateFileImportFunction(void);

    // private variants
    enum {MAX_FUNCBTN_NUM = 7, MAX_TECH_LAYOUT_NUM = 15,MAX_TECH_PARAM_BTN_NUM = 8};
    QGroupBox *parentGrpBoxPtr;
    QLabel *importFileNameLabel;
    QLineEdit *importFilePathLineEdit;
    QPushButton *functionBtnPtr[MAX_FUNCBTN_NUM];
    QLabel *techNameLabel;
    QPushButton *techLayoutBtnPtr[MAX_TECH_LAYOUT_NUM];
    QComboBox *techParamComboBtnPtr[MAX_TECH_PARAM_BTN_NUM];

signals:

public slots:
};

#endif // IMPORT_CUTTINGFILE_MODULE_H
