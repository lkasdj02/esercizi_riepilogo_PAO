#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

class A { // => A e' una classe polimorfa in quanto contiene almeno un metodo virtuale.
public:
  virtual ~A() { };
  A() { cout << "A "; }
};
class B : public A { 
public:
  B() { cout << "B "; }
}; // deriva da A => A polimorfa.
class C : virtual public B { public: C() { cout << "C "; } };
class D : virtual public B { public: D() { cout << "D "; } };
class E : public C, public D { public: E() { cout << "E "; } };

char F(A* p, C& r) {
  B* punt = dynamic_cast<B*>(p); // dato che dynamic_cast e' eseguito a run-time => (punt != nullptr) <=> TD(p) sottotipo di B* => TD(p) <= di B*
  try {
    E& s = dynamic_cast<E&>(r);
  } catch (std::bad_cast) {
    if(punt) return 'O';
    else return 'M';
  }
  if (punt) return 'R';
  return 'A';
}

int main() {
  A a; 
  B b; 
  C c; 
  D d; 
  E e;
  // cout << "A B C D E" << endl; // debug fatto per i costruttori.
  cout << endl;
  cout << /* F() << F() << F() << F()*/ " "<< endl;
  cout <<  F(&b, e) << F(&c, c) << F(&a, c) << F(&a, e) << endl;
}
