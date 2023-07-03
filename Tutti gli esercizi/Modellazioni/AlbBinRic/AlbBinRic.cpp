#include <iostream>
#include "AlbBinRic.h"

using namespace std;

template <class T>
ostream& operator<<(ostream& os, Nodo<T>& p){
    if(!p) os << "@"; //caso base
    else{
        os << p.info << " ";
        os << p.sinistro << " ";
        os << p.destro;
    }
    return os;
}

template <class T>
Nodo<T>* AlbBinRic<T>::Find(T x) const{
    return FindRic(x, radice);
}

template <class T>
Nodo<T>* AlbBinRic<T>::FindRic(T x, Nodo<T>* p){
    if(!p) return 0;
    if(x==p->info) return p;
    if(x < p->info) return FindRic(x, p->sinistro);
    return FindRic(x, p->destro);
}

template <class T>
Nodo<T>* AlbBinRic<T>::Massimo() const{
    if(!radice) return 0;
    return MassimoRic(radice);
}

template <class T>
Nodo<T>* AlbBinRic<T>::MassimoRic(Nodo<T>* p){
    if(!p->destro) return p;
    return MassimoRic(p->destro);
}

template <class T>
Nodo<T>* AlbBinRic<T>::Minimo() const{
    if(!radice) return 0;
    return MinimoRic(radice);
}

template <class T>
Nodo<T>* AlbBinRic<T>::MinimoRic(Nodo<T>* p){
    if(!p->sinistro) return p;
    return MinimoRic(p->sinistro);
}

template <class T>
Nodo<T>* AlbBinRic<T>::Succ(Nodo<T>* x) const{
    if(!x) return 0;
    if(x->destro) return MinimoRic(x->destro);
    //caso x->destro==0
    while(x->padre && x->padre->destro==x) x=x->padre;
    return x->padre;
}

template <class T>
Nodo<T>* AlbBinRic<T>::Pred(Nodo<T>* x) const{
    if(!x) return 0;
    if(x->sinistro) return MassimoRic(x->sinistro);
    //caso x->sinistro==0
    while(x->padre && x->padre->sinistro==x) x=x->padre;
    return x->padre;
}

template <class T>
void AlbBinRic<T>::Insert(T x){
    if(!radice) radice=new Nodo<T>(x);
    else InsertRic(radice, x);
}

template <class T>
void AlbBinRic<T>::InsertRic(Nodo<T>* p, T x){
    if(x < p->info){
        if(!p->sinistro) p->sinistro=new Nodo<T>(p, x);
        InsertRic(p->sinistro, x);
    }
    else{
        if(!p->destro) p->destro=new Nodo<T>(p, x);
        InsertRic(p->destro, x);
    }
}

template <class T>
ostream& operator<<(ostream& os, const AlbBinRic<T>& a) {
    os << *(a.radice);
    return os;
}


template <class T>
void AlbBinRic<T>::Delete(T x){
    Nodo<T>* p=Find(x);
    if(!p) return;
    if(!p->sinistro && !p->destro){
        if(!p->padre) radice=0;
        else if(p->padre->sinistro==p) p->padre->sinistro=0;
        else p->padre->destro=0;
        delete p;
    }
    else if(!p->sinistro || !p->destro){
        Nodo<T>* figlio=p->sinistro ? p->sinistro : p->destro;
        if(!p->padre) radice=figlio;
        else if(p->padre->sinistro==p) p->padre->sinistro=figlio;
        else p->padre->destro=figlio;
        figlio->padre=p->padre;
        delete p;
    }
    else{
        Nodo<T>* s=MinimoRic(p->destro);
        p->info=s->info;
        if(s->padre->sinistro==s) s->padre->sinistro=s->destro;
        else s->padre->destro=s->destro;
        if(s->destro) s->destro->padre=s->padre;
        delete s;
    }
}

int main(){
    return 0;
}