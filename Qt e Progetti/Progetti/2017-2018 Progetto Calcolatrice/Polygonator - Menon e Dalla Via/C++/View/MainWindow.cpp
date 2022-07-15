#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Polygonator");
    setFixedSize(850, 750);
    setWindowIcon(QIcon(":/icon.png"));
    setFont(QFont("Lucida Sans Unicode", 10, QFont::ExtraLight));

    QRect mainWindowPosition = geometry();
    mainWindowPosition.moveCenter(qApp->desktop()->availableGeometry().center());
    setGeometry(mainWindowPosition);

    pointInsertModule = nullptr;
    graphModule = new GraphModule(this);
    pointChoiceModule = new PointChoiceModule(this);
    figureType = new QLabel("Figure Type: Unknown", this);
    numericPadModule = new NumericPadModule(this);
    functionChoiceModule = nullptr;
    errorLabel = new ErrorLabel(this);

    figureType->setStyleSheet("font-weight: bold;"
                                       "color: #c1bec6;");

    layout = new QGridLayout(this);

    layout->setHorizontalSpacing(50);
    layout->setVerticalSpacing(20);
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    layout->addWidget(graphModule, 0, 1, Qt::AlignRight);
    layout->addWidget(figureType, 1, 0, 1, 2, Qt::AlignRight);
    layout->addWidget(pointChoiceModule, 2, 0, Qt::AlignCenter);
    layout->addWidget(numericPadModule, 3, 0, Qt::AlignCenter);
    layout->addWidget(errorLabel, 0, 0, 1, 2, Qt::AlignTop | Qt::AlignHCenter);

    connect(pointChoiceModule, SIGNAL(pointChoice(int)), this, SLOT(updatePointNumber(int)));

    updatePointNumber(4); //By default, we assume the user wants a quadrilateral
}

QList<Point> MainWindow::getPoints() const {
    return pointInsertModule->getPoints();
}

QList<FunctionType> MainWindow::getSelectedFunctionList() const {
    return functionChoiceModule->getSelectedFunctionList();
}

QString MainWindow::getUnitMeasurement() const {
    return functionChoiceModule->getUnitMeasurement();
}

void MainWindow::updatePoints(const QList<Point> &points) const {
    pointInsertModule->updatePoints(points);
}

void MainWindow::updateFigureType(const QString &figureName, const QString &regular) const {
    figureType->setText("Figure Type: " + figureName + "\n" + regular);
}

void MainWindow::enableFunctionChoice(bool enabled) const {
    functionChoiceModule->setEnabled(enabled);
}

void MainWindow::setFunctionEnabled(const FunctionType &functionType, bool enable, const QString &reason) const {
    functionChoiceModule->setFunctionEnabled(functionType, enable, reason);
}

void MainWindow::setGraph(const QList<Point> &points) const {
    graphModule->setGraph(points);
}

void MainWindow::clearGraph() const {
    graphModule->clearGraph();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    setFocus();
    QWidget::mousePressEvent(event);
}

void MainWindow::sendError(const QString &reason) const {
    errorLabel->sendError(reason);
}

void MainWindow::updatePointNumber(int pointNumber) {
    clearGraph();
    updateFigureType("Unknown", "");

    layout->removeWidget(pointInsertModule);
    delete pointInsertModule;
    pointInsertModule = new PointInsertModule(pointNumber, this);

    layout->removeWidget(functionChoiceModule);
    delete functionChoiceModule;
    functionChoiceModule=new FunctionChoiceModule(this, QList<FunctionType>::fromStdList(Function::getFunctionList(pointNumber)));

    if(pointNumber == 1) {
        functionChoiceModule->hideUnitMeasurement(true);
    }
    functionChoiceModule->setEnabled(false);

    layout->addWidget(pointInsertModule, 0, 0, Qt::AlignCenter);
    layout->addWidget(functionChoiceModule, 2, 1, 2, 1, Qt::AlignRight);

    connect(functionChoiceModule, SIGNAL(calc()), this, SIGNAL(calc()));

    connect(numericPadModule, SIGNAL(keyClicked(int)), pointInsertModule, SIGNAL(keyClicked(int)));
    connect(numericPadModule, SIGNAL(specialKeyClicked(int)), pointInsertModule, SIGNAL(specialKeyClicked(int)));

    connect(pointInsertModule, &PointInsertModule::allPointsSet, [=] { emit setFigure(); });
}
