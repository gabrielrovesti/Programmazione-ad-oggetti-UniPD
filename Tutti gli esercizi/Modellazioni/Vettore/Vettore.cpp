/*
Definire una classe Vettore i cui oggetti rappresentano
array di interi. Vettore deve includere:
un costruttore di default, 
un'operazione di concatenazione
che restituisce un nuovo vettore v1+v2, 
una operazione di append v1.append(v2), 
l'overloading dell'uguaglianza,
dell'operatore di output e dell'operatore
di indicizzazione.
Deve inoltre includere il costruttore di copia profonda,
assegnazione profonda e la distruzione profonda.
*/

// Vettore = Vector = Vogliamo sapere sia i suoi camp
// che la dimensione
#include <iostream>
using namespace std;
class Vettore{
    private:
        int *a; // lo usiamo solo per fare delle operazioni
        unsigned int size;
    public:
        // Riempiamo tutto il vettore "a" di dimensione 
        // "dim" dei valori "val"
        Vettore(unsigned int dim =0, int val =0){
            size = dim; // Un vettore di dimensione "dim"
            a = new int[size]; // un array di dimensione 
            // "size" di interi
            for(unsigned int i=0; i<size; i++)
                a[i] = val;  
        }
        // Assegnazione profonda
        Vettore& operator=(const Vettore& v){
            // Pattern:
            // diversità tra oggetto "const" e "this" (1)
            // cancellazione delle cose precedenti (2)
            // copia di tutti gli elementi (3)
            // ritornando *this (4)
            
            if(this != &v){  //(1)
                delete[] a; //(2)
                size = v.size; 
                // Se "size" = 0, "a" è nullptr
                // Se "size" > 0, "a" è un array di dimensione "size"
                a = size == 0 ? nullptr : new int[size];
                // Copiamo tutti gli elementi (3)
                for(unsigned int i=0; i<size; i++){
                    a[i] = v.a[i];
                }
            }
            return *this; //(4)
        }
        // Distruttore
        ~Vettore(){
           // Se esiste l'array "a", cancellalo tutto
           if(a) delete[] a;
        }
        /*
        Append in vector significa
        aggiungere uno o più elementi in fondo al vettore.
        Quindi:
        1) se il vettore è vuoto, allora il vettore risultante è nullo
        2) se il vettore non è vuoto, allora il vettore risultante
        è dato dalla concatenazione del vettore aux con "v",
        diminuendo la sua size (in maniera tale da scorrerlo tutto)
        oppure aumentando la size di aux rispetto ad "i" (sempre
        per scorrerlo tutto).
        Liberiamo lo heap dall'array precedente,
        lo assegniamo e poi aggiungiamo la size
        del vettore su cui si è eseguito una append.
        */
        
        // Risultato = A[10] e B[5] -> A[10] + B[5] = array[15]
        Vettore& append(const Vettore& v){
            // Prima cosa: vettore non nullo
            if(v.size !=0){
                // Creo la dimensione "somma" dell'array ausiliario
                int* aux = new int[size + v.size];
                // Copio tutti gli elementi del vettore "this" in "aux"
                for(unsigned int i=0; i<size; i++){
                    aux[i] = a[i];
                }
                // Ci prendiamo tutti gli elementi "rimanenti
                // da attaccare"
                for(unsigned int i=0; i<v.size; i++){
                    aux[i+size] = v.a[i];
                }
                // Liberiamo lo heap dall'array precedente
                delete[] a;
                // Assegniamo l'array ausiliario
                a = aux;
                // Sommiamo le size
                size += v.size;
            }
            return *this;
        }
        // Metodi get per i campi privati
        unsigned int getSize() const{
            return size;
        }
        // Costruttore di copia profonda - Fanno copie degli oggetti
        Vettore(const Vettore& v){
            size = v.size; // Copiare la size del vettore
            // Se "size" = 0, "a" è nullptr 
            // altrimenti crea un vettore di dimensione "size"
            a = size == 0 ? nullptr : new int[size];
            // Assegna elemento per elemento
            for(unsigned int i=0; i<size; i++){
                a[i] = v.a[i];
            }
        }
        // Operatore di indicizzazione - Subscripting - []
        int& operator[](unsigned int i){
            return a[i]; //return *(a+i); (con i puntatori)
            // a[i] = 5; // *(a+i) = 5; 
            // Mi sposto dal primo elemento di 5 elementi
        }
        // Operatore di somma - Concatenazione
        // Usiamo la funzione "append"
        // per sommare tutti gli elementi dei vettori
        Vettore operator+(const Vettore& v) const{
            Vettore aux(*this); // Copia profonda
            aux.append(v); // Attacchiamo tutti gli elementi
            return aux; // Ritorna il vettore
        }
        // Operatore di stampa - Output
        friend ostream& operator<<(ostream& os, const Vettore& v){
            // Stampa: [1 2 3 4 5]
            os << "[";
            for(unsigned int i=0; i<v.size; i++){
                os << v.a[i] << " ";
            }
            os << "]";
            return os;
        }
        // Operatore di uguaglianza - ==
        // Due vettori sono uguali se
        // hanno la stessa dimensione, 
        // hanno tutti gli stessi elementi
        // rispetto alla loro posizione
        bool operator==(const Vettore& v) const{
            // Se sono uguali, si ritorna indietro 
            if(this == &v) return true;
            // Se hanno dimensione diversa, ritorna false
            if(size != v.size) return false;
            // Controlliamo se tutti gli elementi sono uguali
            for(unsigned int i=0; i<size; i++){
                // Usciamo dal ciclo sse (iff)
                // abbiamo trovato un elemento diverso
                if(a[i] != v.a[i]) return false;
            }
            return true; // Prima o poi si ferma con un'uguaglianza
        }
};

int main(){
    // Solito main() che usa tutto quello
    // che abbiamo fatto
    Vettore v1(4), v2(3, 2), v3(5, -3);
    v1=v2+v3;
    v2.append(v2);
    v3.append(v1).append(v3);
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
    return 0;
}