#include "DesktopWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopWidget desktopWidget;
    desktopWidget.show(); // Отобразить виджет на рабочем столе

    return a.exec();
}
