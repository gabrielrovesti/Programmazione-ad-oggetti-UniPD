#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QWidget>
#include <QTimer>
#include <QGridLayout>
#include "Model/Function.h"
#include "View/Components/ErrorLabel.h"
#include "View/Modules/GraphModule.h"
#include "View/Modules/PointChoiceModule.h"
#include "View/Modules/FunctionChoiceModule.h"
#include "View/Modules/NumericPadModule.h"
#include "View/Modules/PointInsertModule.h"

class MainWindow : public QWidget {
private:
Q_OBJECT
    QGridLayout *layout;

    PointInsertModule *pointInsertModule;
    GraphModule *graphModule;
    PointChoiceModule *pointChoiceModule;
    QLabel *figureType;
    NumericPadModule *numericPadModule;
    FunctionChoiceModule *functionChoiceModule;
    ErrorLabel *errorLabel;

public:
    explicit MainWindow(QWidget * = nullptr);

    //Returns the list of points inserted
    QList<Point> getPoints() const;

    //Updates the point values in PointInsertModule
    void updatePoints(const QList<Point> &) const;

    QList<FunctionType> getSelectedFunctionList() const;

    QString getUnitMeasurement() const;

    void updateFigureType(const QString &, const QString &) const;

    void enableFunctionChoice(bool) const;

    //Enables or disables a function (permits to set a reason when disables)
    void setFunctionEnabled(const FunctionType &, bool, const QString & = "") const;

    void setGraph(const QList<Point> &) const;

    void clearGraph() const;

    void sendError(const QString &) const;

protected:
    //Reimplemented to make the MainWindow clickable
    void mousePressEvent(QMouseEvent*);

public slots:
    //Shows the correct number of points and the correct list of functions available, depending on the PointChoice
    void updatePointNumber(int);

signals:
    //Sends a "calculate" request
    void calc();

    void setFigure();
};


#endif
