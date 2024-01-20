QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += WIN32
DEFINES += __WINDOWS_DS__

SOURCES += \
    DesktopWidget.cpp \
    main.cpp \
    mainwindow.cpp \
    RtAudio.cpp \
    #lib/RtAudio/RtAudio.cpp  # Добавьте RtAudio.cpp в список исходных файлов

HEADERS += \
    DesktopWidget.h \
    mainwindow.h \
    RtAudio.h \
    #lib/RtAudio/RtAudio.h  # Помните также указать путь к RtAudio.h

INCLUDEPATH += $$PWD/lib
INCLUDEPATH += lib/RtAudio



LIBS += -ldsound
LIBS += -lole32
LIBS += -lwinmm


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
