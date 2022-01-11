/*
ESERCIZIO. 

Definire un template di classe dList<T> i cui oggetti rappresentano una struttura dati lista doppiamente concatenata (doubly linked list) per elementi di uno stesso tipo T. Il template dList<T> deve soddisfare i seguenti vincoli:

1. Gestione della memoria senza condivisione.

2. dList<T> rende disponibile un costruttore dList(unsigned int k, const T& t) che costruisce una 
lista contenente k nodi ed ognuno di questi nodi memorizza una copia di t.

3. dList<T> permette l’inserimento in testa ed in coda ad una lista in tempo O(1) (cioe` costante):
-- Deve essere disponibile un metodo void insertFront(const T&) con il seguente comportamento: dl.insertFront(t) inserisce l’elemento t in testa a dl in tempo O(1).
-- Deve essere disponibile un metodo void insertBack(const T&) con il seguente comportamento: dl.insertBack(t) inserisce l’elemento t in coda a dl in tempo O(1).

4. dList<T> rende disponibile un opportuno overloading di operator< che implementa l’ordinamento lessicografico (ad esempio, si ricorda che per l'ordinamento lessicografico tra stringhe abbiamo che "campana" < "cavolo" e che
"eccellente" < "ottimo").

5. dList<T> rende disponibile un tipo iteratore costante dList<T>::constiterator i cui oggetti permettono di iterare sugli elementi di una lista.
*/

#include <iostream>

template <class T>
class dlist{
    private:
        class nodo{
            friend class dlist;
            T info;
            nodo *prev, *next;
            nodo(const T& t = T(), nodo* p=nullptr, nodo* n=nullptr): info(t), prev(p), next(n) {}
            ~nodo(){delete next;}
        };
        nodo *last, *first;
    
    //varie operazioni in quanto trattasi di lista doppiamente linkata
    //quindi prendo nodi precedenti/successivi e si va avanti così
    static nodo* copia(nodo*f, nodo*&last){
        if(!f)    return last=nullptr;
        nodo* first=new nodo(f->info, nullptr, nullptr);
        nodo*curr=first;
        while(f->next != nullptr){
            curr=new nodo(f->next->info, curr, nullptr);
            curr->prev->next=curr;
            f=f->next;
        }
        last=curr;
        return first;
    }

    //versione ricorsiva
    static nodo *copia_r(nodo* f, nodo*&last, nodo* prev=nullptr){
        if(f==nullptr)  return last=nullptr;
        nodo *aux=new nodo(f->info, prev, nullptr);
        aux->next=copia(f->next, last, aux);
        if(f->next == nullptr)  last=aux;
        return aux;
    }

    //ordine lessicografico, quindi o sono uguali, minore o si va avanti
    //o è la prima è vuota e quindi nel confronto ritorna true
    //o è vuota la seconda e nel confronto ritorna false
    static bool check(nodo* d1, nodo* d2){
        if(d1 == nullptr)  return true;
        if(d2 == nullptr)  return false;
        return d1->info < d2->info || (d1->info == d2->info || check(d1->next, d2->next));
    }
    //se uno dei due elementi non è minore dell'altro,
    //uso la valutazione lazy della congiunzione & per sfruttare il caso limite di confronto
    //dei due nodi, altrimenti avanzo ricorsivamente.
    //Logicamente ha senso per la valutazione considerata. 

    static void distruggi(nodo* r){
        if(r == nullptr)    return;
        distruggi(r->next);
        delete r;
    }

    public:
        dlist(const dlist& d):  last(nullptr), first(copia(d.first, last)){}
        dlist(unsigned int k, const T& t): last(nullptr), first(nullptr){
            for(unsigned int i=0; k>0; --i) 
                insertFront(t);
        }
        dlist& operator=(const dlist& t){
            if(this != &t){
                delete first;
                first=copia(t.first, last);
            }
            return *this;
        }
        ~dlist() { if(first) distruggi(first); }
        void insertFront(const T& t){
            first=new nodo(t, nullptr, first);
            if(last != nullptr)
                last=first;
            else
                (first->next)->prev=first;
        }

        void insertBack(const T& t){
            last=new nodo(t, last, nullptr);
            if(last == nullptr)
                first=last;
            else
                (last->prev)->next=last;
        }
        bool operator<(const dlist& dl) const{
            return check(first, dl.first);
        }
        class const_iterator{
            friend class dlist<T>;
            private:
                nodo* ptr;      //ptr al nodo attuale
                bool pte;       //per gestire il passaggio dopo l'ultimo elemento, quindi past-the-end
                const_iterator(nodo* p, bool p_t_e=false): ptr(p), pte(p_t_e) {}
            public:
                const_iterator(): ptr(nullptr), pte(false) {}
                const T& operator*() const{
                    return ptr->info;
                }
                const T* operator->() const{
                    return &(ptr->info);
                }
                const_iterator& operator++(){
                    if(!ptr && !pte){
                        ++ptr;
                        pte=true;
                    }
                    else
                    ptr=ptr->next;

                    return *this;
                }
                const_iterator& operator++(int){
                    const_iterator& i=*this;
                    if(*this != nullptr){
                        if(pte){
                            ptr=ptr->next;
                        }
                        else{
                            if(ptr->next==nullptr){
                                ++(*this);
                                pte=true;
                            }
                        }
                    }
                    return i;
                }
                const_iterator& operator--(){
                    if(ptr!=nullptr) {
                    if(pte) 
                    {   
                        ptr--; 
                        pte=false;
                    }
                    else ptr=ptr->prev;
                    }
                    return *this;
                }
                const_iterator& operator--(int){
                    const_iterator& i=*this;
                    if(ptr!=nullptr){
                        if(pte){
                        --(*this);
                        pte=false;
                        }
                        else
                        ptr=ptr->next;
                    }
                    return i;
                }
                bool operator==(const const_iterator& i) const{
                    return ptr==i.ptr;
                }
                bool operator!=(const const_iterator& i) const{
                    return ptr!=i.ptr;
                }
        };
    const_iterator begin() const{
        return first;
    }
    const_iterator end() const{
        if(first == nullptr) return const_iterator(nullptr, false);
        return const_iterator(last+1, true);
    }
};

int main() {
  dlist<int> x(4,2), y(0,0), z(6,8);
  y=x;
  x.insertFront(-2); z.insertFront(3); y.insertFront(0);
  if(x<y) std::cout << "x < y" << std::endl;
  if(z<x) std::cout << "z < x" << std::endl;
  if(y<z) std::cout << "y < z" << std::endl;
  if(z<y) std::cout << "z < y" << std::endl;

  std::cout << "x= ";
  dlist<int>::const_iterator j = --(x.end());
  for(; j != x.begin(); --j) std::cout << *j << ' '; 
  std::cout << *j << std::endl << "y= ";
  for(dlist<int>::const_iterator k = y.begin(); k != y.end(); ++k) std::cout << *k << ' ';  
  std::cout << std::endl << "z= ";
  dlist<int>::const_iterator i = z.begin(); 
  for( ; i != z.end(); ++i) std::cout << *i << ' ';  
  std::cout << std::endl;
}