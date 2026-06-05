#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>
using namespace std;

#include "../internal/internal-function.hpp"

// start : 始点
// goal  : 到達した終点 (goal が無い/着かない場合 Index{})
// dist  : start - goal 間の距離
// reachable : goal に着いたか？を意味する bool
// path  : start から goal へのパス (reachable = false の場合は空)
// mp    : mp[頂点] = (最短距離, 1 つ前の頂点) を管理する map
template <typename Index, typename Cost>
struct DijkstraResult {
  Index start, goal;
  Cost dist;
  bool reachable;
  map<Index, pair<Cost, Index>> mp;
  vector<Index> path;

  DijkstraResult(const Index& s, const Index& g, Cost d, bool r,
                 const map<Index, pair<Cost, Index>>& m)
      : start(s), goal(g), dist(d), reachable(r), mp(m) {
    if (reachable) {
      for (Index c = g; c != s; c = mp[c].second) path.push_back(c);
      path.push_back(s);
      reverse(begin(path), end(path));
    }
  }
};

// 引数 f は (頂点 v, s-v 間の距離, 関数 g) を引数に取る
// f の内部で g(次の頂点 w, s-w 間の距離) を呼び出して使う
//
// 返り値は DijkstraResult<Index, Cost> を返す
//
// goal は lambda 式 or 値 を渡せる, goal が複数ある場合に対応している
// (始点が複数ある場合は超頂点を使うことにする)
template <typename Index, typename Cost, bool has_goal = true, typename F,
          typename IsGoal>
auto dijkstra_abstruct(F&& f, const Index& start, IsGoal&& is_goal)
    -> enable_if_t<is_invocable_r_v<bool, IsGoal&, Index>,
                   DijkstraResult<Index, Cost>> {
  using P = pair<Cost, Index>;

  map<Index, P> d;
  priority_queue<P, vector<P>, greater<P>> Q;
  d[start] = P(0, Index{});
  Q.emplace(0, start);

  while (!Q.empty()) {
    auto [u, t] = Q.top();
    Q.pop();
    if (d[t].first != u) continue;
    if constexpr (has_goal) {
      if (std::invoke(is_goal, t)) return {start, t, u, true, d};
    }
    auto add = [&](Index nt, Cost nu) {
      if (d.count(nt) == 0 or nu < d[nt].first) {
        d[nt] = P(nu, t);
        Q.emplace(nu, nt);
      }
    };
    static_assert(is_invocable_r_v<void, F&, Index, Cost, decltype(add)&>,
                  "dijkstra_abstruct transition must be callable as "
                  "void(Index, Cost, add_callback)");
    std::invoke(f, t, u, add);
  }
  return {start, Index{}, Cost{}, false, d};
}

// 引数 f は (頂点 v, s-v 間の距離, 関数 g) を引数に取る
// f の内部で g(次の頂点 w, s-w 間の距離) を呼び出して使う
//
// 返り値は DijkstraResult<Index, Cost> を返す
//
// goal は lambda 式 or 値 を渡せる, goal が複数ある場合に対応している
// (始点が複数ある場合は超頂点を使うことにする)
template <typename Index, typename Cost, bool has_goal = true, typename F>
DijkstraResult<Index, Cost> dijkstra_abstruct(F&& f, const Index& start,
                                              const Index& goal = Index{}) {
  auto is_goal = [&goal](Index i) -> bool { return i == goal; };
  return dijkstra_abstruct<Index, Cost, has_goal>(std::forward<F>(f), start,
                                                  is_goal);
}
