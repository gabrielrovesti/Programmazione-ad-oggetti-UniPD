#include "punto.h"
Punto::Punto():x(0),y(0){}
Punto::Punto(double a,double b):x(a),y(b){}
Punto::Punto(const Punto& p):x(p.x),y(p.y){}

double Punto:: get_X()const{return x;}
double Punto:: get_Y()const{return y;}

//overraiding operatori
bool Punto::operator==(const Punto& p)const{	return x == p.x && y == p.y;}
bool Punto::operator!=(const Punto& p)const{	return x != p.x || y != p.y;}
bool Punto::operator<(const Punto& p)const{
  if (y != p.y)
      return y < p.y;
  return x < p.x;
}

QString Punto::toString()const{
  return QString("(" + to_string_nozero(x) + "," + to_string_nozero(y)+ ")");
}
double distanza(const Punto& p1, const Punto& p2)
{
    const double dX = ((p1.get_X()-p2.get_X())*(p1.get_X()-p2.get_X()));
    const double dY = ((p1.get_Y()-p2.get_Y())*(p1.get_Y()-p2.get_Y()));
    return sqrt( dX + dY );
}

std::ostream& operator<<(std::ostream& os,const Punto& p){
        return os<<p.toString().toUtf8().constData();
}

QString to_string_nozero(double a){
  std::string s= std::to_string(a);
  int i=s.size()-1;
  bool out=false;
  while(s[i] != '.' && !out){
      if(s[i] == '0'){
        s.erase(s.size()-1,1);
        i--;
        }
      else
        out=true;
    }
  if(s[i]=='.') s.erase(s.size()-1,1);
  QString str = QString::fromStdString(s);
  return str;
}
