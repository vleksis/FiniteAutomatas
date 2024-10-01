#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <map>
#include <vector>

class DFA;

// A class for nondeterministic finite automata with
// <= 1 letter and epsilon transitions
class NFA {
  friend class DFA;

 public:
  NFA(size_t alphabet, size_t states_count);

  // assumption: orig < size() && letter <= alphabet && dest < size()
  bool contains_transition(size_t orig, size_t letter, size_t dest);

  // assumption: orig < size() && letter <= alphabet && dest < size()
  NFA& AddTransition(size_t orig, size_t letter, size_t dest);

  NFA& AddTerminated(size_t state);

  NFA& AddInitial(size_t state);

  size_t alphabet_size() const noexcept;

  size_t size() const noexcept;

  NFA& EpsilonClosure();

  friend std::ostream& operator<<(std::ostream& out, const NFA& automata);

  friend NFA Reverse(const NFA& automata);

  friend NFA Reverse(const DFA& automata);

 private:
  // makes transitive closure of epsilon transitions
  NFA& EpsClosureStep1();

  // adding of terminated marks through epsilon transitions
  NFA& EpsClosureStep2();

  // adding letter transition through epsilon transitions
  NFA& EpsClosureStep3();

  // deleting epsilon transitions
  NFA& EpsClosureStep4();

  friend NFA ReadNFA();

  std::vector<size_t> initial;
  // epsilon has index alphabet
  size_t alphabet = 2;
  std::vector<std::multimap<size_t, size_t>> transition;
  std::vector<bool> terminated;
};

NFA ReadNFA();

NFA Reverse(const NFA& automata);

#endif
