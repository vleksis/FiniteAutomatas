#include "NFA.h"

NFA::NFA(size_t alphabet, size_t states_count)
    : alphabet(alphabet), transition(states_count), terminated(states_count) {}

bool NFA::contains_transition(size_t orig, size_t letter, size_t dest) {
  auto begin = transition[orig].lower_bound(letter);
  auto end = transition[orig].upper_bound(letter);

  for (auto it = begin; it != end; ++it) {
    if (it->second == dest) {
      return true;
    }
  }

  return false;
}

NFA& NFA::AddTransition(size_t orig, size_t letter, size_t dest) {
  // do not add the same edge twice
  if (!contains_transition(orig, letter, dest)) {
    transition[orig].emplace(letter, dest);
  }
  return *this;
}

NFA& NFA::AddTerminated(size_t state) {
  terminated[state] = true;
  return *this;
}

NFA& NFA::AddInitial(size_t state) {
  initial.emplace_back(state);
  return *this;
}

size_t NFA::alphabet_size() const noexcept { return alphabet; }

size_t NFA::size() const noexcept { return transition.size(); }

NFA& NFA::EpsilonClosure() {
  return EpsClosureStep1()
      .EpsClosureStep2()
      .EpsClosureStep3()
      .EpsClosureStep4();
}

std::ostream& operator<<(std::ostream& out, const NFA& automata) {
  out << "alhabet: " << automata.alphabet << "\n";
  out << "states: " << automata.size() << "\n";
  out << "initials: ";
  for (auto i : automata.initial) {
    std::cout << i << " ";
  }
  out << "terminated: ";
  for (size_t i = 0; i < automata.size(); ++i) {
    if (automata.terminated[i]) {
      out << i << " ";
    }
  }
  out << "\ntransitions:\n";
  for (size_t u = 0; u < automata.size(); ++u) {
    for (size_t letter = 0; letter <= automata.alphabet; ++letter) {
      auto [begin, end] = automata.transition[u].equal_range(letter);
      for (auto it = begin; it != end; ++it) {
        std::string symb(1, static_cast<char>('a' + letter));
        if (letter == automata.alphabet) {
          symb = "eps";
        }
        out << "{ " << u << ", " << symb << ", " << it->second << " }\n";
      }
    }
  }

  return out;
}

NFA& NFA::EpsClosureStep1() {
  std::vector<std::vector<bool>> graph(size(), std::vector<bool>(size()));
  for (size_t u = 0; u < size(); ++u) {
    auto [begin, end] = transition[u].equal_range(alphabet);
    for (auto it = begin; it != end; ++it) {
      size_t v = it->second;
      graph[u][v] = true;
    }
  }

  for (size_t v = 0; v < size(); ++v) {
    for (size_t u = 0; u < size(); ++u) {
      for (size_t w = 0; w < size(); ++w) {
        graph[u][w] = graph[u][w] || (graph[u][v] && graph[v][w]);
      }
    }
  }

  for (size_t u = 0; u < size(); ++u) {
    for (size_t v = 0; v < size(); ++v) {
      if (graph[u][v] && u != v) {
        AddTransition(u, alphabet, v);
      }
    }
  }

  return *this;
}

NFA& NFA::EpsClosureStep2() {
  for (size_t u = 0; u < size(); ++u) {
    auto [begin, end] = transition[u].equal_range(alphabet);
    for (auto it = begin; it != end; ++it) {
      size_t v = it->second;
      if (terminated[v]) {
        terminated[u] = true;
      }
    }
  }

  return *this;
}

NFA& NFA::EpsClosureStep3() {
  for (size_t u = 0; u < size(); ++u) {
    auto [eps_begin, eps_end] = transition[u].equal_range(alphabet);
    for (auto it1 = eps_begin; it1 != eps_end; ++it1) {
      size_t v = it1->second;
      for (size_t letter = 0; letter < alphabet; ++letter) {
        auto [begin, end] = transition[v].equal_range(letter);
        for (auto it2 = begin; it2 != end; ++it2) {
          size_t w = it2->second;
          AddTransition(u, letter, w);
        }
      }
    }
  }

  return *this;
}

NFA& NFA::EpsClosureStep4() {
  for (size_t i = 0; i < size(); ++i) {
    transition[i].erase(alphabet);
  }

  return *this;
}

NFA ReadNFA(std::istream& in, std::ostream& out) {
  size_t alphabet;
  size_t state;
  size_t states;
  size_t initial;
  size_t transition_cnt;
  size_t terminated_cnt;

  out << "Alphabet: ";
  out.flush();
  in >> alphabet;

  out << "States: ";
  out.flush();
  in >> states;

  NFA automata(alphabet, states);

  out << "Initial: ";
  out.flush();
  in >> initial;
  automata.AddInitial(initial);

  out << "Terminated states count: ";
  out.flush();
  in >> terminated_cnt;

  out << "Terminated states in 0-numeration (ex. 0 3 1 5): ";
  for (size_t i = 0; i < terminated_cnt; ++i) {
    in >> state;
    automata.terminated[state] = true;
  }

  out << "Transition count: ";
  out.flush();
  in >> transition_cnt;

  size_t orig;
  std::string letter;
  size_t dest;
  out << "Transitions in format 'orig letter dest' (ex. 0 eps 3):\n";
  out.flush();
  for (size_t i = 0; i < transition_cnt; ++i) {
    in >> orig >> letter >> dest;
    if (letter == "eps") {
      automata.AddTransition(orig, alphabet, dest);
    } else {
      automata.AddTransition(orig, letter[0] - 'a', dest);
    }
  }

  return automata;
}

NFA Reverse(const NFA& automata) {
  NFA res(automata.alphabet_size(), automata.size());

  for (size_t u = 0; u < automata.size(); ++u) {
    for (size_t letter = 0; letter < automata.alphabet_size(); ++letter) {
      auto [begin, end] = automata.transition[u].equal_range(letter);
      for (auto it = begin; it != end; ++it) {
        auto v = it->second;
        res.AddTransition(v, letter, u);
      }
    }
  }

  for (size_t u = 0; u < automata.size(); ++u) {
    if (automata.terminated[u]) {
      res.initial.emplace_back(u);
    }
  }

  for (size_t u : automata.initial) {
    res.terminated[u] = true;
  }

  return res;
}
