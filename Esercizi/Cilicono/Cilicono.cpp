#include <cmath>
#include <iostream>

using namespace std;

class solidoConCerchio{ //classe base astratta
    protected:
        double raggio;
        double circonferenza() const {return (2 * M_PI * raggio);}
        double area_cerchio() const {return (M_PI * raggio * raggio);}
    public:
        solidoConCerchio(double r): raggio(r) {}
        virtual double area() const = 0;
        virtual double volume() const = 0;
};

class cilindro: virtual public solidoConCerchio{
    protected:
        double altezza;
        double area_laterale() const{
            return (circonferenza() * altezza);
        }
    public:
        cilindro(double r, double h): solidoConCerchio(r), altezza(h) {}
        double area() const override {
            return (2 * area_cerchio() + area_laterale());
        }
        double volume() const override {
            return (area_cerchio() * altezza);
        }
};

class cono: virtual public solidoConCerchio {
    protected:
        double altezza;
        double area_laterale() const{
            double apotema = sqrt(raggio * raggio + altezza * altezza);
            return (2 * circonferenza() * apotema);
        }
    public:
        cono(double r, double h): solidoConCerchio(r), altezza(h) {}
        double area() const override {
            return (area_cerchio() + area_laterale());
        }
        double volume() const override {
            return (area_cerchio() * altezza / 3);
        }
};

class cilicono: public cilindro, public cono {
    public:
        cilicono(double r, double h1, double h2):
        solidoConCerchio(r), cilindro(r, h1), cono(r, h2){}
        //la chiamata solidoConCerchio è data da responsabilità a chi scrive, compresa la base cilindro, che prende
        //raggio ed altezza; per coerenza il parametro r viene lo stesso messo in cilindro e cono ma la
        //chiamata virtuale su solidoConCerchio lo costruisce ugualmente
        double area() const override {
            return (cilindro::area_laterale() + cono::area_laterale() + area_cerchio());
        }
        double volume() const override {
            return (cilindro::volume() + cono::volume());
        }
};

int main(){
    solidoConCerchio* p;
    cilindro cil(1,2); cono co(1,2);
    cilindro clc(1.0,2.0);
    p=&cil;
    cout << "Area cilindro: " << p->area() << endl;
    cout << "Volume cilindro: " << p->volume() << endl;
    p=&co;
    cout << "Area cono: " << p->area() << endl;
    cout << "Volume cono: " << p->volume() << endl;
    p=&clc;
    cout << "Area cilicono: " << p->area() << endl;
    cout << "Volume cilicono: " << p->volume() << endl;
}