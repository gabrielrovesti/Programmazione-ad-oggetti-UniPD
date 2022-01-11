#include <iostream>

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