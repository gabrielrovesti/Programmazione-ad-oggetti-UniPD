#include "FunctionChoiceModule.h"

FunctionChoiceModule::FunctionChoiceModule(QWidget *parent, const QList<FunctionType> &functionList) : QWidget(parent),
                                                                                                  functionList(functionList) {
    calculate= new RoundedButton("Calculate", this, 120);
    calculate->setEnabled(false);
    connect(calculate, SIGNAL(clicked()), this, SIGNAL(calc()));

    all = new RoundedToggleSwitchLabel("ALL", this, 50, 30);
    connect(all, SIGNAL(clicked()), this, SLOT(checkEnableButton()));

    unit = new QComboBox(this);
    unit->setFixedSize(150, 30);
    unit->addItems({"Unit of measure", "mm", "cm", "m", "in", "ft", "yd"});
    unit->setToolTip("Click to change the unit of measure");
    unit->setStyleSheet("QComboBox {"
                        "background: transparent;"
                        "border-width: 0px;"
                        "border-bottom: 2px solid #85b7c4;"
                        "border-radius: 0px;"
                        "selection-background-color: transparent;"
                        "selection-color: black;"
                        "}"
                        ""
                        "QComboBox::drop-down {"
                        "border: 0px;"
                        "}"
                        ""
                        "QComboBox::down-arrow {"
                        "image: url(:/down-arrow.png);"
                        "padding-top: 5px;"
                        "width: 18px;"
                        "height: 18px;"
                        "}"
                        ""
                        "QComboBox QAbstractItemView {"
                        "background: #efefef;"
                        "selection-background-color: #85b7c4;"
                        "}");

    layout = new QVBoxLayout(this);

    layout->setSpacing(5);
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    layout->addWidget(all, 0, Qt::AlignRight);

    for (const auto &row : functionList) {
        RoundedToggleSwitchLabel *toggle = new RoundedToggleSwitchLabel(Function::getFunctionName(row).c_str(), this);

        toggleList.push_back(toggle);
        layout->addWidget(toggle);

        connect(all, SIGNAL(switchedOn()), toggle, SLOT(switchOn()));
        connect(all, SIGNAL(switchedOff()), toggle, SLOT(switchOff()));
        connect(toggle, SIGNAL(switchedOff()), all, SLOT(switchOff()));
        connect(toggle, SIGNAL(switchedOn()), this, SLOT(checkSwitchAll()));
        connect(toggle, SIGNAL(clicked()), this, SLOT(checkEnableButton()));
    }

    layout->addWidget(unit, 0, Qt::AlignRight);
    layout->addWidget(calculate, 0, Qt::AlignCenter);
    layout->insertSpacing(functionList.size()+1, 15);
    layout->insertSpacing(functionList.size()+3, 15);
}

QList<FunctionType> FunctionChoiceModule::getSelectedFunctionList() const {
    QList<FunctionType> functionList;
    for(const auto &toggle : toggleList) {
        if(toggle->isSwitched()) {
            functionList.push_back(Function::fromString(toggle->getLabel().toStdString()));
        }
    }
    return functionList;
}

QString FunctionChoiceModule::getUnitMeasurement() const {
    if(unit->currentIndex() == 0) {
        return "";
    }

    return unit->currentText();
}

void FunctionChoiceModule::setFunctionEnabled(const FunctionType &functionType, bool enable, const QString &reason) const {
    for(const auto &toggle : toggleList) {
        if(toggle->getLabel().toStdString() == Function::getFunctionName(functionType)) {
            toggle->setEnabled(enable);
            toggle->setToolTip(reason);
        }
    }
}

void FunctionChoiceModule::hideUnitMeasurement(bool hide) const {
    if(hide && !unit->isHidden()) {
        unit->hide();
    } else if (!hide && unit->isHidden()) {
        unit->show();
    }
}

void FunctionChoiceModule::checkSwitchAll() {
    bool allSwitched = true;

    for(RoundedToggleSwitchLabel *toggle : toggleList) {
        if(toggle->isEnabled() && !toggle->isSwitched()) {
            allSwitched = false;
            break;
        }
    }

    if(allSwitched) {
        all->switchOn();
    }
}

void FunctionChoiceModule::checkEnableButton() {
    bool oneSwitched = false;

    for(RoundedToggleSwitchLabel *toggle : toggleList) {
        if(toggle->isSwitched()) {
            oneSwitched = true;
            break;
        }
    }

    calculate->setEnabled(oneSwitched);
}
