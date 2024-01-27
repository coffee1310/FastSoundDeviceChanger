#ifndef DESKTOPWIDGET_H
#define DESKTOPWIDGET_H

#include <QWidget>
#include <QCoreApplication>
#include <QPushButton>
#include "RtAudio.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>

int get_device_names(std::vector<RtAudio::DeviceInfo>& names);

class DesktopWidget : public QWidget {
    Q_OBJECT
private:
    QCoreApplication* app;
    std::vector<RtAudio::DeviceInfo> names;
    QVBoxLayout* devices_layout = new QVBoxLayout(this);
    QButtonGroup* inputs_devices = new QButtonGroup(this);
    QButtonGroup* output_devices = new QButtonGroup(this);
public:
    DesktopWidget(QWidget *parent = nullptr);
private slots:
    void handleButtonClick();
};

#endif // DESKTOPWIDGET_H
