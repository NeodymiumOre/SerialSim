QT += core gui
QT += serialport
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/chartwindow.cpp \
    src/vehicle.cpp \
    src/chart.cpp

HEADERS += \
    inc/mainwindow.hpp \
    inc/chartwindow.hpp \
    inc/vehicle.hpp \
    inc/chart.hpp

FORMS += \
    ui/mainwindow.ui \
    ui/chartwindow.ui

TRANSLATIONS += \
    serial-sim_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += inc src ui
