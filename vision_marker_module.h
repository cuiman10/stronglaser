#ifndef VISION_MARKER_MODULE_H
#define VISION_MARKER_MODULE_H

#include <QGroupBox>
#include <QLabel>

#include "base_public_widget.h"

class vision_marker_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit vision_marker_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    // private function
    void UpdateCcdFunction(void);

    // private variants
    enum {MAX_MARKER_NUM = 2};
    QGroupBox *markerParentBoxPtr[MAX_MARKER_NUM];
    QLabel *markerLabel[MAX_MARKER_NUM];

signals:

public slots:

};

#endif // VISION_MARKER_MODULE_H
