#include <iostream>

class IntMod {
private:
  int numero;
  static int modulo;
public:
  explicit IntMod(int n = 0);
  IntMod operator+(const IntMod&) const;
  IntMod operator*(const IntMod&) const;
  operator int() const;
};

