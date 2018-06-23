#ifndef CCD_VISION_MODULE_H
#define CCD_VISION_MODULE_H

#include <QGroupBox>
#include <QLabel>

#include "base_public_widget.h"

class ccd_vision_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit ccd_vision_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    // private function
    void UpdateCcdFunction(void);

    // private variants
    QGroupBox *ccdParentBoxPtr;

signals:

public slots:
};

#endif // CCD_VISION_MODULE_H
