/* dizionario <T>
 string->valore
 defining:
  bool insert (string, const& T) MAP <string, T>
  T* findvalue (string)
  vector <string> findkey (const T&)
 operator [] e operator <<
 */


#include <iostream>
using namespace std;

template <class T>
	class dizionario;

template <typename T>
ostream& operator<< (ostream& os, const dizionario <T> &d); 

class dizionario {
	friend ostream& operator<< <T> (ostream& os, const dizionario <T> &d); 
	
public:
	bool insert (string, const& T);
	
	void print (ostream& os, const dizionario <T> d)
	{
		d.print(os);
		return (os);
	}
	
	bool ERASE (const string& S);
	
	
	
	
private:
	vector<string>; //chiavi
	vector<T>; //valori
	int indice (string);

};

//--------------------

template <class T>
bool dizionario <T>::insert (string k, const T& t)
{
	int idx=indice (k);
	if (idx==-1) return false;
	chiavi.push_back (k);
	valori.push_back (k);
	return false;
}


template <class T>
T * dizionario <T>::operator[] (const string& s)
{
	int idx= indice (s);
	if (S==-1) return 0; //dovrebbe esserci idx al posto di s
	return &valori [idx];
}

template <class T>
bool dizionario <T>::ERASE (const string s)
{
	int idx=indice (s);
	if (idx==-1) return false;
	chiavi.erase (chiavi.begin()+idx);
	valori.erase (valori.begin()+idx);
	return true;
}



int main () 
{
}
