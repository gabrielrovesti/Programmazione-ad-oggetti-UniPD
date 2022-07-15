#include "eptadecagono.h"
#include "triangolo.h"

Eptadecagono::Eptadecagono(const Eptadecagono & T):PoligonoConvesso(T){set_lati(T.Lista);}



Eptadecagono::Eptadecagono(const QVector<Vertice>&V,bool b):PoligonoConvesso(V,17,"Eptadecagono",b){
      set_lati(V);
}
double Eptadecagono::get_perimetro()const{
  return lati[0]+lati[1]+lati[2]+lati[3]+lati[4]+lati[5]+lati[6]+lati[7]+lati[8]+lati[9]+lati[10]+lati[11]+lati[12]+lati[13]+lati[14]+lati[15]+lati[16];
}

double Eptadecagono::get_area()const{
  int a=0,b=1, c=2;
  double area=0;
  while(c < Lista.size()){
      area+= Triangolo({Lista[a], Lista[b], Lista[c]}).get_area();
      c++;b++;
    }
  return area;
}

ostream& operator<< (ostream& os,const Eptadecagono& T){
 os<<T.toString().toUtf8().constData();
 return os;
}

void Eptadecagono::set_lati(const QVector<Vertice>& v){
  int x=0,y=1;
  while(x<v.size()){
      if(y==v.size())y=0;
      lati[x] = std::sqrt((std::pow((v[y].get_X()-v[x].get_X()),2)+std::pow(v[y].get_Y()-v[x].get_Y(),2)));
      x++; y++;
    }
}

QString Eptadecagono::toString() const{
  QString s ="Eptadecagono: ";
  for(auto it=Lista.begin();it!=Lista.end();it++){
    s+= it->toString();
    }
  return s;
}
QString Eptadecagono::get_nomeClasse()const{
    return "Eptadecagono";
}
double  Eptadecagono::get_lati(unsigned int i)const{
  return lati[i];
}
unsigned int Eptadecagono::get_nLati()const{
  return nLati;
}
