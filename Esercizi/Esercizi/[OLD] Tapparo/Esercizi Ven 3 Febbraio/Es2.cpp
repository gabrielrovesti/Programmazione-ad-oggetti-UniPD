class A{
private:
    int x;
public:
    A(int k=5): x(k)        // costruttore di default
    {
        cout << k << "A01";
    }

    A(const A&a): x(a.x)    { cout << "AC";}    //construttore di copia

    A g() const {return *this;}
};


class B{
private:
    A ar[2];    //array di due oggetti di tipo A
    static A a;
public:
    B(){ar[1] = ar(7); cout << "BA";}
};

A B::a = A(9);

int main()
{
    cout << "Zero" << endl;
    A a1; cout << "Uno" << endl;
    A a2(3); cout << "Due" << endl;
    A *b = &a1; cout << "Tre" << endl;
    B b; cout << "Quattro";
}
