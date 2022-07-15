#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "aggiungifigura.h"
#include"sceltavertice.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pGraphicsScene(new GraphicsScene(this)),
    controller(new Controller(this,m_pGraphicsScene))
{
    m_pGraphicsScene->setController(controller);
    ui->setupUi(this);
    setWindowTitle("Kalk");
    setWindowIconText("Kalk");
    setWindowIcon(QIcon("View/calculator.png"));
    ui->graphicsView->setScene(m_pGraphicsScene);
    ui->graphicsView->scale(3,3);
    cp= new ControllerProprieta(m_pGraphicsScene,ui->PropertyTable,this);

    connect(m_pGraphicsScene, SIGNAL(cursorChanged(QPointF, QPointF)), this, SLOT(onCursorChanged( QPointF, QPointF)));
    connect(ui->aggiungifigura, SIGNAL(pressed()), this, SLOT(aggiungifigura_click()));
    connect(ui->zoommeno,SIGNAL(pressed()),this,SLOT(zoommeno()));
    connect(ui->zoompiu,SIGNAL(pressed()),this,SLOT(zoompiu()));
    connect(ui->quitButton,SIGNAL(pressed()),this,SLOT(quit()));
    connect(ui->rimuoviFiguraButton,SIGNAL(pressed()),m_pGraphicsScene,SLOT(rimuoviSelezionati()));
    connect(ui->aggiungiVerticeButton,SIGNAL(pressed()),this,SLOT(aggiungiVertice()));
    connect(ui->rimuoviVerticeButton,SIGNAL(pressed()),this,SLOT(rimuoviVertice()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pGraphicsScene;
    delete cp;
    delete controller;
}

GraphicsScene* MainWindow::get_scene()const{
 return m_pGraphicsScene;
}

void MainWindow::onCursorChanged(const QPointF &scenePos, const QPointF &screenPos)
{
    ui->statusBar->showMessage("scenePos : (" + QString::number(scenePos.x()) + ", " + QString::number(scenePos.y()) + "); " +
                               "screenPos : (" + QString::number(screenPos.x()) + ", " + QString::number(screenPos.y()) + ")" );
}

void MainWindow::aggiungifigura_click(){
    AggiungiFigura addFigura(controller,this);
    addFigura.setModal(true);
    addFigura.exec();
}
void MainWindow::zoommeno(){
  ui->graphicsView->scale(0.8,0.8);
}
void MainWindow::zoompiu(){
  ui->graphicsView->scale(1.2,1.2);
}
void MainWindow::quit(){
  close();
}

void MainWindow::attivaButtonPoligono(int x)const{
  switch (x) {
    case 1:
      ui->rimuoviVerticeButton->setDisabled(false);
      ui->rimuoviVerticeButton->setStyleSheet("background-color:rgb(240,150,100)");
      ui->aggiungiVerticeButton->setDisabled(false);
      ui->aggiungiVerticeButton->setStyleSheet("background-color:rgb(240,150,100)");
      ui->rimuoviFiguraButton->setDisabled(false);
      ui->rimuoviFiguraButton->setStyleSheet("background-color:rgb(240,150,100)");
      ui->rimuoviFiguraButton->setText("Rimuovi Figura");
      break;
    case 2:
      ui->rimuoviFiguraButton->setDisabled(false);
      ui->rimuoviFiguraButton->setStyleSheet("background-color:rgb(240,150,100)");
      ui->rimuoviFiguraButton->setText("Rimuovi Figura");
      break;
    case 3:
      ui->sommaFiguraButton->setDisabled(false);
      ui->sommaFiguraButton->setStyleSheet("background-color:rgb(240,150,100)");
      ui->sottraiFiguraButton->setDisabled(false);
      ui->sottraiFiguraButton->setStyleSheet("background-color:rgb(240,150,100)");
      ui->rimuoviFiguraButton->setDisabled(false);
      ui->rimuoviFiguraButton->setText("Rimuovi Figure");
      break;
    case 4:
      ui->rimuoviFiguraButton->setDisabled(false);
      ui->rimuoviFiguraButton->setStyleSheet("background-color:rgb(240,150,100)");
      ui->rimuoviFiguraButton->setText("Rimuovi Figure");
      break;
    default:
      break;
    }

}
void MainWindow::disattivaButtonPoligono()const{
    ui->rimuoviFiguraButton->setDisabled(true);
    ui->rimuoviFiguraButton->setStyleSheet("background-color:rgb(180,180,180)");
    ui->rimuoviVerticeButton->setDisabled(true);
    ui->rimuoviVerticeButton->setStyleSheet("background-color:rgb(180,180,180)");
    ui->aggiungiVerticeButton->setDisabled(true);
    ui->aggiungiVerticeButton->setStyleSheet("background-color:rgb(180,180,180)");
    ui->sommaFiguraButton->setDisabled(true);
    ui->sommaFiguraButton->setStyleSheet("background-color:rgb(180,180,180)");
    ui->sottraiFiguraButton->setDisabled(true);
    ui->sottraiFiguraButton->setStyleSheet("background-color:rgb(180,180,180)");

    ui->rimuoviFiguraButton->setText("Rimuovi Figura");
}

void MainWindow::aggiungiVertice(){
   SceltaVertice scelta("Aggiungi le nuove coordinate",controller,true,this);
   scelta.windowTitleChanged("Aggiungi Vertice");
   scelta.setModal(true);
   scelta.exec();
}
void MainWindow::rimuoviVertice(){
   SceltaVertice scelta("Inserisci le coordinate del vertice da rimuovere",controller,false,this);
   scelta.windowTitleChanged("Rimuovi Vertice");
   scelta.setModal(true);
   scelta.exec();
}

void MainWindow::on_rimuoviTuttoButton_clicked()
{
    QList<QGraphicsItem*> Q = m_pGraphicsScene->items();
    for(auto it = Q.begin();it!= Q.end();++it){
        (*it)->setSelected(true);
    }
    controller->rimuoviSelezionati();
}


void MainWindow::on_sommaFiguraButton_clicked()
{
  if(dynamic_cast<FigurePolygon*>(m_pGraphicsScene->selectedItems().first()) && dynamic_cast<FigurePolygon*>(m_pGraphicsScene->selectedItems().last())  )
    controller->sommaFigure(static_cast<FigurePolygon*>(static_cast<Figure*>(m_pGraphicsScene->selectedItems().first())),static_cast<FigurePolygon*>(static_cast<Figure*>(m_pGraphicsScene->selectedItems().last())));
}

void MainWindow::on_sottraiFiguraButton_clicked()
{
  controller->sottraiFigure(static_cast<FigurePolygon*>(static_cast<Figure*>(m_pGraphicsScene->selectedItems().first())),static_cast<FigurePolygon*>(static_cast<Figure*>(m_pGraphicsScene->selectedItems().last())));
}
