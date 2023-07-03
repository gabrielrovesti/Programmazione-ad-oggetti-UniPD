/*
ESERCIZIO. 

Definire un template di classe dList<T> i cui oggetti rappresentano 
una struttura dati lista doppiamente concatenata (doubly linked list) 
per elementi di uno stesso tipo T. 
Il template dList<T> deve soddisfare i seguenti vincoli:

1. Gestione della memoria senza condivisione.
(distruzione e copia profonda)

2. dList<T> rende disponibile un costruttore dList(unsigned int k, const T& t) 
che costruisce una 
lista contenente k nodi ed ognuno di questi nodi memorizza una copia di t.

3. dList<T> permette l’inserimento in testa ed in coda ad una lista in tempo O(1) (cioe` costante):
-- Deve essere disponibile un metodo void insertFront(const T&) con il seguente comportamento: 
dl.insertFront(t) inserisce l’elemento t in testa a dl in tempo O(1).
-- Deve essere disponibile un metodo void insertBack(const T&) con il seguente comportamento: 
dl.insertBack(t) inserisce l’elemento t in coda a dl in tempo O(1).

4. dList<T> rende disponibile un opportuno overloading di operator< 
che implementa l’ordinamento lessicografico (ad esempio, 
si ricorda che per l'ordinamento lessicografico tra stringhe 
abbiamo che "campana" < "cavolo" e che
"eccellente" < "ottimo").

5. dList<T> rende disponibile un tipo iteratore costante dList<T>::constiterator 
i cui oggetti permettono di iterare sugli elementi di una lista.
*/

#include <iostream>

template <class T>
class dList{
    private:
    class nodo{
        public:
        T info;
        nodo* next;
        nodo* prev;
        nodo(const T& t, nodo* n=0, nodo* p=0): info(t), next(n), prev(p){}
    };
    nodo* first, *last;
    
    static void destroy(nodo* n){
        if(n){
            destroy(n->next);
            delete n;
        }
    }
    static void deep_copy(nodo* src, nodo*& f, nodo*& l){
        if(src){
            f = new nodo(src->info);
            l = f;
            src = src->next;
            while(src){
                l->next = new nodo(src->info, 0, l);
                l = l->next;
                src = src->next;
            }
        }
        else{
            f = l = 0;
        }
    }
    static bool isLess(const nodo* n1, const nodo* n2){
        if(!n1 && !n2) return false;
        if(!n1) return true;
        if(!n2) return false;
        if(n1->info < n2->info) return true;
        if(n1->info > n2->info) return false;
        return isLess(n1->next, n2->next);
    }

    public:
    dList(unsigned int k, const T& t): first(0), last(0){
        for(unsigned int i=0; i<k; i++){
            insertBack(t);
        }
    }
    dList(const dList& dl): first(0), last(0){
        deep_copy(dl.first, first, last);
    }
    ~dList(){
        destroy(first);
    }
    dList& operator=(const dList& dl){
        if(this != &dl){
            destroy(first);
            deep_copy(dl.first, first, last);
        }
        return *this;
    }
    void insertFront(const T& t){
        if(first){
            first = new nodo(t, first, 0);
            first->next->prev = first;
        }
        else{
            (first->next)->prev = first;
        }
    }
    void insertBack(const T& t){
        if(last){
            last = new nodo(t, 0, last);
            last->prev->next = last;
        }
        else{
            first = last = new nodo(t);
        }
    }
    bool operator<(const dList& dl) const{
        if(this == &dl) return false;
        return isLess(first, dl.first);
    }
    class const_iterator{
        friend class dList<T>;
        private:
        const nodo* ptr;
        bool pte;
        const_iterator(const nodo* p, bool b): ptr(p), pte(b){}
        public:
        const_iterator(): ptr(0), pte(false){}
        const_iterator& operator++(){
            if(ptr){
                if(!pte){
                    if(ptr -> next != nullptr) ptr = ptr -> next;
                    else {
                        ptr = ptr+1;
                        pte = true;
                    }
                }
            }
            return *this;
        }
        const_iterator operator++(int){
            const_iterator aux = *this;
            if(ptr){
                if(!pte){
                    if(ptr -> next != nullptr) ptr = ptr -> next;
                    else {
                        ptr = ptr+1;
                        pte = true;
                    }
                }
            }
            return aux;
        }
        const_iterator& operator--(){
            if(ptr){
                if(ptr->prev == nullptr) ptr=nullptr;
                else if (!pte) ptr = ptr->prev;
                else {
                    ptr = ptr-1;
                    pte = false;
                }
            }
            return *this;
        }
        const_iterator operator--(int){
            const_iterator aux = *this;
            if(ptr){
                if(ptr->prev == nullptr) ptr=nullptr;
                else if (!pte) ptr = ptr->prev;
                else {
                    ptr = ptr-1;
                    pte = false;
                }
            }
            return aux;
        }
        const T& operator*() const{
            return ptr->info;
        }
        const T* operator->() const{
            return &(ptr->info);
        }
        bool operator==(const const_iterator& cit) const{
            return ptr == cit.ptr;
        }
        bool operator!=(const const_iterator& cit) const{
            return ptr != cit.ptr;
        }
    };
    const_iterator begin() const{
        return const_iterator(first, false);
    }
    const_iterator end() const{
        if(!last) return const_iterator();
        return const_iterator(last+1, true);
    }
};

int main(){
        
    dList<int> x(4,2), y(0,0), z(6,8);
    
    y=x;
    x.insertFront(-2); z.insertFront(3); y.insertFront(0);
    if(x<y) std::cout << "x < y" << std::endl;
    if(z<x) std::cout << "z < x" << std::endl;
    if(y<z) std::cout << "y < z" << std::endl;
    if(z<y) std::cout << "z < y" << std::endl;

    std::cout << "x= ";
    dList<int>::const_iterator j = --(x.end());
    for(; j != x.begin(); --j) std::cout << *j << ' '; 
    std::cout << *j << std::endl << "y= ";
    for(dList<int>::const_iterator k = y.begin(); k != y.end(); ++k) std::cout << *k << ' ';  
    std::cout << std::endl << "z= ";
    dList<int>::const_iterator i = z.begin(); 
    for( ; i != z.end(); ++i) std::cout << *i << ' ';  
    std::cout << std::endl;
    
}