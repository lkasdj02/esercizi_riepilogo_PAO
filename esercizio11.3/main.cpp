#include <iostream>

using std::cout;

class It {
  friend class C; // C puo' accedere ai campi privati di It.
public:
  bool operator<(It i) const { return index < i.index; } // attenzione che i viene passato per valore => costruzione di copia.
  It operator++(int) { It t = *this; index++; return t;} // operatore di incremento postfisso.
  It operator+(int k) { index = index + k; return *this; } // operatore di incremento prefisso (lo si capisce dal fatto che il parametro implicito e' this).
  
private:
  int index;
};

// essenzialmente C e' un contenitore che ha come campo privato un puntatore ad intero.
class C {
public:
  C(int k) {
    if (k > 0) { dim = k; p = new int[k]; }
    for(int i = 0; i < k; i++) *(p+i) = i; // inizializzazione di un array allocato dinamicamente => sullo heap.
  }
  It begin() const { It t; t.index = 0; return t; }
  It end() const { It t; t.index = dim; return t; }
  int& operator[](It i) { return *(p + i.index); } // redifinizione dell'operatore di subscripting.

private:
  int *p;
  int dim;
};


int main() {
  C c1(4), c2(8); // => vengono costruiti due oggetti di tipo C
  for (It i = c1.begin(); i < c1.end(); i++) {
    cout << c1[i] << ' ';    
  }
  cout << "UNO\n"; // vengono stampati 0 1 2 3 UNO;
}
