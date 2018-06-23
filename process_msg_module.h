#ifndef PROCESS_MSG_MODULE_H
#define PROCESS_MSG_MODULE_H

#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QPlainTextEdit>

#include "base_public_widget.h"

class process_msg_module : public base_public_widget
{
    Q_OBJECT
public:
    explicit process_msg_module(QWidget *parent = nullptr);
    // public function
    void UpdateData(void);
    void Respond_operate(int, bool);
    void Refresh_button_text(int, const QString &);

private:
    // private function
    void UpdateProcessFunction(void);

    // private variants for this class
    QPlainTextEdit *processTextListPtr;

signals:

public slots:
};

#endif // PROCESS_MSG_MODULE_H
