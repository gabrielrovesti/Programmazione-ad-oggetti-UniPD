#include <iostream>
#include <typeinfo>
#include <fstream>
#include <vector>

using namespace std;

class Log{
    private:
    string applicazione;
    string messaggio;
    public:
    Log(string a="", string m=""): applicazione(a), messaggio(m) {}
    virtual ~Log()=default;
    string getApplicazione() const{return applicazione;};
    string getMessaggio() const{return messaggio;};
    virtual Log* clone() const=0;
    virtual string toString() const=0;
    virtual bool operator==(const Log& l) const{
        return typeid(*this) == typeid(l) && applicazione == l.applicazione && messaggio == l.messaggio;
    }
};

class DebugLog: public Log{
    private:
    int lineNum;
    public:
    int getLineNum() const{return lineNum;}
    Log* clone() const{return new DebugLog(*this);}
    string toString() const{
        return "App: " + getApplicazione() + "\n Messaggio: " + getMessaggio()
        + "\n Linea: " + to_string(lineNum);
    }
    virtual bool operator==(const Log& l){
        return Log::operator==(l) && lineNum==static_cast<const DebugLog&>(l).lineNum;
    }
};

class AppLog: public Log{
    private:
    int criticita;
    public:
    int getCriticita() const{return criticita;}
    Log* clone() const{return new AppLog(*this);}
    virtual bool operator==(const Log& l){
        return Log::operator==(l) && criticita==static_cast<const AppLog&>(l).criticita;
    }
    string toString() const{
        return "App: " + getApplicazione() + "\n Messaggio: " + getMessaggio()
        + "\n Criticità: " + to_string(criticita);
    }
};

class LogManager{
    private:
    class Nodo{
        public:
        Log* info;
        Nodo* next;
    };  
    Nodo* first;
    class IteratoreApp{
        public:
        Nodo* it;
        IteratoreApp& operator++(){
            while(it){
                it=it->next;
                if(dynamic_cast<AppLog*>(it->info)) return *this;
                return *this;
            }
        }
        bool operator==(const IteratoreApp& i) const{
            if(this == &i){
                if(it->info == i.it->info){
                    return true;
                }
                return false;
            }
        }
        Log* operator*() const{return it->info;}
        };
        class IteratoreDebug{
        public:
        Nodo* it;
        IteratoreDebug& operator++(){
            while(it){
                it=it->next;
                if(dynamic_cast<DebugLog*>(it->info)) return *this;
                return *this;
            }
        }
        bool operator==(const IteratoreDebug& i) const{
            if(this == &i){
                if(it->info == i.it->info){
                    return true;
                }
                return false;
            }
        }
        Log* operator*() const{return it->info;}
        };
    public:
    IteratoreApp beginApp(){
        IteratoreApp ia;
        ia.it=first;
        if(!dynamic_cast<AppLog*>(first->info)) ++ia;
        return ia;
    }
    IteratoreApp endApp(){
        IteratoreApp ia;
        ia.it=0;
        return ia;
    }
    IteratoreDebug beginDebug(){
        IteratoreDebug id;
        id.it=first;
        if(!dynamic_cast<DebugLog*>(first->info)) ++id;
        return id;
    }
    IteratoreDebug endDebug(){
        IteratoreDebug id;
        id.it=0;
        return id;
    }
    vector<Log*>messaggi(){
        vector<Log*> v;
        Nodo* aux=first;
        while(aux->next){
            v.push_back(aux->info->clone());
            aux=aux->next;
        }
        return v;
    }
    void save(){
        ofstream file("messages.txt");
        if(!first) return;
        Nodo* aux=first;
        while(aux){
            if(dynamic_cast<AppLog*>(aux->info)){
                file << "App: " << aux->info->getApplicazione() << "\n Messaggio: " << aux->info->getMessaggio();
            }
            if(dynamic_cast<DebugLog*>(aux->info)){
                file << "App: " + aux->info->getApplicazione() << "\n Messaggio: " << aux->info->getMessaggio()
                << "\n Linea: " + to_string(dynamic_cast<DebugLog*>(aux->info)->getLineNum());
            }
            aux=aux->next;
        }
    }
};

int main(){

}