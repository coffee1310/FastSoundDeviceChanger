#ifndef DESKTOPWIDGET_H
#define DESKTOPWIDGET_H

#include <QWidget>
#include <QCoreApplication>
#include <QAudioDeviceInfo>

class DesktopWidget : public QWidget {
private:
    QCoreApplication a ();
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::aviableDevice(QAudio::AudioOutput);
public:
    DesktopWidget(QWidget *parent = nullptr) : QWidget(parent) {

    }
};

#endif // DESKTOPWIDGET_H
