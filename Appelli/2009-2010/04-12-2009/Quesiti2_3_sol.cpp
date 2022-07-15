//Quesito 2
#include <iostream>
using namespace std;

typedef void (*caller)(void);

class base
{
  public:
  base()
  {
    caller vfunc1;
    caller vfunc2;
    cout << "Object base constructed" <<endl;
    cout << "Object address is "<< this <<endl;
    cout << "vfptr address is "<< *(void**)this <<endl;
    cout << "base::funct1 address is "<< *(void**)(*(void**)this) <<endl;
    cout << "base::funct2 address is "<< *((void**)(*(void**)this)+1) <<endl;
    cout << "Calling vfunctions using vptr and vtable:" <<endl;
    
    /* Base class vtable function 1, 2 */
    vfunc1 = (caller)(*(void**)(*(void**)this));
    vfunc2 = (caller)(*((void**)(*(void**)this)+1));
    
    /* Call base class vtable function 1, 2 */
    vfunc1();
    vfunc2();
  }
  virtual void funct1(void)
  {
    cout << "base::funct1" <<endl;
  }
  virtual void funct2(void)
  {
    cout << "base::funct2" <<endl;
  }
};

class derived : public base
{
  public:
  derived()
  {
    caller vfunc1;
    caller vfunc2;
    cout << "Object derived constructed" <<endl;
    cout << "Object address is "<< this <<endl;
    cout << "vfptr address is "<< *(void**)this <<endl;
    cout << "derived::funct1 address is "<< *(void**)(*(void**)this) <<endl;
    cout << "derived::funct2 address is "<< *((void**)(*(void**)this)+1) <<endl;
    cout << "Calling vfunctions using vptr and vtable:" <<endl;
    
    /* Derived class vtable function 1, 2 */
    vfunc1 = (caller)(*(void**)(*(void**)this));
    vfunc2 = (caller)(*((void**)(*(void**)this)+1));
    
    /* Call derived class vtable function 1, 2 */
    vfunc1();
    vfunc2();
  }
  void funct1(void);
  void funct2(void);
};

void derived::funct1(void)
{
  cout << "derived::funct1" <<endl;
}

void derived::funct2(void)
{
   cout << "derived::funct2" <<endl;
}

int main (int argh, char *argv[])
{
  derived d;
  caller vfunc1;
  caller vfunc2;
  void *** vfptr = (void ***) &d;
  void ** vtable = (void **)*vfptr;
  
  /* class vtable function 1, 2 */
  vfunc1 = (caller)(vtable[0]);
  vfunc2 = (caller)(vtable[1]);
  cout << "From main" <<endl;
  cout << "Address of d is " << &d << endl;
  cout << "d.vfptr is " << vtable << endl;
  cout << "Address of d.funct1 is " << vtable[0] << endl;
  cout << "Address of d.funct2 is " << vtable[1] << endl; 
  cout << "Calling vfunctions using vptr and vtable:" <<endl;
  
  /* Call vtable function 1, 2 */
  vfunc1();
  vfunc2();
  
  return 0; 
}

//Quesito 3
#include <iostream>

class A{
    public:
    virtual ~A() {} 
};

class B: public A{};
class C: public A{};

A* fun(){
    C* pc; A*pa;
    pa=pc;
    return pa;
}

//L'unico modo per fare compilazione ma errore è creare un dangling pointer
int main(){
    A* pa = new A; B* pb = new B; C* pc = new C;
    pa=fun();
    std::cout << pa;
}