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
  out << "``` mermaid\n\n";
  out << "graph\n\n";

  out << "classDef terminated_node fill:#bbb,stroke:#333,stroke-width:4px;\n";
  out << "classDef normal_node fill:#b46,stroke:#333,stroke-width:4px;\n\n";

  out << "Start(( ))\n";
  for (size_t i = 0; i < automata.size(); ++i) {
    out << "V" << i << "((" << i << "))\n";
  }
  out << "\n";

  out << "class ";
  for (size_t i = 0; i < automata.size(); ++i) {
    if (automata.terminated[i]) {
      out << "V" << i << ',';
    }
  }
  out << " terminated_node;\n";

  out << "class ";
  for (size_t i = 0; i < automata.size(); ++i) {
    if (!automata.terminated[i]) {
      out << "V" << i << ',';
    }
  }
  out << " normal_node;\n\n";

  out << "Start --> V" << automata.initial << '\n';
  for (size_t u = 0; u < automata.size(); ++u) {
    for (size_t letter = 0; letter < automata.alphabet; ++letter) {
      auto symb = static_cast<char>('a' + letter);
      size_t v = automata.transition[u][letter];
      out << "V" << u << " -- " << symb << " ---> V" << v << '\n';
    }
  }

  out << "\n```";

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

DFA MFDFA(const NFA& automata) { return DFA(Reverse(DFA(Reverse(automata)))); }

// in assumption that all nodes are reachable
bool Isomorphic(const DFA& lhs, const DFA& rhs) {
  if (lhs.alphabet != rhs.alphabet) {
    return false;
  }
  if (lhs.size() != rhs.size()) {
    return false;
  }

  std::vector<size_t> bijection(lhs.size(), lhs.size());
  std::queue<size_t> queue;
  bijection[lhs.initial] = rhs.initial;
  queue.emplace(lhs.initial);

  while (!queue.empty()) {
    auto u1 = queue.front();
    auto u2 = bijection[u1];
    queue.pop();

    for (size_t letter = 0; letter < lhs.alphabet; ++letter) {
      auto v1 = lhs.transition[u1][letter];
      auto v2 = rhs.transition[u2][letter];
      if (bijection[v1] == lhs.size()) {
        bijection[v1] = v2;
        queue.emplace(v1);
      }
      if (bijection[v1] != v2) {
        return false;
      }
    }
  }

  for (size_t u1 = 0; u1 < lhs.size(); ++u1) {
    auto u2 = bijection[u1];
    if (lhs.terminated[u1] != rhs.terminated[u2]) {
      return false;
    }
  }

  return true;
}

DFA::DFA(size_t alphabet, size_t size)
    : alphabet(alphabet),
      transition(size, std::vector<size_t>(alphabet)),
      terminated(size) {}

DFA::DFA() = default;
