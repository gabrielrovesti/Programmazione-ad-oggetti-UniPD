#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QVBoxLayout>
#include "View/Modules/FunctionChoiceModule.h"
#include "View/Modules/ResultModule.h"
#include "View/Components/RoundedButton.h"
#include "View/Modules/GraphModule.h"

class OutputWindow : public QWidget {
private:
Q_OBJECT
    GraphModule *graphModule;
    QLabel *figureType;
    ResultModule *resultModule;
    RoundedButton *backButton;

    QVBoxLayout *layout;

public:
    explicit OutputWindow(QWidget * = nullptr);

    GraphModule* getGraph();

    void updateFigure(const QList<Point> &) const;

    void updateFigureType(const QString &, const QString &) const;

    void updateOutput(const QMap<QString, QString> &);

public slots:
    void hide();

signals:
    void hideWindow();
};


#endif
