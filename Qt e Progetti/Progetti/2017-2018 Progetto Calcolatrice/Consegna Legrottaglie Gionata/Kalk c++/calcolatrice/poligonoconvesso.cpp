#include "poligonoconvesso.h"
#include "PoligoniConvessi/triangolo.h"
#include "PoligoniConvessi/quadrilatero.h"
#include "PoligoniConvessi/pentagono.h"
#include "PoligoniConvessi/esagono.h"
#include "PoligoniConvessi/ettagono.h"
#include "PoligoniConvessi/ottagono.h"
#include "PoligoniConvessi/ennagono.h"
#include "PoligoniConvessi/decagono.h"
#include "PoligoniConvessi/endecagono.h"
#include "PoligoniConvessi/dodecagono.h"
#include "PoligoniConvessi/tridecagono.h"
#include "PoligoniConvessi/tetradecagono.h"
#include "PoligoniConvessi/pentadecagono.h"
#include "PoligoniConvessi/esadecagono.h"
#include "PoligoniConvessi/eptadecagono.h"
#include "PoligoniConvessi/ottadecagono.h"
#include "PoligoniConvessi/ennadecagono.h"
#include "PoligoniConvessi/icosagono.h"

const QVector<Vertice>& PoligonoConvesso::getPunt_vertici()const{
  return Lista;
}

PoligonoConvesso::PoligonoConvesso(){}
PoligonoConvesso::PoligonoConvesso(const PoligonoConvesso& p):Poligono(),Lista(p.Lista){}
PoligonoConvesso::PoligonoConvesso(const QVector<Vertice>& V, int x, QString name):Poligono(),Lista(V){
  const_cast<QVector<Vertice>&>(V) = grahamScan(const_cast<QVector<Vertice>&>(V));
  if(V.size() == x){
      Lista = V;
    }else{
      reduce_n_shape();
      std::string s(name.toUtf8().constData());
      throw  std::invalid_argument("Impossibile creare un "+ s +" utilizzando questi vertici");
    }
}

PoligonoConvesso::PoligonoConvesso(const QVector<Vertice>& V, int x, QString name,bool check):Poligono(),Lista(V){

  if(check){
      if(V.size() == x){
          Lista = V;
        }else{
          reduce_n_shape();
          std::string s(name.toUtf8().constData());
          throw  std::invalid_argument("Impossibile creare un "+ s +" utilizzando questi vertici");
        }
    }

}
int PoligonoConvesso::size()const{return Lista.size();}

PoligonoConvesso* PoligonoConvesso::aggiungi_vertice(Vertice v) const{
  QVector<Vertice> newVector(Lista);
  newVector.push_back(v);
  PoligonoConvesso* p= PoligonoConvesso::crea_poligono(newVector);
  reduce_n_shape();
  return p;
}

PoligonoConvesso* PoligonoConvesso::rimuovi_vertice(Vertice v)const{
  bool found = false;
  QVector<Vertice> V(Lista);
  auto it = V.begin();
  for(; it != V.end() && !found; ){
      if(*it == v){
          found=true;}
      else ++it;
    }
  if(found){
      V.erase(it);
      PoligonoConvesso* p= PoligonoConvesso::crea_poligono(V);
      reduce_n_shape();
      return p;
    }
  else{
      throw std::invalid_argument("Vertice non trovato");
    }
  return nullptr;
}

QVector<Vertice> PoligonoConvesso::get_vertici()const{return Lista;}

PoligonoConvesso* operator+(const PoligonoConvesso& p1,const PoligonoConvesso& p2){
    QVector<Vertice> V(p1.get_vertici());
    const QVector<Vertice>& V2(p2.getPunt_vertici());
    for(auto it=V2.begin();it!=V2.end();it++){
        V.push_back(*it);
    }
    return PoligonoConvesso::crea_poligono(V);
}

PoligonoConvesso* operator-(const PoligonoConvesso& p1,const PoligonoConvesso& p2){
  QVector<Vertice> v1(p1.get_vertici());
  const QVector<Vertice>& v2(p2.getPunt_vertici());
  for(auto it2=v2.begin();it2!=v2.end();it2++){
      bool found=false;
      for(auto it1=v1.begin();it1!=v1.end() && !found && v1.size() >= 3;it1++){
          if(*it1 == *it2)
            {
              v1.erase(it1);
              it1--;
              found = true;
            }
        }
    }
  return PoligonoConvesso::crea_poligono(v1);
}

bool PoligonoConvesso::operator ==(const PoligonoConvesso& p)const{
  int i;
  if(Lista.size() == p.size()) i=Lista.size();
  else return false;
  for(int j=0;j<i;j++){
      if(Lista[i]!=p.Lista[i]) return false;
    }
  return true;
}
bool PoligonoConvesso::operator !=(const PoligonoConvesso& p)const{
  int i;
  if(Lista.size() == p.size()) i=Lista.size();
  else return false;
  for(int j=0;j<i;j++){
      if(Lista[i]!=p.Lista[i]) return true;
    }
  return false;
}


// Le prossime funzioni vengono utilizzate per filtrare il QVector<Vertice> che viene utilizzato per costruire
// un poligono. Vengono rimossi tutti i vertici che non possono far parte del poligono, ad esempio i punti interni.

Vertice pivot;

