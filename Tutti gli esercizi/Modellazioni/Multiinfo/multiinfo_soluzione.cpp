#include <iostream>
using namespace std;

template <class T, int size> class C;
template <class T, int size> ostream& operator<<(ostream& os, const C<T, size>& c);

template <class T, int size> /* PUNTO 1) Per renderlo annidato e associato dobbiamo usare lo stesso parametro di tipo, che è nella la stessa classe */
class C {
    friend ostream& operator<< <T, size> (ostream& os, const C<T, size>& c);
    class MultiInfo {
        friend ostream& operator<< <T, size> (ostream& os, const C<T, size>& c);
        friend class C<T, size>; //questo permette di accedere direttamente a MultiInfo[i]
        T informazione;
        int molteplicita;
    };
    private:
        MultiInfo m[size];
        void copy(const C&other) {
            for (int i=0; i<size; i++) {
                m[i].informazione = other.m[i].informazione;
                m[i].molteplicita = other.m[i].molteplicita;
            }
        }
    public:
        C(const T& t, int k) : new MultiInfo[size] { /* PUNTO 2/3) Il costruttore prende un valore di tipo informazione per rif costante, e va a riempire con il ciclo*/
            for (int i=0; i<size; i++) { // l'array contiene in ogni posizione un oggetto multiInfo t con informazione = a e molteplicita = k
                m[i].informazione = t;
                m[i].molteplicita = k > 0 ? k : 0;
            }
        }

        /*
        Altri modi di fare il costruttore:

        C(const T& t, int k){
            for (int i=0; i<size; i++) {
                m[i] = MultiInfo{t, k > 0 ? k : 0};
            }
        }

        C(const T& t, int k) : new MultiInfo[size] { MultiInfo{t, k > 0 ? k : 0} } {}
        
        */

        virtual ~C() {
            delete[] m;
        }

        C (const C& other) : m(new MultiInfo[size]) {
            copy(other); // } PUNTO 4) creo copia profonda, poi creo un array diverso da quello esistente
        }

        T* operator[] (int ind) {
            if(ind<0 || ind >= size) return nullptr;
            return &m[ind]; // PUNTO 5)
        }

        int occorrenze(const T& t) {
            int sum = 0;
            for(int i = 0; i < size; i++) {
                if(m[i].informazione == t) {
                    sum += m[i].molteplicita;
                }
            }
            return sum;
        } // PUNTO 6) contiamo tutte le occ. con il ciclo e le ritorniamo
};

template <class T, int size> ostream& operator<<(ostream& os, const C<T, size>& c) {
    for(int i = 0; i < size; i++) {
        os << c.m[i].informazione << " " << c.m[i].molteplicita << endl;
    }
    return os;
}

int main() {
    //Esempio di main che usa tutti gli elementi

    C<int, 5> c(3, 2);
    cout << c << endl;
    cout << c.occorrenze(3) << endl;

    C<int, 5> c2(c);
    cout << c2 << endl;
    cout << c2.occorrenze(3) << endl;

}