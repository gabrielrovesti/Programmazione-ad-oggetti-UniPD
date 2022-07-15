#ifndef SCELTAVERTICE_H
#define SCELTAVERTICE_H

#include <QDialog>
#include "figurepolygon.h"
#include "./Controller/controller.h"

namespace Ui {
class SceltaVertice;
}

class SceltaVertice : public QDialog
{
    Q_OBJECT

public:
    explicit SceltaVertice(QString s, Controller *g,bool, QWidget *parent = 0);
    ~SceltaVertice();

private slots:
  void on_applicaButton_clicked();
  void on_annullaButton_clicked();
  void rimuoviButton_clicked();

private:
    Ui::SceltaVertice *ui;
    Controller* controller;

};

#endif // SCELTAVERTICE_H
