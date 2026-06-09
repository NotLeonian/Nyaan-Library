---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: random_graph/graph.hpp
    title: random_graph/graph.hpp
  - icon: ':warning:'
    path: random_graph/random.hpp
    title: random_graph/random.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"random_graph/gen.hpp\"\n\n#include <array>\n#include <cassert>\n\
    #include <chrono>\n#include <numeric>\n#include <set>\n#include <vector>\n\n#line\
    \ 2 \"random_graph/graph.hpp\"\n\n#include <algorithm>\n#line 5 \"random_graph/graph.hpp\"\
    \n#include <iostream>\n#line 7 \"random_graph/graph.hpp\"\n\nusing namespace std;\n\
    \n// \u8FBA\u306E\u91CD\u307F\u306Flong long\u6C7A\u3081\u6253\u3061\nusing W\
    \ = long long;\n\n// \u8FBA\u306E\u60C5\u5831\u3092\u683C\u7D0D\u3059\u308B\u69CB\
    \u9020\u4F53\nstruct Edge {\n  int u, v;\n  W w;\n  int idx;\n  Edge(int _u, int\
    \ _v, W _w = 1, int _idx = -1)\n      : u(_u), v(_v), w(_w), idx(_idx) {}\n};\n\
    \n// \u30B0\u30E9\u30D5\u306E\u60C5\u5831\u3092\u683C\u7D0D\u3059\u308B\u69CB\u9020\
    \u4F53\nstruct Graph {\n private:\n  int n, m;\n  vector<Edge> es;\n  bool weighted;\n\
    \n public:\n  Graph(int _n = 0, bool _weighted = false)\n      : n(_n), m(0),\
    \ weighted(_weighted) {}\n\n  int edges_size() const { return m; }\n\n  // u ->\
    \ v, \u91CD\u307F w \u306E\u8FBA\u3092\u8FFD\u52A0\n  // 0-indexed \u3067\u8FFD\
    \u52A0\u3059\u308B\u5FC5\u8981\u3042\u308A\n  void add_directed_edge(int u, int\
    \ v, W w = 1, int idx = -1) {\n    es.emplace_back(u, v, w, idx);\n    m++;\n\
    \  }\n\n  // min(u,v) -> max(u,v), \u91CD\u307F w \u306E\u8FBA\u3092\u8FFD\u52A0\
    \n  // 0-indexed \u3067\u8FFD\u52A0\u3059\u308B\u5FC5\u8981\u3042\u308A\n  void\
    \ add_undirected_edge(int u, int v, W w = 1, int idx = -1) {\n    int mn = min(u,\
    \ v), mx = max(u, v);\n    add_directed_edge(mn, mx, w, idx);\n  }\n\n  // \u96A3\
    \u63A5\u30EA\u30B9\u30C8\u3092\u8FD4\u3059\n  vector<vector<Edge>> adjacent_list(bool\
    \ directed = false) const {\n    vector<vector<Edge>> g(n);\n    for (auto& [u,\
    \ v, w, i] : es) {\n      g[u].emplace_back(u, v, w, i);\n      if (!directed)\
    \ g[v].emplace_back(v, u, w, i);\n    }\n    return g;\n  }\n\n  // \u96A3\u63A5\
    \u884C\u5217\u3092\u8FD4\u3059\n  vector<vector<W>> adjacent_matrix(bool directed\
    \ = false) const {\n    vector<vector<W>> g(n, vector<W>(n, 0));\n    for (auto&\
    \ [u, v, w, _] : es) {\n      g[u][v] = w;\n      if (!directed) g[v][u] = w;\n\
    \    }\n    return g;\n  }\n\n  // \u30B0\u30E9\u30D5\u3092\u96A3\u63A5\u884C\u5217\
    \u306E\u5F62\u5F0F\u3067\u51FA\u529B\n  void print_matrix(ostream& os, bool directed\
    \ = false) const {\n    auto g = adjacent_matrix(directed);\n    for (int i =\
    \ 0; i < n; i++) {\n      for (int j = 0; j < n; j++) {\n        os << g[i][j]\
    \ << \" \\n\"[j == n - 1];\n      }\n    }\n  }\n\n  // \u30B0\u30E9\u30D5\u306E\
    \u8FBA\u60C5\u5831\u3092\u4E00\u822C\u7684\u306A\u5F62\u5F0F\u3067\u51FA\u529B\
    \n  void print_edge(ostream& os, bool origin_0 = false) const {\n    for (auto&\
    \ e : es) {\n      os << e.u + (origin_0 ? 0 : 1);\n      os << \" \" << e.v +\
    \ (origin_0 ? 0 : 1);\n      if (weighted) os << \" \" << e.w;\n      os << \"\
    \\n\";\n    }\n  }\n\n  // \u30B0\u30E9\u30D5\u3092\u4E00\u822C\u7684\u306A\u5F62\
    \u5F0F\u3067\u51FA\u529B\n  void print(ostream& os, bool origin_0 = false) const\
    \ {\n    os << n << \" \" << m << \"\\n\";\n    print_edge(os, origin_0);\n  }\n\
    \n  friend ostream& operator<<(ostream& os, const Graph& g) {\n    g.print(os);\n\
    \    return os;\n  }\n};\n#line 2 \"random_graph/random.hpp\"\n\n// SPDX-License-Identifier:\
    \ Apache-2.0\n// This file includes code derived from Library Checker Problems:\n\
    //   https://github.com/yosupo06/library-checker-problems/blob/1e3da4fd4135f4f3cb3a6d76b51c827f7d987942/common/random.h\n\
    //\n// The original work is licensed under the Apache License, Version 2.0.\n\
    //\n// Local modifications in this repository:\n// - Moved #pragma once to the\
    \ first line for oj-bundle compatibility.\n// - Made this header self-contained\
    \ by adding missing standard library\n//   includes and removing an unused include.\n\
    \n#line 17 \"random_graph/random.hpp\"\n#include <cstddef>\n#include <cstdint>\n\
    #line 21 \"random_graph/random.hpp\"\n#include <string>\n#include <utility>\n\
    #line 24 \"random_graph/random.hpp\"\n\nstruct Random {\n  private:\n    // Use\
    \ xoshiro256**\n    // References: http://xoshiro.di.unimi.it/xoshiro256starstar.c\n\
    \    static uint64_t rotl(const uint64_t x, int k) {\n        return (x << k)\
    \ | (x >> (64 - k));\n    }\n\n    std::array<uint64_t, 4> s;\n\n    uint64_t\
    \ next() {\n        const uint64_t result_starstar = rotl(s[1] * 5, 7) * 9;\n\n\
    \        const uint64_t t = s[1] << 17;\n\n        s[2] ^= s[0];\n        s[3]\
    \ ^= s[1];\n        s[1] ^= s[2];\n        s[0] ^= s[3];\n\n        s[2] ^= t;\n\
    \n        s[3] = rotl(s[3], 45);\n\n        return result_starstar;\n    }\n\n\
    \    // random choice from [0, upper]\n    uint64_t next(uint64_t upper) {\n \
    \       if (!(upper & (upper + 1))) {\n            // b = 00..0011..11\n     \
    \       return next() & upper;\n        }\n        int lg = 63 - __builtin_clzll(upper);\n\
    \        uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;\n      \
    \  while (true) {\n            uint64_t r = next() & mask;\n            if (r\
    \ <= upper)\n                return r;\n        }\n    }\n\n  public:\n    Random(uint64_t\
    \ seed = 0) {\n        // Use splitmix64\n        // Reference: http://xoshiro.di.unimi.it/splitmix64.c\n\
    \        for (int i = 0; i < 4; i++) {\n            uint64_t z = (seed += 0x9e3779b97f4a7c15);\n\
    \            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n            z = (z ^ (z\
    \ >> 27)) * 0x94d049bb133111eb;\n            s[i] = z ^ (z >> 31);\n        }\n\
    \    }\n\n    // random choice from [lower, upper]\n    template <class T>\n \
    \   T uniform(T lower, T upper) {\n        assert(lower <= upper);\n        return\
    \ T(lower + next(uint64_t(upper - lower)));\n    }\n\n    // random choice from\
    \ false or true\n    bool uniform_bool() { return uniform(0, 1) == 1; }\n\n  \
    \  // random choice from [0.0, 1.0]\n    double uniform01() {\n        uint64_t\
    \ v = next(1ULL << 63);\n        return double(v) / (1ULL << 63);\n    }\n\n \
    \   // random choice non-empty sub-interval from interval [lower, upper)\n   \
    \ // equal: random choice 2 disjoint elements from [lower, upper]\n    template\
    \ <class T>\n    std::pair<T, T> uniform_pair(T lower, T upper) {\n        assert(upper\
    \ - lower >= 1);\n        T a, b;\n        do {\n            a = uniform(lower,\
    \ upper);\n            b = uniform(lower, upper);\n        } while (a == b);\n\
    \        if (a > b) std::swap(a, b);\n        return {a, b};\n    }\n\n    //\
    \ generate random lower string that length = n\n    std::string lower_string(std::size_t\
    \ n) {\n        std::string res = \"\";\n        for (std::size_t i = 0; i < n;\
    \ i++) {\n            res += uniform('a', 'z');\n        }\n        return res;\n\
    \    }\n\n    // random shuffle\n    template <class Iter>\n    void shuffle(Iter\
    \ first, Iter last) {\n        if (first == last) return;\n        // Reference\
    \ and edit:\n        // cpprefjp - C++\u65E5\u672C\u8A9E\u30EA\u30D5\u30A1\u30EC\
    \u30F3\u30B9\n        // (https://cpprefjp.github.io/reference/algorithm/shuffle.html)\n\
    \        int len = 1;\n        for (auto it = first + 1; it != last; it++) {\n\
    \            len++;\n            int j = uniform(0, len - 1);\n            if\
    \ (j != len - 1)\n                iter_swap(it, first + j);\n        }\n    }\n\
    \n    // generate random permutation that length = n\n    template <class T>\n\
    \    std::vector<T> perm(std::size_t n) {\n        std::vector<T> idx(n);\n  \
    \      std::iota(idx.begin(), idx.end(), T(0));\n        shuffle(idx.begin(),\
    \ idx.end());\n        return idx;\n    }\n\n    // random choise n elements from\
    \ [lower, upper]\n    template <class T>\n    std::vector<T> choice(std::size_t\
    \ n, T lower, T upper) {\n        assert(T(n) <= upper - lower + 1);\n       \
    \ std::set<T> res;\n        while (res.size() < n) res.insert(uniform(lower, upper));\n\
    \        return {res.begin(), res.end()};\n    }\n} global_gen;\n#line 12 \"random_graph/gen.hpp\"\
    \n\n// \u30B8\u30A7\u30CD\u30EC\u30FC\u30BF\u672C\u4F53\nstruct UndirectedGraphGenerator\
    \ {\n private:\n  // \u4E71\u6570\u751F\u6210\u5668 (static\u30E1\u30F3\u30D0\u5909\
    \u6570\u306E\u4EE3\u308F\u308A)\n  Random& _gen() {\n    static Random gen{};\n\
    \    return gen;\n  }\n  // [l, r]\u4E0A\u306E\u4E00\u69D8\u4E71\u6570\u3092\u751F\
    \u6210\n  long long random(long long l, long long r) {\n    assert(l <= r && \"\
    UndirectedGraphGenerator::random(l, r)\");\n    return _gen().uniform(l, r);\n\
    \  }\n  // v\u3092\u30E9\u30F3\u30C0\u30E0\u306B\u30B7\u30E3\u30C3\u30D5\u30EB\
    \n  template <typename U>\n  void random_shuffle(vector<U>& v) {\n    _gen().shuffle(begin(v),\
    \ end(v));\n  }\n\n  W _w_min, _w_max;\n\n  // \u8FBA\u306E\u91CD\u307F\u3092\u8A2D\
    \u5B9A\n  void set_weight(bool weighted, W w_min, W w_max) {\n    _w_min = w_min,\
    \ _w_max = w_max;\n    if (!weighted) _w_min = _w_max = 1;\n  }\n\n  // \u8FBA\
    \u3092\u8FFD\u52A0\n  void add_edge(Graph& g, int i, int j) {\n    W w = _w_min\
    \ == _w_max ? _w_min : random(_w_min, _w_max);\n    g.add_undirected_edge(i, j,\
    \ w);\n  }\n\n  // \u4E71\u6570\u751F\u6210s\n  unsigned long long random_seed()\
    \ const {\n    unsigned long long seed =\n        chrono::duration_cast<chrono::nanoseconds>(\n\
    \            chrono::high_resolution_clock::now().time_since_epoch())\n      \
    \      .count();\n    return seed;\n  }\n\n public:\n  UndirectedGraphGenerator(unsigned\
    \ long long seed = 0) : _w_min(1), _w_max(1) {\n    if (seed == 0) seed = random_seed();\n\
    \    set_seed(seed);\n  }\n\n  // \u30B7\u30FC\u30C9\u3092\u8A2D\u5B9A\u3059\u308B\
    \n  void set_seed(unsigned long long seed) { _gen() = Random{seed ^ 1333uLL};\
    \ }\n\n  /**\n   * \u30E9\u30F3\u30C0\u30E0\u30B1\u30FC\u30B9\u751F\u6210\u7528\
    \u3002\n   *  \u6761\u4EF6\u3092\u6E80\u305F\u3059\u5168\u3066\u306E\u95A2\u6570\
    \u306E\u4E2D\u304B\u3089\u30E9\u30F3\u30C0\u30E0\u306B1\u3064\u3092\u9078\u3093\
    \u3067\u30B0\u30E9\u30D5\u3092\u751F\u6210\u3002\n   */\n  Graph test(int n, bool\
    \ is_tree = true, bool weighted = false, W w_min = 1,\n             W w_max =\
    \ 1) {\n    using F = Graph (UndirectedGraphGenerator::*)(int, bool, W, W);\n\
    \    vector<F> f{tree, path, star, perfect, simple, namori, simple_sparse};\n\
    \    int mx = is_tree ? 2 : 6;\n    return (this->*f[random(0, mx)])(n, weighted,\
    \ w_min, w_max);\n  }\n\n  // \u30E9\u30F3\u30C0\u30E0\u306A\u7121\u5411\u306E\
    \u6728\u3092\u51FA\u529B\n  Graph tree(int n, bool weighted = false, W w_min =\
    \ 1, W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    Graph g(n, weighted);\n\
    \    if (n == 2) add_edge(g, 0, 1);\n    if (n <= 2) return g;\n    vector<int>\
    \ code(n - 2), deg(n, 1);\n    for (auto& i : code) i = random(0, n - 1), deg[i]++;\n\
    \    set<int> js;\n    for (int j = 0; j < n; j++) {\n      if (deg[j] == 1) js.insert(j);\n\
    \    }\n    for (auto& i : code) {\n      int j = *js.begin();\n      add_edge(g,\
    \ i, j);\n      js.erase(begin(js));\n      if (--deg[i] == 1) js.insert(i);\n\
    \      deg[j]--;\n    }\n    int u = *js.begin(), v = *next(js.begin());\n   \
    \ add_edge(g, u, v);\n    assert(g.edges_size() == n - 1);\n    return g;\n  }\n\
    \n  // \u30E9\u30F3\u30C0\u30E0\u306A\u7121\u5411\u306E\u30D1\u30B9\u30B0\u30E9\
    \u30D5\u3092\u51FA\u529B\n  Graph path(int n, bool weighted = false, W w_min =\
    \ 1, W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    vector<int>\
    \ ord(n);\n    iota(begin(ord), end(ord), 0);\n    random_shuffle(ord);\n    Graph\
    \ g(n, weighted);\n    for (int i = 0; i < n - 1; i++) add_edge(g, ord[i], ord[i\
    \ + 1]);\n    return g;\n  }\n\n  // \u30E9\u30F3\u30C0\u30E0\u306A\u7121\u5411\
    \u306E\u30B9\u30BF\u30FC\u30B0\u30E9\u30D5\u3092\u51FA\u529B\n  Graph star(int\
    \ n, bool weighted = false, W w_min = 1, W w_max = 1) {\n    set_weight(weighted,\
    \ w_min, w_max);\n    vector<int> ord(n);\n    iota(begin(ord), end(ord), 0);\n\
    \    random_shuffle(ord);\n    Graph g(n, weighted);\n    for (int i = 1; i <\
    \ n; i++) add_edge(g, ord[0], ord[i]);\n    return g;\n  }\n\n  // \u5B8C\u5168\
    \u30B0\u30E9\u30D5\n  Graph perfect(int n, bool weighted = false, W w_min = 1,\
    \ W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    Graph g(n, weighted);\n\
    \    for (int i = 0; i < n; i++) {\n      for (int j = i + 1; j < n; j++) add_edge(g,\
    \ i, j);\n    }\n    return g;\n  }\n\n  // \u5358\u7D14\u30B0\u30E9\u30D5\n \
    \ Graph simple(int n, bool weighted = false, W w_min = 1, W w_max = 1) {\n   \
    \ set_weight(weighted, w_min, w_max);\n    Graph g(n, weighted);\n    for (int\
    \ i = 0; i < n; i++) {\n      for (int j = i + 1; j < n; j++) {\n        if (random(0,\
    \ 1) == 1) add_edge(g, i, j);\n      }\n    }\n    return g;\n  }\n\n  // \u306A\
    \u3082\u308A\u30B0\u30E9\u30D5\n  Graph namori(int n, bool weighted = false, W\
    \ w_min = 1, W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    Graph\
    \ g(n, weighted);\n    for (int i = 0; i < n; i++) {\n      if (i == 0) {\n  \
    \      add_edge(g, i, random(1, n - 1));\n      } else {\n        add_edge(g,\
    \ i, random(0, i - 1));\n      }\n    }\n    return g;\n  }\n\n  // \u758E\u306A\
    \u5358\u7D14\u30B0\u30E9\u30D5\n  Graph simple_sparse(int n, bool weighted = false,\
    \ W w_min = 1, W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    if\
    \ (n == 0) return Graph{};\n    int m = random(0, n - 1);\n    set<pair<int, int>>\
    \ es;\n    while ((int)es.size() < m) {\n      int i = random(0, n - 1);\n   \
    \   int j = random(0, n - 1);\n      if (i >= j) continue;\n      es.emplace(i,\
    \ j);\n    }\n    Graph g(n, weighted);\n    for (auto& [i, j] : es) add_edge(g,\
    \ i, j);\n    return g;\n  }\n} undirected;\n"
  code: "#pragma once\n\n#include <array>\n#include <cassert>\n#include <chrono>\n\
    #include <numeric>\n#include <set>\n#include <vector>\n\n#include \"graph.hpp\"\
    \n#include \"random.hpp\"\n\n// \u30B8\u30A7\u30CD\u30EC\u30FC\u30BF\u672C\u4F53\
    \nstruct UndirectedGraphGenerator {\n private:\n  // \u4E71\u6570\u751F\u6210\u5668\
    \ (static\u30E1\u30F3\u30D0\u5909\u6570\u306E\u4EE3\u308F\u308A)\n  Random& _gen()\
    \ {\n    static Random gen{};\n    return gen;\n  }\n  // [l, r]\u4E0A\u306E\u4E00\
    \u69D8\u4E71\u6570\u3092\u751F\u6210\n  long long random(long long l, long long\
    \ r) {\n    assert(l <= r && \"UndirectedGraphGenerator::random(l, r)\");\n  \
    \  return _gen().uniform(l, r);\n  }\n  // v\u3092\u30E9\u30F3\u30C0\u30E0\u306B\
    \u30B7\u30E3\u30C3\u30D5\u30EB\n  template <typename U>\n  void random_shuffle(vector<U>&\
    \ v) {\n    _gen().shuffle(begin(v), end(v));\n  }\n\n  W _w_min, _w_max;\n\n\
    \  // \u8FBA\u306E\u91CD\u307F\u3092\u8A2D\u5B9A\n  void set_weight(bool weighted,\
    \ W w_min, W w_max) {\n    _w_min = w_min, _w_max = w_max;\n    if (!weighted)\
    \ _w_min = _w_max = 1;\n  }\n\n  // \u8FBA\u3092\u8FFD\u52A0\n  void add_edge(Graph&\
    \ g, int i, int j) {\n    W w = _w_min == _w_max ? _w_min : random(_w_min, _w_max);\n\
    \    g.add_undirected_edge(i, j, w);\n  }\n\n  // \u4E71\u6570\u751F\u6210s\n\
    \  unsigned long long random_seed() const {\n    unsigned long long seed =\n \
    \       chrono::duration_cast<chrono::nanoseconds>(\n            chrono::high_resolution_clock::now().time_since_epoch())\n\
    \            .count();\n    return seed;\n  }\n\n public:\n  UndirectedGraphGenerator(unsigned\
    \ long long seed = 0) : _w_min(1), _w_max(1) {\n    if (seed == 0) seed = random_seed();\n\
    \    set_seed(seed);\n  }\n\n  // \u30B7\u30FC\u30C9\u3092\u8A2D\u5B9A\u3059\u308B\
    \n  void set_seed(unsigned long long seed) { _gen() = Random{seed ^ 1333uLL};\
    \ }\n\n  /**\n   * \u30E9\u30F3\u30C0\u30E0\u30B1\u30FC\u30B9\u751F\u6210\u7528\
    \u3002\n   *  \u6761\u4EF6\u3092\u6E80\u305F\u3059\u5168\u3066\u306E\u95A2\u6570\
    \u306E\u4E2D\u304B\u3089\u30E9\u30F3\u30C0\u30E0\u306B1\u3064\u3092\u9078\u3093\
    \u3067\u30B0\u30E9\u30D5\u3092\u751F\u6210\u3002\n   */\n  Graph test(int n, bool\
    \ is_tree = true, bool weighted = false, W w_min = 1,\n             W w_max =\
    \ 1) {\n    using F = Graph (UndirectedGraphGenerator::*)(int, bool, W, W);\n\
    \    vector<F> f{tree, path, star, perfect, simple, namori, simple_sparse};\n\
    \    int mx = is_tree ? 2 : 6;\n    return (this->*f[random(0, mx)])(n, weighted,\
    \ w_min, w_max);\n  }\n\n  // \u30E9\u30F3\u30C0\u30E0\u306A\u7121\u5411\u306E\
    \u6728\u3092\u51FA\u529B\n  Graph tree(int n, bool weighted = false, W w_min =\
    \ 1, W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    Graph g(n, weighted);\n\
    \    if (n == 2) add_edge(g, 0, 1);\n    if (n <= 2) return g;\n    vector<int>\
    \ code(n - 2), deg(n, 1);\n    for (auto& i : code) i = random(0, n - 1), deg[i]++;\n\
    \    set<int> js;\n    for (int j = 0; j < n; j++) {\n      if (deg[j] == 1) js.insert(j);\n\
    \    }\n    for (auto& i : code) {\n      int j = *js.begin();\n      add_edge(g,\
    \ i, j);\n      js.erase(begin(js));\n      if (--deg[i] == 1) js.insert(i);\n\
    \      deg[j]--;\n    }\n    int u = *js.begin(), v = *next(js.begin());\n   \
    \ add_edge(g, u, v);\n    assert(g.edges_size() == n - 1);\n    return g;\n  }\n\
    \n  // \u30E9\u30F3\u30C0\u30E0\u306A\u7121\u5411\u306E\u30D1\u30B9\u30B0\u30E9\
    \u30D5\u3092\u51FA\u529B\n  Graph path(int n, bool weighted = false, W w_min =\
    \ 1, W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    vector<int>\
    \ ord(n);\n    iota(begin(ord), end(ord), 0);\n    random_shuffle(ord);\n    Graph\
    \ g(n, weighted);\n    for (int i = 0; i < n - 1; i++) add_edge(g, ord[i], ord[i\
    \ + 1]);\n    return g;\n  }\n\n  // \u30E9\u30F3\u30C0\u30E0\u306A\u7121\u5411\
    \u306E\u30B9\u30BF\u30FC\u30B0\u30E9\u30D5\u3092\u51FA\u529B\n  Graph star(int\
    \ n, bool weighted = false, W w_min = 1, W w_max = 1) {\n    set_weight(weighted,\
    \ w_min, w_max);\n    vector<int> ord(n);\n    iota(begin(ord), end(ord), 0);\n\
    \    random_shuffle(ord);\n    Graph g(n, weighted);\n    for (int i = 1; i <\
    \ n; i++) add_edge(g, ord[0], ord[i]);\n    return g;\n  }\n\n  // \u5B8C\u5168\
    \u30B0\u30E9\u30D5\n  Graph perfect(int n, bool weighted = false, W w_min = 1,\
    \ W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    Graph g(n, weighted);\n\
    \    for (int i = 0; i < n; i++) {\n      for (int j = i + 1; j < n; j++) add_edge(g,\
    \ i, j);\n    }\n    return g;\n  }\n\n  // \u5358\u7D14\u30B0\u30E9\u30D5\n \
    \ Graph simple(int n, bool weighted = false, W w_min = 1, W w_max = 1) {\n   \
    \ set_weight(weighted, w_min, w_max);\n    Graph g(n, weighted);\n    for (int\
    \ i = 0; i < n; i++) {\n      for (int j = i + 1; j < n; j++) {\n        if (random(0,\
    \ 1) == 1) add_edge(g, i, j);\n      }\n    }\n    return g;\n  }\n\n  // \u306A\
    \u3082\u308A\u30B0\u30E9\u30D5\n  Graph namori(int n, bool weighted = false, W\
    \ w_min = 1, W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    Graph\
    \ g(n, weighted);\n    for (int i = 0; i < n; i++) {\n      if (i == 0) {\n  \
    \      add_edge(g, i, random(1, n - 1));\n      } else {\n        add_edge(g,\
    \ i, random(0, i - 1));\n      }\n    }\n    return g;\n  }\n\n  // \u758E\u306A\
    \u5358\u7D14\u30B0\u30E9\u30D5\n  Graph simple_sparse(int n, bool weighted = false,\
    \ W w_min = 1, W w_max = 1) {\n    set_weight(weighted, w_min, w_max);\n    if\
    \ (n == 0) return Graph{};\n    int m = random(0, n - 1);\n    set<pair<int, int>>\
    \ es;\n    while ((int)es.size() < m) {\n      int i = random(0, n - 1);\n   \
    \   int j = random(0, n - 1);\n      if (i >= j) continue;\n      es.emplace(i,\
    \ j);\n    }\n    Graph g(n, weighted);\n    for (auto& [i, j] : es) add_edge(g,\
    \ i, j);\n    return g;\n  }\n} undirected;\n"
  dependsOn:
  - random_graph/graph.hpp
  - random_graph/random.hpp
  isVerificationFile: false
  path: random_graph/gen.hpp
  requiredBy: []
  timestamp: '2026-06-09 10:27:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: random_graph/gen.hpp
layout: document
redirect_from:
- /library/random_graph/gen.hpp
- /library/random_graph/gen.hpp.html
title: random_graph/gen.hpp
---
