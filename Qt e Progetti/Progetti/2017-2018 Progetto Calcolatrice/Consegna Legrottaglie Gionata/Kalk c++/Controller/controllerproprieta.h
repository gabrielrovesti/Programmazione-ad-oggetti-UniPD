#ifndef CONTROLLERPROPRIETA_H
#define CONTROLLERPROPRIETA_H

#include <QObject>
#include <QTableWidget>
#include "./View/GraphicsScene.h"
class GraphicsScene;
class ControllerProprieta: public QObject
{
    Q_OBJECT
public:
  explicit ControllerProprieta(GraphicsScene *, QTableWidget *, QObject * = nullptr);
private:
    GraphicsScene *m_pGraphicsScene = nullptr;
    QTableWidget *m_tableWidget = nullptr;

signals:

public slots:

private slots:
    void onItemPropertyChanged();

};

#endif // CONTROLLERPROPRIETA_H
