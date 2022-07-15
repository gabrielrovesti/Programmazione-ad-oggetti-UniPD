#include "triangolo.h"

Triangolo::Triangolo(const Triangolo & T):PoligonoConvesso(T){set_lati(T.Lista);}


Triangolo::Triangolo(const QVector<Vertice>&V):PoligonoConvesso(V,3,"Triangolo"){
      set_lati(V);
}

Triangolo::Triangolo(const QVector<Vertice>&V,bool b):PoligonoConvesso(V,3,"Triangolo",b){
      set_lati(V);
}

double Triangolo::get_perimetro()const{
  return lati[0]+lati[1]+lati[2];
}

double Triangolo::get_area()const{
  //semiperimetro
  double p = get_perimetro()/2;
  double x =p*(p-lati[0])*(p-lati[1])*(p-lati[2]);
  return std::sqrt(x);
}

ostream& operator<< (ostream& os,const Triangolo& T){
 os<<T.toString().toUtf8().constData();
 return os;
}

void Triangolo::set_lati(const QVector<Vertice>& v){
  int x=0,y=1;
  while(x<v.size()){
      if(y==v.size())y=0;
      lati[x] = std::sqrt((std::pow((v[y].get_X()-v[x].get_X()),2)+std::pow(v[y].get_Y()-v[x].get_Y(),2)));
      x++; y++;
    }
}

QString Triangolo::toString() const{
  QString s ="Triangolo: ";
  for(auto it=Lista.begin();it!=Lista.end();it++){
    s+= it->toString();
    }
  return s;
}

QString Triangolo::get_nomeClasse()const{
    return "Triangolo";
}
double  Triangolo::get_lati(unsigned int i)const{
  return lati[i];
}
unsigned int Triangolo::get_nLati()const{
  return nLati;
}
