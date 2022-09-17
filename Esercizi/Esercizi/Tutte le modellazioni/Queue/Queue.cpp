#include "Queue.h"
#include <iostream>

using std::cout;
using std::endl;

int main(){
    Queue<int>* pi=new Queue<int>;
    int i;
    for(i=0; i<10; i++) pi->add(i);
    for(i=0; i<10; i++) cout<< "Rimozione:" << pi->remove() <<endl;
}