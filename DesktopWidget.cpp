#include "DesktopWidget.h"
#include <QWidget>
#include <QCoreApplication>
#include <QPushButton>
#include "RtAudio.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QRadioButton>
#include <QGroupBox>

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
    std::cout << "Input chanels " << info.inputChannels << std::endl;
    if (info.inputChannels > 0) {
        return true;
    }
    return false;
}

DesktopWidget::DesktopWidget(QWidget *parent) : QWidget(parent) {
    app = QCoreApplication::instance();
    //QPushButton* button = new QPushButton("Нажми меня", this);
    //connect(button, &QPushButton::clicked, this, &DesktopWidget::handleButtonClick);
    get_device_names(names);

    for (size_t i = 0; i < names.size() - 1; i++) {
        QLabel* device = new QLabel(this);
        QFont font = device->font();
        QLabel* device_icon;
        QPixmap device_label_icon;
        QHBoxLayout* device_layout = new QHBoxLayout(this);
        QVBoxLayout* names_layout = new QVBoxLayout(this);
        QString device_name = QString::fromStdString(names[i].name);
        QRadioButton* change_device = new QRadioButton(this);
        font.setFamily("SF Pro Display");
        font.setPointSize(15);
        device->setFont(font);

        device->setText(device_name);
        device->setStyleSheet("color: white;"
                              "padding: 0;"
                              "font-weight: 500;"
                              "width:500px;");
        device->setWordWrap(true);
        device->setFixedWidth(500);
        device->setAlignment(Qt::AlignCenter);

        change_device->setStyleSheet("QRadioButton {"
                                     "margin:0;"
                                     "}"
                                     "QRadioButton::indicator {"
                                     "  width: 20px;"
                                     "  height: 20px;"
                                     "  border-radius: 13px;"
                                     "  border: 3px solid white;"
                                     "}"
                                     "QRadioButton::indicator:checked {"
                                     "  background-color:white;"
                                     "  border: 3px solid white;"
                                     "}");

        if (isInputDevice(names[i])) {
            device_label_icon.load("C:\\Users\\user\\Desktop\\projects\\FastSoundDeviceChanger\\FastSoundDeviceChanger\\images\\microphone.png");
            inputs_devices->addButton(change_device);

            QLabel* device_type = new QLabel("Microphone");
            device_type->setStyleSheet("color: white;"
                                       "padding: 0;");
            device_type->setAlignment(Qt::AlignCenter);

            device_icon = new QLabel(this);
            device_label_icon = device_label_icon.scaled(75, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            device_icon->setPixmap(device_label_icon);

            names_layout->addWidget(device);
            names_layout->addWidget(device_type);
            names_layout->setAlignment(Qt::AlignCenter);
            device_icon->setParent(this);

        }
        else {
            device_label_icon.load("C:\\Users\\user\\Desktop\\projects\\FastSoundDeviceChanger\\FastSoundDeviceChanger\\images\\headphones.png");
            output_devices->addButton(change_device);

            QLabel* device_type = new QLabel("Headphones");
            device_type->setStyleSheet("color: white;"
                                       "padding: 0;");
            device_type->setAlignment(Qt::AlignCenter);

            device_icon = new QLabel(this);
            device_label_icon = device_label_icon.scaled(75, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            device_icon->setPixmap(device_label_icon);

            names_layout->addWidget(device);
            names_layout->addWidget(device_type);
            names_layout->setAlignment(Qt::AlignCenter);
            device_icon->setParent(this);

        }

        device_layout->addWidget(device_icon);
        //device_layout->addWidget(device);
        device_layout->addLayout(names_layout);
        device_layout->addWidget(change_device);
        device_layout->setAlignment(Qt::AlignLeft);
        devices_layout->addLayout(device_layout);;
        devices_layout->setAlignment(Qt::AlignCenter);
    }

}

void DesktopWidget::handleButtonClick() {
    if (app) {
        app->sendEvent(this, new QEvent(QEvent::User));
    }
}

