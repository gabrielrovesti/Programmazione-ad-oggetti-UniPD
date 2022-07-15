#ifndef VALORI_H
#define VALORI_H

#include "Dati.cpp"

class Valori { // dati normalizzati
private:
  int size_;
  int* v;
  int max_;
public:
  Valori(const Dati& d, int m): size_(d.size()), v(new int[size_]), max_(m) {
    int max=d[0]; 
    for(int i=1;i<size_;i++) if(max<d[i]) max = d[i];
    for(int i=0;i<size_;i++) v[i] = max_*d[i]/max;
  }
  int& operator[](int k) const {return v[k];}
  int max() const {return max_;}
  int size() const {return size_;}
  ~Valori() {delete[] v;}
};
#endif
