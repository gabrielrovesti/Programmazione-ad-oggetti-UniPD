/*
Nota: il codice è stato modificato rispetto a quello fornito, 
in quanto dava errori di esecuzione.

Le principali correzioni effettuate sono state:

Nel costruttore di Smart e nel suo copy constructor, ho controllato se p era valido prima di incrementare il contatore.
Nella definizione di N, ho modificato il tipo di next da Smart& a N*.
Nel costruttore di C, ho passato nullptr come valore di default per `next

*/

#include <iostream>
using namespace std;

class N {
public:
    string s;
    int counter;
    N* next; // correggo qui, N* invece di Smart& per evitare conflitti
    N(string x, N* y = nullptr) : s(x), counter(0), next(y) {
        cout << "N()";
    }
    ~N() {
        cout << "~N ";
    }
};

class Smart {
public:
    N* p;
    Smart(N* q = nullptr) : p(q) {
        if (p) p->counter++; // incrementa il contatore solo se N è valido
        cout << "Smart() ";
    }
    Smart(const Smart& x) : p(x.p) {
        if (p) p->counter++; // incrementa il contatore solo se N è valido
        cout << "SmartCopy() ";
    }
    ~Smart() {
        if (p) {
            p->counter--;
            if (p->counter == 0) delete p;
        }
        cout << "~Smart() ";
    };
    operator bool() { return p != nullptr; }
    Smart& operator=(const Smart& x) {
        Smart t = *this;
        p = x.p;
        if (p) p->counter++; // incrementa il contatore solo se N è valido
        cout << "Smart=";
        return *this;
    }
    N* operator->() { return p; }
    bool operator==(const Smart& x) { return p == x.p; }
    bool operator==(N* x) { return p == x; }
};

class C {
public:
    Smart punt;
    C(string s = "BIANCO") : punt(new N(s)) {}
    void add(string s) {
        punt = new N(s, punt.p); // punt.p per accedere direttamente all'oggetto N
    }
    void modify() {
        if (punt && punt->next) punt->next = (punt->next)->next;
    }
    void print() {
        N* temp = punt.p;
        while (temp) {
            cout << temp->s << " ";
            temp = temp->next;
        }
    }
};

int main() {
    C c1;
    cout << " **0" << endl;
    C c2("ROSSO");
    cout << " **1" << endl;
    C c3(c2);
    cout << " **2" << endl;
    c3.add("VERDE");
    cout << " **3" << endl;
    c3.add("BLU");
    cout << " **4" << endl;
    c3.modify();
    cout << " **5" << endl;
    c1 = c3;
    cout << " **6" << endl;
    c1.print();
    cout << " **7" << endl;
    c2.print();
    cout << " **8" << endl;
    c3.print();
    cout << " **9" << endl;
    return 0;
}

/*
N() Smart()  **0
N() Smart()  **1
SmartCopy()  **2
N() Smart() SmartCopy() Smart=~Smart() ~Smart()  **3
N() Smart() SmartCopy() Smart=~Smart() ~Smart()  **4
**5
SmartCopy() Smart=~Smart()  **6
BLU ROSSO  **7
ROSSO  **8
BLU ROSSO  **9
~Smart() ~Smart() ~N ~Smart()
*/
