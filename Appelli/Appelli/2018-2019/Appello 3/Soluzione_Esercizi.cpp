#include <iostream>
#include <vector>

//Esercizio 1
using namespace std;
vector<QAbstractButton*> fun(list<QWidget*>&q, const QSize& sz, vector <const QWidget*>& v){
   vector<QAbstractButton*> v;
   list<QWidget*>::iterator it = q.begin();

   for(; it!=v.end(); ++it){
       if(*it && (*it)->sizeHint() == size) q.push_front((*it)->clone());
       QAbstractSlider *s=dynamic_cast<QWidget*>(*it);
       if((*it) && !s && (*it)->sizeHint() == s){
            delete *it; 
            it = lista.erase(it);
       }
       if((*it) && dynamic_cast<QCheckBox*>(*it) || dynamic_cast<QPushButton*>(*it)){
           v.push_back(static_cast<QAbstractButton*>(*it));
           it=lista.erase(it);
       }
   }
   return v;
}

//Esercizio 2
#include<iostream>
using namespace std;

class A {
    public:
    virtual ~A();
};

A::~A() {}

class B : public A {
    public:
};

class C {
    public:
        B* fun(A* par) { return dynamic_cast<B*>(par); } 
};

/*********************************************************** II VERSIONE ***********************************************************/

#include<iostream>
using namespace std;

class A {
    public:
    virtual ~A();
};

A::~A() {}

class B : public A {
    public:
};

class C {
    private:
        B* b;
    public:
        C(A* a=new A()) : b(dynamic_cast<B*>(a)) {}
};

//Esercizio 3
F-F-F-V-F-V-V-F-P-V-F-F

//Esercizio 4
F(const F& f): pz(f.pz) {}