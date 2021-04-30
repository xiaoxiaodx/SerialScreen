QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mywidget/mybutton.cpp \
    mywidget/mygraph.cpp \
    mywidget/mylabel.cpp \
    mywidget/mypage.cpp \
    mywidget/myprogressbar.cpp \
    mywidget/myradio.cpp \
    mywidget/myrolllabel.cpp \
    mywidget/mysilder.cpp \
    shape/Shape.cpp \
    shape/marc.cpp \
    shape/mcurve.cpp \
    shape/mdashboard.cpp \
    shape/mimage.cpp \
    shape/mline.cpp \
    shape/mpoint.cpp \
    shape/mrect.cpp \
    shape/mtext.cpp \
    utils/debuglog.cpp \
    utils/resourcesmanager.cpp


HEADERS += \
    mainwindow.h \
    mywidget/mybutton.h \
    mywidget/mygraph.h \
    mywidget/mylabel.h \
    mywidget/mypage.h \
    mywidget/myprogressbar.h \
    mywidget/myradio.h \
    mywidget/myrolllabel.h \
    mywidget/mysilder.h \
    shape/Shape.h \
    shape/marc.h \
    shape/mcurve.h \
    shape/mdashboard.h \
    shape/mimage.h \
    shape/mline.h \
    shape/mpoint.h \
    shape/mrect.h \
    shape/mtext.h \
    uart/cmdproc.h \
    uart/tty_dev.h \
    uart/uarttest.h \
    util.h \
    utils/debuglog.h \
    utils/resourcesmanager.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
