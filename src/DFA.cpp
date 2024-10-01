#include "DFA.h"

DFA::DFA(const NFA& automata) : alphabet(automata.alphabet), initial(0) {
  std::queue<mask_t> queue;
  std::unordered_map<mask_t, size_t> states;
  {
    mask_t mask = 0;
    for (auto i : automata.initial) {
      mask |= (1 << i);
    }
    queue.push(mask);
  }
  transition.emplace_back(alphabet);
  terminated.emplace_back();
  states.emplace(queue.front(), 0);
  while (!queue.empty()) {
    auto mask = queue.front();
    queue.pop();
    size_t dfa_u = states[mask];
    bool is_terminated = false;
    std::vector<size_t> masked_states;

    {
      size_t u = 0;
      while (mask > 0) {
        if (mask & 1) {
          is_terminated |= automata.terminated[u];
          masked_states.emplace_back(u);
        }
        ++u;
        mask >>= 1;
      }
    }
    terminated[dfa_u] = is_terminated;

    for (size_t letter = 0; letter < alphabet; ++letter) {
      mask_t new_mask = 0;

      for (auto u : masked_states) {
        auto [begin, end] = automata.transition[u].equal_range(letter);
        for (auto it = begin; it != end; ++it) {
          auto v = it->second;
          new_mask |= (1 << v);
        }
      }

      if (!states.contains(new_mask)) {
        queue.push(new_mask);
        states.emplace(new_mask, states.size());
        transition.emplace_back(alphabet);
        terminated.emplace_back();
      }
      size_t dfa_v = states[new_mask];
      transition[dfa_u][letter] = dfa_v;
    }
  }
}

std::ostream& operator<<(std::ostream& out, const DFA& automata) {
  out << "alhabet: " << automata.alphabet << "\n";
  out << "states: " << automata.size() << "\n";
  out << "initial: " << automata.initial << "\n";
  out << "terminated: ";
  for (size_t i = 0; i < automata.size(); ++i) {
    if (automata.terminated[i]) {
      out << i << " ";
    }
  }
  out << "\ntransitions:\n";
  for (size_t u = 0; u < automata.size(); ++u) {
    for (size_t letter = 0; letter < automata.alphabet; ++letter) {
      auto symb = static_cast<char>('a' + letter);
      size_t v = automata.transition[u][letter];
      out << "{ " << u << ", " << symb << ", " << v << " }\n";
    }
  }

  return out;
}

size_t DFA::alphabet_size() const noexcept { return alphabet; }

size_t DFA::size() const noexcept { return transition.size(); }

NFA Reverse(const DFA& automata) {
  NFA res(automata.alphabet_size(), automata.size());

  for (size_t u = 0; u < automata.size(); ++u) {
    for (size_t letter = 0; letter < automata.alphabet_size(); ++letter) {
      size_t v = automata.transition[u][letter];
      res.AddTransition(v, letter, u);
    }
  }

  for (size_t u = 0; u < automata.size(); ++u) {
    if (automata.terminated[u]) {
      res.initial.emplace_back(u);
    }
  }

  res.terminated[automata.initial] = true;

  return res;
}

DFA MFDFA(const NFA& automata) {
  return DFA(Reverse(DFA(Reverse(automata))));
}