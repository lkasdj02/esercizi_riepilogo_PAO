#include <iostream>
#include <string>
#include <vector>
// #include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// aggiungere get e set solo quando ti accorgi che possono servire ai fini dell'esercizio.
class FileAudio {
private:
  string titolo;
  int dimensione;
public:
  // metodi virtuali puri e distruttore virtuale.
  virtual FileAudio* clone() const = 0;
  virtual bool qualita() const = 0;
  virtual ~FileAudio() { cout << "Df ";};   // solamente ridefiniti a scopo di tracciamento.


  string getTitolo() const { return titolo; } // metodo non necessario (non inserire un metodo se non e' necessario ai fini dell'esercizio).
  int getDimensione() const { return dimensione; }
  FileAudio(string t = "", int d = 0) : titolo(t), dimensione(d) { }
  virtual bool operator==(const FileAudio& o) const { // fare l'override di questo metodo.
    return ((titolo == o.titolo) && (dimensione == o.dimensione));
  }
};

class Mp3 : public FileAudio {
private:
  double bitrate;
public:
  double getBitrate() const { return bitrate; }
  ~Mp3() { cout << "Dmp3 ";}
  Mp3(string t = "", int d = 0, int b = 0) : FileAudio(t, d), bitrate(b) { }
  FileAudio* clone() const override { //  questo override si puo' fare in quanto valre la regola della covarianza sul tipo di ritorno.
    return new Mp3(*this); // costruttore di copia.
  }
  bool qualita() const override { 
    return (bitrate >= 192) ? true : false;
  }
};

class Wav : public FileAudio {
private:
  double campionamento;
  bool lossless;
public:
  double getCampionamento() const { return campionamento; }
  bool isLossless() const { return lossless; }
  Wav(string t = "", int d = 0, int c = 0, bool l = false) : FileAudio(t, d), campionamento(c), lossless(l) { }
  FileAudio* clone() const override { //  questo override si puo' fare in quanto valre la regola della covarianza sul tipo di ritorno.
    return new Wav(*this); // costruttore di copia.
  }
  bool qualita() const override { 
    return (campionamento >= 96) ? true : false;
  }

};

class Izod { 
private:
  class Brano {
  public:
    FileAudio* pb; 
    Brano(FileAudio* p) : pb(p->clone()) { }
    Brano(const Brano& b) : pb((b.pb)->clone()) { }
    Brano& operator=(const Brano& b) {
      if(this != &b) {
        delete pb;
        pb = (b.pb)->clone();
      }
      return (*this);
    }
    ~Brano() {
      if(pb) delete pb; // ricordati questo check da fare assolutamente.
    }
  };
  vector<Brano> brani;
public:
  //getters and setters
  // metodi da implenetare
  vector<Mp3> mp3(double dim, int br) const; 
  vector<FileAudio*> braniQual() const;
  void insert(Mp3*);
};


vector<Mp3> Izod::mp3(double dim, int br) const {
  vector<Mp3> aux;
  for (int i = 0; i < brani.size(); i++) {
    // checckare se il brani i esimo ha un puntatore con tipo dinamico Mp3*
    // se si => controllare che questo brano abbia dimensione >= dim e bitrate >= bitrate.
    // se questi requisiti vengono rispettati => costruire di copia un puntatore da questo per pusharlo in aux.
    Mp3* ptr = dynamic_cast<Mp3*>(brani[i].pb);
    if(ptr) {
      if (ptr->getDimensione() >= dim && ptr->getBitrate() >= br) {
        Mp3 item = *ptr;
        aux.push_back(item);
      }
    }
  }
  return aux;
}

vector<FileAudio*> Izod::braniQual() const {
  vector<FileAudio*> aux;
  for (vector<Brano>::const_iterator it = brani.begin(); it != brani.end(); it++) {
    FileAudio* ptr = (*it).pb;
    if (ptr->qualita()) {
      Wav *ptr_wav = dynamic_cast<Wav*>(ptr);
      if(ptr_wav) {
        if (ptr_wav->isLossless()) aux.push_back(ptr);
      } else { // TD(ptr) != Wav* => TD(ptr) == Mp3*
        aux.push_back(ptr);
      }
    }
  }
}

void Izod::insert(Mp3* p) {
  bool is_present = false;
  for(auto cit = brani.begin(); cit != brani.end(); cit++)
    if(*(cit->pb) == *p) is_present = true; // il confronto andrebbe fatto sul File audio...non tra puntatori a file audio
  // sarebbe errore all'esame: dovrei definire un override per il metodo operato= anche nella classe Mp3.

  if(!is_present) {
    Brano nuovo(p);
    brani.push_back(p);
  }
}

int main() {
  FileAudio* p = new Mp3("london calling", 35, 192);
  delete p;
}
