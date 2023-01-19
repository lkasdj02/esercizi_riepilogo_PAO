#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::string;

class C {
private:
  int d;
public:
  C(string s="") : d(s.size()) { }
  explicit C(int n) : d(n) { } // questo funge da convertitore di tipo da int -> c.
  // con la keyword explicit facciamo si che la conversione implicita da int -> c non avvenga. 
  operator int() { return d; } // convertitore di tipo da c -> int.
  C operator+ (C x) {return C(d+x.d); }

};


int main() {
  C a, b("pippo"), c(3);
  cout << a << " " << 1 + b << ' ' << c + 4 << c+b;
  // 0 6 7 8
}
