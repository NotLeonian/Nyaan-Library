---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph-template.hpp
    title: "\u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8"
  - icon: ':heavy_check_mark:'
    path: tree/convert-tree.hpp
    title: "\u6839\u4ED8\u304D\u6728\u30FB\u9006\u8FBA\u304B\u3089\u306A\u308B\u6728\
      \u3078\u306E\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: tree/heavy-light-decomposition.hpp
    title: "Heavy Light Decomposition(\u91CD\u8EFD\u5206\u89E3)"
  - icon: ':heavy_check_mark:'
    path: tree/static-top-tree-vertex-based.hpp
    title: Static Top Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-unit-test/dynamic-diameter-faster.test.cpp
    title: verify/verify-unit-test/dynamic-diameter-faster.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tree/dynamic-diameter-faster.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\nusing namespace std;\n\
    \n#line 2 \"graph/graph-template.hpp\"\n\ntemplate <typename T>\nstruct edge {\n\
    \  int src, to;\n  T cost;\n\n  edge(int _to, T _cost) : src(-1), to(_to), cost(_cost)\
    \ {}\n  edge(int _src, int _to, T _cost) : src(_src), to(_to), cost(_cost) {}\n\
    \n  edge &operator=(const int &x) {\n    to = x;\n    return *this;\n  }\n\n \
    \ operator int() const { return to; }\n};\ntemplate <typename T>\nusing Edges\
    \ = vector<edge<T>>;\ntemplate <typename T>\nusing WeightedGraph = vector<Edges<T>>;\n\
    using UnweightedGraph = vector<vector<int>>;\n\n// Input of (Unweighted) Graph\n\
    UnweightedGraph graph(int N, int M = -1, bool is_directed = false,\n         \
    \             bool is_1origin = true) {\n  UnweightedGraph g(N);\n  if (M == -1)\
    \ M = N - 1;\n  for (int _ = 0; _ < M; _++) {\n    int x, y;\n    cin >> x >>\
    \ y;\n    if (is_1origin) x--, y--;\n    g[x].push_back(y);\n    if (!is_directed)\
    \ g[y].push_back(x);\n  }\n  return g;\n}\n\n// Input of Weighted Graph\ntemplate\
    \ <typename T>\nWeightedGraph<T> wgraph(int N, int M = -1, bool is_directed =\
    \ false,\n                        bool is_1origin = true) {\n  WeightedGraph<T>\
    \ g(N);\n  if (M == -1) M = N - 1;\n  for (int _ = 0; _ < M; _++) {\n    int x,\
    \ y;\n    cin >> x >> y;\n    T c;\n    cin >> c;\n    if (is_1origin) x--, y--;\n\
    \    g[x].emplace_back(x, y, c);\n    if (!is_directed) g[y].emplace_back(y, x,\
    \ c);\n  }\n  return g;\n}\n\n// Input of Edges\ntemplate <typename T>\nEdges<T>\
    \ esgraph([[maybe_unused]] int N, int M, int is_weighted = true,\n           \
    \      bool is_1origin = true) {\n  Edges<T> es;\n  for (int _ = 0; _ < M; _++)\
    \ {\n    int x, y;\n    cin >> x >> y;\n    T c;\n    if (is_weighted)\n     \
    \ cin >> c;\n    else\n      c = 1;\n    if (is_1origin) x--, y--;\n    es.emplace_back(x,\
    \ y, c);\n  }\n  return es;\n}\n\n// Input of Adjacency Matrix\ntemplate <typename\
    \ T>\nvector<vector<T>> adjgraph(int N, int M, T INF, int is_weighted = true,\n\
    \                           bool is_directed = false, bool is_1origin = true)\
    \ {\n  vector<vector<T>> d(N, vector<T>(N, INF));\n  for (int _ = 0; _ < M; _++)\
    \ {\n    int x, y;\n    cin >> x >> y;\n    T c;\n    if (is_weighted)\n     \
    \ cin >> c;\n    else\n      c = 1;\n    if (is_1origin) x--, y--;\n    d[x][y]\
    \ = c;\n    if (!is_directed) d[y][x] = c;\n  }\n  return d;\n}\n\n/**\n * @brief\
    \ \u30B0\u30E9\u30D5\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8\n * @docs docs/graph/graph-template.md\n\
    \ */\n#line 2 \"tree/static-top-tree-vertex-based.hpp\"\n\n#line 4 \"tree/static-top-tree-vertex-based.hpp\"\
    \n#include <functional>\n#line 7 \"tree/static-top-tree-vertex-based.hpp\"\nusing\
    \ namespace std;\n\n#line 2 \"tree/convert-tree.hpp\"\n\n#line 4 \"tree/convert-tree.hpp\"\
    \n\ntemplate <typename T>\nstruct has_cost {\n private:\n  template <typename\
    \ U>\n  static auto confirm(U u) -> decltype(u.cost, std::true_type());\n  static\
    \ auto confirm(...) -> std::false_type;\n\n public:\n  enum : bool { value = decltype(confirm(std::declval<T>()))::value\
    \ };\n};\n\ntemplate <typename T>\nvector<vector<T>> inverse_tree(const vector<vector<T>>&\
    \ g) {\n  int N = (int)g.size();\n  vector<vector<T>> rg(N);\n  for (int i = 0;\
    \ i < N; i++) {\n    for (auto& e : g[i]) {\n      if constexpr (is_same<T, int>::value)\
    \ {\n        rg[e].push_back(i);\n      } else if constexpr (has_cost<T>::value)\
    \ {\n        rg[e].emplace_back(e.to, i, e.cost);\n      } else {\n        assert(0);\n\
    \      }\n    }\n  }\n  return rg;\n}\n\ntemplate <typename T>\nvector<vector<T>>\
    \ rooted_tree(const vector<vector<T>>& g, int root = 0) {\n  int N = (int)g.size();\n\
    \  vector<vector<T>> rg(N);\n  vector<char> v(N, false);\n  v[root] = true;\n\
    \  queue<int> que;\n  que.emplace(root);\n  while (!que.empty()) {\n    auto p\
    \ = que.front();\n    que.pop();\n    for (auto& e : g[p]) {\n      if (v[e] ==\
    \ false) {\n        v[e] = true;\n        que.push(e);\n        rg[p].push_back(e);\n\
    \      }\n    }\n  }\n  return rg;\n}\n\n/**\n * @brief \u6839\u4ED8\u304D\u6728\
    \u30FB\u9006\u8FBA\u304B\u3089\u306A\u308B\u6728\u3078\u306E\u5909\u63DB\n */\n\
    #line 2 \"tree/heavy-light-decomposition.hpp\"\n\n#line 4 \"tree/heavy-light-decomposition.hpp\"\
    \n\ntemplate <typename G>\nstruct HeavyLightDecomposition {\n private:\n  void\
    \ dfs_sz(int cur) {\n    size[cur] = 1;\n    for (auto& dst : g[cur]) {\n    \
    \  if (dst == par[cur]) {\n        if (g[cur].size() >= 2 && int(dst) == int(g[cur][0]))\n\
    \          swap(g[cur][0], g[cur][1]);\n        else\n          continue;\n  \
    \    }\n      depth[dst] = depth[cur] + 1;\n      par[dst] = cur;\n      dfs_sz(dst);\n\
    \      size[cur] += size[dst];\n      if (size[dst] > size[g[cur][0]]) {\n   \
    \     swap(dst, g[cur][0]);\n      }\n    }\n  }\n\n  void dfs_hld(int cur) {\n\
    \    down[cur] = id++;\n    for (auto dst : g[cur]) {\n      if (dst == par[cur])\
    \ continue;\n      nxt[dst] = (int(dst) == int(g[cur][0]) ? nxt[cur] : int(dst));\n\
    \      dfs_hld(dst);\n    }\n    up[cur] = id;\n  }\n\n  // [u, v)\n  vector<pair<int,\
    \ int>> ascend(int u, int v) const {\n    vector<pair<int, int>> res;\n    while\
    \ (nxt[u] != nxt[v]) {\n      res.emplace_back(down[u], down[nxt[u]]);\n     \
    \ u = par[nxt[u]];\n    }\n    if (u != v) res.emplace_back(down[u], down[v] +\
    \ 1);\n    return res;\n  }\n\n  // (u, v]\n  vector<pair<int, int>> descend(int\
    \ u, int v) const {\n    if (u == v) return {};\n    if (nxt[u] == nxt[v]) return\
    \ {{down[u] + 1, down[v]}};\n    auto res = descend(u, par[nxt[v]]);\n    res.emplace_back(down[nxt[v]],\
    \ down[v]);\n    return res;\n  }\n\n public:\n  G& g;\n  int root, id;\n  vector<int>\
    \ size, depth, down, up, nxt, par;\n  HeavyLightDecomposition(G& _g, int _root\
    \ = 0)\n      : g(_g),\n        root(_root),\n        id(0),\n        size(g.size(),\
    \ 0),\n        depth(g.size(), 0),\n        down(g.size(), -1),\n        up(g.size(),\
    \ -1),\n        nxt(g.size(), root),\n        par(g.size(), root) {\n    dfs_sz(root);\n\
    \    dfs_hld(root);\n  }\n\n  pair<int, int> idx(int i) const { return make_pair(down[i],\
    \ up[i]); }\n\n  template <typename F>\n  void path_query(int u, int v, bool vertex,\
    \ const F& f) {\n    int l = lca(u, v);\n    for (auto&& [a, b] : ascend(u, l))\
    \ {\n      int s = a + 1, t = b;\n      s > t ? f(t, s) : f(s, t);\n    }\n  \
    \  if (vertex) f(down[l], down[l] + 1);\n    for (auto&& [a, b] : descend(l, v))\
    \ {\n      int s = a, t = b + 1;\n      s > t ? f(t, s) : f(s, t);\n    }\n  }\n\
    \n  template <typename F>\n  void path_noncommutative_query(int u, int v, bool\
    \ vertex, const F& f) {\n    int l = lca(u, v);\n    for (auto&& [a, b] : ascend(u,\
    \ l)) f(a + 1, b);\n    if (vertex) f(down[l], down[l] + 1);\n    for (auto&&\
    \ [a, b] : descend(l, v)) f(a, b + 1);\n  }\n\n  template <typename F>\n  void\
    \ subtree_query(int u, bool vertex, const F& f) {\n    f(down[u] + int(!vertex),\
    \ up[u]);\n  }\n\n  int lca(int a, int b) {\n    while (nxt[a] != nxt[b]) {\n\
    \      if (down[a] < down[b]) swap(a, b);\n      a = par[nxt[a]];\n    }\n   \
    \ return depth[a] < depth[b] ? a : b;\n  }\n\n  int dist(int a, int b) { return\
    \ depth[a] + depth[b] - depth[lca(a, b)] * 2; }\n};\n\n/**\n * @brief Heavy Light\
    \ Decomposition(\u91CD\u8EFD\u5206\u89E3)\n * @docs docs/tree/heavy-light-decomposition.md\n\
    \ */\n#line 11 \"tree/static-top-tree-vertex-based.hpp\"\n\nnamespace StaticTopTreeVertexBasedImpl\
    \ {\n\nenum Type { Vertex, Compress, Rake, Add_Edge, Add_Vertex };\n\ntemplate\
    \ <typename G>\nstruct StaticTopTreeVertexBased {\n  const HeavyLightDecomposition<G>&\
    \ hld;\n  vector<vector<int>> g;\n  int root;     // \u5143\u306E\u6728\u306E\
    \ root\n  int tt_root;  // top tree \u306E root\n  vector<int> P, L, R;\n  vector<Type>\
    \ T;\n\n  StaticTopTreeVertexBased(const HeavyLightDecomposition<G>& _hld) : hld(_hld)\
    \ {\n    root = hld.root;\n    g = rooted_tree(hld.g, root);\n    int n = g.size();\n\
    \    P.resize(n, -1), L.resize(n, -1), R.resize(n, -1);\n    T.resize(n, Type::Vertex);\n\
    \    build();\n  }\n\n private:\n  int add(int l, int r, Type t) {\n    if (t\
    \ == Type::Compress or t == Type::Rake) {\n      assert(l != -1 and r != -1);\n\
    \    }\n    if (t == Type::Add_Edge) {\n      assert(l != -1 and r == -1);\n \
    \   }\n    assert(t != Type::Vertex and t != Type::Add_Vertex);\n    int k = P.size();\n\
    \    P.push_back(-1), L.push_back(l), R.push_back(r), T.push_back(t);\n    if\
    \ (l != -1) P[l] = k;\n    if (r != -1) P[r] = k;\n    return k;\n  }\n  int add2(int\
    \ k, int l, int r, Type t) {\n    assert(k < (int)g.size());\n    assert(t ==\
    \ Type::Vertex or t == Type::Add_Vertex);\n    if (t == Type::Vertex) {\n    \
    \  assert(l == -1 and r == -1);\n    } else {\n      assert(l != -1 and r == -1);\n\
    \    }\n    P[k] = -1, L[k] = l, R[k] = r, T[k] = t;\n    if (l != -1) P[l] =\
    \ k;\n    if (r != -1) P[r] = k;\n    return k;\n  }\n  pair<int, int> merge(const\
    \ vector<pair<int, int>>& a, Type t) {\n    assert(!a.empty());\n    if (a.size()\
    \ == 1) return a[0];\n    int sum_s = 0;\n    for (auto& [_, s] : a) sum_s +=\
    \ s;\n    vector<pair<int, int>> b, c;\n    for (auto& [i, s] : a) {\n      (sum_s\
    \ > s ? b : c).emplace_back(i, s);\n      sum_s -= s * 2;\n    }\n    auto [i,\
    \ si] = merge(b, t);\n    auto [j, sj] = merge(c, t);\n    return {add(i, j, t),\
    \ si + sj};\n  }\n  pair<int, int> compress(int i) {\n    vector<pair<int, int>>\
    \ chs;\n    while (true) {\n      chs.push_back(add_vertex(i));\n      if (g[i].empty())\
    \ break;\n      i = g[i][0];\n    }\n    return merge(chs, Type::Compress);\n\
    \  }\n  pair<int, int> rake(int i) {\n    vector<pair<int, int>> chs;\n    for\
    \ (int j = 1; j < (int)g[i].size(); j++) chs.push_back(add_edge(g[i][j]));\n \
    \   if (chs.empty()) return {-1, 0};\n    return merge(chs, Type::Rake);\n  }\n\
    \  pair<int, int> add_edge(int i) {\n    auto [j, sj] = compress(i);\n    return\
    \ {add(j, -1, Type::Add_Edge), sj};\n  }\n  pair<int, int> add_vertex(int i) {\n\
    \    auto [j, sj] = rake(i);\n    return {add2(i, j, -1, j == -1 ? Type::Vertex\
    \ : Type::Add_Vertex), sj + 1};\n  }\n  void build() {\n    auto [i, n] = compress(root);\n\
    \    assert((int)g.size() == n);\n    tt_root = i;\n  }\n};\n\ntemplate <typename\
    \ G, typename Path, typename Point, typename Vertex,\n          typename Compress,\
    \ typename Rake, typename Add_edge,\n          typename Add_vertex>\nstruct DPonStaticTopTreeVertexBased\
    \ {\n  const StaticTopTreeVertexBased<G> tt;\n  vector<Path> path;\n  vector<Point>\
    \ point;\n  Vertex vertex;\n  Compress compress;\n  Rake rake;\n  Add_edge add_edge;\n\
    \  Add_vertex add_vertex;\n\n  DPonStaticTopTreeVertexBased(const HeavyLightDecomposition<G>&\
    \ hld,\n                               const Vertex& _vertex, const Compress&\
    \ _compress,\n                               const Rake& _rake, const Add_edge&\
    \ _add_edge,\n                               const Add_vertex& _add_vertex)\n\
    \      : tt(hld),\n        vertex(_vertex),\n        compress(_compress),\n  \
    \      rake(_rake),\n        add_edge(_add_edge),\n        add_vertex(_add_vertex)\
    \ {\n    int n = tt.P.size();\n    path.resize(n), point.resize(n);\n    dfs(tt.tt_root);\n\
    \  }\n\n  Path get() { return path[tt.tt_root]; }\n  void update(int k) {\n  \
    \  while (k != -1) _update(k), k = tt.P[k];\n  }\n\n private:\n  void _update(int\
    \ k) {\n    if (tt.T[k] == Type::Vertex) {\n      path[k] = std::invoke(vertex,\
    \ k);\n    } else if (tt.T[k] == Type::Compress) {\n      path[k] = std::invoke(compress,\
    \ path[tt.L[k]], path[tt.R[k]]);\n    } else if (tt.T[k] == Type::Rake) {\n  \
    \    point[k] = std::invoke(rake, point[tt.L[k]], point[tt.R[k]]);\n    } else\
    \ if (tt.T[k] == Type::Add_Edge) {\n      point[k] = std::invoke(add_edge, path[tt.L[k]]);\n\
    \    } else {\n      path[k] = std::invoke(add_vertex, point[tt.L[k]], k);\n \
    \   }\n  }\n\n  void dfs(int k) {\n    if (tt.L[k] != -1) dfs(tt.L[k]);\n    if\
    \ (tt.R[k] != -1) dfs(tt.R[k]);\n    _update(k);\n  }\n};\n\n}  // namespace StaticTopTreeVertexBasedImpl\n\
    \nusing StaticTopTreeVertexBasedImpl::DPonStaticTopTreeVertexBased;\nusing StaticTopTreeVertexBasedImpl::StaticTopTreeVertexBased;\n\
    \n/*\n\n  // template\n  using Path = ;\n  using Point = ;\n  auto vertex = [&](int\
    \ i) -> Path {\n\n  };\n  auto compress = [&](const Path& p, const Path& c) ->\
    \ Path {\n\n  };\n  auto rake = [&](const Point& a, const Point& b) -> Point {\n\
    \n  };\n  auto add_edge = [&](const Path& a) -> Point {\n\n  };\n  auto add_vertex\
    \ = [&](const Point& a, int i) -> Path {\n\n  };\n  HeavyLightDecomposition hld{g};\n\
    \  DPonStaticTopTreeVertexBased<vector<vector<int>>, Path, Point,\n  decltype(vertex),\
    \ decltype(compress), decltype(rake), decltype(add_edge),\n                  \
    \  decltype(add_vertex)>\n      dp(hld, vertex, compress, rake, add_edge, add_vertex);\n\
    */\n\n/**\n * @brief Static Top Tree\n */\n#line 11 \"tree/dynamic-diameter-faster.hpp\"\
    \n\nnamespace DynamicDiameterFasterImpl {\n\ntemplate <typename T>\nstruct HalfPath\
    \ {\n  T d;\n  int u;\n  friend HalfPath max(const HalfPath& lhs, const HalfPath&\
    \ rhs) {\n    if (lhs.d != rhs.d) return lhs.d > rhs.d ? lhs : rhs;\n    return\
    \ lhs.u > rhs.u ? lhs : rhs;\n  }\n};\ntemplate <typename T>\nstruct Path {\n\
    \  T d;\n  int u, v;\n  friend Path max(const Path& lhs, const Path& rhs) {\n\
    \    if (lhs.d != rhs.d) return lhs.d > rhs.d ? lhs : rhs;\n    if (lhs.u != rhs.u)\
    \ return lhs.u > rhs.u ? lhs : rhs;\n    return lhs.v > rhs.v ? lhs : rhs;\n \
    \ }\n};\ntemplate <typename T>\nPath<T> path(T d, int u, int v) {\n  if (u < v)\
    \ swap(u, v);\n  return {d, u, v};\n}\n\ntemplate <typename T>\nstruct L {\n \
    \ Path<T> dia;\n  HalfPath<T> d1, d2;\n};\ntemplate <typename T>\nstruct H {\n\
    \  Path<T> dia;\n  HalfPath<T> pd, cd;\n  T p_to_c;\n  int p, c;\n};\n\ntemplate\
    \ <typename T>\nH<T> vertex(int i) {\n  H<T> r;\n  r.dia = path<T>(0, i, i);\n\
    \  r.pd = r.cd = {0, i};\n  r.p_to_c = 0;\n  r.p = r.c = i;\n  return r;\n}\n\n\
    template <typename T>\nstruct RootedEdgeInfo {\n  int N, root;\n  vector<int>\
    \ par, depth;\n  vector<T> cost_to_parent;\n\n  RootedEdgeInfo() = default;\n\n\
    \  RootedEdgeInfo(const WeightedGraph<T>& g, int r = 0)\n      : N((int)g.size()),\n\
    \        root(r),\n        par(N, -2),\n        depth(N, 0),\n        cost_to_parent(N,\
    \ T{}) {\n    vector<int> st;\n    st.push_back(root);\n    par[root] = -1;\n\n\
    \    for (int it = 0; it < (int)st.size(); it++) {\n      int v = st[it];\n  \
    \    for (auto& e : g[v]) {\n        if (e.to == par[v]) continue;\n        if\
    \ (par[e.to] != -2) continue;\n        par[e.to] = v;\n        depth[e.to] = depth[v]\
    \ + 1;\n        cost_to_parent[e.to] = e.cost;\n        st.push_back(e.to);\n\
    \      }\n    }\n    assert((int)st.size() == N);\n  }\n\n  int child_if_adjacent(int\
    \ u, int v) const {\n    if (par[u] == v) return u;\n    if (par[v] == u) return\
    \ v;\n    return -1;\n  }\n\n  int parent_if_adjacent(int u, int v) const {\n\
    \    int c = child_if_adjacent(u, v);\n    if (c == -1) return -1;\n    return\
    \ u ^ v ^ c;\n  }\n\n  bool adjacent(int u, int v) const { return child_if_adjacent(u,\
    \ v) != -1; }\n\n  T get_parent_edge(int child) const {\n    assert(child != root);\n\
    \    return cost_to_parent[child];\n  }\n\n  T get_between_adjacent(int u, int\
    \ v) const {\n    int c = child_if_adjacent(u, v);\n    assert(c != -1);\n   \
    \ return cost_to_parent[c];\n  }\n\n  void set_between_adjacent(int u, int v,\
    \ T x) {\n    int c = child_if_adjacent(u, v);\n    assert(c != -1);\n    cost_to_parent[c]\
    \ = x;\n  }\n};\n\ntemplate <typename T>\nvector<vector<int>> to_unweighted(const\
    \ WeightedGraph<T>& g) {\n  int n = (int)g.size();\n  vector<vector<int>> res(n);\n\
    \  for (int i = 0; i < n; i++) {\n    for (auto& e : g[i]) res[i].push_back(e.to);\n\
    \  }\n  return res;\n}\n\ntemplate <typename T>\nH<T> compress(const H<T>& p,\
    \ const H<T>& c, T w) {\n  H<T> r;\n  r.dia = max(max(p.dia, c.dia),\n       \
    \       path<T>(p.cd.d + w + c.pd.d, p.cd.u, c.pd.u));\n  r.pd = max(p.pd, HalfPath<T>{p.p_to_c\
    \ + w + c.pd.d, c.pd.u});\n  r.cd = max(c.cd, HalfPath<T>{c.p_to_c + w + p.cd.d,\
    \ p.cd.u});\n  r.p_to_c = p.p_to_c + w + c.p_to_c;\n  r.p = p.p;\n  r.c = c.c;\n\
    \  return r;\n}\n\ntemplate <typename T>\nL<T> rake(const L<T>& a, const L<T>&\
    \ b) {\n  L<T> r;\n  r.dia = max(a.dia, b.dia);\n\n  vector<HalfPath<T>> xs;\n\
    \  for (auto x : {a.d1, a.d2, b.d1, b.d2}) {\n    if (x.u != -1) xs.push_back(x);\n\
    \  }\n  assert(!xs.empty());\n\n  sort(xs.begin(), xs.end(), [](const HalfPath<T>&\
    \ x, const HalfPath<T>& y) {\n    if (x.d != y.d) return x.d > y.d;\n    return\
    \ x.u > y.u;\n  });\n\n  r.d1 = xs[0];\n  r.d2 = xs.size() >= 2 ? xs[1] : HalfPath<T>{0,\
    \ -1};\n  return r;\n}\n\ntemplate <typename T>\nL<T> add_edge(const H<T>& a,\
    \ T w) {\n  L<T> r;\n  r.dia = a.dia;\n  r.d1 = {w + a.pd.d, a.pd.u};\n  r.d2\
    \ = {0, -1};\n  return r;\n}\n\ntemplate <typename T>\nH<T> add_vertex(const L<T>&\
    \ a, int i) {\n  H<T> r;\n  r.dia = max(a.dia, path<T>(a.d1.d, a.d1.u, i));\n\
    \  if (a.d2.u != -1) {\n    r.dia = max(r.dia, path<T>(a.d1.d + a.d2.d, a.d1.u,\
    \ a.d2.u));\n  }\n  r.pd = r.cd = max(HalfPath<T>{0, i}, a.d1);\n  r.p_to_c =\
    \ 0;\n  r.p = r.c = i;\n  return r;\n}\n\ntemplate <typename T>\nstruct DynamicDiameter\
    \ {\n  const WeightedGraph<T>& g;\n  int n;\n  vector<vector<int>> tree;\n  RootedEdgeInfo<T>\
    \ edge;\n  HeavyLightDecomposition<vector<vector<int>>> hld;\n\n  struct VertexOp\
    \ {\n    H<T> operator()(int i) const { return DynamicDiameterFasterImpl::vertex<T>(i);\
    \ }\n  };\n  struct CompressOp {\n    DynamicDiameter* self;\n    H<T> operator()(const\
    \ H<T>& p, const H<T>& c) const {\n      return DynamicDiameterFasterImpl::compress<T>(\n\
    \          p, c, self->edge.get_between_adjacent(p.c, c.p));\n    }\n  };\n  struct\
    \ RakeOp {\n    L<T> operator()(const L<T>& a, const L<T>& b) const {\n      return\
    \ DynamicDiameterFasterImpl::rake<T>(a, b);\n    }\n  };\n  struct AddEdgeOp {\n\
    \    DynamicDiameter* self;\n    L<T> operator()(const H<T>& a) const {\n    \
    \  return DynamicDiameterFasterImpl::add_edge<T>(\n          a, self->edge.get_parent_edge(a.p));\n\
    \    }\n  };\n  struct AddVertexOp {\n    H<T> operator()(const L<T>& a, int i)\
    \ const {\n      return DynamicDiameterFasterImpl::add_vertex<T>(a, i);\n    }\n\
    \  };\n\n  using DP = DPonStaticTopTreeVertexBased<vector<vector<int>>, H<T>,\
    \ L<T>,\n                                          VertexOp, CompressOp, RakeOp,\n\
    \                                          AddEdgeOp, AddVertexOp>;\n  DP dp;\n\
    \n  DynamicDiameter(const WeightedGraph<T>& _g, int root = 0)\n      : g(_g),\n\
    \        n((int)g.size()),\n        tree(to_unweighted(g)),\n        edge(g, root),\n\
    \        hld(tree, root),\n        dp(hld, VertexOp{}, CompressOp{this}, RakeOp{},\
    \ AddEdgeOp{this},\n           AddVertexOp{}) {}\n\n  pair<T, pair<int, int>>\
    \ get() {\n    auto [d, u, v] = dp.get().dia;\n    return make_pair(d, make_pair(u,\
    \ v));\n  }\n\n  bool adjacent(int u, int v) const { return edge.adjacent(u, v);\
    \ }\n\n  int child_if_adjacent(int u, int v) const {\n    return edge.child_if_adjacent(u,\
    \ v);\n  }\n\n  int parent_if_adjacent(int u, int v) const {\n    return edge.parent_if_adjacent(u,\
    \ v);\n  }\n\n  void update(int u, int v, T x) {\n    int c = edge.child_if_adjacent(u,\
    \ v);\n    assert(c != -1);\n    edge.cost_to_parent[c] = x;\n    dp.update(c);\n\
    \  }\n};\n}  // namespace DynamicDiameterFasterImpl\n\nusing DynamicDiameterFasterImpl::DynamicDiameter;\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\nusing namespace std;\n\n#include \"../graph/graph-template.hpp\"\
    \n#include \"static-top-tree-vertex-based.hpp\"\n\nnamespace DynamicDiameterFasterImpl\
    \ {\n\ntemplate <typename T>\nstruct HalfPath {\n  T d;\n  int u;\n  friend HalfPath\
    \ max(const HalfPath& lhs, const HalfPath& rhs) {\n    if (lhs.d != rhs.d) return\
    \ lhs.d > rhs.d ? lhs : rhs;\n    return lhs.u > rhs.u ? lhs : rhs;\n  }\n};\n\
    template <typename T>\nstruct Path {\n  T d;\n  int u, v;\n  friend Path max(const\
    \ Path& lhs, const Path& rhs) {\n    if (lhs.d != rhs.d) return lhs.d > rhs.d\
    \ ? lhs : rhs;\n    if (lhs.u != rhs.u) return lhs.u > rhs.u ? lhs : rhs;\n  \
    \  return lhs.v > rhs.v ? lhs : rhs;\n  }\n};\ntemplate <typename T>\nPath<T>\
    \ path(T d, int u, int v) {\n  if (u < v) swap(u, v);\n  return {d, u, v};\n}\n\
    \ntemplate <typename T>\nstruct L {\n  Path<T> dia;\n  HalfPath<T> d1, d2;\n};\n\
    template <typename T>\nstruct H {\n  Path<T> dia;\n  HalfPath<T> pd, cd;\n  T\
    \ p_to_c;\n  int p, c;\n};\n\ntemplate <typename T>\nH<T> vertex(int i) {\n  H<T>\
    \ r;\n  r.dia = path<T>(0, i, i);\n  r.pd = r.cd = {0, i};\n  r.p_to_c = 0;\n\
    \  r.p = r.c = i;\n  return r;\n}\n\ntemplate <typename T>\nstruct RootedEdgeInfo\
    \ {\n  int N, root;\n  vector<int> par, depth;\n  vector<T> cost_to_parent;\n\n\
    \  RootedEdgeInfo() = default;\n\n  RootedEdgeInfo(const WeightedGraph<T>& g,\
    \ int r = 0)\n      : N((int)g.size()),\n        root(r),\n        par(N, -2),\n\
    \        depth(N, 0),\n        cost_to_parent(N, T{}) {\n    vector<int> st;\n\
    \    st.push_back(root);\n    par[root] = -1;\n\n    for (int it = 0; it < (int)st.size();\
    \ it++) {\n      int v = st[it];\n      for (auto& e : g[v]) {\n        if (e.to\
    \ == par[v]) continue;\n        if (par[e.to] != -2) continue;\n        par[e.to]\
    \ = v;\n        depth[e.to] = depth[v] + 1;\n        cost_to_parent[e.to] = e.cost;\n\
    \        st.push_back(e.to);\n      }\n    }\n    assert((int)st.size() == N);\n\
    \  }\n\n  int child_if_adjacent(int u, int v) const {\n    if (par[u] == v) return\
    \ u;\n    if (par[v] == u) return v;\n    return -1;\n  }\n\n  int parent_if_adjacent(int\
    \ u, int v) const {\n    int c = child_if_adjacent(u, v);\n    if (c == -1) return\
    \ -1;\n    return u ^ v ^ c;\n  }\n\n  bool adjacent(int u, int v) const { return\
    \ child_if_adjacent(u, v) != -1; }\n\n  T get_parent_edge(int child) const {\n\
    \    assert(child != root);\n    return cost_to_parent[child];\n  }\n\n  T get_between_adjacent(int\
    \ u, int v) const {\n    int c = child_if_adjacent(u, v);\n    assert(c != -1);\n\
    \    return cost_to_parent[c];\n  }\n\n  void set_between_adjacent(int u, int\
    \ v, T x) {\n    int c = child_if_adjacent(u, v);\n    assert(c != -1);\n    cost_to_parent[c]\
    \ = x;\n  }\n};\n\ntemplate <typename T>\nvector<vector<int>> to_unweighted(const\
    \ WeightedGraph<T>& g) {\n  int n = (int)g.size();\n  vector<vector<int>> res(n);\n\
    \  for (int i = 0; i < n; i++) {\n    for (auto& e : g[i]) res[i].push_back(e.to);\n\
    \  }\n  return res;\n}\n\ntemplate <typename T>\nH<T> compress(const H<T>& p,\
    \ const H<T>& c, T w) {\n  H<T> r;\n  r.dia = max(max(p.dia, c.dia),\n       \
    \       path<T>(p.cd.d + w + c.pd.d, p.cd.u, c.pd.u));\n  r.pd = max(p.pd, HalfPath<T>{p.p_to_c\
    \ + w + c.pd.d, c.pd.u});\n  r.cd = max(c.cd, HalfPath<T>{c.p_to_c + w + p.cd.d,\
    \ p.cd.u});\n  r.p_to_c = p.p_to_c + w + c.p_to_c;\n  r.p = p.p;\n  r.c = c.c;\n\
    \  return r;\n}\n\ntemplate <typename T>\nL<T> rake(const L<T>& a, const L<T>&\
    \ b) {\n  L<T> r;\n  r.dia = max(a.dia, b.dia);\n\n  vector<HalfPath<T>> xs;\n\
    \  for (auto x : {a.d1, a.d2, b.d1, b.d2}) {\n    if (x.u != -1) xs.push_back(x);\n\
    \  }\n  assert(!xs.empty());\n\n  sort(xs.begin(), xs.end(), [](const HalfPath<T>&\
    \ x, const HalfPath<T>& y) {\n    if (x.d != y.d) return x.d > y.d;\n    return\
    \ x.u > y.u;\n  });\n\n  r.d1 = xs[0];\n  r.d2 = xs.size() >= 2 ? xs[1] : HalfPath<T>{0,\
    \ -1};\n  return r;\n}\n\ntemplate <typename T>\nL<T> add_edge(const H<T>& a,\
    \ T w) {\n  L<T> r;\n  r.dia = a.dia;\n  r.d1 = {w + a.pd.d, a.pd.u};\n  r.d2\
    \ = {0, -1};\n  return r;\n}\n\ntemplate <typename T>\nH<T> add_vertex(const L<T>&\
    \ a, int i) {\n  H<T> r;\n  r.dia = max(a.dia, path<T>(a.d1.d, a.d1.u, i));\n\
    \  if (a.d2.u != -1) {\n    r.dia = max(r.dia, path<T>(a.d1.d + a.d2.d, a.d1.u,\
    \ a.d2.u));\n  }\n  r.pd = r.cd = max(HalfPath<T>{0, i}, a.d1);\n  r.p_to_c =\
    \ 0;\n  r.p = r.c = i;\n  return r;\n}\n\ntemplate <typename T>\nstruct DynamicDiameter\
    \ {\n  const WeightedGraph<T>& g;\n  int n;\n  vector<vector<int>> tree;\n  RootedEdgeInfo<T>\
    \ edge;\n  HeavyLightDecomposition<vector<vector<int>>> hld;\n\n  struct VertexOp\
    \ {\n    H<T> operator()(int i) const { return DynamicDiameterFasterImpl::vertex<T>(i);\
    \ }\n  };\n  struct CompressOp {\n    DynamicDiameter* self;\n    H<T> operator()(const\
    \ H<T>& p, const H<T>& c) const {\n      return DynamicDiameterFasterImpl::compress<T>(\n\
    \          p, c, self->edge.get_between_adjacent(p.c, c.p));\n    }\n  };\n  struct\
    \ RakeOp {\n    L<T> operator()(const L<T>& a, const L<T>& b) const {\n      return\
    \ DynamicDiameterFasterImpl::rake<T>(a, b);\n    }\n  };\n  struct AddEdgeOp {\n\
    \    DynamicDiameter* self;\n    L<T> operator()(const H<T>& a) const {\n    \
    \  return DynamicDiameterFasterImpl::add_edge<T>(\n          a, self->edge.get_parent_edge(a.p));\n\
    \    }\n  };\n  struct AddVertexOp {\n    H<T> operator()(const L<T>& a, int i)\
    \ const {\n      return DynamicDiameterFasterImpl::add_vertex<T>(a, i);\n    }\n\
    \  };\n\n  using DP = DPonStaticTopTreeVertexBased<vector<vector<int>>, H<T>,\
    \ L<T>,\n                                          VertexOp, CompressOp, RakeOp,\n\
    \                                          AddEdgeOp, AddVertexOp>;\n  DP dp;\n\
    \n  DynamicDiameter(const WeightedGraph<T>& _g, int root = 0)\n      : g(_g),\n\
    \        n((int)g.size()),\n        tree(to_unweighted(g)),\n        edge(g, root),\n\
    \        hld(tree, root),\n        dp(hld, VertexOp{}, CompressOp{this}, RakeOp{},\
    \ AddEdgeOp{this},\n           AddVertexOp{}) {}\n\n  pair<T, pair<int, int>>\
    \ get() {\n    auto [d, u, v] = dp.get().dia;\n    return make_pair(d, make_pair(u,\
    \ v));\n  }\n\n  bool adjacent(int u, int v) const { return edge.adjacent(u, v);\
    \ }\n\n  int child_if_adjacent(int u, int v) const {\n    return edge.child_if_adjacent(u,\
    \ v);\n  }\n\n  int parent_if_adjacent(int u, int v) const {\n    return edge.parent_if_adjacent(u,\
    \ v);\n  }\n\n  void update(int u, int v, T x) {\n    int c = edge.child_if_adjacent(u,\
    \ v);\n    assert(c != -1);\n    edge.cost_to_parent[c] = x;\n    dp.update(c);\n\
    \  }\n};\n}  // namespace DynamicDiameterFasterImpl\n\nusing DynamicDiameterFasterImpl::DynamicDiameter;\n"
  dependsOn:
  - graph/graph-template.hpp
  - tree/static-top-tree-vertex-based.hpp
  - tree/convert-tree.hpp
  - tree/heavy-light-decomposition.hpp
  isVerificationFile: false
  path: tree/dynamic-diameter-faster.hpp
  requiredBy: []
  timestamp: '2026-06-05 19:46:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-unit-test/dynamic-diameter-faster.test.cpp
documentation_of: tree/dynamic-diameter-faster.hpp
layout: document
redirect_from:
- /library/tree/dynamic-diameter-faster.hpp
- /library/tree/dynamic-diameter-faster.hpp.html
title: tree/dynamic-diameter-faster.hpp
---
