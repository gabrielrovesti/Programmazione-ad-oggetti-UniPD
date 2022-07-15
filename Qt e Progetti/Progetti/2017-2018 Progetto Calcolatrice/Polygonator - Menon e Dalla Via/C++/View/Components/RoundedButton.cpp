#include "RoundedButton.h"

RoundedButton::RoundedButton(QWidget *parent, int width, int height) : QPushButton(parent) {
    setFixedSize(width, height);

    setStyleSheet("QPushButton {"
                  "border-radius: " + QString::number(height/2) + "px;"
                  "border: 1px solid #85b7c4;"
                  "background: #c1bec6;"
                  "}"
                  ""
                  "QPushButton:hover, QPushButton:pressed {"
                  "background: #85b7c4;"
                  "}");
}

RoundedButton::RoundedButton(const QString &text, QWidget *parent, int width, int height) : RoundedButton(parent, width, height) {
    setText(text);
}

RoundedButton::RoundedButton(const QIcon &icon, QWidget *parent, int width, int height) : RoundedButton(parent, width, height) {
    setIcon(icon);
}

RoundedButton::RoundedButton(const QIcon &icon, const QString &toolTip, QWidget *parent, int width, int height) : RoundedButton(parent, width, height) {
    setIcon(icon);
    setToolTip(toolTip);
    setToolTipDuration(2000);
}

void RoundedButton::enterEvent(QEvent *e) {
    setCursor(Qt::PointingHandCursor);
    QPushButton::enterEvent(e);
}