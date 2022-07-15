#ifndef POINTINSERTMODULE_H
#define POINTINSERTMODULE_H

#include <QWidget>
#include <QGridLayout>
#include "View/Components/PointInsertBox.h"

class PointInsertModule : public QWidget {
private:
Q_OBJECT
    QGridLayout *layout;
    QList<PointInsertBox *> points;

public:
    explicit PointInsertModule(int, QWidget * = nullptr);

    QList<Point> getPoints() const;

    //Updates the point values
    void updatePoints(const QList<Point> &) const;

public slots:
    //Checks if all points are set
    void pointSet();

signals:
    void allPointsSet();

    void keyClicked(int);

    void specialKeyClicked(int);
};


#endif
