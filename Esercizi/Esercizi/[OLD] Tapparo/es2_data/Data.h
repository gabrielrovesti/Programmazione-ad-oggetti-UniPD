/* scrivere una classe Data che rappresenti un giorno dell'anno.
-costruttori
-getter & setter
-aggiungiGiorni(int d)
-op di conversione stringa */

#ifndef DATA_H
#define DATA_H
#include <string>

using std::string;

class Data{
public:
    Data();//costruttore default
    Data(int d,int m,int y);//costruttore 3 interi
    Data sommaGiorni(int d) const;
    operator string();
    int getDay() const;
    int getMonth() const;
    int getYear() const;
private:
    int year;
    int days;
    static const int days_in_month[];
};
#endif
