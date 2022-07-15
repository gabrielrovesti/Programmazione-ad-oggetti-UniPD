#include "sceltavertice.h"
#include "ui_sceltavertice.h"
#include"GraphicsScene.h"
#include<QDebug>
#include<QMessageBox>
#include<QPushButton>
    SceltaVertice::SceltaVertice(QString s,Controller* g,bool add, QWidget *parent) :
    QDialog(parent),ui(new Ui::SceltaVertice),controller(g){

    ui->setupUi(this);
    ui->title->setText(s);
    QList<Figure*>* lista= const_cast<QList<Figure*>*>(g->getLista()); //lista poligoni aggiunti
    if(add == false){
        ui->applicaButton->setHidden(true);
        QPushButton* rimuovi = new QPushButton("Rimuovi",this);
        rimuovi->setGeometry(220,570,141,41);
        rimuovi->setFont(QFont("MS Shell Dlg 2",11));
        connect(rimuovi,SIGNAL(pressed()),this,SLOT(rimuoviButton_clicked()));
      }

    Figure* figura=nullptr;
    bool found = false;
    for(auto it=(*lista).begin();it!=(*lista).end() && !found;++it){
        Figure* f = dynamic_cast<Figure*>(g->selectedItemFirst()); // unico elemento selezionato nella graphicsview
        if(f){
            if((*it)->getPunt() == f->getPunt()){
                figura = f;
                found=true;
              }
          }
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    if(figura && found && dynamic_cast<PoligonoConvesso*>(figura->getPunt())){
        const QVector<Vertice>& vettore = static_cast<PoligonoConvesso*>(figura->getPunt())->getPunt_vertici();
        ui->tableWidget->setRowCount(vettore.size());
        ui->id_figura->setText(QString::number(static_cast<PoligonoConvesso*>(figura->getPunt())->get_id()));
        int x=0;
        for(auto it = vettore.begin();it!=vettore.end();++it){
            QTableWidgetItem *item_x= new QTableWidgetItem(QString::number(it->get_X()));
            QTableWidgetItem *item_y= new QTableWidgetItem(QString::number(it->get_Y()));
            ui->tableWidget->setItem(x,0,item_x);
            ui->tableWidget->setItem(x,1,item_y);
            ++x;
          }
     }
}

SceltaVertice::~SceltaVertice()
{
    delete ui;
}


void SceltaVertice::on_applicaButton_clicked()
{
     double id = ui->id_figura->text().toDouble();
     Shape *newShape=nullptr;
     QList<Figure*>* lista = const_cast<QList<Figure*>*>(controller->getLista());

     for(auto it= lista->begin();it!=lista->end();++it){
         if(dynamic_cast<PoligonoConvesso*>((*it)->getPunt()) && (*it)->getPunt()->get_id() == id){
             try{
               newShape= static_cast<PoligonoConvesso*>((*it)->getPunt())->aggiungi_vertice(Vertice(ui->x_text->text().toDouble(),ui->y_text->text().toDouble()));
               Figure *figuraDaInserire = new FigurePolygon(newShape);
               figuraDaInserire->setCursor(Qt::PointingHandCursor);
               controller->rimuoviFigura(it);
               controller->cambiaFigura(it,figuraDaInserire);
               accept();
             }
             catch(std::invalid_argument& e){
                QString err = e.what();
                QMessageBox::StandardButton answer;
                answer = QMessageBox::warning(this, tr("Errore di inserimento"),
                   err + "\nSe vuoi modificare i valori inseriti clicca SI altrimenti clicca NO",
                   QMessageBox::Yes | QMessageBox::No);
                if (answer == QMessageBox::Yes){
                   return;
                }
                else if(answer == QMessageBox::No){
                   reject();
               }
             }
           }
       }
}

void SceltaVertice::rimuoviButton_clicked(){
  double id = ui->id_figura->text().toDouble();
  Shape *newShape=nullptr;
  QList<Figure*>* lista = const_cast<QList<Figure*>*>(controller->getLista());

  for(auto it= lista->begin();it!=lista->end();++it){
      if(dynamic_cast<PoligonoConvesso*>((*it)->getPunt()) && (*it)->getPunt()->get_id() == id){
          try{
            newShape= static_cast<PoligonoConvesso*>((*it)->getPunt())->rimuovi_vertice(Vertice(ui->x_text->text().toDouble(),ui->y_text->text().toDouble()));
            Figure *figuraDaInserire = new FigurePolygon(newShape);

            figuraDaInserire->setCursor(Qt::PointingHandCursor);
            controller->rimuoviFigura(it);
            controller->cambiaFigura(it,figuraDaInserire);
            accept();
          }
          catch(std::invalid_argument& e){
             QString err = e.what();
             QMessageBox::StandardButton answer;
             answer = QMessageBox::warning(this, tr("Errore di inserimento"),
                err + "\nSe vuoi modificare i valori inseriti clicca SI altrimenti clicca NO",
                QMessageBox::Yes | QMessageBox::No);
             if (answer == QMessageBox::Yes){
                return;
             }
             else if(answer == QMessageBox::No){
                reject();
            }
          }
        }
    }
}
void SceltaVertice::on_annullaButton_clicked()
{
    reject();
}
