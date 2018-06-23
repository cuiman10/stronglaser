#ifndef BASE_PUBLIC_WIDGET_H
#define BASE_PUBLIC_WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTextCodec>
#include <QIcon>

#include "custom_constant.h"

extern int languageFlag;
extern bool unitIsInchFlag;
extern const MOTION_STATUS_GRP* motionStatPtr;
extern MOTION_CMD_TYPE* motionCmdPtr;

class base_public_widget : public QWidget
{
    Q_OBJECT
public:
    explicit base_public_widget(QWidget *parent = nullptr);
    virtual void UpdateData(void);
    virtual void Respond_operate(int, bool);
    virtual void Refresh_button_text(int, const QString &);
    virtual void InitData(void);

    // public function
    bool BisInch(void);
    int LanguageType(void);
    // public variant
    QTextCodec *gbkCodec;
    QString textStr;

signals:
    void Signal_refresh_button_text(int, const QString &);

private:
    int oldStatus;



};

#endif // BASE_PUBLIC_WIDGET_H
