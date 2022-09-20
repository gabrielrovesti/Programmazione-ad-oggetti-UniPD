#include <iostream>

class Vettore{
    private:
    int* a;
    unsigned int size;
    //vettore vuoto If=a==nullptr && size==0
    //vettore non vuoto If a!=nullptr && size > 0

    public:
  Vettore(unsigned int dim =0, int init =0):
    a(dim == 0 ? nullptr : new int[dim]), size(dim) {
    for(unsigned int j=0; j<dim; ++j) a[j]=init;
  }
  
  Vettore& operator=(const Vettore& v) {
    if(this != &v) {
      delete[] a;
      size = v.size;
      a = size == 0 ? nullptr : new int[size];
      for(unsigned int j=0; j<size; ++j) a[j] = v.a[j];
    }
    return *this;
  }

  Vettore(const Vettore& v):
    a(v.size == 0 ? nullptr : new int[v.size]),
    size(v.size) {
    for(unsigned int j=0; j<size; ++j) a[j] = v.a[j];
  }

    ~Vettore(){delete[] a;}

    bool operator==(const Vettore& v) const {
        if(this == &v) return true; 
        if(size != v.size) return false;
        for(unsigned int j=0; j<size; ++j)
        if(a[j] != v.a[j]) return false;
        return true;
    }

      Vettore& append(const Vettore& v) {
        if(v.size!=0){
        int* p = new int[size+v.size];
        unsigned int j=0;
        for(; j<size; ++j) p[j]=a[j];
        for( ;j<size+v.size; ++j) p[j] = v.a[j-size];
        delete[] a; // FONDAMENTALE
        a=p;
        size+=v.size;
        }
        return *this;  
    }

    //ritorna int& perché è un riferimento anche per operare in scrittura se possibile
    int& operator[](unsigned int j) const{
        return *(a+j);
    }   

    //di fatto viene messo così perché è un campo privato, accessibile in due modi:
    //o dichiaro la classe come friend di vettore, in questo caso lo std,
    //oppure uso un metodo che mi permetta di accedere al campo interessato. 
    unsigned int getsize() const{return size;}

    Vettore operator+(const Vettore& v) const{
    Vettore aux(*this);
    aux.append(v);
    return aux;
    }
};

std::ostream& operator<<(std::ostream& os, const Vettore &v){
    for(unsigned int j=0; j<v.getsize(); ++j)
    {
        os << v[j] << ' ';
    } 
    return os;
}

int main(){
    Vettore v1(4), v2(3, 2), v3(5, -3);
    v1=v2+v3;
    v2.append(v2);
    v3.append(v1).append(v3);
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
}