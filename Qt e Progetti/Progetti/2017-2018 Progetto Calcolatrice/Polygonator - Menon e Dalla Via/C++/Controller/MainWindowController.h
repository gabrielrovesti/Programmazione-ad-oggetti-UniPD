#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QtCore/QObject>
#include "Model/PolygonFactory.h"
#include "View/OutputWindow.h"
#include "View/MainWindow.h"

class MainWindowController : public QObject {
private:
Q_OBJECT
    Point *point;
    Line *line;
    Polygonator::Polygon* polygon;

    MainWindow *mainWindow;
    OutputWindow *outputWindow;
public:
    explicit MainWindowController(QObject *parent = nullptr);

    ~MainWindowController();
};


#endif
