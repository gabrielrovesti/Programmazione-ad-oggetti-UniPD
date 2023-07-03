#include <iostream>
/*
Definire un template di chime Coda<T> i cui oggetti rappresentano una struttura dati coda per elementi di uno stesso tipo T, ossia la coda implementa
l'usuale politica FIFO (First In First Out) di inserimento/estrazione degli elementi:
gli elementi vengono estratti nello stesso ordine in cui sono stati inseriti. II template Coda<T> deve soddisfare i seguenti vincoli: 
1. Coda<T> non puo usare i contenitori STL come campi dati (inclusi puntatori e riferimenti a contenitori STL). 
2. 11 parametro di tipo del template Coda<T> ha come valore di default double. 
3. Gestione della memoria senza condivisione. 
4. Deve essere disponibile un costruttore di default che costruisce la coda vuota. 
5. Deve essere disponibile un costruttore coda (int k, const T& t) che costruisce una coda contenente k copie dell'elemento t. 
6. Deve essere disponibile un metodo void insert (const T&) con il seguente comportamento: c.insert (t) inserisce l'elemento 
t in coda a c in tempo costante. 
7. Deve essere disponibile un metodo T removeNext() con il seguente comportamento: se la coda c non è vuota, 
c.removeNext() rimuove l'elemento in testa alla coda c in tempo costante e lo ritorna; 
se invece c è vuota allora provoca undefined behaviour (da definirsi opportunamente). 
8. Deve essere disponibile un metodo T* getNext() con il seguente comportamento: 
se Ia coda c non è vuota, c.getNext() ritorna un puntatore all'elemento in testa a c in tempo costante; 
se invece c è vuota ritorna il puntatore nullo. 
9. Overloading di operator< che implementa il confronto lessicografico tra code. 
10. Overloading dell'operatore di somma che agisca come concatenazione: c + d ritorna la coda che si otticne aggiungendo d in coda a c. 
11. Coda<T> rende disponibile un tipo iteratore costante Coda<T>::const_iterator 
i cui oggetti permettono di iterare sugli elementi di una coda c senza permettere modifiche al contenuto di c. 
*/

using namespace std;

class ErrorQueue{
    public:
    ErrorQueue(){cout << "Errore: ";}
};

template<class T = double>
class Coda{
    private:
    class Nodo{
        public:
        T info;
        Nodo* next;

        Nodo(const T& t=T(), Nodo*n=nullptr): info(t), next(n){}
        ~Nodo(){delete next;}
    };
    Nodo* first, *last;
    static Nodo* copy(Nodo* n){
        if(!n)  return nullptr;
        else    return new Nodo*(n->info, copy(n->next));
    }
    public:
    Coda(): first(nullptr), last(nullptr){}
    Coda(int k, const T& t){
        if(!k) first=last=nullptr;
        else{
            first=last=new Nodo(t);
            for(; k>0; k--){
                Nodo* aux=new Nodo(t, first);
                first=aux;
            }
        }
    }
    void insert(const T& t){
        Nodo* aux=new Nodo(t);
        if(first == nullptr) first=last=aux;
        else{
            if(last->next){
                last->next=aux;
                last=aux;
            }
            else{
                last=aux;
            }
        }
    }
    T removeNext(){
        if(!first) throw ErrorQueue();
        else{
            T info_ret=first->info;
            Nodo* x=first;
            first=first->next;
            x->next = nullptr;
            delete x;
            return info_ret;
        }
    }
    T* getNext() const{
        T info_ret;
        if(!first)  return nullptr;
        return &first->info;    //ritorno & in accordo con il tipo T*, occhio a quello
    }
    static bool ifminus(Nodo*p1, Nodo*p2){
        if(!p1 && !p2) return true;
        if(!p1 || !p2)  return false;
        else return p1->info < p2->info && ifminus(p1->next, p2->next);
    }
    bool operator<(const Coda& c) const{
        return ifminus(first, c.first);
    }
    Coda& operator+(const Coda& c) const{
        Coda aux=new Coda();
        aux.first=first;
        aux.last=last;
        aux.last->next=c.first;
        return aux;
    }
    class const_iter{
        private:
        const Nodo* n;
        public:
        const_iter operator++(){
            if(!n)  n=n->next;
            return *this;
        }
        const T& operator*() const{
            return (*n)->info;
        }
        const T* operator->() const{
            return n;
        }
        const T operator[](const_iter i){
            return (i.n->info);
        }
    };
};

int main(){
    Coda<double> a;
    double x = 1.2;
    a.insert(x);
    
    double* p = a.getNext();
}