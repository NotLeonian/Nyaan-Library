#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
using namespace std;

#include "../graph/graph-template.hpp"
#include "static-top-tree-vertex-based.hpp"

namespace DynamicDiameterFasterImpl {

template <typename T>
struct HalfPath {
  T d;
  int u;
  friend HalfPath max(const HalfPath& lhs, const HalfPath& rhs) {
    if (lhs.d != rhs.d) return lhs.d > rhs.d ? lhs : rhs;
    return lhs.u > rhs.u ? lhs : rhs;
  }
};
template <typename T>
struct Path {
  T d;
  int u, v;
  friend Path max(const Path& lhs, const Path& rhs) {
    if (lhs.d != rhs.d) return lhs.d > rhs.d ? lhs : rhs;
    if (lhs.u != rhs.u) return lhs.u > rhs.u ? lhs : rhs;
    return lhs.v > rhs.v ? lhs : rhs;
  }
};
template <typename T>
Path<T> path(T d, int u, int v) {
  if (u < v) swap(u, v);
  return {d, u, v};
}

template <typename T>
struct L {
  Path<T> dia;
  HalfPath<T> d1, d2;
};
template <typename T>
struct H {
  Path<T> dia;
  HalfPath<T> pd, cd;
  T p_to_c;
  int p, c;
};

template <typename T>
H<T> vertex(int i) {
  H<T> r;
  r.dia = path<T>(0, i, i);
  r.pd = r.cd = {0, i};
  r.p_to_c = 0;
  r.p = r.c = i;
  return r;
}

template <typename T>
struct RootedEdgeInfo {
  int N, root;
  vector<int> par, depth;
  vector<T> cost_to_parent;

  RootedEdgeInfo() = default;

  RootedEdgeInfo(const WeightedGraph<T>& g, int r = 0)
      : N((int)g.size()),
        root(r),
        par(N, -2),
        depth(N, 0),
        cost_to_parent(N, T{}) {
    vector<int> st;
    st.push_back(root);
    par[root] = -1;

    for (int it = 0; it < (int)st.size(); it++) {
      int v = st[it];
      for (auto& e : g[v]) {
        if (e.to == par[v]) continue;
        if (par[e.to] != -2) continue;
        par[e.to] = v;
        depth[e.to] = depth[v] + 1;
        cost_to_parent[e.to] = e.cost;
        st.push_back(e.to);
      }
    }
    assert((int)st.size() == N);
  }

  int child_if_adjacent(int u, int v) const {
    if (par[u] == v) return u;
    if (par[v] == u) return v;
    return -1;
  }

  int parent_if_adjacent(int u, int v) const {
    int c = child_if_adjacent(u, v);
    if (c == -1) return -1;
    return u ^ v ^ c;
  }

  bool adjacent(int u, int v) const { return child_if_adjacent(u, v) != -1; }

  T get_parent_edge(int child) const {
    assert(child != root);
    return cost_to_parent[child];
  }

  T get_between_adjacent(int u, int v) const {
    int c = child_if_adjacent(u, v);
    assert(c != -1);
    return cost_to_parent[c];
  }

