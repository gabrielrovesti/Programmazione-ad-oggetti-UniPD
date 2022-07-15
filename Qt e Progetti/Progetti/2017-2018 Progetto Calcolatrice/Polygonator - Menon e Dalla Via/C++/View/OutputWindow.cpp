#include "OutputWindow.h"

OutputWindow::OutputWindow(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Polygonator");
    setFixedSize(850, 750);
    setWindowIcon(QIcon(":/icon.png"));
    setFont(QFont("Lucida Sans Unicode", 13, QFont::ExtraLight));

    QRect outputWindowPosition = geometry();
    outputWindowPosition.moveCenter(qApp->desktop()->availableGeometry().center());
    setGeometry(outputWindowPosition);

    graphModule = new GraphModule(this);
    figureType = new QLabel(this);
    resultModule = nullptr;
    backButton = new RoundedButton("Back", this, 100);

    figureType->setStyleSheet("font-weight: bold;"
                              "color: #c1bec6;");

    layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    layout->addWidget(graphModule, 0, Qt::AlignCenter);
    layout->addWidget(figureType, 0, Qt::AlignCenter);

    connect(backButton, SIGNAL(clicked()), this, SLOT(hide()));
}

GraphModule *OutputWindow::getGraph() {
    return graphModule;
}

void OutputWindow::updateFigure(const QList<Point> &points) const {
    graphModule->setGraph(points);
}

void OutputWindow::updateFigureType(const QString &figureName, const QString &regular) const {
    figureType->setText("Figure Type: " + figureName + "\n" + regular);
}

void OutputWindow::updateOutput(const QMap<QString, QString> &output) {
    layout->removeWidget(resultModule);
    layout->removeWidget(backButton);

    delete resultModule;
    resultModule = new ResultModule(this, output);
    resultModule->setFixedWidth(500);

    layout->addWidget(resultModule, 0, Qt::AlignCenter);
    layout->addWidget(backButton, 0, Qt::AlignRight);
}

void OutputWindow::hide() {
    graphModule->clearGraph();

    emit hideWindow();
    QWidget::hide();
}