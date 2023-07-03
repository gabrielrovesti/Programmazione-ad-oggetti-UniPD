#include<ios>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
class D: public ios {
	
};

int F(ios& ref){
		if(dynamic_cast<istream*>(&ref) && !(dynamic_cast<ostream*>(&ref)))
			return -1; //TD(ref) =istream && TD(ref) != ostream -> TD(ref) non è una classe di solo input
		if(!(dynamic_cast<istream*>(&ref)) && (dynamic_cast<ostream*>(&ref)))
			return 1; //TD(ref) !=istream && TD(ref) = ostream -> TD(ref) non è una classe di solo output
		if(dynamic_cast<istream*>(&ref) && (dynamic_cast<ostream*>(&ref)))
			return 0; //TD(ref) =istream && TD(ref) = ostream -> TD(ref) è una classe di  input/output
		return 9;
	}
	
main(){
	istream & b = cin;
	ostream& c = cout;
	stringstream d;
	ifstream e("pippo");
	ofstream f("pluto");
	D g;
	
	cout << F(b) << ' ' << F(c) << ' ' << F(d) << ' ' << F(e) 
	<< ' ' << F(f) << ' ' << F(g) << endl;
	
	//stampa -1 1 0 -1 1 9
	
	//queste tre righe servono solo per tenere aperto il terminale in windows
	cin.clear();
	cin.ignore(255, '\n');
	cin.get();
}