#include "PointInsertModule.h"

PointInsertModule::PointInsertModule(int pointNumber, QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    layout->setVerticalSpacing(15);
    layout->setHorizontalSpacing(5);
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    char letter = 'A';

    for(int i=0; pointNumber!=0; i++) {
        for(int j=0; j<2 && pointNumber!=0; j++, pointNumber--, letter++) {
            PointInsertBox *pointInsertBox = new PointInsertBox(QString(letter), this);

            points.push_back(pointInsertBox);

            if(pointNumber == 1 && j == 0) {
                layout->addWidget(pointInsertBox, i, j, 1, 2, Qt::AlignCenter);
            } else {
                layout->addWidget(pointInsertBox, i, j);
            }

            connect(pointInsertBox, SIGNAL(pointSet()), this, SLOT(pointSet()));
            connect(this, SIGNAL(keyClicked(int)), pointInsertBox, SLOT(keyClicked(int)));
            connect(this, SIGNAL(specialKeyClicked(int)), pointInsertBox, SLOT(specialKeyClicked(int)));
        }
    }
}

QList<Point> PointInsertModule::getPoints() const {
    QList<Point> pointList;

    for(PointInsertBox *point : points) {
        pointList.push_back(point->getPoint());
    }

    return pointList;
}

void PointInsertModule::updatePoints(const QList<Point> &points) const {
    for(int i=0; i<points.size(); i++) {
        this->points.at(i)->setPoint(points.at(i).getX(), points.at(i).getY());
    }
}

void PointInsertModule::pointSet() {
    bool allSet = true;
    for(PointInsertBox *point : points) {
        if(!point->isSet() || point->hasFocus()) {
            allSet = false;
            break;
        }
    }

    if(allSet) {
        emit allPointsSet();
    }
}