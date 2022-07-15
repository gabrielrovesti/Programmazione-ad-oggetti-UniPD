#ifndef RESULTMODULE_H
#define RESULTMODULE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QtCore/QMultiMap>

class ResultModule : public QWidget {
private:
Q_OBJECT
    QMultiMap<QString, QString> results;
    QGridLayout *layout;

public:
    explicit ResultModule(QWidget * = nullptr, const QMultiMap<QString, QString> & = {});
};


#endif
