#include <iostream>
#include <vector>

using namespace std;
vector<QAbstractButton*> fun(list<QWidget*>&q, const QSize& sz, vector <const QWidget*>& v){
   vector<QAbstractButton*> v;
   list<QWidget*>::iterator it = q.begin();

   for(; it!=v.end(); ++it){
       if(*it && (*it)->sizeHint() == size) q.push_front((*it)->clone());
       QAbstractSlider *s=dynamic_cast<QWidget*>(*it);
       if((*it) && !s && (*it)->sizeHint() == s){
            delete *it; 
            it = lista.erase(it);
       }
       if((*it) && dynamic_cast<QCheckBox*>(*it) || dynamic_cast<QPushButton*>(*it)){
           v.push_back(static_cast<QAbstractButton*>(*it));
           it=lista.erase(it);
       }
   }
   return v;
}
