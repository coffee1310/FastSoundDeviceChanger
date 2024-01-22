#include "DesktopWidget.h"
#include <QWidget>
#include <QCoreApplication>
#include <QPushButton>
#include "RtAudio.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>

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

    for (size_t i = 0; i < names.size(); i++) {
        QLabel* device = new QLabel(this);
        QFont font = device->font();
        QLabel* device_icon;
        QPixmap device_label_icon;
        QHBoxLayout* device_layout = new QHBoxLayout(this);

        if (device_label_icon.load("C:\\Users\\user\\Desktop\\projects\\FastSoundDeviceChanger\\FastSoundDeviceChanger\\images\\microphone.png")) {
            if (isInputDevice(names[i])) {
                // Изображение успешно загружено
                device_icon = new QLabel(this);
                device_label_icon = device_label_icon.scaled(100,100, Qt::KeepAspectRatio);
                device_icon->setPixmap(device_label_icon);

                // Добавляем QLabel с иконкой в ваш интерфейс
                device_icon->setParent(this);
                //device_icon->setGeometry(10,10,50,50);
            }
            else {
                // Изображение успешно загружено
                device_icon = new QLabel(this);
                device_label_icon = device_label_icon.scaled(100,100, Qt::KeepAspectRatio);
                device_icon->setPixmap(device_label_icon);

                // Добавляем QLabel с иконкой в ваш интерфейс
                device_icon->setParent(this);
                //device_icon->setGeometry(10,10,50,50);
            }

        } else {
            // Обработка ошибки загрузки изображения
            qDebug() << "Ошибка загрузки изображения";
        }

        font.setFamily("Kreon");
        font.setPointSize(20);
        device->setFont(font);

        QString device_name = QString::fromStdString(names[i].name);
        device->setText(device_name);

        device->setStyleSheet("color: white;"
                              "padding: 0;"
                              "font-weight: 700;");
        device_layout->addWidget(device_icon);
        device_layout->addWidget(device);
        device_layout->setAlignment(Qt::AlignLeft);
        devices_layout->addLayout(device_layout);;
        devices_layout->setAlignment(Qt::AlignCenter);
        isInputDevice(names[i]);
    }

}

void DesktopWidget::handleButtonClick() {
    if (app) {
        app->sendEvent(this, new QEvent(QEvent::User));
    }
}

