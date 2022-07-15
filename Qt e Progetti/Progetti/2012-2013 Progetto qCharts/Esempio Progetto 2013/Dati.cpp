#ifndef DATI_H
#define DATI_H

class Dati { // dati numerici interi generati casualmente
private:
  int size_;
  int* dati;
public:
  Dati(int n): size_(n), dati(new int[n]) {
    for(int i=0; i<size_; ++i) dati[i]= rand()%100; // [0,99]
  }
  int& operator[](int k) const {return dati[k];}
  int size() const {return size_;}
  ~Dati() {delete[] dati;}
};
#endif
