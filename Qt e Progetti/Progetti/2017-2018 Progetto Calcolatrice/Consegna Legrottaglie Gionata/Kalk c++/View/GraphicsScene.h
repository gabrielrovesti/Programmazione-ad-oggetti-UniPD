#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "figureellipse.h"
#include "figurepolygon.h"
#include<QWheelEvent>
#include<QTimeLine>
#include "./Controller/controller.h"
class Controller;

class GraphicsScene : public QGraphicsScene
{
  friend class MainWindow;
    Q_OBJECT

public:
     explicit GraphicsScene(QObject *parent = nullptr);
     ~GraphicsScene() =default;
     void wheelEvent ( QWheelEvent * );


signals:
    void cursorChanged( const QPointF &scenePos, const QPointF &screenPos);
public slots:
    void rimuoviSelezionati();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
private slots:
    void refreshSelect();
private:
    Controller* controller;
    void setController(Controller*);
};


#endif // GRAPHICSSCENE_H
