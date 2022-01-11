#include <iostream>
using namespace std;

template <class T, int size> class C;

template <class T, int size>
class C{
    private:
    class MultiInfo{
        friend class C;
        MultiInfo* array;
        int molt_n=0;
    };
    T informazione;

    public:
    C(const T& t=T(), int k=10): MultiInfo::array(new MultiInfo[size](t,k)) {}
    
    C(const C& c): MultiInfo::array(new MultiInfo[size]) {
        MultiInfo *p;
        for(int i=0; i<size; ++i) MultiInfo::array[i]=p[i];
    }
    ~C() {delete[] MultiInfo::array;}
    C& operator=(const C& c){
        MultiInfo *p;
        if(this != &c){
            for(int i=0; i<size; i++)   MultiInfo::array[i]=p[i];
        }
    }
    T& operator=(int j) const{
        if(j >= 0 && j < size)  return MultiInfo::array[j].informazione;
        return 0;
    }
    int occorrenze(const T&){
        int sum=0;
        for(int i=0; i<size; i++) sum+=MultiInfo::array[i].molt_n;
        return sum;
    }
};

template <class T, int size>
ostream& operator<<(ostream& os, const C<T,size>& c){
    for(int i=0; i<size; ++i) os << "Valore dell'array: " <<c.array[i]<< "Moltepliicità: "<<c.array[i].molt_n<< endl;
    return os;
}
