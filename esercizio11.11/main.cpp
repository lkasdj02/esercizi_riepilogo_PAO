#include <iostream>
#include <list>
#include <string>


using std::cout;
using std::endl;
using std::string;
using std::list;

class Biglietto {
private:
  string aquirente;
  const bool platea;
public:
  virtual ~Biglietto() { } ; // dobbiamo rendere questa classe polimorfa => il modo piu' semplice e' quello di includere un costruttore virtuale.
  Biglietto(string a = "", bool p = false) : aquirente(a), platea(p) { }
  string getAcquirente() const { return aquirente; }
  void setAcquirente(string s) { aquirente = s; }
  const bool getPlatea() const { return platea; }
  virtual double getPrezzo(double, double) const = 0;
};

class BigliettoNumerato : public Biglietto {
private:
  int fila;
public:
  BigliettoNumerato(string s = "", int f = true) : Biglietto(s, f), fila(f) { }
  void setFila(int x) { fila = x; }
  int getFila() const { return fila; }
  virtual double getPrezzo(double b, double a) const override {
    return (fila < 1) ? ((2*a) + (2*b)) : 2*a; // questo comportamento polimorfo e' frutto di un'incomprensione del problema.
  }
};

class BigliettoNonNumerato : public Biglietto {
private:
  const bool ridotto;
public:
  BigliettoNonNumerato(string s = "", bool p = false, bool r = false) : Biglietto(s, p), ridotto(r) { }
  const bool getRidotto() const { return ridotto; }
  virtual double getPrezzo(double b, double a) const override {
    double somma = 0.0; 
    if (Biglietto::getPlatea()) somma+=a;
    if (getRidotto()) somma -= (somma/2);
    return somma;
  }
};

class Spettacolo {
private:
  const double base;
  const double addizionale;
  const int max_posti_numerati;
  int n_posti_prima_fila; 
  int n_numerati_venduti; // questo deve essere controllato.
  list<Biglietto*> posti_venduti;
public:
  Spettacolo(double b, double a, int mpn, int nppf, int nnv) : base(b), addizionale(a), max_posti_numerati(mpn),
    n_posti_prima_fila(nppf), n_numerati_venduti(nnv) { }
  void addBiglietto(const Biglietto& b) {
    BigliettoNumerato *p = dynamic_cast<BigliettoNumerato*>(&(const_cast<Biglietto&>(b)));
    if(p) {
      if ((max_posti_numerati - n_numerati_venduti) > 0) {
        posti_venduti.push_front(p);
        --n_numerati_venduti;
      }
    } else {
      posti_venduti.push_front(&(const_cast<Biglietto&>(b)));
    }

  }
  void stampa() const {
    for (list<Biglietto*>::const_iterator i = posti_venduti.begin(); i != posti_venduti.end(); i++) {
      cout << (*i)->getAcquirente() << " ";
    }
    cout << "\n";
  }
  double prezzo (const Biglietto& b) const {
    return b.getPrezzo(base, addizionale);
  }
  double incasso() const {
    double tot = 0.0;
    for (list<Biglietto*>::const_iterator i = posti_venduti.begin(); i != posti_venduti.end(); i++) {
      tot = tot + (*i)->getPrezzo(base, addizionale);
    }
    return tot;
  }
};

int main() {
  Spettacolo s(10.0, 6.0, 200, 10, 0);

  BigliettoNumerato a1("pippo", 1); // 32
  BigliettoNumerato a2("pluto", 17); // 
  BigliettoNonNumerato b1("zagor");
  BigliettoNonNumerato b2("pluto", false, true);
  s.addBiglietto(a1); s.addBiglietto(a2);
  s.addBiglietto(b1); s.addBiglietto(b2); 
  s.stampa(); 
  cout << "totale biglietti sino ad ora venduti: " << s.incasso() << endl;
}

