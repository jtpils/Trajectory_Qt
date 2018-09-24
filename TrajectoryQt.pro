#-------------------------------------------------
#
# Project created by QtCreator 2018-08-14T20:09:21
#
#-------------------------------------------------

QT       += core gui xml opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrajectoryQt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#eigen
INCLUDEPATH += /usr/include/eigen3
#vtk
INCLUDEPATH+=/usr/include/vtk-6.2
LIBS+=/usr/lib/x86_64-linux-gnu/libvtk*.so
#boost
INCLUDEPATH+=/usr/include/boost
LIBS+=/usr/lib/x86_64-linux-gnu/libboost*.so
#PCL
INCLUDEPATH+=/usr/include/pcl-1.7
LIBS+=/usr/lib/x86_64-linux-gnu/libpcl_*.so
#G2O
INCLUDEPATH+=/usr/local/include/g2o
LIBS+=/usr/local/lib/libg2o_*.so
#Cholmod
INCLUDEPATH+=/usr/include/suitesparse
LIBS+=/usr/lib/x86_64-linux-gnu/libcholmod.so
#CSparse
LIBS+=/usr/lib/x86_64-linux-gnu/libcsparse.so
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    trajectory.cpp \
    MyVtkWidget.cpp

HEADERS += \
        mainwindow.h \
    tracjectory.h \
    MyVtkWidget.h \
    myfunction.h

FORMS += \
        mainwindow.ui


