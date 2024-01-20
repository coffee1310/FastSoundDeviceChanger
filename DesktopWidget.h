#ifndef DESKTOPWIDGET_H
#define DESKTOPWIDGET_H

#include <QWidget>
#include <QCoreApplication>
#include <QPushButton>
#include "RtAudio.h"
#include <QVBoxLayout>
int get_device_names(std::vector<RtAudio::DeviceInfo>& names);

class DesktopWidget : public QWidget {
    Q_OBJECT
private:
    QCoreApplication* app;
    std::vector<RtAudio::DeviceInfo> names;
    QVBoxLayout* names_layout = new QVBoxLayout(this);
public:
    DesktopWidget(QWidget *parent = nullptr);
private slots:
    void handleButtonClick();
};

#endif // DESKTOPWIDGET_H
