#include "strongMainWin.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Windows"));
    MainWin w;
    w.show();

    return a.exec();
}
