#include <iostream>


using std::cout;
using std::endl;
using std::ostream;

template <class T, int size>
class C; // dichiarazione incompleta per poi sovraccaricare l'operatore di output.

template <class T, int size>
ostream& operator<<(ostream& os, const C<T, size>&);

template <class T, int size>
class C {
  friend ostream& operator<< <T>(ostream&, const C<T, size>&);
private:
  class MultiInfo {
  public:
    T info;
    int molteplicita;  
    T getInfo() const { return info; }
    void  setInfo(T i) { info = i; }
    int getMolteplicita() { return molteplicita; }
    void setMolteplicita(int m) { molteplicita = m; }
  };
  MultiInfo *array;
public:
  C() { array = new MultiInfo[size]; } 
  ~C() { delete[] array; }
  int getSize() const { return size; }
  C(const C& c) : array(new MultiInfo[size]) { 
      for (int i = 0; i < size; i++) array[i] = c.array[i];
  } 
  C& operator=(const C& c) {
    if (this != &c) {
      for (int i = 0; i < size; i++) {
        array[i] = c.array[i];
      }
    }
    return *this;
  }
  C(const T& t = T(), int k = 0) : array(new MultiInfo[size]) { 
    for (int i = 0; i < size; i++) {
      array[i].setInfo(t);
      array[i].setMolteplicita(k);
    }
  } 
  void stampa() const { 
    for (int i = 0; i < size; i++) {
      cout << array[i].getMolteplicita() << " ";
    }
    cout << endl;
  }
  T* operator[](int i) const {
    return (0 <= i < size) ? /* comportamento */ &(array[i].info) : 0;
  }
  int occorrenze(const T& t) const {
    int tot = 0;
    for (int i = 0; i < size; i++) {
      if (array[i].info == t) tot+=array[i].molteplicita;
    }
    return tot;
  }
};

template <class T, int size>
ostream& operator<<(ostream& os, const C<T, size>& c) {
  os << "c: ";
  for (int i = 0; i < size; i++) {
    os << *(c[i]) << " "; 
  }
  os << endl;
  return os;
}

int main() {
  C<int, 10> c(3, 3);
  C<int, 10> d(4, 4);
  d = c;
  
  cout << d;
}

