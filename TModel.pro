QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/dialog_power.cpp \
    source/Distribution.cpp \
    source/Generator.cpp \
    source/Histogram.cpp \
    source/TID_Generator.cpp \
    source/TISM_Generator.cpp \
    source/dialog_model.cpp \
    source/dialog_plevels.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/model.cpp \
    source/probdist.cpp

HEADERS += \
    includes/dialog_power.h \
    includes/Distribution.h \
     includes/Generator.h \
     includes/Histogram.h \
     includes/TID_Generator.h \
     includes/TISM_Generator.h \
     includes/dialog_model.h \
     includes/dialog_plevels.h \
     includes/mainwindow.h \
     includes/model.h \
     includes/probdist.h \

FORMS += \
    ui/dialog_model.ui \
    ui/dialog_plevels.ui \
    ui/dialog_power.ui \
    ui/mainwindow.ui

INCLUDEPATH+= includes/
INCLUDEPATH+= ui/
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




