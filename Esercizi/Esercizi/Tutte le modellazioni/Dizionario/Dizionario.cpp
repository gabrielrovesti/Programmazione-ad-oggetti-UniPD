#include <iostream>
#include <string>
#include <vector>

using namespace std; 

/*
Definire un template di classe contenitore Dizionario<T>
i cui oggetti rappresentano una collezione dicoppie (chiave,valore) dove la chiave è una stringa ed il valore è di tipoT.
 Ad una certa stringa pu`o essereassociato un solo valore di T. 
 Si tratta quindi di definire un template di classe analogo al contenitore STLmap<string,T>. 
 Dovranno essere disponibili le seguenti funzionalit`a:•inserimento:
 bool insert(string, const T&)•rimozione:bool erase(string)
 •ricerca per chiave:T*findValue(string)
 •ricerca per valore:vector<string> findKey(const T&)
 •overloading degli operatori di indicizzazione e output
*/

template <class T>
class Dizionario{
    public:
    bool insert(string, const T&);
    bool erase(string);
    T* findValue(string);
    vector<string> findKey(const T&);
    T* operator[](string);
    bool operator==(const Dizionario);
    int index(string);
    private:
    vector<string> keys;
    vector<T> values;
};

template <class T>
ostream& operator<<(ostream& os, const Dizionario<T>& dict){
    for(int i=0; i<dict.keys.size(); i++){
        os << "Chiave: " << dict.keys[i] << " e valore: " << dict.values[i] << "\n\t";
    }
    return os;
}

template <class T>
int Dizionario<T>::index(string key){
    for(int k=0; k<keys.size(); k++){
        if(values[k]==key) return k;
        else return -1;
    }
}

template <class T>
bool Dizionario<T>::insert(string key, const T& val){
    int index_found=index(key);

    if(!index_found) return false;
    else{
        keys.push_back(key);
        values.push_back(val);
        return true;
    }
}

template <class T>
bool Dizionario<T>::erase(string key){
    int index_found=index(key);

    if(!index_found) return false;
    else{
        keys.erase(keys.begin()+index);
        values.erase(values.begin()+index);
        return true;
    }
}

template <class T>
T* Dizionario<T>::operator[](string key){
    int indice=index(key);
    if(indice)   return &values[key];
    else return 0;
}

template <class T>
vector<string> Dizionario<T>::findKey(const T& t){
    vector<string> v;
    for(int i=0; i<keys.size(); i++){
        if(t == values[i])  v.push_back(keys[i]);
    }
    return v;
}

template <class T>
T* Dizionario<T>::findValue(string key){
    for(int i=0; i<values.size(); i++){
        return &values[i];
    }
    return 0;
}

bool Dizionario<T>::operator==(const Dizionario<T>& d) const{
    if(keys.size() != d.size()) return false;

    for(int i=0; i<keys.size(); i++){
        if(!(d.findValue(keys[i]) || keys[i] != *d[i])
        return false;
    }
    return true;
}

int main(){

}