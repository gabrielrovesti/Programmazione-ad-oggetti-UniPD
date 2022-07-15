#include <iostream>

class Empty{};

template <class T=int>
class Stack{
private:
    class Node{
        private:
        T info;
        Node*next;
        Node(T i, Node*n): info(i), next(n) {}
    };  
    Node* first;
public:
    Stack(): first(0){}
    void push(const T& t){
        first=new Node(t, first);
    }
    Stack(int k, const T& t){
        for(int i=0; i<k; ++i) push(t);
    }
    bool isEmpty() const{
        if(!first) return false;
        else return true;
    }
    T pop(){
        if(!isEmpty()){
            Node* t=first;
            first=first->next;
            T result=t->info;
            delete t;
            return result;
        }
        else{
            throw Empty();
        }
    }
    T* top(){
        if(!isEmpty()){
            Node* t=first;
            return t->info;
        }
        else return nullptr;
    }
    class Iterator{
        friend class Stack;
        private:
        Node* pointer;
        public:
        Iterator operator++(){
            if(pointer) pointer->next;
            return *this;
        }
        Iterator operator++(int){
            Node* temp=*this;
            temp=temp->next;
            return temp;
        }
        T& operator*(){
            return pointer->info;
        }
        T* operator->(){
            return &pointer->info;
        }
        bool operator==(Iterator i) const{
            return (pointer == i.pointer);
        }
        bool operator!=(Iterator i) const{
            return (pointer != i.pointer);
        }
    };
    Iterator begin() const{
        Iterator aux;
        aux.punt=first;
        return aux;
    }
    Iterator end() const{
        Iterator aux;
        aux.punt=0;
        return aux;
    }
    friend std::ostream& operator<<(std::ostream& os, const Stack& s){
        for(Stack<T>::Iterator it=s.begin(); it!=s.end(); ++it){
            os << *it << " ";
        }
        return os;
    }
};

int main(){

}