#include "flash_label.h"

flash_label::flash_label(QWidget *parent)
    : QLabel(parent)
{
    pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()),this,SLOT(FlashSlot()));
    bIsShowing = false;
    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    setPalette(QPalette(QColor(0,64,128)));
    setAutoFillBackground(true);
}
void flash_label::FlashSlot()
{
    printf("&&&&&&&&&&&&&&&&&Test flash slot function!\n");
    if( bIsShowing )
    {
        //Hide Myself
        this->setText("");
        this->setPalette(QPalette(QColor(0,64,128)));
        bIsShowing =false;
    }
    else
    {
        //Show Myself
        this->setText(tr(strTextToShow));
        this->setPalette(QPalette(QColor(255,0,0)));
        bIsShowing =true;
    }

}
void flash_label::SetText(int alarmTypeRet)
{
    switch(alarmTypeRet)
    {
        case -1:
            strTextToShow[0] = 0;
            pTimer->stop();
            bIsShowing = false;
            this->setText("");
            this->setPalette(QPalette(QColor(0,64,128)));
            break;
        case 0:
            {
                switch(languageFlag)
                {
                    case SIMPLIFIED_CHINESE:
                        sprintf(strTextToShow, "提示");
                        break;
                    case CHINESE_TRADITIONAL:
                        sprintf(strTextToShow, "提示");
                        break;
                    case ENGLISH:
                        sprintf(strTextToShow, "HINT");
                        break;
                    case JAPANESE:
                        sprintf(strTextToShow, "提示");
                        break;
                    default:
                        break;
                }
            }
            pTimer->stop();
            bIsShowing = false;
            this->setPalette(QPalette(QColor(0,64,128)));
            break;
        case 1:
            {
                switch(languageFlag)
                {
                    case SIMPLIFIED_CHINESE:
                        sprintf(strTextToShow, "警告");
                        break;
                    case CHINESE_TRADITIONAL:
                        sprintf(strTextToShow, "警告");
                        break;
                    case ENGLISH:
                        sprintf(strTextToShow, "ALARM");
                        break;
                    case JAPANESE:
                        sprintf(strTextToShow, "警告");
                        break;
                    default:
                        break;
                }
            }
            pTimer->start(400);
            break;
        case 2:
            {
                switch(languageFlag)
                {
                    case SIMPLIFIED_CHINESE:
                        sprintf(strTextToShow, "手动报警");
                        break;
                    case CHINESE_TRADITIONAL:
                        sprintf(strTextToShow, "手动报警");
                        break;
                    case ENGLISH:
                        sprintf(strTextToShow, "MAN.ALARM");
                        break;
                    case JAPANESE:
                        sprintf(strTextToShow, "手动报警");
                        break;
                    default:
                        break;
                }
            }
            pTimer->start(400);
            break;
        case 3:
            {
                switch(languageFlag)
                {
                    case SIMPLIFIED_CHINESE:
                        sprintf(strTextToShow, "自动报警");
                        break;
                    case CHINESE_TRADITIONAL:
                        sprintf(strTextToShow, "自动报警");
                        break;
                    case ENGLISH:
                        sprintf(strTextToShow, "AUTO.ALARM");
                        break;
                    case JAPANESE:
                        sprintf(strTextToShow, "自动报警");
                        break;
                    default:
                        break;
                }
            }
            pTimer->start(400);
            break;
        case 4:
            {
                switch(languageFlag)
                {
                    case SIMPLIFIED_CHINESE:
                        sprintf(strTextToShow, "自动报警");
                        break;
                    case CHINESE_TRADITIONAL:
                        sprintf(strTextToShow, "自动报警");
                        break;
                    case ENGLISH:
                        sprintf(strTextToShow, "AUTO.ALARM");
                        break;
                    case JAPANESE:
                        sprintf(strTextToShow, "自动报警");
                        break;
                    default:
                        break;
                }
            }
            pTimer->stop();
            bIsShowing = false;
            this->setPalette(QPalette(QColor(0,64,128)));
            break;
        default:
            break;
    }
}
