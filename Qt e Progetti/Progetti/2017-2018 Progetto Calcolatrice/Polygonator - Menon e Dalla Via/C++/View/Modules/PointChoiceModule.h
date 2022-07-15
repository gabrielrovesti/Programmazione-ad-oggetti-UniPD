#ifndef POINTCHOICEMODULE_H
#define POINTCHOICEMODULE_H

#include <QWidget>
#include <QGridLayout>
#include <QtCore/QMap>
#include "View/Components/RoundedButton.h"

class PointChoiceModule : public QWidget {
private:
Q_OBJECT
    QGridLayout *layout;
    QMap<int, RoundedButton *> points;
    RoundedButton *back;
    RoundedButton *next;
    int menuPage;

    void addPoint(int, const QString &, const QString &, const QString &);

    void updatePointNumber(int);

    void switchPage(int);

public:
    explicit PointChoiceModule(QWidget * = nullptr);

signals:
    void pointChoice(int);
};


#endif
