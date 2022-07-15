// ESERCIZIO 1 DEL COMPITO D'ESAME DEL 18/2/2016

vector<QAbstractButton*> fun(list<QWidget*>& l, const QSize& s) {
  list<QWidget*>::iterator it = l.begin();
  vector<QAbstractButton*> v;
  while(it != l.end()) {
    if(*it && (*it)->sizeHint() == s) l.push_front((*it)->clone());
    QAbstractSlider* p = dynamic_cast<QAbstractSlider*>(*it);
    if(*it && !p && (*it)->sizeHint() == s) {delete *it; it=l.erase(it);}
    else 
      if(dynamic_cast<QCheckBox*>(*it) || dynamic_cast<QPushButton*>(*it)) {
	    v.push_back(static_cast<QAbstractButton*>(*it)); 
	    it=l.erase(it);
      }
      else ++it;
  }
  return v;
}