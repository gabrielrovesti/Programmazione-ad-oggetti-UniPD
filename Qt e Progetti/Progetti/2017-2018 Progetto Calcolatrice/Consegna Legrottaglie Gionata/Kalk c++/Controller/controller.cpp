#include "controller.h"

Controller::Controller(MainWindow * m,GraphicsScene* s):mainw(m),scena(s)
{

}

FigurePolygon* Controller::sommaFigure(FigurePolygon* f1,FigurePolygon*f2){
  if(dynamic_cast<PoligonoConvesso*>(f1->getPunt()) && dynamic_cast<PoligonoConvesso*>(f2->getPunt())){

      try{
        FigurePolygon* nuovaFigura = new FigurePolygon(*(static_cast<PoligonoConvesso*>(f1->getPunt())) + *(static_cast<PoligonoConvesso*>(f2->getPunt())));
        scena->rimuoviSelezionati();
        aggiungiFigura(nuovaFigura);
        return nuovaFigura;
      }
      catch(std::invalid_argument& e){
        return nullptr;
      }

    }
  else return nullptr;
}
FigurePolygon* Controller::sottraiFigure(FigurePolygon*f1,FigurePolygon*f2){
  if(dynamic_cast<PoligonoConvesso*>(f1->getPunt()) && dynamic_cast<PoligonoConvesso*>(f2->getPunt())){
      try{
        FigurePolygon* nuovaFigura = new FigurePolygon(*(static_cast<PoligonoConvesso*>(f1->getPunt())) - *(static_cast<PoligonoConvesso*>(f2->getPunt())));
        bool found = false;
        for(auto it=listaFigure.begin();it!=listaFigure.end() && !found;it++){
            if((*it)->getPunt() == f1->getPunt()){
                scena->removeItem((scena->selectedItems().first()));

                delete *it;
                it = listaFigure.erase(it);
                found=true;
              }
          }
        aggiungiFigura(nuovaFigura);
        return nuovaFigura;
      }
      catch(std::invalid_argument& e){

        QString err = e.what();
        QMessageBox::StandardButton answer;
        answer = QMessageBox::warning(mainw , QString("Errore"),QString(err + "\nImpossibile creare una figura"));
        return nullptr;
      }
    }
  else return nullptr;
}

void Controller::aggiungiFigura(Figure* f){
    listaFigure.push_back(f);
    f->setCursor(Qt::PointingHandCursor);
    scena->addItem(f);
}
void Controller::cambiaFigura(QList<Figure*>::iterator it, Figure* f){
    *it=f;
    f->setCursor(Qt::PointingHandCursor);
    scena->addItem(f);
}
void Controller::rimuoviFigura(QList<Figure*>::iterator it){
    scena->removeItem(*it);
    delete *it;

}
const QList<Figure *> *Controller::getLista()const{
    return &listaFigure;

}

Figure** Controller::getFigura(Shape* s){
  bool found=false;
  Figure** f=nullptr;
  for(auto it= listaFigure.begin();it!= listaFigure.end() && !found;++it){
      if((*it)->getPunt() == s){
          found =true;
          return &(*it);
        }
    }
  return f;
}

QGraphicsItem* Controller::selectedItemFirst() const{
  return scena->selectedItems().first();
}

/*Controller::~Controller(){
    QList<Figure*>::iterator it=listaFigure.begin();
    for(;it!=listaFigure.end();++it)
        delete *it;
}*/

void Controller::rimuoviSelezionati(){
    bool found= false;
    auto lista = scena->selectedItems();
    for(auto it = lista.begin();it!= lista.end();++it){
        if(dynamic_cast<Figure*>(*it)){
            found = false;
            for(auto t = listaFigure.begin(); t != listaFigure.end() && !found;++t){
                if(static_cast<Figure*>(*it)->getPunt() == (*t)->getPunt() ){
                    found=true;
                    scena->removeItem(*it);
                    delete *t;
                    t=listaFigure.erase(t);
                    --t;
                    it = lista.erase(it);
                    --it;
                }
            }
        }
    }
}
