#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// l'unica cosa che puo' mancare e' di definire una classe ACI
// ACI contiene tra i suoi campi privati un vector di puntatori ad Auto.
// la sua interfaccia pubblica si compone di due metodi:
// 1. agggiungiAuto -> aggiunge un puntatore ad un auto (penso allocata sullo heap).
// 2. incasssaBolli -> fa la somma di tutti i bolli delle auto che ci sono in memoria (sullo heap in questo caso).

class Auto {
private:
  unsigned int cavalli_fiscali;
public:
  static unsigned int tassa_bollo;
  virtual unsigned int tassa() const = 0; 
  unsigned int getCavalliFiscali() const { return cavalli_fiscali; } 
  Auto(unsigned int x = 0) : cavalli_fiscali(x) { };
};

unsigned int Auto::tassa_bollo = 5;

class Diesel : public Auto {

  static unsigned int imposta;
public:
  Diesel(unsigned int x) : Auto(x) { }
  unsigned int tassa() const override { 
    return ((Auto::getCavalliFiscali() * Auto::tassa_bollo) + imposta);
  }
};

unsigned int Diesel::imposta = 100;

class Benzina : public Auto {
private:
  const bool euro_quattro;
  static unsigned int bonus;
public:
  Benzina(unsigned int x = 0, bool e4 = false) : Auto(x), euro_quattro(e4) { }
  unsigned int tassa() const override {
    unsigned int senza_bonus = Auto::getCavalliFiscali() * Auto::tassa_bollo;
    if (euro_quattro)
      return senza_bonus - bonus;
    return senza_bonus;
  }
};

unsigned int Benzina::bonus = 50;

class ACI {
private:
  vector<Auto*> v;
public:
  void AggiungiAuto(const Auto& a) { 
    // da a costruisco di copia un nuovo oggetto aux allocato sullo heap. 
    // il puntatore ritornato da questa allocazione lo pusho nel vettore.
    // Auto& t = const_cast<Auto&>(a); // ricordarsi che il const cast rimuove il T.
    cout << "dentro la funzione aggiungi auto: " << &a << endl;
    v.push_back((const_cast<Auto*>(&a))); // in questo caso risulta necessario il const cast in quanto
    // &a produce un const A* => bisogna rendere questa cosa A* in quanto nel vector possono solamente
    // esserci Auto* => di conseguenza l'unico operando disponibile per effettuare questo tipo di conversione
    // risulta const_cast.
  }
  unsigned int incassaBolli() const { 
    unsigned int totale = 0;
    for (vector<Auto*>::const_iterator it = v.begin(); it != v.end(); it++)
      totale += (*it)->tassa();
    return totale;
  }
};


int main() {

  Diesel panda(75);
  cout << "il bollo della panda risulta essere: " << panda.tassa() << endl;

  Benzina cinquecentoL(95, true);
  cout << "il bollo della 500 risulta essere: " << cinquecentoL.tassa() << endl;

  Benzina cinquecento_vecchia(95, false);
  cout << "il bollo della 500 (vecchia) risulta essere: " << cinquecento_vecchia.tassa() << endl;

  Auto& p_benzina = cinquecento_vecchia;
  cout << "il numero di cavalli fiscali di quest'auto e': " << p_benzina.getCavalliFiscali() << endl;
  
  cout << endl;

  // da ricordarsi questa cosa.
  // dato che una variabile e' come una label per una locazione di memoria...
  // una reference e' come se fosse una seconda label per quella locazione di memoria.

  /*
  cout << "address of cinquecento_vecchia: " << &cinquecento_vecchia << endl;
  cout << "addressof p_benzina: " << &p_benzina << endl;
  */

  ACI agenzia_ita;
   
  cout << "fuori aggiungiauto " << &panda << endl;
  agenzia_ita.AggiungiAuto(panda);
  cout << "totale bolli: " << agenzia_ita.incassaBolli() << endl;
}

