/* 
Definire un'unica gerarchia di classi che includa:

1) una classe base polimorfa A alla radice della gerarchia
2) una classe derivata astratta B
3) una sottoclasse C di B che sia concreta
4) una classe D che non permetta la costruzione pubblica
dei suoi oggetti, ma solamente la costruzione di oggetti di D
che siano sottooggetti
5)una classe E derivata direttamente da D e con l'assegnazione ridefinita
pubblicamente con comportamento identico a quello dell'assegnazione standard di E.*/

class A{
   public:
   virtual ~A();
};

class B: public A{
   virtual void method()=0;
};

class C: public B{
   virtual void method(){
      cout << "C redefines method "<<endl;
   }
};

class D;

class D{
   private:
   int d;
   public:
   D();
   D(int d1): d(d1){};
};

class E;

class E: public D{
   public:
   D d;
   E(): d(2){};
   E& operator=(const E& e1){
      if(this != &e1){
         *this = e1;
      }
      return *this;
   }
};