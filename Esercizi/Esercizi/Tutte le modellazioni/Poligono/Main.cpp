#include "Quadrato.h"
#include "Pol.h"
#include<iostream>
int main(){
Punto v[2]={Punto(5,1),Punto(0,1)};
Quadrato p(v);
Rettangolo l(p);
std::cerr<<p.area()<<std::endl;
std::cerr<<p.perimetro()<<std::endl;


return 0;
}



