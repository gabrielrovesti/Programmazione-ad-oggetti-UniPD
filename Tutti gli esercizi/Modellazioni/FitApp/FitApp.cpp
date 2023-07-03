#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Si consideri it seguente modello di realta concemente di app FitApp© per la registrazione di allenamenti sportivi. 
Definire la seguente gerarchia di classi. 
1. Definire una classe base polimorfa astratta Allenamento i cui oggetti rappresentano un allenamento memorizzabile in FitApp. 
Ogni Allenamento è caratterizzato dalla durata in minuti. 
La classe è astratta in quanto prevede i seguenti metodi virtuali puri: 
• un metodo di -clonazione-: Allenamento* clone ()
• un metodo int calorie() con il seguente contratto puro: 
a->calorie () ritoma il numero di calorie consumate durante l'allenamento *a.

2. Definite una classe concreta Ciclismo derivata da Allenamento i cui oggetti
rappresentano un allenamento di ciclismo. Ogni oggetto ciclismo è caratterizzato 
dalla distanza totale percorsa in Km e dal numero di Km percorsi in salita.
La classe ciclismo implementa i metodi virtuali purl di Allenamento come segue: 
• per ogni puntatore p a Ciclismo, p->clone() ritorna un puntatore 
ad un oggetto Ciclismo che è una copia di *p. 
• per ogni puntatore p a ciclismo, p->calorie () ritorna il numero
di calorie dato dalla formula 200K2/D + 100S, dove K è la distanza totale 
percorsa in Km nell'allenamento *p, D è la durata in minuti dell'allenamento *p. 
Se it numero di Km percorsi in salita nell'allenamento *p. 

3. Definire una classe concreta corsa derivata da Allenamento i cui oggetti
rappresentano un allenamento di corsa.
Ogni oggetto Corsa è caratterizzato dalla distanza totale percorsa in Km 
e dal numero di Km percorsi su fondo sterrato. 
La classe Corsa implementa i metodi virtuali purl di Allenarnento come segue: 
• per ogni puntatore p a Corsa, p->clone() ritorna un puntatore ad un oggetto
corsa che è una copia di *p. 
• per ogni puntatore p a Corsa. p->calorie () ritorna il numero
di calorie dato dalla formula 600K2/D, dove K è la distanza totale percorsa 
in Km nell'allenamento *p, D è la durata in minuti dell'allenamento *p. 

4. Definire una classe concreta Nuoto derivata da Allennamento i cui oggetti
rappresentano un allenamento di nuoto. 
Ogni oggetto Nuoto è caratterizzato dal numero di vasche nuotate 
e dallo stile di nuoto (si assumano due soli stili possibili: libero e rana). 
La classe Nuoto implementa i metodi virtuali purl di Allenamento come segue: 
• per ogni puntatore p a Nuoto, p->clone () ritorna un puntatore ad un oggetto Nuoto 
che è una copia di *p. 
• per ogni puntatore p a Nuoto, se N è il numero di vasche nuotate 
nell'allenamento *p, allora p->calorie() ritorna 35N calorie. 
*/

class Allenamento {
    protected:
        double durata;
    public:
        virtual Allenamento* clone() const = 0;
        virtual int calorie() const = 0;
        virtual ~Allenamento() {};
};

class Ciclismo: public Allenamento {
    private:
        double distanza, salita;
    public:
        Allenamento* clone() const { return new Ciclismo(*this); }
        int calorie() const {
        return (200*pow(distanza,2))/durata + 100*salita;
        }
        double getDistanza() const { return distanza; }
        double getSalita() const { return salita; }
};

class Corsa: public Allenamento {
    private:
        double distanza, sterrato;
    public:
        Allenamento* clone() const {
        return new Corsa(*this);
        }
        int calorie() const {
        return (600*pow(distanza,2))/durata;
        }
        double getSterrato() const { return sterrato; }
};

class Nuoto: public Allenamento {
    private:
        double vasche;
        string stile;
    public:
        Allenamento* clone() const { return new Nuoto(*this); }
        int calorie() const { return 35*vasche; }
        string getStile() const { return stile; }
};

class FitApp {
    private:
        vector<const Allenamento*> a;
    public:
        vector<Ciclismo> salita(double perc) const {
        vector<Ciclismo> v;
        for (int i = 0; i < a.size(); ++i) {
        Ciclismo* c = dynamic_cast<Ciclismo*>(const_cast<Allenamento*>(a[i]));
        if (c && (100/c->getDistanza())*c -> getSalita() > perc)
        v.push_back(*c);
        }
        return v;
        }  
    
        vector<Allenamento*> calorie(int x) const {
        vector<Allenamento*> v;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] -> calorie() > x) {
            Nuoto* n = dynamic_cast<Nuoto*>(const_cast<Allenamento*>( a[i] ));
            if (n && n -> getStile() == "libero")
            v.push_back(a[i] -> clone());
            else v.push_back(a[i] -> clone());
            } 
        } 
        return v;
        }

        void insert(Corsa* p) {
            double record = 0;
            for (int i = 0; i < a.size(); ++i) {
            Corsa* c = dynamic_cast<Corsa*>(const_cast<Allenamento*>( a[i] ));
            if (c && c -> getSterrato() > record)
            record = c -> getSterrato(); }
            if (p -> getSterrato() > record) a.push_back(p);
        }

        int conta(double lim) {
            int cont = 0;
            for (int i = 0; i < a.size(); ++i) {
            Ciclismo* c = dynamic_cast<Ciclismo*>(const_cast<Allenamento*>( a[i] ));
            if (c && c -> getDistanza() > lim) cont++;
            }
            return cont;
        }
};
