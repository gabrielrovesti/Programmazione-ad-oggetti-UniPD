#include "PointInsertBox.h"

PointInsertBox::PointInsertBox(const QString &text, QWidget *parent) : QWidget(parent) {
    layout = new QHBoxLayout(this);

    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    label = new QLabel(text, this);
    QFont font = label->font();

    font.setPixelSize(15);
    label->setFont(font);
    label->setFixedSize(30, 30);
    label->setAlignment(Qt::AlignCenter);

    value = new QLabel("", this);

    value->setFixedSize(120, 30);
    value->setAlignment(Qt::AlignCenter);
    value->setStyleSheet("border: 1px solid #85b7c4;"
                                 "border-top-right-radius: 5px;"
                                 "border-bottom-right-radius: 5px;");

    xSpinBox = new QDoubleSpinBox(this);
    ySpinBox = new QDoubleSpinBox(this);

    xSpinBox->installEventFilter(this);
    xSpinBox->setFixedSize(60, 30);
    xSpinBox->setDecimals(2);
    xSpinBox->setRange(-100, +100);
    xSpinBox->setSingleStep(0.01);
    xSpinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
    xSpinBox->setStyleSheet("QDoubleSpinBox {"
                                    "border-top: 1px solid #85b7c4;"
                                    "border-bottom: 1px solid #85b7c4;"
                                    "}");
    xSpinBox->setToolTip("Set the x value");
    xSpinBox->setToolTipDuration(2000);
    connect(xSpinBox, SIGNAL(editingFinished()), this, SLOT(hideXBox()));

    ySpinBox->installEventFilter(this);
    ySpinBox->setFixedSize(60, 30);
    ySpinBox->setDecimals(2);
    ySpinBox->setRange(-100, +100);
    ySpinBox->setSingleStep(0.01);
    ySpinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
    ySpinBox->setStyleSheet("QDoubleSpinBox {"
                                    "border: 1px solid #85b7c4;"
                                    "border-top-right-radius: 5px;"
                                    "border-bottom-right-radius: 5px;"
                                    "}");
    ySpinBox->setToolTip("Set the y value");
    ySpinBox->setToolTipDuration(2000);
    connect(ySpinBox, SIGNAL(editingFinished()), this, SLOT(hideYBox()));

    layout->addWidget(label);
    layout->addWidget(value);
    layout->addWidget(xSpinBox);
    layout->addWidget(ySpinBox);

    show(false);
    value->setText("( X , Y )");
}

Point PointInsertBox::getPoint() const {
    return {xSpinBox->value(), ySpinBox->value()};
}

void PointInsertBox::setPoint(double x, double y) const {
    xSpinBox->setValue(x);
    ySpinBox->setValue(y);

    if(!value->isHidden()) {
        value->setText(("(" + QString::number(xSpinBox->value(), 'f', 2).toStdString() + "," + QString::number(ySpinBox->value(), 'f', 2).toStdString() + ")").c_str());
    }
}

void PointInsertBox::show(bool show) {
    if(show) {
        value->hide();
        xSpinBox->show();
        ySpinBox->show();

        label->setStyleSheet("background: #85b7c4;"
                                     "border-top: 1px solid #85b7c4;"
                                     "border-bottom: 1px solid #85b7c4;"
                                     "border-left: 1px solid #85b7c4;"
                                     "border-top-left-radius: 5px;"
                                     "border-bottom-left-radius: 5px;");
    } else {
        xSpinBox->hide();
        ySpinBox->hide();
        value->show();

        value->setText(("(" + QString::number(xSpinBox->value(), 'f', 2).toStdString() + "," + QString::number(ySpinBox->value(), 'f', 2).toStdString() + ")").c_str());
        label->setStyleSheet("background: rgba(133, 183, 196, 0.5);"
                                     "border-top: 1px solid #85b7c4;"
                                     "border-bottom: 1px solid #85b7c4;"
                                     "border-left: 1px solid #85b7c4;"
                                     "border-top-left-radius: 5px;"
                                     "border-bottom-left-radius: 5px;");
    }
}

void PointInsertBox::enterEvent(QEvent *event) {
    show(true);

    QWidget::enterEvent(event);
}

void PointInsertBox::leaveEvent(QEvent *event) {
    if(!xSpinBox->hasFocus() && !ySpinBox->hasFocus()) {
        bool set = isSet();
        show(false);

        if(!set) {
            emit pointSet();
        }
    }

    QWidget::leaveEvent(event);
}

bool PointInsertBox::eventFilter(QObject *sender, QEvent *event) {
    if(event->type() == QEvent::ShortcutOverride) {
        event->ignore();
        return true;
    }

    if(event->type() == QEvent::Type::KeyPress) {
        int key = static_cast<QKeyEvent *>(event)->key();

        switch(key) {
            case Qt::Key_Delete:
                if(sender == xSpinBox) {
                    xSpinBox->selectAll();
                } else if(sender == ySpinBox) {
                    ySpinBox->selectAll();
                }
                break;
            case Qt::Key_Period:
                keyClicked(Qt::Key_Comma);
                event->ignore();
                return true;
            case Qt::Key_Enter:
                specialKeyClicked(Qt::Key_Return);
                event->ignore();
                return true;
        }
    }

    return QObject::eventFilter(sender, event);
}

void PointInsertBox::hideXBox() {
    if(!ySpinBox->hasFocus()) {
        show(false);
        emit pointSet();
    }
}

void PointInsertBox::hideYBox() {
    if(!xSpinBox->hasFocus()) {
        show(false);
        emit pointSet();
    }
}

bool PointInsertBox::isSet() const {
    return value->text() != "( X , Y )";
}

bool PointInsertBox::hasFocus() const {
    return xSpinBox->hasFocus() || ySpinBox->hasFocus();
}

void PointInsertBox::keyClicked(int key) {
    if(xSpinBox->hasFocus()) {
        QInputMethodEvent event;
        event.setCommitString(QKeySequence(key).toString());
        xSpinBox->event(&event);
    } else if(ySpinBox->hasFocus()) {
        QInputMethodEvent event;
        event.setCommitString(QKeySequence(key).toString());
        ySpinBox->event(&event);
    }
}

void PointInsertBox::specialKeyClicked(int key) {
    if(xSpinBox->hasFocus()) {
        if(key == Qt::Key_Return) {
            ySpinBox->setFocus(Qt::FocusReason::OtherFocusReason);
            ySpinBox->selectAll();
            return;
        }

        if(key == Qt::Key_Delete) {
            xSpinBox->selectAll();
        }

        xSpinBox->event(new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier));
    } else if(ySpinBox->hasFocus()) {
        if(key == Qt::Key_Return) {
            ySpinBox->clearFocus();
            return;
        }

        if(key == Qt::Key_Delete) {
            ySpinBox->selectAll();
        }

        ySpinBox->event(new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier));
    }
}
