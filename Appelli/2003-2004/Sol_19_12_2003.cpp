//Esercizio 1

D(const D& d){
    if(this != &d){
        d.size=size;
        d.val=val;
    }
    return this;
}
 
D& operator=(const D& d){
    if(this != &d){
        for(int i=0; i<size; i++){
            Z*x=punt;
            punt=d.punt;
            punt[i]++;
            delete x;
        }
    }
    return *this;
}

~D(){
    for(int i=0; i<size; i++){
        nodo*x=punt;
        delete punt;
        punt=x->next;
    }
}

bool operator==(iteratore i){
    return punt==i.punt;
}

iteratore begin() const{
    iteratore aux;
    aux.punt=punt;
    return aux;
}

iteratore& operator++(){
    if(punt && punt->next) punt=punt->next;
    return *this;
}

iteratore end() const{
    iteratore aux;
    aux.punt=0;
    return aux;
}

operator[](iteratore it){
    return punt->val;
}

//Esercizio 2

//1 - Non compila perché è protected nel contesto di invocazione
//2 - "7"
//3 - conflicting return type specified for 'virtual void D::m(int)'
//4 - "5"
//5 - Non compila perché ha un tipo proprio diverso
//6 - error: 'int B::i' is protected within this context
//7 - "9"

//Esercizio 3

//Non essendosi mai trattato il set, si usa vector!

#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

class B{
    protected:
    int i;
    public: 
    virtual ~B() {}
    B(int x=1): i(x) {}
    int quadrato() const{return i*i;}
};

class C: public B{
    public:
    C(int x=2): B(x) {}
    int cubo() const{return i*i*i;}
};

class Esercizio{
    private:
    vector<B*> v;
    public:
    void aggiungi(B& b){
        v.push_back(b);
    }
    int Fun(){
        int sum=0;
        vector<B*>::iterator it=v.begin();
        C c;
        for(; it!=v.end(); ++it){
            if(dynamic_cast<B*>(*it) && dynamic_cast<C*>(*it) || typeid(*it) == typeid(c)){
                C* loc=dynamic_cast<C*>(*it);
                sum+=loc->cubo();
            }
            else{
                sum+=(*it)->quadrato();
            }
        }
        return sum;
    }
};

//Esercizio 4
5 5 UNO
5 9 DUE
5 7 TRE
7 7 QUATTRO
9 9 CINQUE
5 5 SEI
-7 Dc -2 2 SETTE

//Esercizio 5
5 Z015 B01 **1
4 Z014 B01 3 Z01D0 **2
5 Z015 B01 1 Z011 Z01D1 **3
5 Z015 B01 Dc Zc Z= B=5 Z015 B01 Dc Z= D= **4
6 Z01Bc **5
5 Z015 B01 Dc Zc Z= B=5 Z015 B01 Dc 6 Z01Bc **6
