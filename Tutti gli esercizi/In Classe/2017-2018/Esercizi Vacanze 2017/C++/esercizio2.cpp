/*
Si consideri il seguente modello di realta concernente l’app InForma per archiviare allenamenti sportivi. `
(A) Definire la seguente gerarchia di classi.
1. Definire una classe base polimorfa astratta Workout i cui oggetti rappresentano un allenamento (workout) archiviabile in InForma. Ogni
Workout e caratterizzato dalla durata temporale espressa in minuti. La classe ` e astratta in quanto prevede i seguenti ` metodi virtuali puri:
• un metodo di “clonazione”: Workout* clone().
• un metodo int calorie() con il seguente contratto puro: w->calorie() ritorna il numero di calorie consumate durante l’allenamento *w.
2. Definire una classe concreta Corsa derivata da Workout i cui oggetti rappresentano un allenamento di corsa. Ogni oggetto Corsa e`
caratterizzato dalla distanza percorsa espressa in Km. La classe Corsa implementa i metodi virtuali puri di Workout come segue:
• implementazione della clonazione standard per la classe Corsa.
• per ogni puntatore p a Corsa, p->calorie() ritorna il numero di calorie dato dalla formula 500K2/D, dove K e la distanza percorsa `
in Km nell’allenamento *p e D e la durata in minuti dell’allenamento ` *p.
3. Definire una classe astratta Nuoto derivata da Workout i cui oggetti rappresentano un generico allenamento di nuoto che non specifica lo
stile di nuoto. Ogni oggetto Nuoto e caratterizzato dal numero di vasche nuotate. `
4. Definire una classe concreta StileLibero derivata da Nuoto i cui oggetti rappresentano un allenamento di nuoto a stile libero. La classe
StileLibero implementa i metodi virtuali puri di Nuoto come segue:
• implementazione della clonazione standard per la classe StileLibero.
• per ogni puntatore p a StileLibero, p->calorie() ritorna il seguente numero di calorie: se D e la durata in minuti dell’allena- `
mento *p e V e il numero di vasche nuotate nell’allenamento ` *p allora quando D < 10 le calorie sono 35V , mentre se D 
*/

#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>
using namespace std;

class Workout{
private:
    double durata;

public:
    double getDurata() const {return durata;}
    virtual Workout* clone() const =0;
    virtual int calorie() const =0;
};

class Corsa: public Workout{
private:
    double distanza; //km

public:
    double getDistanza() const {return distanza;}
    virtual Workout* clone() const {
        return new Corsa(*this);
    }
    virtual int calorie() const {
        return (500*(distanza*distanza)/getDurata());
    }

};

class Nuoto: public Workout{
private:
    int numVasche;

public:
    int getNumVasche() const {return numVasche;}
};

class StileLibero: public Nuoto{
public:
    virtual Workout* clone() const {
        return new StileLibero(*this);
    }
    virtual int calorie() const {
        if(getDurata()<10)
            return 35*getNumVasche();
        else
            return 40*getNumVasche();
    }
};

class Dorso: public Nuoto{
public:
    virtual Workout* clone() const {
        return new Dorso(*this);
    }
    virtual int calorie() const {
        if(getDurata()<15)
            return 30*getNumVasche();
        else
            return 35*getNumVasche();
    }
};

class Rana: public Nuoto{
public:
    virtual Workout* clone() const {
        return new Rana(*this);
    }
    virtual int calorie() const {
        return 25*getNumVasche();
    }
};

class Informa{
private:
    vector<const Workout*> allenamenti;

public:
    vector<Nuoto*> vasche(int v) const {
        vector<Nuoto*> aux;
        for(vector<const Workout*>::const_iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            Nuoto* p=dynamic_cast<Nuoto*>(const_cast<Workout*>(*it));
            if(p && p->getNumVasche()>v)
                aux.push_back(p);
        }
        return aux;
    }

    vector<Workout*> calorie(int x) const {
        vector<Workout*> aux;
        for(vector<const Workout*>::const_iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            Rana* p=dynamic_cast<Rana*>(const_cast<Workout*>(*it));
            if(!p && (*it)->calorie()>x)
                aux.push_back((*it)->clone());
        }
        return aux;
    }

    void removeNuoto(){
        double max=0;
        bool trovato=false;
        for(vector<const Workout*>::iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            if((*it)->calorie()>max)
                max=(*it)->calorie();
        }

        for(vector<const Workout*>::iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            Nuoto* p=dynamic_cast<Nuoto*>(const_cast<Workout*>(*it));
            if(p && p->calorie()==max){
                trovato=true;
                delete p;
                it=allenamenti.erase(it);
            }
        }
    }
};

int main(){}