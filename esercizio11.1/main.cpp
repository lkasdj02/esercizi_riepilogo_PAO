#include "intmod.h"

// definizione metodi ed operatori.
IntMod::IntMod(int n) : numero(n%modulo) {}

IntMod IntMod::operator+(const IntMod& other) const {
  return IntMod(((*this).numero + other.numero) % modulo);
}

IntMod IntMod::operator*(const IntMod& other) const {
  return IntMod(((*this).numero * other.numero) % modulo);
}

IntMod::operator int() const {
  return numero;
}
