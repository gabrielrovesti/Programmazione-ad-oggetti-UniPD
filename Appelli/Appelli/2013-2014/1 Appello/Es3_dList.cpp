// ESERCIZIO SVOLTO IN AULA NELLA LEZIONE DEL 23/1/2015
//soluzione dell'esercizio dList (lista doppiamente linkata, primo appello dell'a.a. 13/14) come discussa in aula nell'ultima lezione del 23/1/2015.
//Soluzione by Ranzato
//URL: http://pastebin.com/JxRX6AAk

template<class T>
class dList {
  friend class const_iterator;
private:
  class nodo {
  public:
    T info;
    nodo *prev, *next; 
    nodo(nodo* p =0, const T& t = T(), nodo* n=0): prev(p), info(t), next(n) {}
    ~nodo() {if(next) delete next;} 
  };
  nodo *first, *last; // empty list  IFF  first==0==last

  static nodo* copia(nodo* p) {
    if(p==0) return 0;
    nodo* f = new nodo(0,p->info,0);
    nodo* currN = f;
    while(p->next !=0) {
      currN->next = new nodo(currN, p->next->info,0);
      currN = currN->next;
      p = p->next;
    }
    return f;
  }
  static nodo* getLast(nodo* f) {
    while(f && f->next) f=f->next;
    return f;
  }
  
  static bool compareLex(nodo* p1, nodo* p2) {
    if(!p1) return true;
    if(!p2) return false;
    // p1 && p2
    if(p1->info < p2->info) return true;
    if(p1->info > p2->info) return false;
    // p1 && p2 && p1->info == p2->info
    return compareLex(p1->next,p2->next);
  }
  
public:
  ~dList() {if(first) delete first;} 

  dList(const dList& l): first(copia(l.first)), last(getLast(first)) {}

  dList& operator=(const dList& l) {
    if(this != &l) {
      if(first) delete first;
      first = copia(l.first); 
      last = getLast(first);
    }
    return *this;
  } 
  dList(): first(0), last(0) {}
  dList(int k, const T& t) {
    if(k<=0) {first=last=0;}
    else {
      first = new nodo(0,t,0);
      nodo* temp = first;
      --k;
      while(k>0) {
	temp->next = new nodo(temp,t,0);
	temp = temp->next;
	--k;
      }
      last = temp;
    }
  } 
  void insertFront(const T& t) {
    first = new nodo(0,t,first);
    if(first->next==0) last = first;
    if(first->next) (first->next)->prev=first;
  }
  void insertBack(const T& t) {
    last = new nodo(last,t,0);
    if(last->prev != 0) (last->prev)->next = last;
    else first = last;
  }
  bool operator<(const dList& l) const {
    return compareLex(first,l.first);
  }
  class const_iterator {
    friend class dList<T>;
  private:
    const nodo* punt;
    // costruttore privato
    const_iterator(const nodo* p=0): punt(p) {}
  public:
    const T& operator*() const {
      return punt->info;
    }
    const T* operator->() const { 
      return &(punt->info); 
    }
    const_iterator& operator++() {
      if(punt) punt = punt->next;
      return *this;
    }
    const_iterator& operator--() {
      if(punt) punt=punt->prev;
      return *this;
    }
    bool operator==(const const_iterator& i) const {
      return punt == i.punt;
    }
  };
  const_iterator begin() const {
    return const_iterator(first); 
  }
  const_iterator end() const {
    return const_iterator(0);
  }
};

int main() {
  // codice che istanzia il template dList
  dList<int> x1,x2;
  dList<int> x3(5,2);
  x1=x2;
  x1<x3;
  dList<int>::const_iterator it1 = x1.begin();
  dList<int>::const_iterator it2 = x3.end();
  ++it1;
  --it2;
  x1.insertBack(5);
  x3.insertFront(4);
  dList<int> x4(x3);
  x4<x1;
  bool b = it1 == it2;
}
