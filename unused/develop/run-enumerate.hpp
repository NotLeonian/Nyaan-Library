#include "../../template/template.hpp"
//
#include "../../string/suffix-automaton.hpp"

template <char margin = 'a'>
struct RunEnumerate {
  string s;
  SuffixAutomaton<margin> sa;

  RunEnumerate(const string& _s) : s(_s), sa(_s) {}

 private:
  vector<int> enum_first_occurrence() {
    vector<int> first_occurrence(sa.size(), 1e9);
    for (int i = sa.size() - 1; i >= 0; --i) {
      if (sa[i].origin == -1) {
        first_occurrence[i] = sa[i].len;
      }
      int l = sa[i].link;
      if (i > 0 && sa[l].origin != -1 &&
          first_occurrence[i] < first_occurrence[sa[i].link])
        first_occurrence[sa[i].link] = first_occurrence[i];
    }
    return first_occurrence;
  }

  vector<int> factorize() {
    auto first_occurrence = enum_first_occurrence();
    vector<int> f;
    f.push_back(0);
    int cur = 0;
    for(int i = 0; i < (int)s.size(); i++) {
      if(i > 0) {
        int nx = sa.next(cur, s[i]);

      }
    }
    
  }
  
  vector<array<int, 3>> run(vector<int>& f) {
    unordered_map<uint64_t, array<int,3>> ret;
    for(int i = 0; i < f.size(); i++) {

    }
  }
};
