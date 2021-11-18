QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Distribution.cpp \
    Generator.cpp \
    Histogram.cpp \
    TID_Generator.cpp \
    TISM_Generator.cpp \
    dialog_model.cpp \
    dialog_plevels.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    probdist.cpp

HEADERS += \
    Distribution.h \
    Generator.h \
    Histogram.h \
    TID_Generator.h \
    TISM_Generator.h \
    dialog_model.h \
    dialog_plevels.h \
    mainwindow.h \
    model.h \
    probdist.h

FORMS += \
    dialog_model.ui \
    dialog_plevels.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




