#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Log {
private:
	string applicazione, messaggio;
public:
	Log(string a=" ", string m=" "): applicazione(a), messaggio(m) {}

	virtual Log* clone() const = 0;
	
	virtual string toString() const = 0;
	
	string getApplicazione() const { return applicazione; }
	string getMessaggio() const { return messaggio; }
	
	virtual ~Log();
	
	virtual bool uguale(Log* l) const =0;
};

class DebugLog : public Log {
private:
	int lineNum;
public:
	int getLineNum() const { return lineNum; }
	
	Log* clone() const{ return new DebugLog(*this); }
	
	string toString() const { 
		return "Applicazione : " + getApplicazione() 
		+ "\bMessaggio : " + getMessaggio() 
		+ "\blineNum : " + std::to_string(lineNum);
	}
	bool uguale(Log* l) const {
		return  dynamic_cast<DebugLog*> (l) && toString() == l->toString() ;
	}
	
};

class AppLog : public Log {
private:
	unsigned int criticita;
public:
	AppLog(string a=" ", string m=" ", int c=0): Log(a, m), criticita(c%10){}
	
	string toString() const { 
		return "Applicazione : " + getApplicazione() 
		+ "\bMessaggio : " + getMessaggio() 
		+ "\bCriticità : " + std::to_string(criticita);
	}

	Log* clone() const{ return new AppLog(*this); }
	
	bool uguale(Log* l) const {
		return  dynamic_cast<AppLog*> (l) && toString() == l->toString() ;
	}
	
};


class LogManager {
private:
	
	class Nodo{
	public:
		Log* info;
		Nodo* next;
	};
	
	Nodo* first;
	
	class iteratoreApp{
	public:
		Nodo* it;
		iteratoreApp& operator++() {
			while(it){
				it=it->next;
				if(dynamic_cast<AppLog*>(it->info)){
					return *this;
				}				
			}
			return *this; // se non lo trova ritorna 0
		}
		
		bool operator==(const iteratoreApp& i) const {return it->info->uguale(i.it->info);}
		Log* operator*() const{ return it->info;}
	};
	
	class iteratoreDebug {
	public:
		Nodo* it;
		iteratoreDebug& operator++() {
			while(it){
				it=it->next;
				if(dynamic_cast<DebugLog*>(it->info)){
					return *this;
				}				
			}
			return *this; // se non lo trova ritorna 0
		}
		
		bool operator==(const iteratoreDebug& i) const {return it->info->uguale(i.it->info);}
		
		Log* operator*() const{ return it->info; }
	};
	
public:
	iteratoreApp endApp() const{
		iteratoreApp ia;
		ia.it = 0;
		return ia;
	}
	
	iteratoreApp beginApp() const{
		iteratoreApp temp;
		temp.it = first;
		if (!dynamic_cast<AppLog*> (first->info)) {
			++temp;
		}
		return temp;
	}
	
	iteratoreDebug endBug() const{
		iteratoreDebug ide;
		ide.it = 0;
		return ide;
		
	}
	
	iteratoreDebug beginBug() const{
		iteratoreDebug temp;
		temp.it = first;
		if (!dynamic_cast<DebugLog*> (first->info)) {
			++temp;
		}
		return temp;
		
	}
	
	vector<Log*> messaggi() const{
		vector<Log*> rit;
		Nodo* temp = first;
		while (temp->next) {
			rit.push_back(temp->info->clone());
            temp=temp->next;
		} 
		return rit;
	}
};

int main(){

}


