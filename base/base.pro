QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mqttsubscriber.cpp \
    steganography.cpp

HEADERS += \
    mainwindow.h \
    mqttsubscriber.h \
    steganography.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    steganography.h

INCLUDEPATH += /home/louis/paho.mqtt.c/src

LIBS += -L/home/louis/paho.mqtt.c/build/output \
        -lpaho-mqtt3c

INCLUDEPATH += /home/louis/paho.mqtt.cpp/src

LIBS += -L/home/louis/paho.mqtt.cpp/build/output \
        -lpaho-mqttpp3

RESOURCES += \
    img.qrc
