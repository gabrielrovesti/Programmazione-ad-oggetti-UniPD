#include "cerchio.h"

Cerchio::Cerchio(const Vertice& V, double r):Shape(),origine(V),raggio(r){}
Cerchio::Cerchio(const Cerchio& C):Shape(),origine(C.origine),raggio(C.raggio){}
double Cerchio::get_raggio() const{return raggio;}
Vertice Cerchio::get_origine()const{return origine;}
void Cerchio::set_origine(const Vertice& V){origine = V;}
double Cerchio::get_perimetro()const{return 2 * M_PI * raggio;}
double Cerchio::get_area()const{return M_PI* raggio*raggio;}
QString Cerchio::toString() const{ return "Cerchio origine: " + origine.toString() + " raggio: " + to_string_nozero(raggio);}

ostream& operator<<(ostream& os,const Cerchio& c){
        return os<<c.toString().toUtf8().constData();
}

QString Cerchio::get_nomeClasse()const{
    return "Cerchio";
}

Cerchio& Cerchio::operator +=(double x){
    raggio+=x;
    return *this;
}
Cerchio operator+(const Cerchio& c,double x){
    return Cerchio(c.get_origine(),c.get_raggio()+x);
}

Cerchio operator-(const Cerchio& c,double x){
    if(c.get_raggio() > x)
        return Cerchio(c.get_origine(),c.get_raggio()-x);
    else{
        throw  std::invalid_argument("Non puoi avere un raggio negativo");
        return c;
    }
}

bool Cerchio::operator==(const Cerchio& c2)const{
    return origine == c2.origine && raggio == c2.raggio;
}
bool Cerchio::operator<(const Cerchio& c2)const{
    return raggio < c2.raggio;
}
bool Cerchio::operator>(const Cerchio& c2)const{
  return raggio > c2.raggio;
}
bool Cerchio::operator<=(const Cerchio& c2)const{
  return raggio <= c2.raggio;
}
bool Cerchio::operator>=(const Cerchio& c2)const{
  return raggio >= c2.raggio;
}
Cerchio& Cerchio::operator =(const Cerchio& c){
    origine=c.origine;
    raggio=c.raggio;
    return *this;
}

