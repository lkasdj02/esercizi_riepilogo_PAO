#include <iostream>
#include <istream>

using std::ostream;
using std::cout;
using std::endl;

class Data;

ostream& operator<<(ostream& os, const Data& data);


class Data {
  friend ostream& operator<<(ostream& os, const Data& data); 
private:
  std::string nome_giorno;
  int giorno;
  int mese;
  int anno;
public:
  Data(std::string ng = "", int g = 1, int m = 1, int a = 1970) : nome_giorno(ng), giorno(g), mese(m), anno(a) { }
  std::string getGiornoSettimana() const {
    return nome_giorno;
  }
  int getGiorno() const { return giorno; } 
  int getMese() const { return mese; } 
  int getAnno() const { return anno; } 
  bool operator<(const Data& data) const {
    if (anno < data.anno) return true;
    if (mese < data.mese) return true;
    if (giorno < data.giorno) return true; 
    
    return false;
  }
  bool operator==(const Data& data) const {
    return (anno == data.anno) && (mese == data.mese) && (giorno == data.giorno);
  }
};

ostream& operator<<(ostream& os, const Data& data) {
  return (os << data.nome_giorno << "-" << data.giorno << "-" << data.mese << "-" << data.anno);
}

int main() {
  Data d1("domenica", 15, 1, 2023);
  Data d2("domenica", 15, 1, 2023);
  cout << d1 << " " << d2 << endl;
  (d1 == d2) ? cout << "vero\n" : cout << "falso\n";
}
