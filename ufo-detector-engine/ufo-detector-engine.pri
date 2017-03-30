
QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:CONFIG += windows
win64:CONFIG += windows


include(opencv.pri)

# https://bugreports.qt.io/browse/QTBUG-4329
INCLUDEPATH += $$PWD

SOURCES += $$PWD/recorder.cpp \
    actualdetector.cpp \
    camera.cpp \
    Ctracker.cpp \
    Detector.cpp \
    Kalman.cpp \
    HungarianAlg.cpp \
    config.cpp \
    camerainfo.cpp \
    videocodecsupportinfo.cpp \
    $$PWD/planechecker.cpp \
    $$PWD/detectorstate.cpp

HEADERS  += recorder.h \
    actualdetector.h \
    camera.h \
    Ctracker.h \
    Detector.h \
    Kalman.h \
    HungarianAlg.h \
    config.h \
    camerainfo.h \
    videocodecsupportinfo.h \
    $$PWD/planechecker.h \
    $$PWD/detectorstate.h
