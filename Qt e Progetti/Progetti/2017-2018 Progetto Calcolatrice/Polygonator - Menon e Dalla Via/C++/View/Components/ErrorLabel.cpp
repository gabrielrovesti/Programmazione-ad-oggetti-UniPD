#include "ErrorLabel.h"

ErrorLabel::ErrorLabel(QWidget *parent) : QLabel(parent) {
    setFixedSize(500, 40);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("background-color: rgba(225, 227, 232, 0.5);"
                  "border-bottom-left-radius: 5px;"
                  "border-bottom-right-radius: 5px;"
                  "border-color: rgba(193, 190, 198, 0.5);"
                  "border-style: solid;"
                  "border-width: 0px 1px 1px 1px;"
                  "color: #9b290c;"
                  "opacity: 0.8;");

    animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setStartValue(QRect(QPoint(115, -40), size()));
    animation->setEndValue(QRect(QPoint(115, 0), size()));

    hide();

    connect(animation, &QPropertyAnimation::finished, [=] {
        if(animation->direction() == QVariantAnimation::Forward) {
            if(!errors.isEmpty()) {
                setText(errors.takeFirst());

                QTimer::singleShot(3000, this, [=] {
                    animation->finished();
                });
            } else {
                QTimer::singleShot(3000, this, [=] {
                    animation->setDirection(QVariantAnimation::Backward);
                    animation->start();
                });
            }
        } else {
            animation->setDirection(QVariantAnimation::Forward);

            if(!errors.isEmpty()) {
                setText(errors.takeFirst());
                animation->start();
            } else {
                setText("");
                hide();
            }
        }
    });
}

void ErrorLabel::sendError(const QString &error) {
    if(text() == "") {
        setText(error);
        show();
        animation->start();
    } else {
        errors.append(error);
    }
}