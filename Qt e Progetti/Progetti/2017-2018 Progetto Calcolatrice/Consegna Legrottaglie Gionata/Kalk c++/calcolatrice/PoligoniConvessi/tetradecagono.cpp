#include "tetradecagono.h"

#include "triangolo.h"

Tetradecagono::Tetradecagono(const Tetradecagono & T):PoligonoConvesso(T){set_lati(T.Lista);}


Tetradecagono::Tetradecagono(const QVector<Vertice>&V,bool b):PoligonoConvesso(V,14,"Tetradecagono",b){
      set_lati(V);
}
double Tetradecagono::get_perimetro()const{
  return lati[0]+lati[1]+lati[2]+lati[3]+lati[4]+lati[5]+lati[6]+lati[7]+lati[8]+lati[9]+lati[10]+lati[11]+lati[12]+lati[13];
}

double Tetradecagono::get_area()const{
  int a=0,b=1, c=2;
  double area=0;
  while(c < Lista.size()){
      area+= Triangolo({Lista[a], Lista[b], Lista[c]}).get_area();
      c++;b++;
    }
  return area;
}

ostream& operator<< (ostream& os,const Tetradecagono& T){
 os<<T.toString().toUtf8().constData();
 return os;
}

void Tetradecagono::set_lati(const QVector<Vertice>& v){
  int x=0,y=1;
  while(x<v.size()){
      if(y==v.size())y=0;
      lati[x] = std::sqrt((std::pow((v[y].get_X()-v[x].get_X()),2)+std::pow(v[y].get_Y()-v[x].get_Y(),2)));
      x++; y++;
    }
}

QString Tetradecagono::toString() const{
  QString s ="Tetradecagono: ";
  for(auto it=Lista.begin();it!=Lista.end();it++){
    s+= it->toString();
    }
  return s;
}
QString Tetradecagono::get_nomeClasse()const{
    return "Tetradecagono";
}
double  Tetradecagono::get_lati(unsigned int i)const{
  return lati[i];
}
unsigned int Tetradecagono::get_nLati()const{
  return nLati;
}
