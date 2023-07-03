/*
Definire una classe IntMod i cui oggetti rappresentano numeri interi modulo un dato intero n, che deve essere dichiarato come campo dati statico.
Definire metodi statici di setmodulo() e getmodulo() per tale campo dati statico.
Devono essere disponibili gli operatori di somma e moltiplicazione tra oggetti di IntMod.
Definire inoltre opportuni convertitori di tipo affinché questa classe sia liberamente usabile assieme al tipo primitivo int e valga la seguente condizione:
quando in una espressione compaiono interi e oggetti di IntMod il tipo dell’espressione dovrà essere intero. Scrivere infine un programma d’esempio che utilizza tutti i metodi della classe.
*/

#include <iostream>
using namespace std;

class IntMod{
    public:
    static int n;
    static void setmodulo(const IntMod&);
    static int getmodulo();
    int operator+(int) const;
    int operator*(int) const;
    operator int() const;
};

int IntMod::n = 1;

void IntMod::setmodulo(const IntMod& x){
    n = x.n;
}

int IntMod::getmodulo(){
    return n;
}

int IntMod::operator+(int a) const{
    return abs(a + n);
}

int IntMod::operator*(int a) const{
    return abs(a * n);
}

IntMod::operator int() const{
    return n;
}

int main(){
    IntMod a;
    a.n = 5;
    IntMod::setmodulo(a);
    cout << IntMod::getmodulo() << endl;
    cout << a + 5 << endl;
    cout << a * 5 << endl;
    cout << a << endl;
    return 0;
}