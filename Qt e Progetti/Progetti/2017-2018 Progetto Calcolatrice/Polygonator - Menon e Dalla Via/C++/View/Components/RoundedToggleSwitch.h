#ifndef ROUNDEDTOGGLESWITCH_H
#define ROUNDEDTOGGLESWITCH_H

#include <QAbstractButton>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

class RoundedToggleSwitch: public QAbstractButton {
private:
Q_OBJECT
    Q_PROPERTY(int offset READ getOffset WRITE setOffset)

    bool switched;
    int offset, switchHeight, margin;
    QBrush thumb, brush;
    QPropertyAnimation *animation;

protected:
    //Draws the toggleSwitch
    void paintEvent(QPaintEvent *);

    //Animation on click
    void mouseReleaseEvent(QMouseEvent *);

    void enterEvent(QEvent *);

public:
    explicit RoundedToggleSwitch(QWidget * = nullptr, int = 50);

    QSize sizeHint() const;

    int getOffset() const;

    void setOffset(int);

    bool isSwitched() const;

public slots:
    //Switches the toggle switch
    void click();

    void switchOn();

    void switchOff();

signals:
    void switchedOn();

    void switchedOff();
};


#endif
