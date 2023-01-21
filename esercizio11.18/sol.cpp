#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// aggiungere get e set solo quando ti accorgi che possono servire ai fini dell'esercizio.
class FileAudio {
private:
  string titolo;
  int dimensione;
public:
  virtual ~FileAudio() { cout << "Df ";};   // solamente ridefiniti a scopo di tracciamento.
  string getTitolo() const { return titolo; }
  int getDimensione() const { return dimensione; }
  FileAudio(string t = "", int d = 0) : titolo(t), dimensione(d) { }
  virtual FileAudio* clone() const = 0;
  virtual bool qualita() const = 0;
};

class Mp3 : public FileAudio {
private:
  int bitrate;
public:
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
  int campionamento;
  bool lossless;
public:
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
  private:
    FileAudio* pb; 
    Brano(FileAudio* p) : pb(pb->clone()) { }
    Brano(const Brano& b) : pb((b.pb)->clone()) { }
    Brano& operator=(const Brano& b) {
      if(this != &b) {
        delete pb;
        pb = (b.pb)->clone();
      }
      return (*this);
    }
    ~Brano() {
     delete pb;
    }
  };
};

int main() {
  FileAudio* p = new Mp3("london calling", 35, 192);
  delete p;
}
