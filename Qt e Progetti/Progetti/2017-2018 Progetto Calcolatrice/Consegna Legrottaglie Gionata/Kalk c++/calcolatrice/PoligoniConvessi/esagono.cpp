#include "esagono.h"
#include "triangolo.h"

Esagono::Esagono(const Esagono & T):PoligonoConvesso(T){set_lati(T.Lista);}


Esagono::Esagono(const QVector<Vertice>&V,bool b):PoligonoConvesso(V,6,"Esagono",b){
      set_lati(V);
}
double Esagono::get_perimetro()const{
  return lati[0]+lati[1]+lati[2]+lati[3]+lati[4]+lati[5];
}

double Esagono::get_area()const{
  int a=0,b=1, c=2;
  double area=0;
  while(c < Lista.size()){
      area+= Triangolo({Lista[a], Lista[b], Lista[c]}).get_area();
      c++;b++;
    }
  return area;
}

ostream& operator<< (ostream& os,const Esagono& T){
 os<<T.toString().toUtf8().constData();
 return os;
}

void Esagono::set_lati(const QVector<Vertice>& v){
  int x=0,y=1;
  while(x<v.size()){
      if(y==v.size())y=0;
      lati[x] = std::sqrt((std::pow((v[y].get_X()-v[x].get_X()),2)+std::pow(v[y].get_Y()-v[x].get_Y(),2)));
      x++; y++;
    }
}

QString Esagono::toString() const{
  QString s ="Esagono: ";
  for(auto it=Lista.begin();it!=Lista.end();it++){
    s+= it->toString();
    }
  return s;
}
QString Esagono::get_nomeClasse()const{
    return "Esagono";
}
double  Esagono::get_lati(unsigned int i)const{
  return lati[i];
}
unsigned int Esagono::get_nLati()const{
  return nLati;
}
