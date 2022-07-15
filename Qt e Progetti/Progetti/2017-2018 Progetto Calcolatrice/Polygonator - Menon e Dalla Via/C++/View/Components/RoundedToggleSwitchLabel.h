#ifndef ROUNDEDTOGGLESWITCHLABEL_H
#define ROUNDEDTOGGLESWITCHLABEL_H

#include <QHBoxLayout>
#include <QLabel>
#include "RoundedToggleSwitch.h"

class RoundedToggleSwitchLabel : public QWidget {
private:
Q_OBJECT
    RoundedToggleSwitch *toggleSwitch;
    QLabel *label;
    QHBoxLayout *layout;

public:
    explicit RoundedToggleSwitchLabel(const QString &, QWidget * = nullptr, int = 150, int= 50);

    void setBold(bool);

    void setLabelWidth(int);

    void setTextAlignment(Qt::Alignment);

    bool isSwitched() const;

    QString getLabel() const;

public slots:
    //Switches the toggleSwitch
    void click();

    void switchOn();

    void switchOff();

signals:
    void clicked();

    void switchedOn();

    void switchedOff();
};


#endif
