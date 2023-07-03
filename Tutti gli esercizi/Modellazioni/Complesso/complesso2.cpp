#include <iostream>

using namespace std;

class complesso_polare{
private:
    double modulo;
    double angolo;
public:
    void inizializza (double r, double i){
        modulo = sqrt(r*r + i*i);
        angolo = atan(i/r);
    }
    double get_reale(){
        return modulo*cos(angolo);
    }
    double get_immaginario(){
        return modulo*sin(angolo);
    }
};

