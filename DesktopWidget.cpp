#include "DesktopWidget.h"
#include <QWidget>
#include <QCoreApplication>
#include <QPushButton>
#include "RtAudio.h"
#include <QLabel>
#include <QVBoxLayout>

int get_device_names(std::vector<RtAudio::DeviceInfo>& names)
{
    RtAudio rtaudio;
    int min_id = 0;
    int id = min_id;
    int device_count = rtaudio.getDeviceCount();

    if (device_count == 0) {
        return 1;
    }

    while (min_id == 0) {
        min_id = rtaudio.getDeviceInfo(id).ID;
        id++;
    }

    for (int i = id; i < id + device_count; i++) {
        names.push_back(rtaudio.getDeviceInfo(i));
        std::cout << rtaudio.getDeviceInfo(i).name << std::endl;
        std::cout << rtaudio.getDeviceInfo(i).inputChannels << std::endl;
    }

    return 0;
}

bool isInputDevice(RtAudio::DeviceInfo info)
{
    std::cout << info.inputChannels << std:: endl;
    return true;
}

DesktopWidget::DesktopWidget(QWidget *parent) : QWidget(parent) {
    app = QCoreApplication::instance();
    //QPushButton* button = new QPushButton("Нажми меня", this);
    //connect(button, &QPushButton::clicked, this, &DesktopWidget::handleButtonClick);
    get_device_names(names);

    for (size_t i = 0; i < names.size(); i++) {
        QLabel* device = new QLabel(this);
        QFont font = device->font();
        font.setFamily("Kreon");
        font.setPointSize(20);
        device->setFont(font);

        QString device_name = QString::fromStdString(names[i].name);
        device->setText(device_name);

        device->setStyleSheet("color: white;"
                              "padding: 10;"
                              "font-weight: 700;"
                              "");
        names_layout->addWidget(device);
        names_layout->setAlignment(Qt::AlignCenter);
        isInputDevice(names[i]);
    }

}

void DesktopWidget::handleButtonClick() {
    if (app) {
        app->sendEvent(this, new QEvent(QEvent::User));
    }
}

