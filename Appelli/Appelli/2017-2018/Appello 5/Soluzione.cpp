#include<iostream>
using namespace std;

template <class T>
class SmartP{
    private:
        T* p;
    public:
        //costruttore di default
        SmartP(): p(nullptr) {}

        //costruttore ad un parametro
        SmartP(const T* punt): p(new T(*const_cast<T*>(punt))){}

        //costruttore di copia profondo
        SmartP(const SmartP<T>& s):p(new T(*(s.p))){}
     	
        operator const T* () const {return p;}

        //distruttore profondo
        ~SmartP(){
          if (p)  delete p;
        }
        //assegnazione profonda
        SmartP<T>& operator=(const SmartP<T>& s){
            if(this!=&s)
            {
                delete p;
                p = new T(*s.p);

            }
            return *this;
        }

        //operatore di chiamata a funzione
        SmartP<T> operator ()(T*& p){return SmartP(p);}

        //operatore di dereferenziazione
         T& operator*()const{
            return *p;
        }
        //operatore di selezione di membro
         T* operator->()const
        {return p;}
};

class C{
    public:
        int *p;
        C(): p(new int (5)){}
};

int main(){
    const int a=1; const int* p = &a;
    
    SmartP<int>r;
    SmartP<int>s(&a);
    SmartP<int> t(s);
    
    cout<< *s  << "" <<*t << *p <<endl;
    *s=2; *t = 3;
    
    cout<< *s  << "" <<*t << *p << endl;
    r=t; *r=4;
    
    cout<<*r << *s  << "" <<*t << *p <<endl;
    
    cout<< (s==t) << (s!=p) <<endl;
    
    C c; SmartP<C> x(&c);
    cout << *(c.p) <<" " << *(x->p); cout << endl;
    
    *(c.p) = 6;
    cout << *s(c.p) << " " << *(x->p);cout << endl;
    SmartP<C> * q= new SmartP<C>(&c);
    delete q;
    cout << *(x->p); cout << endl;
}
