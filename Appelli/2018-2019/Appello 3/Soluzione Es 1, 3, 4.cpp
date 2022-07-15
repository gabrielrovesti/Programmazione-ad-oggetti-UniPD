#include <iostream>

//Esercizio 1

vector<QAbstractButton*> fun(list<QWidget*>&q, const QSize& sz, vector <const QWidget*>& v){
   vector<QAbstractButton*> v;
   list<QWidget*>::iterator it = q.begin();

   for(; it!=v.end(); ++it){
       if(*it && (*it)->sizeHint() == size) q.push_front((*it)->clone());
       QAbstractSlider *s=dynamic_cast<QWidget*>(*it);
       if((*it) && !s && (*it)->sizeHint() == s){
            delete *it; 
            it = lista.erase(it);
       }
       if((*it) && dynamic_cast<QCheckBox*>(*it) || dynamic_cast<QPushButton*>(*it){
           v.push_back(static_cast<QAbstractButton*>(*it));
           it=lista.erase(it);
       }
   }
   return v;
}

//Esercizio 3
A <= B  Possibile
A <= C  Falso
A <= D  Falso
B <= A  Possibile
B <= C  Vero
B <= D  Vero
C <= A  Vero
C <= B  Falso
C <= D  Vero
D <= A  Vero
D <= B  Falso
D <= C  Falso

//Esercizio 4
F(const F& f): pz(f.pz) {}