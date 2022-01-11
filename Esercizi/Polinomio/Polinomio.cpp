#include <iostream>
using namespace std;

class Polinomio{
    private:
        class Monomio;
        class SmartP{
            public:
                Monomio* punt;
        };
        class Monomio{
            public:
                int coefficiente, esponente, riferimenti;
                SmartP next;
                Monomio& operator*() const;
                Monomio* operator->() const;
                bool operator==(const SmartP&) const;
                bool operator!=(const SmartP&) const;
                ~SmartP();
                ~Monomio();
        };
        SmartP first;
        public:
        Polinomio();
        bool operator==(const& Polinomio, const&Polinomio) const;
        bool operator!=(const& Polinomio, const&Polinomio) const;
        Polinomio operator/(const& Polinomio, const&Polinomio);
        Polinomio operator+(const& Polinomio, const&Polinomio);
        Polinomio operator*(const& Polinomio, const&Polinomio);
        Polinomio operator-(const& Polinomio, const&Polinomio);
        Polinomio operator%(const& Polinomio, const&Polinomio);

};

int main(){
    Polinomio X(1,1);
    cout << "X = " << X << endl; 
    Polinomio Z(3,4);
    cout << "Z = " << Z << endl; 
    Polinomio T(X);
    cout << "T = " << T << endl;
    T = Z; 
    cout << "T = " << T << endl; 
    cout << "X = " << X << endl; 
    Polinomio Q=3*X + 2*X*X - X*X*X + 7*(X^4);
    cout << "Q = " << Q << endl; 
    Polinomio P = 2*(X^2);
    cout << "P= " << P << endl;
    cout << "Q*Q = " << Q*Q << endl;
    cout << "Q/P = " << Q/P << endl;
    cout << "Q^3 = " << Q^3 << endl;
    cout << "Q%P = " << Q%P << endl;
    cout << "Q(3) = " << Q(3) << endl;
    if(P == 2*(X^2)) cout << "P(3) = " << P(3) << endl;
    if(P != Q) cout << "Q(P(3)) = " << Q(P(3)) << endl;
}