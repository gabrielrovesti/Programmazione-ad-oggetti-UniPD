#ifndef INTMOD
#define INTMOD

class intmod{

public:
    explicit intmod (int n=0);  // Il costruttore di conversione viene invocato solo esplicitamente
    operator int() const;
    static int get_modulo();
    static void set_modulo(int mod);
    intmod operator+(intmod im) const;
    intmod operator*(intmod im) const;
    intmod operator++();    //PREFISSO
    intmod operator++(int);     //POSTFISSO

private:
    static int modulo;
    int val;
};

int intmod::modulo=5;   //Inizializzazione di un campo dati statico
