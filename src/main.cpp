#include <iostream>

#include "DFA.h"
#include "NFA.h"

int main() {
  auto automata = ReadNFA(std::cin, std::cout);
  automata.EpsilonClosure();
  std::cout << "After epsilon-closure:\n" << automata << '\n';
  std::cout << "DFA:\n" << DFA(automata) << '\n';
  std::cout << "MFDKA:\n" << MFDFA(automata) << '\n';
}
