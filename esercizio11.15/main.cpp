#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ostream;

class RitiroPremio {
private:
  std::string ecc;
public:
  RitiroPremio() : ecc("il cliente ha sorpassato la soglia punti") { }
};

class Prodotto {
private:
  double prezzo;
public:
  Prodotto(double x = 0) : prezzo(x) { };
  double getPrezzo() const { return prezzo; }
};

class Cliente {
private:
  vector<Prodotto> carrello;
public:
  vector<Prodotto>::const_iterator getCarrello() const {
    return carrello.begin();
  }
  vector<Prodotto>::const_iterator getEndCarrello() const {
    return carrello.end();
  }
  void AddCarrello(const Prodotto& p) {
    carrello.push_back(p);
  }
  virtual double spesaTotale() const {
    double totale = 0.0;
    for (vector<Prodotto>::const_iterator it = carrello.begin(); it != carrello.end(); ++it) {
      totale = totale + (*it).getPrezzo(); 
    } 
    return totale;
  }
  void stampaProdotti() const {
    for (int i = 0; i < carrello.size(); i++) {
      cout << carrello[i].getPrezzo() << " ";
    }
  }
};

class ClienteFedele : public Cliente {
private:
  int saldo_punti;
  static int soglia_punti;
public:
  ClienteFedele() : Cliente(), saldo_punti(0) { }
  int getSogliaPunti() const {
    return soglia_punti;
  }
  double spesaTotale() const override {
    double totale = 0.0;
    for (vector<Prodotto>::const_iterator it = Cliente::getCarrello(); it != Cliente::getEndCarrello(); ++it) {
      double p = (*it).getPrezzo();
      totale = totale + (p - (p*0.05)); 
    } 
    return totale;
  }
  void accreditaPunti(int x) {
    saldo_punti += x; // incremento.
    if (x >= soglia_punti) { 
      saldo_punti -= soglia_punti;
      throw RitiroPremio();
    }
  }
  int getSaldoPunti() const {
    return saldo_punti;
  }
  void azzeraPunti() {
    saldo_punti = 0; // clear dei punti accreditati..
  }
};

int ClienteFedele::soglia_punti = 100;




class GestioneGiornaliera {
  friend ostream& operator<<(ostream& os, const GestioneGiornaliera& g);
private:
  vector<Cliente*> lista_clienti;
public:
  int getNumeroClienti() {
    return lista_clienti.size();
  }
  void insertCliente(const Cliente& c) {
    lista_clienti.push_back(&(const_cast<Cliente&>(c)));
  }

  double chiudiCassa() const {
    double totale_cassa = 0.0;
    // controllare se il cliente nella lista e' cliente fedele oppure no.
    for (vector<Cliente *>::const_iterator it = lista_clienti.begin(); it != lista_clienti.end(); it++) {
      ClienteFedele* cf = dynamic_cast<ClienteFedele*>(*it); // questo sembra essere il problema 
      if (cf) {
        try {
          cf->accreditaPunti(cf->spesaTotale()/10);
        } catch (RitiroPremio) {
          cout << "un cliente ha diritto ad un premio " << endl;
        }
      }
      totale_cassa = totale_cassa + (*it)->spesaTotale();
    }
    return totale_cassa;
  }

  int saldoPuntiGiornaliero() const {
    int saldo_punti_giornaliero = 0;
    for (int i = 0; i < lista_clienti.size(); i++) {
      ClienteFedele* cf = dynamic_cast<ClienteFedele*>(lista_clienti[i]);
      if (cf) saldo_punti_giornaliero = saldo_punti_giornaliero + cf->getSaldoPunti();
    }
    return saldo_punti_giornaliero;
  }
};


int main() {
  Prodotto latte(4.00);
  Prodotto carne(8.00);
  Prodotto sushi(10.50);
  
  Cliente c;
  ClienteFedele cf;

  c.AddCarrello(latte);
  c.AddCarrello(carne);
  c.AddCarrello(sushi);

  c.stampaProdotti();
  cout << "\n totale carrello cliente: " << c.spesaTotale() << " $" << endl;

  cf.AddCarrello(latte);
  cf.AddCarrello(carne);
  cf.AddCarrello(sushi);

  cf.stampaProdotti();
  cout << "\ntotale carrello cliente fedele: " << cf.spesaTotale() << " $" << endl;
  
  GestioneGiornaliera g;
  g.insertCliente(c);
  g.insertCliente(cf);
  cout << "totale della cassa: " << g.chiudiCassa() << endl;
  cout << "dopo la chiusura della cassa: " << cf.getSaldoPunti() << endl;
  
}

// commenti
// 1. rendere disponibile un distruttore virtuale SEMPRE se si ha una classe polimorfa.
// 2. lo sconto era globale => si poteva fare il totale per (100/100 - 5/100)
// 3. all'esame, piuttosto che incasinarti con l'uso di const_iterator, usa semplicemente gli indici interi
// in quanto vector<T> mette a disposizione un overloading per operator[](int x).
