#ifndef ROUNDEDBUTTON_H
#define ROUNDEDBUTTON_H

#include <QPushButton>

class RoundedButton : public QPushButton {
private:
Q_OBJECT

protected:
    void enterEvent(QEvent *);

public:
    explicit RoundedButton(QWidget * = nullptr, int = 50, int = 50);

    explicit RoundedButton(const QString &, QWidget * = nullptr, int = 50, int = 50);

    explicit RoundedButton(const QIcon &, QWidget * = nullptr, int = 50, int = 50);

    RoundedButton(const QIcon &, const QString &, QWidget * = nullptr, int = 50, int = 50);
};


#endif
