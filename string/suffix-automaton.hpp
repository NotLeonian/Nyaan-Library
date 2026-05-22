#pragma once

#include <immintrin.h>

template <int margin = 'a'>
struct SuffixAutomaton {
  struct state {
    vector<pair<char, int>> nxt;
    uint64_t hit;
    int len, link, origin;
    char key;

    state() : hit(0), len(0), link(-1), origin(-1), key(0) {}
    state(int l, char k) : hit(0), len(l), link(-1), origin(-1), key(k) {}

    void add(char c, int i) {
      int x = int(c) - margin;
      assert(0 <= x && x < 64);
      assert(((hit >> x) & 1) == 0);
      nxt.emplace_back(c, i);
      hit |= 1ULL << x;
    }
  };

  vector<state> st;
  bool sorted;

  SuffixAutomaton() { clear(); }
  explicit SuffixAutomaton(const string &S) { build(S); }

  void clear() {
    st.assign(1, state());
    sorted = false;
  }

  void build(const string &S) {
    clear();
    int last = 0;
    for (int i = 0; i < (int)S.size(); i++) extend(S[i], last);
    tsort();
  }

  int size() const { return (int)st.size(); }

  __attribute__((target("popcnt"))) int get_idx(int i, char c) const {
    const state &s = st[i];
    int x = int(c) - margin;
    assert(0 <= x && x < 64);
    if (((s.hit >> x) & 1) == 0) return -1;
    if (sorted)
      return _mm_popcnt_u64(s.hit & ((1ULL << x) - 1));
    else {
      for (int j = 0; j < (int)s.nxt.size(); j++)
        if (s.nxt[j].first == c) return j;
    }
    assert(false);
    return -1;
  }

  int next(int i, char c) const {
    int j = get_idx(i, c);
    return j >= 0 ? st[i].nxt[j].second : -1;
  }

  vector<pair<char, int>> &chd(int i) { return st[i].nxt; }
  const vector<pair<char, int>> &chd(int i) const { return st[i].nxt; }

  int link(int i) const { return st[i].link; }

  int find(const string &s) const {
    int last = 0;
    for (char c : s) {
      last = next(last, c);
      if (last == -1) return -1;
    }
    return last;
  }

  state &operator[](int i) { return st[i]; }
  const state &operator[](int i) const { return st[i]; }

 private:
  void extend(char c, int &last) {
    int cur = (int)st.size();
    st.emplace_back(st[last].len + 1, c);
    int p = last;
    for (; p != -1 && get_idx(p, c) == -1; p = st[p].link) {
      st[p].add(c, cur);
    }
    if (p == -1) {
      st[cur].link = 0;
    } else {
      int q = next(p, c);
      if (st[p].len + 1 == st[q].len)
        st[cur].link = q;
      else {
        int clone = (int)st.size();
        {
          state cl = st[q];
          cl.len = st[p].len + 1, cl.origin = q;
          st.push_back(std::move(cl));
        }
        for (; p != -1; p = st[p].link) {
          int i = get_idx(p, c);
          if (i == -1 || st[p].nxt[i].second != q) break;
          st[p].nxt[i].second = clone;
        }
        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }

  void tsort() {
    int n = (int)st.size();
    vector<int> topo;
    {
      topo.reserve(n);
      vector<vector<int>> base(n + 1);
      for (int i = 0; i < n; i++) base[st[i].len].push_back(i);
      for (int i = 0; i < n; i++)
        copy(begin(base[i]), end(base[i]), back_inserter(topo));
    }
    {
      vector<state> st2;
      st2.reserve(n);
      for (int i = 0; i < n; i++) st2.emplace_back(std::move(st[topo[i]]));
      st.swap(st2);
    }
    vector<int> inv(n);
    for (int i = 0; i < n; i++) inv[topo[i]] = i;
    for (int i = 0; i < n; i++) {
      state &s = st[i];
      sort(begin(s.nxt), end(s.nxt));
      for (auto &[_, y] : s.nxt) y = inv[y];
      if (s.link != -1) s.link = inv[s.link];
      if (s.origin != -1) s.origin = inv[s.origin];
    }
    sorted = true;
  }
};

/**
 * @brief Suffix Automaton
 * @docs docs/string/suffix-automaton.md
 */
