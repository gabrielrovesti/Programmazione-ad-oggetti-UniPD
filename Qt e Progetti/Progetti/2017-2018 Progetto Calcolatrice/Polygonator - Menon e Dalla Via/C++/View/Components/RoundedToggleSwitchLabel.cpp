#include "RoundedToggleSwitchLabel.h"

RoundedToggleSwitchLabel::RoundedToggleSwitchLabel(const QString &text, QWidget *parent, int labelWidth, int toggleSwitchWidth) : QWidget(parent) {
    toggleSwitch = new RoundedToggleSwitch(this, toggleSwitchWidth);

    connect(toggleSwitch, SIGNAL(clicked()), this, SIGNAL(clicked()));
    connect(toggleSwitch, SIGNAL(switchedOn()), this, SIGNAL(switchedOn()));
    connect(toggleSwitch, SIGNAL(switchedOff()), this, SIGNAL(switchedOff()));

    label = new QLabel(text, this);

    label->setFixedWidth(labelWidth);
    label->setWordWrap(true);

    layout = new QHBoxLayout(this);

    layout->setSpacing(15);
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    layout->addWidget(label);
    layout->addWidget(toggleSwitch);
}

void RoundedToggleSwitchLabel::setBold(bool bold) {
    QFont font = label->font();
    font.setBold(bold);
    label->setFont(font);
}

void RoundedToggleSwitchLabel::setLabelWidth(int labelWidth) {
    label->setFixedWidth(labelWidth);
}

void RoundedToggleSwitchLabel::setTextAlignment(Qt::Alignment alignment) {
    label->setAlignment(alignment);
}

bool RoundedToggleSwitchLabel::isSwitched() const {
    return toggleSwitch->isSwitched();
}

QString RoundedToggleSwitchLabel::getLabel() const {
    return label->text();
}

void RoundedToggleSwitchLabel::click() {
    toggleSwitch->click();
}

void RoundedToggleSwitchLabel::switchOn() {
    if(isEnabled()) {
        toggleSwitch->switchOn();
    }
}

void RoundedToggleSwitchLabel::switchOff() {
    toggleSwitch->switchOff();
}
