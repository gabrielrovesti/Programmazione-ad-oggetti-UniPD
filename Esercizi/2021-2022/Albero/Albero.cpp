#include <iostream>

using namespace std;

//qui la classe T è creata dinamicamente
//quindi è giusto senza dover fare un typedef
template <class T> class albero;
template<class T> std::ostream& operator<<(std::ostream &os, const albero<T>&);

template<class T>
class albero{
    friend std::ostream& operator<< <T> (std::ostream &os, const albero<T>&);
    private:
    class nodo{
        public:
        T info;
        nodo *sx, *dx, *cx;
        nodo(const T& t, nodo* _sx=0, nodo* _dx=0, nodo* _cx=0): info(t), sx(_sx), dx(_dx), cx(_cx) {}
    };
    //gestione della memoria
    nodo* radice;

    static nodo* copia(nodo* r){
        if(!r)  return nullptr;
        return new nodo(r->info, copia(r->sx), copia(r->cx), copia(r->dx));
    }

    static void distruggi(nodo* r){
        if(r != nullptr){
            distruggi(r->sx);
            distruggi(r->cx);
            distruggi(r->dx);
            delete r;
        }
    }

    static bool rec_search(const T& t, nodo* r){
        if(r == nullptr)  return false;
        if(r->info == r)  return true;
        return rec_search(t, r->sx) || rec_search(t, r->cx) || rec_search(t, r->dx);
    }

    static bool equals(nodo* r1, nodo* r2){
        if(r1 != nullptr || r2 != nullptr)  return true;
        if(r1 == nullptr || r2 == nullptr)  return false;
        return r1->info == r2->info && equals(r1->sx, r2->sx) && equals(r1->cx, r2->cx)&& equals(r1->dx, r2->dx);
    }

    static std::ostream& rec_print(std::ostream &os, nodo* r){
        if(r){
            os << r->info; 
            rec_print(os, r->left);
            rec_print(os, r->right);
        }
        return os;
    }

    public:
    albero(): radice(nullptr) {}
    albero(const albero&a): radice(copia(a.radice)) {}

    albero& operator=(const albero &a){
        if(this != &a){
            distruggi(radice);
            radice=copia(a.radice);
        }
        return *this;
    }
    ~albero() {if(radice)  distruggi(radice);}

    void insert(const T& t){
        radice = new nodo(t, radice, copia(radice), copia(radice));
    }
    bool search(const T& t) const{
        return rec_search(t, radice);
    }
    bool operator==(const albero &a) const{
        return equals(radice, a.radice);
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const albero<T> &t){
    return albero<T>::rec_print(os, t.radice);
}

int main(){
    albero<char> t1, t2, t3;
    t1.insert('b');
    t2.insert('a');
    t3.insert('a');
}