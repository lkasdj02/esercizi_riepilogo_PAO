#include <iostream>

using std::string;

class Albero;

class Nodo {
  friend class Albero;
private:
  Nodo(string st="***", Nodo* s = nullptr, Nodo* r = nullptr) : info(st), sx(s), dx(r) { }  

  string info;
  Nodo* sx;
  Nodo* dx;
};

class Albero {
public:
  Albero() : radice(0) {}
  Albero(const Albero& r) : radice(copia(r.radice)) { } // dichiarazione costruttore di copia.
private:
  static Nodo* copia(Nodo *root) {
    if (root == nullptr)
      return nullptr;

    return new Nodo(root->info, copia(root->sx), copia(root->dx));
    // ricorsivamente copia i puntatori.
  };

  Nodo* radice;
};
