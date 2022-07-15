#ifndef ROUNDEDPOINTBOX_H
#define ROUNDEDPOINTBOX_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QtGui/QInputMethodEvent>
#include <QtCore/QEvent>
#include "Model/Point.h"

class PointInsertBox : public QWidget {
private:
Q_OBJECT
    QHBoxLayout *layout;
    QLabel *label;
    QLabel *value;
    QDoubleSpinBox *xSpinBox;
    QDoubleSpinBox *ySpinBox;

    void show(bool);

protected:
    void enterEvent(QEvent *);

    void leaveEvent(QEvent *);

    bool eventFilter(QObject *, QEvent *);

public:
    explicit PointInsertBox(const QString &, QWidget * = nullptr);

    Point getPoint() const;

    void setPoint(double, double) const;

    bool isSet() const;

    bool hasFocus() const;

public slots:
    void hideXBox();

    void hideYBox();

    void keyClicked(int);

    void specialKeyClicked(int);

signals:
    void pointSet();
};


#endif
