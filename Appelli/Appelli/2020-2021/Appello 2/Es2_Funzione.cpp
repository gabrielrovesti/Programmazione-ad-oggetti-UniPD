#include <iostream>
#include <vector>
#include <list>

class QWidget{
    public:
        virtual ~QWidget();
};

class QLabel{
    public:
        void setLineWidth(int);
        void setWordWrap(bool);
};

class QLCDNumber{
    public:
        void setDigitCount(int);
};

class QFrame{
    public:
        int heightDefault();
};

class QSplitter : public QFrame{
    public:
        QSplitter();
};

using namespace std;

list<QFrame*> fun(vector<QWidget*>& v){
    list<QFrame*> ret;
    for(vector<QWidget*>::iterator it=v.begin(); it!=v.end(); it++){
        QLabel* l = dynamic_cast<QLabel*>(*it);
        if(l){
            l->setLineWidth(8);
            l->setWordWrap(false);
        }
        QLCDNumber* n = dynamic_cast<QLCDNumber*>(*it);
        if(n){
            n->setDigitCount(3);
        }
        QFrame* f = dynamic_cast<QFrame*>(*it);
        if(f && !dynamic_cast<QSplitter*>(f) && f->heightDefault()<10) 
            ret.push_back(f);
    }
    return ret;
}