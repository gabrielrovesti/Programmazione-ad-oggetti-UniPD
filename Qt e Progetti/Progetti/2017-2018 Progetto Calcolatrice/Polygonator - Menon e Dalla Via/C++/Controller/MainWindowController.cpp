#include "MainWindowController.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent) {
    point = nullptr;
    line = nullptr;
    polygon = nullptr;

    mainWindow = new MainWindow();
    outputWindow = new OutputWindow();

    mainWindow->show();

    connect(mainWindow, &MainWindow::calc, [=] {
        mainWindow->hide();

        outputWindow->updateFigure(polygon ? QList<Point>::fromStdList(polygon->getVertices()) : mainWindow->getPoints());
        outputWindow->updateFigureType(QString::fromStdString(point ? "Point" : (line ? "Line" : polygon->getName())),
                                       polygon ? (polygon->isRegular() ? "Regular" : "Not regular") : "");

        QList<FunctionType> functionList = mainWindow->getSelectedFunctionList();
        QMap<QString, QString> functionValues;

        for(FunctionType functionType : functionList) {
            QString functionName = QString::fromStdString(Function::getFunctionName(functionType));
            QString unit = mainWindow->getUnitMeasurement();

            int counter = 1;

            switch(functionType) {
                case FunctionType::MIDPOINT:
                    functionValues.insert(functionName, "(" + QString::number(line->getMidPoint().getX(), 'f', 2) + "," + QString::number(line->getMidPoint().getY(), 'f', 2) + ")");
                    outputWindow->getGraph()->addPoint(line->getMidPoint(), 'M', "Middle Point");
                    break;
                case FunctionType::LENGTH:
                    functionValues.insert(functionName, QString::number(line->getDistance(), 'f', 2) + (unit != "" ? QString(" " + unit) : ""));
                    break;
                case FunctionType::EQUATION:
                    functionValues.insert(functionName, QString::fromStdString(point ? point->getEquation() : line->getEquation()));
                    break;
                case FunctionType::AREA:
                    functionValues.insert(functionName, QString::number(polygon->getArea(), 'f', 2) + (unit != "" ? QString(" " + unit + "\u00B2") : ""));
                    break;
                case FunctionType::PERIMETER:
                    functionValues.insert(functionName, QString::number(polygon->getPerimeter(), 'f', 2) + (unit != "" ? QString(" " + unit) : ""));
                    break;
                case FunctionType::BASE:
                    functionValues.insert(functionName, QString::number(polygon->getBase(), 'f', 2) + (unit != "" ? QString(" " + unit) : ""));
                    break;
                case FunctionType::HEIGHT:
                    functionValues.insert(functionName, QString::number(polygon->getHeight(), 'f', 2) + (unit != "" ? QString(" " + unit) : ""));
                    break;
                case FunctionType::APOTHEM:
                    functionValues.insert(functionName, QString::number(polygon->getApothem(), 'f', 2) + (unit != "" ? QString(" " + unit) : ""));
                    break;
                case FunctionType::DIAGONALS:
                    for(Line line : polygon->getDiagonals()) {
                        functionValues.insert("Diagonal " + QString::number(counter),
                                              QString::number(line.getDistance(), 'f', 2) + (unit != "" ? QString(" " + unit) : ""));
                        outputWindow->getGraph()->addLine(line.getA(), line.getB(), "Diagonal " + QString::number(counter),
                                                          QPen(QColor("#61858e"), 1.5, Qt::PenStyle::SolidLine), 0.5);
                        counter++;
                    }
                    break;
                case FunctionType::BISECTORS:
                    for(Line line : static_cast<Triangle *>(polygon)->getBisectors()) {
                        functionValues.insert("Bisector " + QString::number(counter),
                                              QString::number(line.getDistance(), 'f', 2) + (unit != "" ? QString(" " + unit) : ""));
                        outputWindow->getGraph()->addLine(line.getA(), line.getB(), "Bisector " + QString::number(counter),
                                                          QPen(QColor("#61858e"), 1.5, Qt::PenStyle::SolidLine), 0.5);
                        counter++;
                    }
                    break;
                case FunctionType::MEDIANS:
                    for(Line line : static_cast<Triangle *>(polygon)->getMedians()) {
                        functionValues.insert("Median " + QString::number(counter),
                                              QString::number(line.getDistance(), 'f', 2) + (unit != "" ? QString(" " + unit) : ""));
                        outputWindow->getGraph()->addLine(line.getA(), line.getB(), "Median " + QString::number(counter),
                                                          QPen(QColor("#61858e"), 1.5, Qt::PenStyle::SolidLine), 0.5);
                        counter++;
                    }
                    break;
            }
        }

        outputWindow->updateOutput(functionValues);

        outputWindow->show();
    });

    connect(mainWindow, &MainWindow::setFigure, [=] {
        delete point;
        delete line;
        delete polygon;

        point = nullptr;
        line = nullptr;
        polygon = nullptr;

        QList<Point> points = mainWindow->getPoints();

        try {
            switch(points.size()) {
                case 1:
                    point = new Point(points.first());
                    break;
                case 2:
                    line = new Line(points.first(), points.last());
                    break;
                default:
                    polygon = PolygonFactory::makePolygon(mainWindow->getPoints().toStdList());
                    break;
            }

            mainWindow->clearGraph();
            mainWindow->setGraph(polygon ? QList<Point>::fromStdList(polygon->getVertices()) : mainWindow->getPoints());
            if(polygon) {
                mainWindow->updatePoints(QList<Point>::fromStdList(polygon->getVertices()));

                mainWindow->setFunctionEnabled(FunctionType::BASE, false, "Cannot calculate the base of a concave polygon");
                mainWindow->setFunctionEnabled(FunctionType::HEIGHT, false, "Cannot calculate the height of an irregular polygon");
                mainWindow->setFunctionEnabled(FunctionType::APOTHEM, false, "Cannot calculate the apothem of an irregular polygon");
                if(!polygon->isConcave()) {
                    mainWindow->setFunctionEnabled(FunctionType::BASE, true);

                    if(polygon->isRegular() || dynamic_cast<Triangle *>(polygon) || dynamic_cast<Parallelogram *>(polygon)) {
                        mainWindow->setFunctionEnabled(FunctionType::HEIGHT, true);
                    }

                    if(polygon->isRegular() || dynamic_cast<Triangle *>(polygon)) {
                        mainWindow->setFunctionEnabled(FunctionType::APOTHEM, true);
                    }
                }
            }
            mainWindow->updateFigureType(QString::fromStdString(point ? "Point" : (line ? "Line" : polygon->getName())),
                                         polygon ? (polygon->isRegular() ? "Regular" : "Not regular") : "");
            mainWindow->enableFunctionChoice(true);
        } catch(Exception &ex) {
            mainWindow->sendError(ex.getReason().c_str());
            mainWindow->clearGraph();
            mainWindow->updateFigureType("Unknown", "");
            mainWindow->enableFunctionChoice(false);
        }
    });

    connect(outputWindow, SIGNAL(hideWindow()), mainWindow, SLOT(show()));
}

MainWindowController::~MainWindowController() {
    delete point;
    delete line;
    delete polygon;
}
