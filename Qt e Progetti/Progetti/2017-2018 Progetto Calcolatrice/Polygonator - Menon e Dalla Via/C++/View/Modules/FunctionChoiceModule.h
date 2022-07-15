#ifndef FUNCTIONCHOICEMODULE_H
#define FUNCTIONCHOICEMODULE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QtWidgets/QComboBox>
#include "Model/Function.h"
#include "View/Components/RoundedToggleSwitchLabel.h"
#include "View/Components/RoundedButton.h"

class FunctionChoiceModule : public QWidget {
private:
Q_OBJECT
    QList<FunctionType> functionList;
    RoundedButton *calculate;
    RoundedToggleSwitchLabel *all;
    QComboBox *unit;
    QList<RoundedToggleSwitchLabel*> toggleList;
    QVBoxLayout *layout;

public:
    explicit FunctionChoiceModule(QWidget * = nullptr, const QList<FunctionType> & = {});

    //Returns the list of functions selected (switched)
    QList<FunctionType> getSelectedFunctionList() const;

    QString getUnitMeasurement() const;

    //Enables or disables a specific function (permits to set a reason when disables)
    void setFunctionEnabled(const FunctionType &, bool, const QString & = "") const;

    void hideUnitMeasurement(bool) const;

public slots:
    //Switches the 'all' switch on, if possible
    void checkSwitchAll();

    //Enables the 'calculate' button, if possible
    void checkEnableButton();

signals:
    //Sends a "calculate" request
    void calc();
};


#endif
