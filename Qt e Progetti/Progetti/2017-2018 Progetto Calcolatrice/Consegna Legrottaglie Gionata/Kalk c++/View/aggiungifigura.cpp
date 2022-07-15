#include "aggiungifigura.h"
#include "ui_aggiungifigura.h"

AggiungiFigura::AggiungiFigura(Controller* c,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AggiungiFigura),
    controller(c)
{
    ui->setupUi(this);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(creaFigura()));

}

AggiungiFigura::~AggiungiFigura()
{
    delete ui;
}

void AggiungiFigura::creaFigura(){
    int current = ui->comboBox->currentIndex();
    QStringList header;
    switch (current) {
    case 0:
        ui->tableVertici->setRowCount(3);
        ui->tableVertici->setColumnCount(2);
        header<<"X"<<"Y";
        ui->tableVertici->setHorizontalHeaderLabels(header);
        ui->AggiungiVerticeDialog->setGeometry(400,230,171,51);
        ui->RimuoviVerticeDialog->setGeometry(400,290,171,51);
        ui->tableVertici->setGeometry(20,100,325,291);
        break;
    case 1:
        ui->tableVertici->setRowCount(1);
        ui->tableVertici->setColumnCount(3);
        ui->AggiungiVerticeDialog->setGeometry(0,0,0,0);
        ui->RimuoviVerticeDialog->setGeometry(0,0,0,0);
        ui->tableVertici->setGeometry(20,100,530,90);
        header<<"X (centro)"<<"Y (Centro)"<<"Raggio";
        ui->tableVertici->setHorizontalHeaderLabels(header);

        break;

    }
}

void AggiungiFigura::on_AggiungiVerticeDialog_clicked()
{
    if(ui->tableVertici->rowCount()<20)ui->tableVertici->setRowCount(ui->tableVertici->rowCount()+1);
    if(ui->tableVertici->rowCount()==20)ui->AggiungiVerticeDialog->setDisabled(true);
    ui->RimuoviVerticeDialog->setDisabled(false);
}

void AggiungiFigura::on_RimuoviVerticeDialog_clicked()
{
    if(ui->tableVertici->rowCount()>3)ui->tableVertici->setRowCount(ui->tableVertici->rowCount()-1);
    if(ui->tableVertici->rowCount()==3)ui->RimuoviVerticeDialog->setDisabled(true);
    ui->AggiungiVerticeDialog->setDisabled(false);
}

void AggiungiFigura::on_cancelButton_clicked()
{
    reject();
}

void AggiungiFigura::on_okButton_clicked()
{
    Shape *s;
    try{
      bool empty= false;
        if(ui->comboBox->currentIndex() == 0){
            QVector<Vertice> V;
            for(int i=0;i< ui->tableVertici->rowCount() && !empty ;i++){
                QTableWidgetItem* x_item = ui->tableVertici->item(i,0);
                QTableWidgetItem* y_item = ui->tableVertici->item(i,1);
                if(!x_item || !y_item || x_item->text().isNull() || y_item->text().isNull() ||
                        x_item->text().isEmpty() || y_item->text().isEmpty()) {
                    empty=true;
                }

                else{
                    QString x = x_item->text();
                    QString y = y_item->text();
                    bool cast1=true,cast2=true;
                    x.toDouble(&cast1);y.toDouble(&cast2);
                    if(cast1 && cast2)
                       V.push_back(Vertice(x.toDouble(),y.toDouble()));
                    else{
                        empty= true;
                    }
                }
            }
            if(!empty){
                // I dati prelevati dalla tabella sono corretti
                        s = PoligonoConvesso::crea_poligono(V);
                        Figure* f = new FigurePolygon(s,NULL);
                        controller->aggiungiFigura(f);
                        accept();

            }else{
                QMessageBox::StandardButton answer;
                answer = QMessageBox::warning(this, tr("Tabella incompleta"),
                    tr("I valori inseriti non sono corretti se vuoi modificarli clicca SI altrimenti clicca NO"),
                    QMessageBox::Yes | QMessageBox::No);
                if (answer == QMessageBox::Yes){
                    return;
                }
                else if(answer == QMessageBox::No){
                    reject();
                }
            }


        }else if(ui->comboBox->currentIndex() == 1){
            QTableWidgetItem* x_item = ui->tableVertici->item(0,0);
            QTableWidgetItem* y_item = ui->tableVertici->item(0,1);
            QTableWidgetItem* r_item = ui->tableVertici->item(0,2);
            if(!x_item || !y_item || !r_item || x_item->text().isNull() || y_item->text().isNull()
             || r_item->text().isNull() || x_item->text().isEmpty() || y_item->text().isEmpty()|| r_item->text().isEmpty()) {
                empty=true;
            }
            QString x = ui->tableVertici->item(0,0)->text();
            QString y = ui->tableVertici->item(0,1)->text();
            QString r = ui->tableVertici->item(0,2)->text();
            delete x_item;
            delete y_item;
            delete r_item;
            bool cast1=true,cast2=true,cast3=true;
            x.toDouble(&cast1);
            y.toDouble(&cast2);
            r.toDouble(&cast3);
            if(!empty && cast1 && cast2 && cast3){


                    s = new Cerchio(Vertice(x.toDouble(),y.toDouble()),r.toDouble());
                    Figure* f = new FigureEllipse(s,NULL);
                    controller->aggiungiFigura(f);
                    accept();

            }else{
                QMessageBox::StandardButton answer;
                answer = QMessageBox::warning(this, tr("Tabella incompleta"),
                    tr("I valori inseriti non sono corretti. \nSe vuoi modificarli clicca SI altrimenti clicca NO"),
                    QMessageBox::Yes | QMessageBox::No);
                if (answer == QMessageBox::Yes){
                    return;
                }
                else if(answer == QMessageBox::No){
                    reject();
                }
            }

        }}
    catch(std::invalid_argument& e){
        QString err = e.what();
        QMessageBox::StandardButton answer;
        answer = QMessageBox::warning(this, tr("Tabella incompleta"),
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
