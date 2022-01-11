/*
Definire un template di classe stack<T, num> i cui oggetti rappresentano uno stack di valori di
di un generico tipo T con al massimo num elementi.
Si ricorda che lo stack implementa la politica di inserimento/rimozione LIFO: Last In First Out.
Lo stack si dice pieno quando memorizza num elementi.
Il template stack<T, num> deve soddisfare i seguenti vincoli e rendere disponibili le seguenti funzionalità:

1)stack<T, num> non può usare i contenitori STL come campi dati (inclusi puntatore e riferimenti a contenitori STL).

2)Il template stack<T, num> ha come tipo T default char e come valore num default 100.

3)Un costruttore di default che costruisce lo stack vuoto

4)Un costruttore stack(t,k) che costruisce uno stack di c elementi che memorizzano il valore t; se k > num allora lo stack sarò di num elementi, se k < 0 allora lo stack sarà vuoto.

5)Metodi bool isEmpty() e bool isFull() che testano se lo stack è vuoto o pieno.

6)Metodo unsigned int size() che ritorna il numero di elementi memorizzati dallo stack.

7)Gestione della memoria senza condivisione.

8)Operatore esplicito di conversione ad int che ritorna la dimensione dello stack.

9)Metodo bool push(const T&): in una chiamata s.push(t), inserisce al top dello stack s un nuovo elemento che memorizza il valore t se ciò non provoca il superamento del limite num, altrimenti lascia lo stack s invariato.
Ritorna true se l'inserimento è avvenuto, false altrimenti.

10)Metodo void pop(): in una chiamata s.pop() rimuove l'elemento al top
dello stack s non vuoto; se s è vuoto lo lascia inalterato.

11)Metodo T pop():s.top() ritorna una copia dell'elemento al top dello stack
s non vuoto; se s è vuoto, allora s.top() provoca undefined behaviour (da definirsi opportunamente).

12)Metodo T bottom(): s.bottom() ritorna una copia dell'elemento al bottom dello stack s non vuoto; se s è vuoto, allora s.bottom provoca undefined behaviour (da definirsi opportunamente)

13)Metodo bool search(const T&): un una chiamata s.search(t) ritorna true se il valore t occorre nello stack s, altrimenti ritorna false

14)Metodo void flush() che svuota lo stack di invocazione.

15)Overloading dell'operatore di somma tra stack: s1+s2 deve ritornare un nuovo stack ottenuto impilando s2 sopra s1(il bottom di s2 è quiindi sopra il top s1) 
sino all'eventuale raggiungimento del massimo num di elementi.

16)Overloading dell'operatore di uguaglianza.

17)Overloading dell'operatore di output
*/

#include <iostream>

using namespace std;
class EmptyStackException{
    private:
    int e;
    EmptyStackException(int e){cout << "Eccezione: "<< e;}
};

template <class T=char, int num=100>
class stack{
    friend EmptyStackException;
    private:
        T* elem;
        int cont;
    public:
    stack(): elem(new T[num]), cont(0) {}
    stack(const T&t, int n): elem(new T[num]){
        if(n > num)     n=num;
        else if(n<0)    n=0;
        for(int i=0; i<cont; i++){
            elem[i]=t;
        }
    }
    bool isEmpty() const{
        if(cont==0) return true;
        return false;
    }
    bool isFull() const{
        if(cont==num) return true;
        return false;
    }
    unsigned int size() const{
        return cont;
    }
    bool push(const T& t){
        if(cont < num){
            elem[0]=t;
            size++;
        }
        else return false;
    }
    bool search(const T& t){
        bool found=false;
        for(int i=0; i<cont && !found; i++){
            if(elem[i] == t)    found=true;
        }
        return found;
    }
    void pop(){
        if(isEmpty())   throw EmptyStackException();
        else elem[--size];
    }
    void flush(){
        delete [] elem;
    }
    T bottom(){
        if(isEmpty())   throw EmptyStackException();
        else return elem[cont];
    }
    T t_pop(){
        if(isEmpty())   throw EmptyStackException();
        else return elem[0];
    }
    operator int() const{
        return cont;
    }
    stack& operator+(stack& s){
        stack sum;
        while(!sum.isEmpty()){
            sum += s.pop();
            sum.pop();
        } 
    }
    stack& operator=(const stack& s){
        if(this != &s){
            this=s.cont;
            for(int i=0; i<cont; i++){
                elem[i]=s.elem[i];
            }
        }
    }
    ostream& operator<<(ostream& os){
        stack s;
        for(int i=0; i<cont; i++){
            os << "Elemento: " << s[i];
        }
        return os;
    }
};

int main(){

}
