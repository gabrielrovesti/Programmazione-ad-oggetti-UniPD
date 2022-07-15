#include "RoundedToggleSwitch.h"

RoundedToggleSwitch::RoundedToggleSwitch(QWidget *parent, int switchWidth) : QAbstractButton(parent), switchHeight(switchWidth/3),
                                                            switched(false), margin(switchWidth/15), thumb("#85b7c4"), brush("#85b7c4"),
                                                            animation(new QPropertyAnimation(this, "offset", this)) {
    setFixedWidth(switchWidth);
    setOffset(switchHeight / 2);
}

void RoundedToggleSwitch::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen(Qt::NoPen);
    if (isEnabled()) {
        p.setBrush(switched ? brush : Qt::black);
        p.setOpacity(switched ? 0.5 : 0.38);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.drawRoundedRect(QRect(margin + 1, margin + 1, width() - 3 * margin, height() - 3 * margin), height()/3.7, height()/3.7);
        p.setBrush(thumb);
        p.setOpacity(1.0);
    } else {
        p.setBrush(Qt::black);
        p.setOpacity(0.12);
        p.drawRoundedRect(QRect(margin + 1, margin + 1, width() - 3 * margin, height() - 3 * margin),  height()/3.7,  height()/3.7);
        p.setOpacity(1.0);
        p.setBrush(QColor("#BDBDBD"));
    }

    p.drawEllipse(QRectF(offset - (switchHeight / 2), 0, height(), height()));
}

void RoundedToggleSwitch::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() & Qt::LeftButton) {
        click();

        switched ? emit switchedOn() : emit switchedOff();
    }
    QAbstractButton::mouseReleaseEvent(event);
}

void RoundedToggleSwitch::enterEvent(QEvent *event) {
    setCursor(Qt::PointingHandCursor);
    QAbstractButton::enterEvent(event);
}

QSize RoundedToggleSwitch::sizeHint() const {
    return {2 * (switchHeight + margin), switchHeight + 2 * margin};
}

void RoundedToggleSwitch::setOffset(int offset) {
    this->offset = offset;
    update();
}

int RoundedToggleSwitch::getOffset() const {
    return offset;
}

bool RoundedToggleSwitch::isSwitched() const {
    return switched;
}

void RoundedToggleSwitch::click() {
    switched ? switchOff() : switchOn();
}

void RoundedToggleSwitch::switchOn() {
    if(switched) {
        return;
    }

    switched=true;
    thumb=brush;
    animation->setStartValue(switchHeight / 2);
    animation->setEndValue(width() - switchHeight);
    animation->setDuration(120);
    animation->start();
}

void RoundedToggleSwitch::switchOff() {
    if(!switched) {
        return;
    }

    switched=false;
    thumb=QBrush("#85b7c4");
    animation->setStartValue(offset);
    animation->setEndValue(switchHeight / 2);
    animation->setDuration(120);
    animation->start();
}

