int main() {
    
    C c; D d; E e; A& a1 = c; B& b1 = d; B& b2 = e; D& d1 = e; D*pd = dynamic_cast<E*>(&b2);
    
    Fun(c); cout << endl;
    Fun(d); cout << endl;
    Fun(e); cout << endl;
    Fun(a1); cout << endl;
    Fun(b1); cout << endl;
    Fun(d1); cout << endl;
    Fun(*pd); cout << endl;
    Fun<D>(*pd); cout << endl;
    Fun<D>(e); cout << endl;
    // Fun<E>(*pd); cout << endl; --> NON COMPILA
    Fun<E>(e); cout << endl;
    // Fun<E>(d1); cout << endl; --> NON COMPILA
    Fun<A>(c); cout << endl;     
    
    /*
    C 
    B D::f 
    E E::f 
    A 
    B B::f 
    B D::f 
    B D::f 
    B D::f 
    B D::f 
    E E::f 
    A 
    */
}