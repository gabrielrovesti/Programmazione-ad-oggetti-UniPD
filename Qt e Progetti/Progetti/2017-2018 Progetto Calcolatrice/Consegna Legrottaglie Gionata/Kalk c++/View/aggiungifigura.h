#ifndef AGGIUNGIFIGURA_H
#define AGGIUNGIFIGURA_H

#include <QDialog>
#include<QTableWidget>
#include<QStringList>
#include<QTableWidget>
#include<QMessageBox>
#include<./calcolatrice/cerchio.h>
#include<./calcolatrice/poligonoconvesso.h>
#include"figureellipse.h"
#include"figurepolygon.h"
#include"GraphicsScene.h"
#include"MainWindow.h"
#include"./Controller/controller.h"
namespace Ui {
class AggiungiFigura;
}

class AggiungiFigura : public QDialog
{
    Q_OBJECT

public:
    explicit AggiungiFigura(Controller*,QWidget *parent = 0);
    ~AggiungiFigura();
private slots:
    void creaFigura();

    void on_AggiungiVerticeDialog_clicked();

    void on_RimuoviVerticeDialog_clicked();

    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::AggiungiFigura *ui;
    Controller* controller;

};

#endif // AGGIUNGIFIGURA_H
