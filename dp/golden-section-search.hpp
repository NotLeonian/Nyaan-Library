#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>
using namespace std;

// reference：https://twitter.com/noshi91/status/1399003086362865673

namespace golden_section_search_impl {

using i64 = long long;

// [min, max] は閉区間を入力する
template <typename T, bool get_min = true, typename F = void>
auto golden_section_search(F&& f, i64 min, i64 max)
    -> enable_if_t<is_invocable_r_v<T, F&, i64>, pair<i64, T>> {
  assert(min <= max);
  i64 a = min - 1, x, b;
  {
    i64 s = 1, t = 2;
    while (t < max - min + 2) swap(s += t, t);
    x = a + t - s, b = a + t;
  }
  T fx = std::invoke(f, x), fy;
  while (a + b != 2 * x) {
    i64 y = a + b - x;
    if (max < y ||
        (fy = std::invoke(f, y), get_min ? fx < fy : fx > fy)) {
      b = a;
      a = y;
    } else {
      a = x;
      x = y;
      fx = fy;
    }
  }
  return {x, fx};
}

}  // namespace golden_section_search_impl

using golden_section_search_impl::golden_section_search;

/*
  @brief 黄金分割探索
*/
