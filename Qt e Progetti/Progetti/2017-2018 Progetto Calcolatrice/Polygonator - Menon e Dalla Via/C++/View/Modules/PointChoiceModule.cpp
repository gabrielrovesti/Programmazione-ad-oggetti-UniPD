#include "PointChoiceModule.h"

PointChoiceModule::PointChoiceModule(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    layout->setSpacing(20);
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    addPoint(1, "Point", ":/point.png", "Ctrl+P");
    addPoint(2, "Line", ":/line.png", "Ctrl+L");
    addPoint(3, "Triangle", ":/triangle.png", "Ctrl+T");
    addPoint(4, "Quadrilateral", ":/quadrilateral.png", "Ctrl+Q");
    addPoint(5, "Pentagon", ":/pentagon.png", "Ctrl+P");
    addPoint(6, "Hexagon", ":/hexagon.png", "Ctrl+H");

    back = new RoundedButton("\u2B60", this, 20, 20);
    back->setShortcut(tr("Ctrl+B"));
    back->setToolTip("Back");
    layout->addWidget(back, 0, 0);

    next = new RoundedButton("\u2B62", this, 20, 20);
    next->setShortcut(tr("Ctrl+N"));
    next->setToolTip("Next");
    layout->addWidget(next, 0, 4);

    updatePointNumber(4); //By default, we assume the user wants a quadrilateral

    connect(back, &RoundedButton::clicked, [=] { switchPage(menuPage-1); });
    connect(next, &RoundedButton::clicked, [=] { switchPage(menuPage+1); });
}

void PointChoiceModule::addPoint(int pointNumber, const QString &toolTip, const QString &icon, const QString &shortcut) {
    RoundedButton *button = new RoundedButton(QIcon(icon), toolTip, this);

    button->setStyleSheet(button->styleSheet() + "QPushButton:!enabled {background: #85b7c4;}");
    button->setShortcut(tr(shortcut.toStdString().c_str()));
    button->hide();

    layout->addWidget(button, 0, pointNumber%3 == 0 ? 3 : pointNumber%3);

    connect(button, &RoundedButton::clicked, [=] {
        updatePointNumber(pointNumber);
        emit pointChoice(pointNumber);
    });

    points.insert(pointNumber, button);
}

void PointChoiceModule::updatePointNumber(int pointNumber) {
    switchPage((pointNumber-1)/3 + 1);

    for(int i=1; i<=points.size(); i++) {
        points.value(i)->setEnabled(i != pointNumber);
    }
}

void PointChoiceModule::switchPage(int pageNumber) {
    menuPage = pageNumber;

    for(int i=1; i<=points.size(); i++) {
        (((i-1)/3)+1)==menuPage ? points.value(i)->show() : points.value(i)->hide();
    }

    back->setEnabled(menuPage != 1);
    next->setEnabled(menuPage != ceil(points.size()/3.0));
}