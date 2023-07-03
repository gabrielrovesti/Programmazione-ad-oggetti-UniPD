/*
Definire, separando interfaccia ed implementazione, una classe Raz
i cui oggetti rappresentano un numero razionale num/den
(naturalmente, i numeri razionali hanno sempre un denominatore diverso da zero).
La classe deve avere i seguenti metodi:
1. opportuni costruttori
2. un metodo Raz inverso() con il seguente comportamento:
se l'oggetto di invocazione n/m, allora inverso ritorna un oggetto che rappresenta m/n.
3. un operatore esplicito di conversione al tipo primitivo double
4. l'overloading degli operatori somma e moltiplicazione
5. l'overloading dell'operatore di incremento postfisso che,
naturalmente, dovrà incrementare di 1 il razionale
di invocazione
6. l'overloading dell'operatore di uguaglianza
7. l'overloading dell'operatore di output su ostream
8. un metodo Raz unTerzo() che ritorna il razionale 0.3333...
*/

#include <iostream>

class Raz {
    private:
    int num, den; //ci aspettiamo che il denominatore sia != 0
    public:
    //explicit = blocca la conversione implicita dall'esterno
    //se scrivo explicit, viene fatto solo nel file header (se su 2 file)
    explicit Raz(int n=0, int d=1): num(n), den(d==0? 1 : d) {}
    // inverso di Raz(0,d) è Raz(0,1)
    Raz inverso() const{
        return Raz (num == 0 ? 0 : den, num);
    }
    //Raz(1,3);
    operator double() const{
        //return (double)num/den;
        return static_cast<double>(num)/static_cast<double>(den);
    }
    //MCD - Stesso denominatore e somma dei numeratori (prodotto
    //perché sono due frazioni
    Raz operator+(const Raz& r) const{
        return Raz(num*r.den + r.num*den, den*r.den);
    }
    //Confronto tra frazioni ==
    //stesso numeratore e stesso denominatore
    bool operator==(const Raz& r) const{
        //return num == r.num && den == r.den;
        return num*r.den == r.num*den;
        //Frazioni uguali = numeratori e denominatori uguali
        //X     Y   
        //             ==
        //Y     X
    }
    //1/2 * 1/2 = 1/4
    Raz operator*(const Raz& r) const{
        return Raz(num*r.num, den*r.den);
    }
    //Postfisso = ++x
    //si mette "int" per distinguere il postfisso
    Raz operator++(int){
        Raz aux(*this); //this = puntatore a Raz (punta ad un intero Raz&)
        num = num + den;  //num += den;
        return aux;
    }
    //Prefisso = x++
    Raz operator++(){
        num = num + den;
        return *this;
    }
    //Numero fisso = metodo statico (cioè una sola copia
    //
    static Raz unTerzo(){
        return Raz(1,3); // 1/3 = 0.3333... (1 num. , 3 den.)
    }
    //friend std::ostream& operator<<(std::ostream& os, const Raz& r);
};

std::ostream& operator<<(std::ostream& os, const Raz& r){
    return os << r.num << "/" << r.den; //stampa ad es. 1/3
    //return os << static_cast<double>(r); //stampa ad es. 0.3333...
}

int main() {
  Raz x(2,3), y(2), z, u(1,8), v(3,2), w(8,4);
  // Crea:
  // x=2/3, y=2/1=2, z=0, u=1/8, v=3/2, w=8/4=2

  std::cout << x+y+v*u << std::endl; // 2.85417
  std::cout << u.inverso() << std::endl; // 8
  std::cout << (y == w) << std::endl; // true
  std::cout << y++ << " " << ++w << std::endl; // 2 3
  std::cout << (++y + Raz::unTerzo()) << std::endl; // 4.33333
  std::cout << 2 + Raz(1,2) << std::endl; // 2.5
}