#ifndef ERRORLABEL_H
#define ERRORLABEL_H

#include <QtWidgets/QLabel>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>

class ErrorLabel : public QLabel {
private:
Q_OBJECT
    QPropertyAnimation *animation;
    QList<QString> errors;

public:
    explicit ErrorLabel(QWidget * = nullptr);

    void sendError(const QString &);
};


#endif
