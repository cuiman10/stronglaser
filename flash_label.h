#ifndef FLASH_LABEL_H
#define FLASH_LABEL_H

#include <QLabel>
#include "custom_constant.h"
#include <QTimer>

extern int languageFlag;

class flash_label : public QLabel
{
    Q_OBJECT
public:
    explicit flash_label(QWidget *parent = nullptr);
    void SetText(int);

    QTimer *pTimer;
    char strTextToShow[20];
    bool bIsShowing;

private slots:
    void FlashSlot();


};

#endif // FLASH_LABEL_H
