#include <iostream>

using namespace std;

class N {
    friend class Lista;
    private:
        int info;
        N* prev; 
        N* next;
    public:
        N(int y, N* p = 0, N* q = 0): info(y), prev(p), next(q) {}
        ~N() {if(next) delete next; cout << info << " ~N ";}
        N* getNext() const { return next; }
};

class Lista {
    private:
        N* last;
    public:
        Lista() : last(0) {}
        ~Lista() {
            if(last) {
                while(last->prev) last = last->prev;
                delete last;
            }
        }
        void add(int x) {
            N* p = new N(x,0,0);
            if(last) {last->next = p; p->prev = last;}
            last = p;
        }
        void operator--() { if(last) last = last->prev; }
        void operator--(int) {
            if(last){ 
                N* p = last;
                last = last->prev;
                if (last) {
                    last->next = 0;
                }
                else {
                    // lista vuota
                    last = 0;
                }
                delete p; 
            }
        }
        
        void print() {
            if (last) {
                N* p = last->getNext();
                while (p) {
                    cout << p->info << " ";
                    p = p->getNext();
                }
            }
        }

        void operator=(const Lista& l) {
            if(this == &l) return; // check for self-assignment

            // create new list by copying values from source list
            N* p = l.last;
            Lista tmp;
            while(p) {
                tmp.add(p->info);
                p = p->prev;
            }

            // clear current list
            if(last) {
                while(last->prev) last = last->prev;
                delete last;
            }

            // set last pointer to newly created list
            last = tmp.last;
        }

        const N& operator[](int i) const {
            N* p = last;
            while(p->prev) p = p->prev;
            while(i--) p = p->next;
            return *p;
        }

};

/*
Si considerino le classi N e Lista definite sopra. Si chiede di
• definire una classe Iteratore che permette di iterare sugli elementi di una lista. La classe deve
contenere un solo metodo pubblico che ridefinisce l’operatore di incremento prefisso
• ridefinire per la classe Lista l’operatore di subscripting.
*/

class Iteratore {
    friend class Lista;
    private:
        N* p;
    public:
        Iteratore(N* x = 0) : p(x) {}
        Iteratore& operator++() {
            if(p) p = p->getNext();
            return *this;
        }
};



int main() {
    Lista* p = new Lista; Lista* q = new Lista;
    p->add(3); p->add(4); p->add(5); p->add(6);
    q->add(7);
    *q=*p;
    --(*q);
    p->print(); cout << " **1\n";
    q->print(); cout << " **2\n";
    p->add(8);
    p->print(); cout << " **3\n";
    (*q)--; cout << " **4\n";
    q->print(); cout << " **5\n";
    --(*q); delete q; cout << " **6\n"; 
}

