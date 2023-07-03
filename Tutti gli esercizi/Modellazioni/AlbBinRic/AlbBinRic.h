#include <iostream>

using namespace std;

template <class T>
struct Nodo{
    T info;
    Nodo<T>* sinistro, * destro, * padre;
    Nodo(T i, Nodo<T>* s=0, Nodo<T>* d=0, Nodo<T>* p=0):info(i), sinistro(s), destro(d), padre(p){}
};

template <class T>
class AlbBinRic{
public:
    AlbBinRic():radice(0){}
    ~AlbBinRic(){cancellaR(radice);}
    Nodo<T>* Find(T x) const;
    Nodo<T>* Minimo() const;
    Nodo<T>* Massimo() const;
    Nodo<T>* Succ(Nodo<T>* x) const;
    Nodo<T>* Pred(Nodo<T>* x) const;
    void Insert(T);
    void Delete(T);
    static T Valore(Nodo<T>* p) {return p->info;}
private:
    Nodo<T>* radice;
    void cancellaR(Nodo<T>* p){
        if(p){
            cancellaR(p->sinistro);
            cancellaR(p->destro);
            delete p;
        }
    }
    static Nodo<T>* FindRic(T, Nodo<T>*);
    static Nodo<T>* MinimoRic(Nodo<T>*);
    static Nodo<T>* MassimoRic(Nodo<T>*);
    static void InsertRic(Nodo<T>*, T);
};

//dichiarazione di operator <<
template <class T> ostream& operator<<(ostream&, AlbBinRic<T>&);