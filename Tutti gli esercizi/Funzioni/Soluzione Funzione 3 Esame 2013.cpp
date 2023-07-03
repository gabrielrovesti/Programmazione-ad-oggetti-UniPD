#include <iostream>
#include <list>
#include <vector>
using namespace std;

class QWidget{
private:
	int hDefault;
public:
	virtual int heightForWidth(int z) const { return hDefault * z; }
};

class QFrame : public QWidget{
private:
	int largCornice;
public:
	void setLineWidth(int z) { largCornice = z; }
};

class QLabel : public QFrame{
private:
	bool word_wrapping;
public:
	int heightForWidth(int z) const {}
	void setWordWrap(bool b) { word_wrapping = b; }
};

class QSplitter : public QFrame {};

class QLCDNumber : public QFrame {
public:
	void setDigitCount(int z) { nCifre = z; }
private:
	int nCifre;
};

list<QFrame*>fun(vector<QWidget*>& v) {
	list<QFrame*> rit;
	for(vector<QWidget*>::iterator it = v.begin(); it != v.end(); ++it){
		QLabel* pQL = dynamic_cast<QLabel*>(*it);
		QLCDNumber* pQLCD = dynamic_cast<QLCDNumber*> (*it); 
		if(pQL){ 
			pQL->setLineWidth(9);
			pQL->setWordWrap(false);
		}
		if(pQLCD){
			pQLCD->setDigitCount(2);
		}
		QFrame* pQF = dynamic_cast<QFrame*> (*it);
		if(pQF && !dynamic_cast<QSplitter*>(pQF) && pQF->heightForWidth(8) < 16)
			rit.push_back(pQF);

	}
	return rit;
}

int main(){
}