double PoligonoConvesso::ccw(Vertice a, Vertice b, Vertice c) {
    double area = (b.get_X() - a.get_X()) * (c.get_Y() - a.get_Y()) - (b.get_Y() - a.get_Y()) * (c.get_X() - a.get_X());
    if (area > 0)
        return -1;
    else if (area < 0)
        return 1;
    return 0;
}

// restituisce il quadrato della distanza euclidea tra due punti
double PoligonoConvesso::sqrDist(Vertice a, Vertice b)  {
    double dx = a.get_X() - b.get_X(), dy = a.get_Y() - b.get_Y();
    return dx * dx + dy * dy;
}
// ordinamento dei punti in ordine polare
bool PoligonoConvesso::POLAR_ORDER(Vertice a, Vertice b)  {
    double order = ccw(pivot, a, b);
    if (order == 0)
        return sqrDist(pivot, a) < sqrDist(pivot, b);
    if (order == -1)
      return 1;
    else
      return 0;
}
// controllo che la somma di tutti gli angoli non superi il massimo consentito.
bool PoligonoConvesso::checkVector(QVector<Vertice>&Points){
  double somma=0;
  int b=0;
  for(auto itb=Points.begin(); itb != Points.end();itb++){
      int a,c;
      if(b==0) {a=Points.size()-1; c=b+1;}
      else if(b==Points.size()-1){c=0; a=b-1;}
      else {a=b-1; c=b+1;}
      double angolo=  Vertice::get_Angolo(Points[b],Points[a],Points[c]);
      if(angolo == 180) {
          Points.erase(itb);
          angolo=0;
        }else{
          b++;
        }
      if(angolo > 180) return false;
      somma+= angolo;
      if(somma > (180*(Points.size()-2)) || somma==0)
        return false;

    }
    return true;
}
//Rimuove eventuali vertici doppioni
void PoligonoConvesso::rimuovi_doppioni(QVector<Vertice>& V ){
  for(auto i=V.begin();i!= V.end();i++){
      for(auto j=i+1; j!=V.end();j++){
          if(*i==*j) {
              V.erase(j); j--;
            }
        }
    }
}
QVector<Vertice> PoligonoConvesso::grahamScan(QVector<Vertice>& Points){

    rimuovi_doppioni(Points);
    QVector<Vertice> hull;
    int N= Points.size();

    // find the Vertice having the least y coordinate (pivot),
    // ties are broken in favor of lower x coordinate
    int leastY = 0;
    for (int i = 1; i < N; i++)
        if (Points[i] < Points[leastY])
            leastY = i;

    // swap the pivot with the first vertice
    Vertice temp = Points[0];
    Points[0] = Points[leastY];
    Points[leastY] = temp;
    if (N < 3 )
        throw  std::invalid_argument("Vertici non validi per la creazione di un Poligono.");
    //ordinamento polare del vettore Points
    pivot = Points[0];
    auto it = Points.begin();
    it++;
    std::sort(it, Points.end(), POLAR_ORDER);
    hull.push_back(Points[0]);
    hull.push_back(Points[1]);
    hull.push_back(Points[2]);

    for (int i = 3; i < N; i++) {
        Vertice top = hull[hull.size()-1];
        hull.pop_back();
        while (ccw(hull[hull.size()-1], top, Points[i]) != -1)   {
            top = hull[hull.size()-1];
            hull.pop_back();
        }
        hull.push_back(top);
        hull.push_back(Points[i]);
    }

    std::reverse(hull.begin(),hull.end());
    if (!checkVector(hull))
        throw  std::invalid_argument("Vertici non validi per la creazione di un Poligono.");
    return hull;
}

PoligonoConvesso* PoligonoConvesso::crea_poligono(QVector<Vertice>& V){
  // ricevo un vettore di vertici, elimino eventuali vertici inutili, e se 3 <= N <= 20 costruisco un poligono

   V =grahamScan(V);
    if(V.size()>20) throw  std::invalid_argument("Nel modello non è incluso un poligono di queste dimensioni");

   switch (V.size()) {
     case 3:
       return new Triangolo(V,true);
       break;
     case 4:
       return new Quadrilatero(V,true);
       break;
     case 5:
       return new Pentagono(V,true);
       break;
     case 6:
       return new Esagono(V,true);
       break;
     case 7:
       return new Ettagono(V,true);
       break;
     case 8:
       return new Ottagono(V,true);
       break;
     case 9:
       return new Ennagono(V,true);
       break;
     case 10:
       return new Decagono(V,true);
       break;
     case 11:
       return new Endecagono(V,true);
       break;
     case 12:
       return new Dodecagono(V,true);
       break;
     case 13:
       return new Tridecagono(V,true);
       break;
     case 14:
       return new Tetradecagono(V,true);
       break;
     case 15:
       return new Pentadecagono(V,true);
       break;
     case 16:
       return new Esadecagono(V,true);
       break;
     case 17:
       return new Eptadecagono(V,true);
       break;
     case 18:
       return new Ottadecagono(V,true);
       break;
     case 19:
       return new Ennadecagono(V,true);
       break;
     case 20:
       return new Icosagono(V,true);
       break;

     default:
       throw  std::invalid_argument("Impossibile creare un poligono di questa dimensione");
       break;
     }

  return 0;
}


