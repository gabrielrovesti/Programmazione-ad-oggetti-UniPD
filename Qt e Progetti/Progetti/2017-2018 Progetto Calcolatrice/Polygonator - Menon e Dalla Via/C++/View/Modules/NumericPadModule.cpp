#include "NumericPadModule.h"

NumericPadModule::NumericPadModule(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    one = new RoundedButton("1", this);
    two = new RoundedButton("2", this);
    three = new RoundedButton("3", this);
    four = new RoundedButton("4", this);
    five = new RoundedButton("5", this);
    six = new RoundedButton("6", this);
    seven = new RoundedButton("7", this);
    eight = new RoundedButton("8", this);
    nine = new RoundedButton("9", this);
    zero = new RoundedButton("0", this, 120);
    minus = new RoundedButton("-", this);
    del = new RoundedButton("\u2B60", this);
    ac = new RoundedButton("×", this);
    comma = new RoundedButton(",", this);
    ins = new RoundedButton("INS", this);

    QFont symbolFont=del->font();
    symbolFont.setBold(true);

    ins->setFont(symbolFont);
    comma->setFont(symbolFont);

    symbolFont.setPixelSize(20);

    minus->setFont(symbolFont);
    ac->setFont(symbolFont);
    del->setFont(symbolFont);

    one->setShortcut(Qt::Key_1);
    two->setShortcut(Qt::Key_2);
    three->setShortcut(Qt::Key_3);
    four->setShortcut(Qt::Key_4);
    five->setShortcut(Qt::Key_5);
    six->setShortcut(Qt::Key_6);
    seven->setShortcut(Qt::Key_7);
    eight->setShortcut(Qt::Key_8);
    nine->setShortcut(Qt::Key_9);
    zero->setShortcut(Qt::Key_0);
    minus->setShortcut(Qt::Key_Minus);
    del->setShortcut(Qt::Key_Backspace);
    ac->setShortcut(Qt::Key_Delete);
    comma->setShortcut(Qt::Key_Comma);
    ins->setShortcut(Qt::Key_Return);

    layout->setVerticalSpacing(20);
    layout->setHorizontalSpacing(20);
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    layout->addWidget(one, 0, 0);
    layout->addWidget(two, 0, 1);
    layout->addWidget(three, 0, 2);
    layout->addWidget(four, 1, 0);
    layout->addWidget(five, 1, 1);
    layout->addWidget(six, 1, 2);
    layout->addWidget(seven, 2, 0);
    layout->addWidget(eight, 2, 1);
    layout->addWidget(nine, 2, 2);
    layout->addWidget(zero, 3, 0, 1, 2);
    layout->addWidget(minus, 2, 3);
    layout->addWidget(del, 0, 3);
    layout->addWidget(ac, 1, 3);
    layout->addWidget(comma, 3, 2);
    layout->addWidget(ins, 3, 3);

    one->setFocusPolicy(Qt::NoFocus);
    two->setFocusPolicy(Qt::NoFocus);
    three->setFocusPolicy(Qt::NoFocus);
    four->setFocusPolicy(Qt::NoFocus);
    five->setFocusPolicy(Qt::NoFocus);
    six->setFocusPolicy(Qt::NoFocus);
    seven->setFocusPolicy(Qt::NoFocus);
    eight->setFocusPolicy(Qt::NoFocus);
    nine->setFocusPolicy(Qt::NoFocus);
    zero->setFocusPolicy(Qt::NoFocus);
    minus->setFocusPolicy(Qt::NoFocus);
    del->setFocusPolicy(Qt::NoFocus);
    ac->setFocusPolicy(Qt::NoFocus);
    comma->setFocusPolicy(Qt::NoFocus);
    ins->setFocusPolicy(Qt::NoFocus);

    connect(one, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_1); });
    connect(two, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_2); });
    connect(three, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_3); });
    connect(four, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_4); });
    connect(five, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_5); });
    connect(six, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_6); });
    connect(seven, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_7); });
    connect(eight, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_8); });
    connect(nine, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_9); });
    connect(zero, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_0); });
    connect(minus, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_Minus); });
    connect(del, &RoundedButton::clicked, [=] { emit specialKeyClicked(Qt::Key_Backspace); });
    connect(ac, &RoundedButton::clicked, [=] { emit specialKeyClicked(Qt::Key_Delete); });
    connect(comma, &RoundedButton::clicked, [=] { emit keyClicked(Qt::Key_Comma); });
    connect(ins, &RoundedButton::clicked, [=] { emit specialKeyClicked(Qt::Key_Return); });
}
