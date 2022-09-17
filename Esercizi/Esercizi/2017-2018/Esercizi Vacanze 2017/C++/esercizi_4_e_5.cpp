// esercizio 4
Button** Fun(const Container& c) {
  std::vector<Component*> v = c.getComponents();
  std::list<Button*> acc;
  for(int i=0; i<v.size(); ++i) { 
    Button* p = dynamic_cast<Button*>(v[i]);
    if(p) {
      MenuItem* q = dynamic_cast<MenuItem*>(p);
      if(q && (p->getContainers()).size()>1) q->setEnabled(false); 
      acc.push_back(p);
    }
  }
  if(acc.size() == 0) return nullptr;
  Button** a = new Button*[acc.size()];
  auto it = acc.begin();
  for(int i=0 ; it != acc.end(); ++it,++i) a[i]=*it;
  return a;
}

// esercizio 5
template <class T1, class T2>
bool Fun(T1* p, T2& r) {
  return 
    typeid(T1)==typeid(T2) &&
    typeid(*p)==typeid(r) &&
    dynamic_cast<ios*>(p);
}