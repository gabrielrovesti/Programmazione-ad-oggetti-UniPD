#include <iostream>

using namespace std;
class Lavoratore{
    private:
        string nome;
    public:
        virtual ~Lavoratore() {}
        Lavoratore(string s): nome(s) {};
        string getNome() const {return nome;};
        virtual double stipendio() const=0;
        virtual void printInfo() const {cout << nome; };
};

class Dirigente: public Lavoratore {
    private:
        double fissoMensile;
    public:
        Dirigente(string s, double d=0): Lavoratore(s), fissoMensile(0) {}
            virtual double stipendio() const{
                return fissoMensile;
            }
        virtual void printInfo() const{
            cout << "Dirigente ";
            Lavoratore::printInfo();
        }
};

class Rappresentante: public Lavoratore {
    private:
        double baseMensile;
        double commissione;
        int tot;
    public:
        Rappresentante(string s, double d=0, double e=0, int x=0):
        Lavoratore(s), baseMensile(d), commissione(e), tot(x) {}
    
        virtual double stipendio() const{
            return baseMensile + commissione * tot;
        }

        virtual void printInfo() const{
            cout << "Rappresentante "; Lavoratore::printInfo();
        }
};

class LavoratoreOre : public Lavoratore {
    private:
        double pagaOraria;
        double oreLavorate;
    public:
        LavoratoreOre(string s, double d=0, double e=0):
            Lavoratore(s), pagaOraria(d), oreLavorate(e){}
        
        virtual double stipendio() const{
            if(oreLavorate <= 160)
                return pagaOraria * oreLavorate;
            else
                return 160 * pagaOraria + (oreLavorate - 160) * 2 * pagaOraria;
        };
        virtual void printInfo() const{
            cout << "Lavoratore a ore "; Lavoratore::printInfo();
        };
};

void stampaStipendio(const Lavoratore& x){
    x.printInfo();
    cout << " In quanto mese ha guadagnato " << x.stipendio() << " Euro. \n";
}

int main()
{
    Dirigente d("Pippo", 4000);
    Rappresentante r("Topolino", 1000, 3, 250);
    LavoratoreOre l("Pluto", 15, 170);
    stampaStipendio(d);
    stampaStipendio(r);
    stampaStipendio(l);
}