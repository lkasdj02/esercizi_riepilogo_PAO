#include <iostream>


using std::cout;


class A {
friend class C; // => all'interno della classe C posso accedere ai campi privati di A (=> k)
private:
  int k;
public:
  A(int x = 2) : k(x) { } // => funge da: costruttore di default e da convertitore da int => A
  void m(int x = 3) { k = x; } // metodo che provoca side effects.
};

class C {
private:
  A* p;
  int n;
public:
  C(int k = 3) { if (k > 0) { p = new A[k]; n = k; } } // funge anche da costruttore di default
  // questo array di A costruisce k celle con il costruttore di default
  // dato che e' stato invocato con la parola chiave new => questo array viene invocato nello heap.
  A* operator->() const { return p; }
  A& operator*() const { return *p; } // ritorna un A& in quanto su questo possono essere fatti dei side effect.
  A* operator+(int i) const { return p + i; } // aritmetica dei puntatori.
  void F(int k, int x) { if (k < n) p[k].m(x); }
  void stampa() const {
    for (int i = 0; i < n; i++) cout << p[i].k << ' ';
  }
};

int main() {
  C c1; // costruzione di default => viene invocato C(3).
  // c1.stampa();
  c1.F(2, 9);
  C c2(5);
  c2.F(0, 8);
  *c1 = *c2; // assegnazione standard per A => A& operator(const A&). => viene fatta la copia campo dati per campo dati da *c2 a *c1.
  (c2+3)->m(7);
  c1.stampa(); cout << "UNO\n";
  c2.stampa(); cout << "DUE\n";


  c1 = c2; // assegnazione standard per c => viene fatta una copia campo dati per campo dati da c2 a c1; => c1 e c2 puntano tutte e due alla stessa area di memoria
  // => nella pratica questo si deve evitare in quanto produce garbage (memoria inutilizzata).
  *(c2+1) = A(3); //A(3) costruisce un temporaneo anonimo che viene assegnato a *(c2 + 1);
  c1->m(1);
  *(c2 + 2) = *c1;
  c1.stampa();  cout << "TRE\n";
  c2.stampa(); cout << "QUATTRO\n";


}
