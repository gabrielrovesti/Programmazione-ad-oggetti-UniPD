int main()
{
    p1->k();    //B::k A::n
    p2->f();    //A::f B::g A::r 
    p2->m();    //A::m B::g A::r 
    p3->k();    //A::r  A::k  C::r  A::m  A::g  C::r 
    p3->f();    //A::f  A::g  C::r 
    p5->g();    //A::g
    (p3->n())->m(); // A::n  A::m  A::g  C::r 
    (p3->n())->n()->g();    // A::n  A::n  A::g 
    (p4->n())->m(); // D::n  A::m  B::g  D::r 
    (p5->n())->g(); //Non compila
    (dynamic_cast<B *>(p1))->m();   // D::m  B::g  D::r 
    (static_cast<C *>(p2))->k();    //C::k all'infinito
}