  void set_between_adjacent(int u, int v, T x) {
    int c = child_if_adjacent(u, v);
    assert(c != -1);
    cost_to_parent[c] = x;
  }
};

template <typename T>
vector<vector<int>> to_unweighted(const WeightedGraph<T>& g) {
  int n = (int)g.size();
  vector<vector<int>> res(n);
  for (int i = 0; i < n; i++) {
    for (auto& e : g[i]) res[i].push_back(e.to);
  }
  return res;
}

template <typename T>
H<T> compress(const H<T>& p, const H<T>& c, T w) {
  H<T> r;
  r.dia = max(max(p.dia, c.dia),
              path<T>(p.cd.d + w + c.pd.d, p.cd.u, c.pd.u));
  r.pd = max(p.pd, HalfPath<T>{p.p_to_c + w + c.pd.d, c.pd.u});
  r.cd = max(c.cd, HalfPath<T>{c.p_to_c + w + p.cd.d, p.cd.u});
  r.p_to_c = p.p_to_c + w + c.p_to_c;
  r.p = p.p;
  r.c = c.c;
  return r;
}

template <typename T>
L<T> rake(const L<T>& a, const L<T>& b) {
  L<T> r;
  r.dia = max(a.dia, b.dia);

  vector<HalfPath<T>> xs;
  for (auto x : {a.d1, a.d2, b.d1, b.d2}) {
    if (x.u != -1) xs.push_back(x);
  }
  assert(!xs.empty());

  sort(xs.begin(), xs.end(), [](const HalfPath<T>& x, const HalfPath<T>& y) {
    if (x.d != y.d) return x.d > y.d;
    return x.u > y.u;
  });

  r.d1 = xs[0];
  r.d2 = xs.size() >= 2 ? xs[1] : HalfPath<T>{0, -1};
  return r;
}

template <typename T>
L<T> add_edge(const H<T>& a, T w) {
  L<T> r;
  r.dia = a.dia;
  r.d1 = {w + a.pd.d, a.pd.u};
  r.d2 = {0, -1};
  return r;
}

template <typename T>
H<T> add_vertex(const L<T>& a, int i) {
  H<T> r;
  r.dia = max(a.dia, path<T>(a.d1.d, a.d1.u, i));
  if (a.d2.u != -1) {
    r.dia = max(r.dia, path<T>(a.d1.d + a.d2.d, a.d1.u, a.d2.u));
  }
  r.pd = r.cd = max(HalfPath<T>{0, i}, a.d1);
  r.p_to_c = 0;
  r.p = r.c = i;
  return r;
}

template <typename T>
struct DynamicDiameter {
  const WeightedGraph<T>& g;
  int n;
  vector<vector<int>> tree;
  RootedEdgeInfo<T> edge;
  HeavyLightDecomposition<vector<vector<int>>> hld;

  struct VertexOp {
    H<T> operator()(int i) const { return DynamicDiameterFasterImpl::vertex<T>(i); }
  };
  struct CompressOp {
    DynamicDiameter* self;
    H<T> operator()(const H<T>& p, const H<T>& c) const {
      return DynamicDiameterFasterImpl::compress<T>(
          p, c, self->edge.get_between_adjacent(p.c, c.p));
    }
  };
  struct RakeOp {
    L<T> operator()(const L<T>& a, const L<T>& b) const {
      return DynamicDiameterFasterImpl::rake<T>(a, b);
    }
  };
  struct AddEdgeOp {
    DynamicDiameter* self;
    L<T> operator()(const H<T>& a) const {
      return DynamicDiameterFasterImpl::add_edge<T>(
          a, self->edge.get_parent_edge(a.p));
    }
  };
  struct AddVertexOp {
    H<T> operator()(const L<T>& a, int i) const {
      return DynamicDiameterFasterImpl::add_vertex<T>(a, i);
    }
  };

  using DP = DPonStaticTopTreeVertexBased<vector<vector<int>>, H<T>, L<T>,
                                          VertexOp, CompressOp, RakeOp,
                                          AddEdgeOp, AddVertexOp>;
  DP dp;

  DynamicDiameter(const WeightedGraph<T>& _g, int root = 0)
      : g(_g),
        n((int)g.size()),
        tree(to_unweighted(g)),
        edge(g, root),
        hld(tree, root),
        dp(hld, VertexOp{}, CompressOp{this}, RakeOp{}, AddEdgeOp{this},
           AddVertexOp{}) {}

  pair<T, pair<int, int>> get() {
    auto [d, u, v] = dp.get().dia;
    return make_pair(d, make_pair(u, v));
  }

  bool adjacent(int u, int v) const { return edge.adjacent(u, v); }

  int child_if_adjacent(int u, int v) const {
    return edge.child_if_adjacent(u, v);
  }

  int parent_if_adjacent(int u, int v) const {
    return edge.parent_if_adjacent(u, v);
  }

  void update(int u, int v, T x) {
    int c = edge.child_if_adjacent(u, v);
    assert(c != -1);
    edge.cost_to_parent[c] = x;
    dp.update(c);
  }
};
}  // namespace DynamicDiameterFasterImpl

using DynamicDiameterFasterImpl::DynamicDiameter;
