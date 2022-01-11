/*
Definire una superclasse Auto i cui oggetti rappresentano generiche automobili e due sue sottoclassi
Benzina e Diesel, i cui oggetti rappresentano automobili alimentate, rispettivamente, a benzina e a
diesel (ovviamente non esistono automobili non alimentate e si assume che ogni auto + o benzina o diesel). 
Ci interesserà l’aspetto fiscale delle automobili, cioè il calcolo del bollo auto.  Queste classi devono
soddisfare le seguenti specifiche:
•Ogni automobile è caratterizzata da un numero di cavalli fiscali. La tassa per cavallo fiscale`e unica
per tutte le automobili (sia benzina che diesel) ed è fissata in 5 euro.  La classe
Autofornisce un metodo tassa() che ritorna la tassa di bollo fiscale per l’automobile di invocazione.
•La classeDiesel`e dotata (almeno) di un costruttore ad un parametro intero x che permette di creare un’auto diesel di x cavalli fiscali. 
Il calcolo del bollo fiscale per un’auto diesel viene fatto nel seguente modo:  
si moltiplica il numero di cavalli fiscali per la tassa per cavallo fiscale e si somma una addizionale fiscale unica per ogni automobile diesel fissata in 100 euro.
•Un’auto benzina può soddisfare o meno la normativa europea Euro4.  La classe Benzina è dotata di (almeno) un costruttore ad un parametro interoxe ad un parametro booleano
b che permette di creare un’auto benzina di x cavalli fiscali che soddisfa Euro4 se b vale true altrimenti che non soddisfa Euro4. 
Il calcolo del bollo fiscale per un’auto benzina viene fatto nel seguente modo:  
si moltiplica il numero di cavalli fiscali per la tassa per cavallo fiscale; se l’auto soddisfa Euro4 allora si detrae un bonus fiscale 
unico per ogni automobile benzina fissato in 50 euro, altrimenti non vi è alcuna detrazione. 
Si  definisca  inoltre  una  classe ACI i  cui  oggetti  rappresentano  delle  filiali  ACI  addette  all’incasso
dei bolli auto.  Ogni oggetto ACI è caratterizzato da un vector di puntatori ad auto, cioè un oggetto vector<Auto*>,  
che rappresenta  la  lista  delle  automobili  gestite  da  una  filiale  ACI.  La  classe ACI fornisce un metodo 
aggiungiAuto(const Auto& a)che aggiunge l’autoaalla lista gestita dallafiliale di invocazione. Inoltre, la classe
ACI fornisce un metodoincassaBolli()che ritorna la somma
totale dei bolli che devono pagare tutte le auto gestite dalla filiale di invocazione.
Definire infine un esempio dimain()
in cui viene costruita una filiale ACI a cui vengono aggiunte
quattro automobili in modo tale che l’incasso dei bolli ammonti a 1600 euro.
*/

#include<iostream>
#include <vector>
using namespace std;
class Auto{
    private:
        static double cavalli;
        static double tassa_cv;
    protected:
        Auto(int);
        virtual ~Auto();
    public:
        static double getTassa() {return tassa_cv;}
        static double getCavalli() {return cavalli;}
        virtual double tassa() const =0;
};
double Auto::tassa_cv=5;

class Benzina: public Auto{
    private:
    static double bonus;
    bool euro4;
    public:
        Benzina(int x, bool b=true): Auto(x), euro4(b) {};
        virtual double tassa() const;
};

    double Benzina::tassa() const{
        if(euro4){
            return getCavalli()*getTassa()-bonus;
        }
        return getCavalli()*getTassa();
    }


class Diesel: public Auto{
    static double tassaD;
    public:
        Diesel(int x): Auto(x) {}
        virtual double tassa() const;
};
double Diesel::tassa() const{
    return getCavalli() * getTassa() + tassaD;
}

class ACI{
    private:
        vector<Auto*> v;
    public:
        void aggiungiAuto(const Auto &);
        double incassaBolli() const;
};
    void ACI::aggiungiAuto(const Auto &a){
            Auto &b=const_cast<Auto&>(a);
            v.push_back(&b);
    }
    double ACI::incassaBolli() const{
            double tot=0;
            vector<Auto*>::const_iterator it;
            for(it=v.begin(); it != v.end(); it++){
                tot+=(*it)->tassa();
            }
            return tot;
    }

int main(){
    Benzina fiat(60, false), lancia(60, true);
    Diesel bmw(90), audi(80);
    ACI a;
    a.aggiungiAuto(fiat); a.aggiungiAuto(lancia);
    a.aggiungiAuto(bmw); a.aggiungiAuto(audi);
    cout<<a.incassaBolli()<<endl;
}