#include <iostream>


using std::cout;


class Z {
public:
  Z() { cout << "Z() "; }
  Z(const Z& x) { cout << "Zc "; }
};

class A {
private:
  Z w;
public:
  A() { cout << "A() "; }
  A(const A& x) { cout << "Ac "; }
};

class B : virtual public A {
private:
  Z z;
public:
  B() { cout << "B() "; }
  B(const B& x) { cout << "Bc "; }
};

class C : virtual public A {
private:
  Z z;
public:
  C() { cout << "C() "; }
};

class D: public B, public C {
public:
  D() { cout << "D() "; }
  D(const D& x) : C(x) { cout << "Dc "; }
}; 

int main() {
  B b1; C c1; cout << "**0\n";
  B b2 = b1; cout << "**1\n";
  C c2 = c1; cout << "**2\n";
  D d1; cout << "**3\n"; // algoritmo della costruzione di un oggetto di un timpo T che chiude un diamante di una gerarchia di classi con derivazione multipla.
  D d2 = d1; cout << "**4\n";
}
