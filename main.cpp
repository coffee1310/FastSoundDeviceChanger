#include "DesktopWidget.h"
#include <QApplication>
#include "RtAudio.h"
#include <windows.h>
#include <vector>


int main(int argc, char *argv[])
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::vector<RtAudio::DeviceInfo> names;

    get_device_names(names);

    QApplication a(argc, argv);
    a.setStyleSheet("background-color: #242424;");
    a.setStyleSheet("font-family: kreon;");
    a.setStyleSheet("font-weight: 700;");

    DesktopWidget desktopWidget;
    desktopWidget.resize(512, 512);
    desktopWidget.setStyleSheet("background-color: #242424;");
    desktopWidget.show(); // Отобразить виджет на рабочем столе
    return a.exec();
}
