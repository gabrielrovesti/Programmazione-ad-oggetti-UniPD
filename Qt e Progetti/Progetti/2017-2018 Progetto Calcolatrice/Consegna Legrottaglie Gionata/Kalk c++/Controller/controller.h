#ifndef CONTROLLER_H
#define CONTROLLER_H

#include"./View/MainWindow.h"
#include"./calcolatrice/cerchio.h"
#include"./calcolatrice/PoligoniConvessi/triangolo.h"
#include"./View/figureellipse.h"
#include"./View/figurepolygon.h"
#include"./View/GraphicsScene.h"
#include<QMessageBox>

class MainWindow;
class GraphicsScene;
class Controller
{

public:
  Controller(MainWindow*,GraphicsScene*);
  ~Controller() = default;

  FigurePolygon* sommaFigure(FigurePolygon*,FigurePolygon*);
  FigurePolygon* sottraiFigure(FigurePolygon*,FigurePolygon*);
  void aggiungiFigura( Figure *);
  void cambiaFigura(QList<Figure *>::iterator, Figure *);
  void rimuoviFigura(QList<Figure *>::iterator);
  Figure** getFigura(Shape*);
  const QList<Figure *> *getLista()const;
  QGraphicsItem * selectedItemFirst() const;
  void rimuoviSelezionati();

private:
  MainWindow *mainw;
  QList<Figure*> listaFigure;
  GraphicsScene* scena;

};

#endif // CONTROLLER_H
