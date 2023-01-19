#include <iostream>
#include <sstream>
#include <fstream>
#include <ios>
#include <vector>

using std::cout;
using std::endl;
using std::ios;

class C {
private:
  std::vector<ios*> v;
  unsigned int k;
public:
  C(int x = 4) { 
    k = x;
    cout << "il numero massimo di elementi che il vettore puo' contenere e' : " << k << endl;
  }
  void insert(const ios& s) {
    if (v.size() < k) { 
      if (!dynamic_cast<std::fstream*>(const_cast<ios*>(&s)) && !dynamic_cast<std::stringstream*>(const_cast<ios*>(&s))) {
        v.push_back(&(const_cast<ios&>(s)));
      }
    } 
  }

  template <class T> // dato che la classe non e' templatizzata => il template di metodo viene messo all'interno della classe.
  int conta(T& t) const { // dato che il metodo e' const => this e' const.
    int conta = 0;
    for(std::vector<ios*>::const_iterator it = v.begin(); it != v.end(); it++) {
      if (dynamic_cast<T*>(*it)) {
        conta+=1;
      }
    }
    return conta;
  }
};

int main() {
  std::ifstream f("pippo");
  std::ofstream g("mandrake");
  std::fstream h("pluto");
  std::fstream i("zagor");
  std::ostream* p = &g;
  std::stringstream s;
  C c(10);

  c.insert(f);
  c.insert(g);
  c.insert(h);
  c.insert(i);
  c.insert(*p);
  c.insert(s);

  std::istream& r = f;
  cout << c.conta(r);
}
