#include <iostream>

#ifndef QUEUE_H
#define QUEUE_H 

template <class T>
class Queue{
    private:
    class QueueItem{
    friend class Queue<T>;
    private:
    T info;
    QueueItem* next;
    QueueItem (const T& value): info(value), next(0) {}
    };
    private:
    QueueItem* primo;
    QueueItem* ultimo;
    public:
    Queue(const Queue&);
    ~Queue();
    void add(const T&);
    T remove();
    bool empty() const;
    Queue(): primo(0), ultimo(0){}

    Queue& operator=(const Queue& q){
        if(this!=&q){
            if(empty()){
                primo=q.primo=ultimo=q.ultimo;
            }
            else{
                primo=q.primo->next;
            }
        }
        return *this;
    }

    static QueueItem* copia(QueueItem*);
	static void distruggi(QueueItem*);
};


template <class T>
typename Queue<T>::QueueItem* Queue<T>::copia(QueueItem* p){
	if(!p)  return 0;
	return new QueueItem(p->info,copia(p->next));
}

template<class T>
void Queue<T>::distruggi(QueueItem *p){
    if(p){
        distruggi(p->next);
        delete p;
    }
}

template <class T>
Queue<T>::Queue(const Queue& t): primo(copia(t.primo)),ultimo(t.ultimo){}

template <class T>
bool Queue<T>::empty() const {
    if(primo==ultimo==0)    return true;
    else return false;
}

template<class T>
void Queue<T>::add(const T& val){
    QueueItem* p=new QueueItem(val);
    if(!empty()){
        ultimo->next=p;
        ultimo=p;
    }
    else{
        primo=ultimo=p;
    }
}

template<class T>
T Queue<T>::remove(){
    if(empty()){
    std::cerr<<"Lista vuota"<<std::endl;
    exit(1);
    }
    QueueItem* q=primo;
    primo=primo->next;
    T aux=q->info;
    delete q;
    return aux;
}

template<class T>
Queue<T>::~Queue(){
    while(!empty()) remove();
}

template <class T>
std::ostream& operator<< (std::ostream& os, const Queue<T>& p){
    typename Queue<T>::QueueItem *t=p.primo;
    
    while(t->next !=nullptr);
    os << *t << std::endl;

    return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const typename Queue<T>::QueueItem& q){
	os<<q.info;
	return os;

}

#endif