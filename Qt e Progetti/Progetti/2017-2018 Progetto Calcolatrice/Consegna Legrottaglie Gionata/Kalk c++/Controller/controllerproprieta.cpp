#include "controllerproprieta.h"

ControllerProprieta::ControllerProprieta(GraphicsScene * g, QTableWidget *t, QObject *parent):
  QObject(parent),
  m_pGraphicsScene(g),
  m_tableWidget(t)

{
  connect(m_pGraphicsScene, SIGNAL(selectionChanged()), this, SLOT(onItemPropertyChanged()));
  m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ControllerProprieta::onItemPropertyChanged()
{
    if (m_pGraphicsScene->selectedItems().isEmpty() || m_pGraphicsScene->selectedItems().length() > 1 )
    {
        m_tableWidget->clearContents();
        m_tableWidget->setRowCount(0);
        m_tableWidget->setColumnCount(0);
        return;
    }

    QGraphicsItem *selectedItem = m_pGraphicsScene->selectedItems().last();
    if(dynamic_cast<Figure*>(selectedItem)){
        Figure* f = static_cast<Figure*>(selectedItem);
        Shape* Figura=f->getPunt();
        m_tableWidget->setRowCount(3);
        m_tableWidget->setColumnCount(2);
        m_tableWidget->setHorizontalHeaderLabels(QStringList{tr(""), tr("")});
        m_tableWidget->setColumnWidth(0, m_tableWidget->width() * 0.45);
        m_tableWidget->setColumnWidth(1, m_tableWidget->width() * 0.44);

        QTableWidgetItem *newItem;
        newItem = new QTableWidgetItem("Classe");
        m_tableWidget->setItem(0, 0, newItem);
        newItem = new QTableWidgetItem(Figura->get_nomeClasse());
        m_tableWidget->setItem(0, 1, newItem);
        m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            newItem = new QTableWidgetItem("Area");
            m_tableWidget->setItem(1, 0, newItem);
            newItem = new QTableWidgetItem(QString::number(Figura->get_area()));
            m_tableWidget->setItem(1, 1, newItem);

            newItem = new QTableWidgetItem("Perimetro");
            m_tableWidget->setItem(2, 0, newItem);
            newItem = new QTableWidgetItem(QString::number(Figura->get_perimetro()));
            m_tableWidget->setItem(2, 1, newItem);
            if(dynamic_cast<PoligonoConvesso*>(Figura)){
                const QVector<Vertice>& V(static_cast<PoligonoConvesso*>(Figura)->getPunt_vertici());
                unsigned int nLati = static_cast<PoligonoConvesso*>(Figura)->get_nLati();
                m_tableWidget->setRowCount(6+ nLati + V.size() );
                newItem = new QTableWidgetItem("N Lati");
                m_tableWidget->setItem(3, 0, newItem);
                newItem = new QTableWidgetItem(QString::number(static_cast<PoligonoConvesso*>(Figura)->get_nLati()));
                m_tableWidget->setItem(3, 1, newItem);

                newItem = new QTableWidgetItem("Lista lati");
                newItem->setTextColor("red");
                m_tableWidget->setItem(4, 0, newItem);
                unsigned int indice =5;
                for(unsigned int i=0;i< nLati;i++){

                    newItem = new QTableWidgetItem("Lato " + QString::number(i));
                    m_tableWidget->setItem(indice, 0, newItem);
                    newItem = new QTableWidgetItem(QString::number(static_cast<PoligonoConvesso*>(Figura)->get_lati(i)));
                    m_tableWidget->setItem(indice, 1, newItem);
                    indice +=1;
                }

                newItem = new QTableWidgetItem("Lista Vertici");
                newItem->setTextColor("red");
                m_tableWidget->setItem(indice++, 0, newItem);
                for(unsigned int i=0;i< nLati;i++){
                    newItem = new QTableWidgetItem("Vertice " + QString::number(i));
                    m_tableWidget->setItem(indice, 0, newItem);
                    newItem = new QTableWidgetItem(QString::number(V[i].get_X()) + "," + QString::number(V[i].get_Y()));
                    m_tableWidget->setItem(indice, 1, newItem);
                    indice +=1;
                }
          }

      }
}
