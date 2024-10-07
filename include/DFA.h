#ifndef FORMAL_DFA_H
#define FORMAL_DFA_H

#include <queue>
#include <unordered_map>
#include "NFA.h"

class DFA {
  using mask_t = u_int32_t;

 public:

  // tests only
  DFA();

  // tests only
  explicit DFA(size_t alphabet, size_t size);

  explicit DFA(const NFA& automata);

  size_t alphabet_size() const noexcept;

  size_t size() const noexcept;

  friend std::ostream& operator<<(std::ostream& out, const DFA& automata);

  // return NFA for reversed language
  friend NFA Reverse(const DFA& automata);

  // check if two DFA are isomorphic
  friend bool Isomorphic(const DFA& lhs, const DFA& rhs);

 private:
  size_t alphabet;
  size_t initial;
  std::vector<bool> terminated;
  std::vector<std::vector<size_t>> transition;
};

NFA Reverse(const DFA& automata);

DFA MFDFA(const NFA& automata);

bool Isomorphic(const DFA& lhs, const DFA& rhs);

#endif  // FORMAL_DFA_H
