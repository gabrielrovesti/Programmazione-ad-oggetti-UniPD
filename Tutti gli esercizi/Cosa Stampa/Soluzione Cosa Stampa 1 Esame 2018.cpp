p1->g();   cout << endl;// 1 ............................  B::g
p1->k();   cout << endl;// 2 ............................  B::k  A::n 
p2->f();    cout << endl;// 3............................. A::f  B::g  A::j
p2->m();    cout << endl;// 4 ......................... .  A::m  B::g  A::j
p3->k();   cout << endl;// 5 ............................ A::k  C::j  A::m  A::g  C::j
p3->f();   cout << endl;// 6 ...........................  A::f  A::g  C::j 
p4->m();   cout << endl;// 7 ...........................  D::m  B::g  D::j
p4->k();   cout << endl;// 8 ...........................  B::k  A::n
p5->g();   cout << endl;// 9 ............................ A::g 
(p3->n())->m();   cout << endl;// 10 .................... A::n  A::m  A::g  C::j 
(p3->n())->n()->g();   cout << endl;// 11 ............... A::n  A::n  A::g 
(p4->n())->m();    cout << endl;// 12 ..................  D::n  A::m  B::g  D::j
//(p5->n())->g();  cout << endl;  // 13  ...............   non compila (dovuto al const su this)
(dynamic_cast<B*>(p1))->m(); // 14 ..................    D::m  B::g  D::j 
//(static_cast<C*>(p2))->k(); // 15 ........................errore run time (chiamata infinita di k() in c)
(static_cast<B*>(p3->n()))->g();  //16 ..................  A::n  A::g 