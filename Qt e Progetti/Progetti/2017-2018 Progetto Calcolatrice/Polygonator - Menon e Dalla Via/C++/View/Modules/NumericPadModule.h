#ifndef NUMERICPADMODULE_H
#define NUMERICPADMODULE_H

#include <QWidget>
#include <QGridLayout>
#include "View/Components/RoundedButton.h"

class NumericPadModule : public QWidget {
private:
Q_OBJECT
    QGridLayout *layout;

    RoundedButton *one;
    RoundedButton *two;
    RoundedButton *three;
    RoundedButton *four;
    RoundedButton *five;
    RoundedButton *six;
    RoundedButton *seven;
    RoundedButton *eight;
    RoundedButton *nine;
    RoundedButton *zero;
    RoundedButton *minus;
    RoundedButton *del;
    RoundedButton *ac;
    RoundedButton *comma;
    RoundedButton *ins;

public:
    explicit NumericPadModule(QWidget * = nullptr);

signals:
    void keyClicked(int);

    void specialKeyClicked(int);
};


#endif
