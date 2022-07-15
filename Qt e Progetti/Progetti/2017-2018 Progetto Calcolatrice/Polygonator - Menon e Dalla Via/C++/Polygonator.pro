TEMPLATE = app
TARGET   = Polygonator
QT       += widgets
QMAKE_CXXFLAGS += -std=c++11
RESOURCES += resources.qrc

SOURCES += main.cpp \
    Model/Exception.cpp \
    Model/Function.cpp \
    Model/Line.cpp \
    Model/Point.cpp \
    Model/PolygonFactory.cpp \
    Model/Polygons/Hexagon.cpp \
    Model/Polygons/Kite.cpp \
    Model/Polygons/Parallelogram.cpp \
    Model/Polygons/Pentagon.cpp \
    Model/Polygons/Polygon.cpp \
    Model/Polygons/Quadrilateral.cpp \
    Model/Polygons/Rectangle.cpp \
    Model/Polygons/Rhombus.cpp \
    Model/Polygons/Square.cpp \
    Model/Polygons/Triangle.cpp \
    View/MainWindow.cpp \
    View/OutputWindow.cpp \
    View/Components/ErrorLabel.cpp \
    View/Components/PointInsertBox.cpp \
    View/Components/RoundedButton.cpp \
    View/Components/RoundedToggleSwitch.cpp \
    View/Components/RoundedToggleSwitchLabel.cpp \
    View/Modules/FunctionChoiceModule.cpp \
    View/Modules/GraphModule.cpp \
    View/Modules/NumericPadModule.cpp \
    View/Modules/PointChoiceModule.cpp \
    View/Modules/PointInsertModule.cpp \
    View/Modules/ResultModule.cpp \
    Controller/MainWindowController.cpp

HEADERS  += \
    Model/Exception.h \
    Model/Function.h \
    Model/Line.h \
    Model/Point.h \
    Model/PolygonFactory.h \
    Model/Polygons/Hexagon.h \
    Model/Polygons/Kite.h \
    Model/Polygons/Parallelogram.h \
    Model/Polygons/Pentagon.h \
    Model/Polygons/Polygon.h \
    Model/Polygons/Quadrilateral.h \
    Model/Polygons/Rectangle.h \
    Model/Polygons/Rhombus.h \
    Model/Polygons/Square.h \
    Model/Polygons/Triangle.h \
    View/MainWindow.h \
    View/OutputWindow.h \
    View/Components/ErrorLabel.h \
    View/Components/PointInsertBox.h \
    View/Components/RoundedButton.h \
    View/Components/RoundedToggleSwitch.h \
    View/Components/RoundedToggleSwitchLabel.h \
    View/Modules/FunctionChoiceModule.h \
    View/Modules/GraphModule.h \
    View/Modules/NumericPadModule.h \
    View/Modules/PointChoiceModule.h \
    View/Modules/PointInsertModule.h \
    View/Modules/ResultModule.h \
    Controller/MainWindowController.h
