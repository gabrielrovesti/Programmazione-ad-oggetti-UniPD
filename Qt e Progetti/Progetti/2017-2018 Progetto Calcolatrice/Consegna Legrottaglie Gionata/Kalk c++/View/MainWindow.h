#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "GraphicsScene.h"
#include "./Controller/controllerproprieta.h"
#include "./Controller/controller.h"
class Controller;
class ControllerProprieta;
class GraphicsScene;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GraphicsScene* get_scene()const;
    void attivaButtonPoligono(int)const;
    void disattivaButtonPoligono()const;
private slots:
    void onCursorChanged(const QPointF &scenePos, const QPointF &screenPos);
    void aggiungifigura_click();
    void zoommeno();
    void zoompiu();
    void quit();
    void on_rimuoviTuttoButton_clicked();    
    void on_sommaFiguraButton_clicked();

    void on_sottraiFiguraButton_clicked();
    void aggiungiVertice();
    void rimuoviVertice();

private:
    Ui::MainWindow *ui;
    GraphicsScene *m_pGraphicsScene;
    Controller* controller;
    ControllerProprieta *cp;



};

#endif // MAINWINDOW_H
