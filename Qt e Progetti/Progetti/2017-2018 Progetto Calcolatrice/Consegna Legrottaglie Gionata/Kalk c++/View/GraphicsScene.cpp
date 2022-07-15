#include "GraphicsScene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include "GraphicsCoordinateAxisItem.h"
#include "MainWindow.h"
#include<QVBoxLayout>
GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{

    addItem(new GraphicsCoordinateAxisItem);

    connect(this,SIGNAL(selectionChanged()),this,SLOT(refreshSelect()));
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    emit cursorChanged(mouseEvent->scenePos(), mouseEvent->screenPos());
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
void GraphicsScene::setController(Controller* c){
  controller=c;
}

//slot
void  GraphicsScene::refreshSelect(){
    if(dynamic_cast<MainWindow*>(parent())){
        (static_cast<MainWindow*>(parent()))->disattivaButtonPoligono();
        auto listaItems = selectedItems();
        if(listaItems.length() == 1){
            if(dynamic_cast<FigurePolygon*>(listaItems.last())){
                (static_cast<MainWindow*>(parent()))->attivaButtonPoligono(1);
              }
            else if(dynamic_cast<FigureEllipse*>(listaItems.last())){
                (static_cast<MainWindow*>(parent()))->attivaButtonPoligono(2);
              }
        }
        else if(listaItems.length() >1){
            if(listaItems.length() == 2 && dynamic_cast<FigurePolygon*>(listaItems.first()) && dynamic_cast<FigurePolygon*>(listaItems.last())){
                (static_cast<MainWindow*>(parent()))->disattivaButtonPoligono();
                (static_cast<MainWindow*>(parent()))->attivaButtonPoligono(3);
              }
            else{
                (static_cast<MainWindow*>(parent()))->disattivaButtonPoligono();
                (static_cast<MainWindow*>(parent()))->attivaButtonPoligono(4);
              }

        }
        else
            (static_cast<MainWindow*>(parent()))->disattivaButtonPoligono();
    }
}
void GraphicsScene::rimuoviSelezionati(){
  controller->rimuoviSelezionati();
}


