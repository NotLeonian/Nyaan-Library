#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>
using namespace std;

#include "../internal/internal-function.hpp"

// DS ... data_structure_type
// S ... size_type
// T ... value_type
template <typename DS, typename S, typename T,
          typename NewFunc = nyaan_internal::inplace_function<DS*(int), 64>,
          typename AddFunc = nyaan_internal::inplace_function<void(DS&, int, T), 64>,
          typename SumFunc = nyaan_internal::inplace_function<T(DS&, int, int), 64>,
          typename MergeFunc = nyaan_internal::inplace_function<T(T, T), 64>>
struct RangeTree {
  using NEW = NewFunc;
  using ADD = AddFunc;
  using SUM = SumFunc;
  using MRG = MergeFunc;
  using P = pair<S, S>;

  static_assert(is_invocable_r_v<DS*, NEW&, int>,
                "RangeTree NEW must be callable as DS*(int)");
  static_assert(is_invocable_r_v<void, ADD&, DS&, int, T>,
                "RangeTree ADD must be callable as void(DS&, int, T)");
  static_assert(is_invocable_r_v<T, SUM&, DS&, int, int>,
                "RangeTree SUM must be callable as T(DS&, int, int)");
  static_assert(is_invocable_r_v<T, MRG&, T, T>,
                "RangeTree MRG must be callable as T(T, T)");

  S N, M;
  NEW ds_new;
  ADD ds_add;
  SUM ds_sum;
  MRG t_merge;
  const T ti;
  vector<DS*> ds;
  vector<vector<S>> ys;
  vector<P> ps;

  template <typename FNew, typename FAdd, typename FSum, typename FMerge>
  RangeTree(FNew&& nw, FAdd&& ad, FSum&& sm, FMerge&& mrg, const T& ti_)
      : ds_new(std::forward<FNew>(nw)),
        ds_add(std::forward<FAdd>(ad)),
        ds_sum(std::forward<FSum>(sm)),
        t_merge(std::forward<FMerge>(mrg)),
        ti(ti_) {}

  void add_point(S x, S y) { ps.push_back(make_pair(x, y)); }

  void build() {
    sort(begin(ps), end(ps));
    ps.erase(unique(begin(ps), end(ps)), end(ps));
    N = ps.size();
    ds.resize(2 * N, nullptr);
    ys.resize(2 * N);
    for (int i = 0; i < N; ++i) {
      ys[i + N].push_back(ps[i].second);
      ds[i + N] = std::invoke(ds_new, 1);
    }
    for (int i = N - 1; i > 0; --i) {
      ys[i].resize(ys[i << 1].size() + ys[(i << 1) | 1].size());
      merge(begin(ys[(i << 1) | 0]), end(ys[(i << 1) | 0]),
            begin(ys[(i << 1) | 1]), end(ys[(i << 1) | 1]), begin(ys[i]));
      ys[i].erase(unique(begin(ys[i]), end(ys[i])), end(ys[i]));
      ds[i] = std::invoke(ds_new, ys[i].size());
    }
  }

  int id(S x) const {
    return lower_bound(
               begin(ps), end(ps), make_pair(x, S()),
               [](const P& a, const P& b) { return a.first < b.first; }) -
           begin(ps);
  }

  int id(int i, S y) const {
    return lower_bound(begin(ys[i]), end(ys[i]), y) - begin(ys[i]);
  }

  void add(S x, S y, T a) {
    int i = lower_bound(begin(ps), end(ps), make_pair(x, y)) - begin(ps);
    assert(ps[i] == make_pair(x, y));
    for (i += N; i; i >>= 1) std::invoke(ds_add, *ds[i], id(i, y), a);
  }

  T sum(S xl, S yl, S xr, S yr) {
    T L = ti, R = ti;
    int a = id(xl), b = id(xr);
    for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
      if (a & 1)
        L = std::invoke(t_merge, L,
                        std::invoke(ds_sum, *ds[a], id(a, yl), id(a, yr))),
        ++a;
      if (b & 1)
        --b,
            R = std::invoke(t_merge,
                            std::invoke(ds_sum, *ds[b], id(b, yl), id(b, yr)),
                            R);
    }
    return std::invoke(t_merge, L, R);
  }
};

/*
 * @brief 抽象化領域木
 */
