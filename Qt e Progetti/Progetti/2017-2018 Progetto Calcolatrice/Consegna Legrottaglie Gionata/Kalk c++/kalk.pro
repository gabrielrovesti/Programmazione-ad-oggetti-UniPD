#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T19:41:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kalk
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        View/MainWindow.cpp \
    View/GraphicsScene.cpp \
    View/GraphicsCoordinateAxisItem.cpp \
    calcolatrice/cerchio.cpp \
    calcolatrice/poligono.cpp \
    calcolatrice/poligonoconvesso.cpp \
    calcolatrice/punto.cpp \
    calcolatrice/shape.cpp \
    calcolatrice/vertice.cpp \
    View/figure.cpp \
    calcolatrice/PoligoniConvessi/decagono.cpp \
    calcolatrice/PoligoniConvessi/dodecagono.cpp \
    calcolatrice/PoligoniConvessi/endecagono.cpp \
    calcolatrice/PoligoniConvessi/ennadecagono.cpp \
    calcolatrice/PoligoniConvessi/ennagono.cpp \
    calcolatrice/PoligoniConvessi/eptadecagono.cpp \
    calcolatrice/PoligoniConvessi/esadecagono.cpp \
    calcolatrice/PoligoniConvessi/esagono.cpp \
    calcolatrice/PoligoniConvessi/ettagono.cpp \
    calcolatrice/PoligoniConvessi/icosagono.cpp \
    calcolatrice/PoligoniConvessi/ottadecagono.cpp \
    calcolatrice/PoligoniConvessi/ottagono.cpp \
    calcolatrice/PoligoniConvessi/pentadecagono.cpp \
    calcolatrice/PoligoniConvessi/pentagono.cpp \
    calcolatrice/PoligoniConvessi/quadrilatero.cpp \
    calcolatrice/PoligoniConvessi/tetradecagono.cpp \
    calcolatrice/PoligoniConvessi/triangolo.cpp \
    calcolatrice/PoligoniConvessi/tridecagono.cpp \
    View/aggiungifigura.cpp \
    View/sceltavertice.cpp \
    Controller/controllerproprieta.cpp \
    View/figurepolygon.cpp \
    View/figureellipse.cpp \
    Controller/controller.cpp

HEADERS += \
        View/MainWindow.h \
    View/GraphicsScene.h \
    View/GraphicsCoordinateAxisItem.h \
    calcolatrice/PoligoniConvessi/dodecagono.h \
    calcolatrice/PoligoniConvessi/decagono.h \
    calcolatrice/PoligoniConvessi/endecagono.h \
    calcolatrice/PoligoniConvessi/ennadecagono.h \
    calcolatrice/PoligoniConvessi/ennagono.h \
    calcolatrice/PoligoniConvessi/eptadecagono.h \
    calcolatrice/PoligoniConvessi/esadecagono.h \
    calcolatrice/PoligoniConvessi/ettagono.h \
    calcolatrice/PoligoniConvessi/esagono.h \
    calcolatrice/PoligoniConvessi/icosagono.h \
    calcolatrice/PoligoniConvessi/ottadecagono.h \
    calcolatrice/PoligoniConvessi/ottagono.h \
    calcolatrice/PoligoniConvessi/pentadecagono.h \
    calcolatrice/PoligoniConvessi/pentagono.h \
    calcolatrice/PoligoniConvessi/quadrilatero.h \
    calcolatrice/PoligoniConvessi/tetradecagono.h \
    calcolatrice/PoligoniConvessi/tridecagono.h \
    calcolatrice/PoligoniConvessi/triangolo.h \
    calcolatrice/cerchio.h \
    calcolatrice/poligono.h \
    calcolatrice/poligonoconvesso.h \
    calcolatrice/punto.h \
    calcolatrice/shape.h \
    calcolatrice/vertice.h \
    View/figure.h \
    View/aggiungifigura.h \
    View/sceltavertice.h \
    Controller/controllerproprieta.h \
    View/figurepolygon.h \
    View/figureellipse.h \
    Controller/controller.h

FORMS += \
        View/mainwindow.ui \
    View/aggiungifigura.ui \
    View/sceltavertice.ui
