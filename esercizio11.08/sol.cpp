#include <typeinfo>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class B {
public:
  virtual ~B() { };
};
class C : public B { };
class D : public B { };
class E : public C { };

int Fun(vector<B*>& v) {
  if (v.size() == 0)
    return 0;
  // => almeno un elemento ce lo abbiamo.  
  int contatore = 0;
  for (int i = 0; i < v.size(); i++) {
    if (dynamic_cast<C*>(v[i]) && ( typeid(*(v[i])) != typeid(*(v[0]))) ) {
      contatore+=1;  
    }
  }
  return contatore;
}

int main() {

  vector<B*> u, v, w;
  cout << Fun(u) << endl;

  B b; C c; D d; E e; B *p = &e, *q = &c;
  v.push_back(&c); v.push_back(&b); v.push_back(&d);
  v.push_back(&c); v.push_back(&e); v.push_back(p);
  cout << Fun(v) << endl;

  w.push_back(p); w.push_back(&d); w.push_back(q);
  w.push_back(&e);
  cout << Fun(w) << endl;

}
