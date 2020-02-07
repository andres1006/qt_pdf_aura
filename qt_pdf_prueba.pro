QT += core gui dbus sql quick
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport



CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG +=qml_debug

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    process.cpp \
    data.cpp \
    logger.cpp \
    qutils.cpp \
    utilsprocess.cpp \
    aurajson.cpp \
    pdfreporthelper.cpp \
    pdfreport.cpp \
    oscannplot.cpp \
    qcustomplot.cpp \
    videopreview.cpp


LIBS += \
    -L/usr/local/lib \
    -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs \
    -lmongocxx \
    -lbsoncxx \

HEADERS += \
    data.h \
    process.h \
    logger.h \
    qutils.h \
    utilsprocess.h \
    aurajson.h \
    pdfreporthelper.h \
    pdfreport.h \
    oscannplot.h \
    qcustomplot.h \
    videopreview.h
