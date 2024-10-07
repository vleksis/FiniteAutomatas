#include <iostream>

#include "DFA.h"


// codes "last a_bit b_bit c_bit" from binary to decimal + 1
// each bit means that corresponding letter was met previously
// 'last' is last letter in the word
size_t Code(size_t a_bit, size_t b_bit, size_t c_bit, size_t last) {
  return (last << 3) + (a_bit << 2) + (b_bit << 1) + (c_bit << 0) + 1;
}

int main() {
  NFA aut(3, 25);
  aut.AddInitial(0);
  aut.AddTransition(0, 0, Code(0, 0, 0, 0));
  aut.AddTransition(0, 1, Code(0, 0, 0, 1));
  aut.AddTransition(0, 2, Code(0, 0, 0, 2));

  for (size_t a = 0; a < 2; ++a) {
    for (size_t b = 0; b < 2; ++b) {
      for (size_t c = 0; c < 2; ++c) {
        for (size_t Last = 0; Last < 3; ++Last) {
          size_t u = Code(a, b, c, Last);
          switch (Last) {
            case 0:
              if (a == 1)
                aut.AddTerminated(u);
              break;
            case 1:
              if (b == 1)
                aut.AddTerminated(u);
              break;
            case 2:
              if (c == 1)
                aut.AddTerminated(u);
              break;
            default:
              exit(1);
          }
          for (size_t letter = 0; letter < 3; ++letter) {
            size_t na = a | (Last == 0);
            size_t nb = b | (Last == 1);
            size_t nc = c | (Last == 2);
            size_t v = Code(na, nb, nc, letter);
            aut.AddTransition(u, letter, v);
          }
        }
      }
    }
  }
  aut.EpsilonClosure();
  std::cout << MFDFA(aut);
}
