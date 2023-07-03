#include <iostream>
using std::cout;
class Empty {}; //classe da lanciare quando ho un eccezione


template <class T = int>  //no condivisione memoria
class Stack {
private:
    class StackItem {
    friend class Stack<T>;
    private:
        T info;
        StackItem* next;
        StackItem(T i, StackItem* n): info(i), next(n) {}
    };
    StackItem *first;
public:
    Stack() : first(0) {}

    /*uno Stack con k copie di t*/
    Stack(int k, const T& t) {
        for (int i = 0; i < k; i++) {
            push(t);
        }
    }

    /*true se Stack vuoto, false altrimenti*/
    bool isEmpty() const {
        return !(first);
    }
    void push(const T& t) {
        first = new StackItem(t, first);
    }

    T* top() {
        if (!isEmpty()) {
            T risultato = (*this).info;
            return &risultato;
        }
        return 0;
    }

    T pop() {
        if (!isEmpty()) {
            T *temp = first;
            first = first->next;
            T risultato = temp->info;
            delete temp;
            return risultato;
        }
        throw Empty();
    }

    class Iterator {
    friend class Stack;
    private:
        StackItem* punt;
    public:
        bool operator==(Iterator i) const {
            return (punt == i.punt);
        }

        bool operator!=(Iterator i) const {
            return !(punt == i.punt);
        }

        Iterator operator++() { //prefisso
            if (punt) {
                punt = punt->next;
            }
            return *this;
        }

        T& operator*() {
            return punt->info;
        }
    };

    Iterator begin() const {
        Iterator aux;
        aux.punt = first;
        return aux;
    }

    Iterator end() const {
        Iterator aux;
        aux.punt = 0;
        return aux;
    }

    T operator[](Iterator i) {
        return (i.punt)->info;

    }

    friend std::ostream& operator<<(std::ostream& os, const Stack& s) {
        for (Stack<T>::Iterator i = s.begin(); i != s.end(); ++i) {
            os<<*i<<" ";
        }
        return os;
    }
};


main() {
    Stack<int> ver1;
    for (int i = 0; i < 10; i++) {
        ver1.push(i);
    }
    cout<<ver1;
}