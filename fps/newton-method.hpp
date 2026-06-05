#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>
using namespace std;

// G(f) = 0 mod x^{deg} を満たす f を返す
// f0 : 初期解, 非空な fps か mint を入れる
// g : (g(f), g'(f)) を返す
template <typename fps, typename F>
auto newton_method(F&& calc_g, fps f0, int deg)
    -> enable_if_t<is_invocable_r_v<pair<fps, fps>, F&, fps, int>, fps> {
  assert(!f0.empty());
  if (deg <= (int)f0.size()) return f0.pre(deg);
  fps f = newton_method<fps>(calc_g, f0, (deg + 1) / 2);
  int extra = 10, offset = 0;
  auto [g, dgdf] = std::invoke(calc_g, f, deg + extra);
  while (offset < (int)dgdf.size() && dgdf[offset] == 0) offset++;
  assert(offset <= extra);
  dgdf = dgdf >> offset, g = g >> offset;
  return (f - g * dgdf.inv()).pre(deg);
}
// G(f) = 0 mod x^{deg} を満たす f を返す
// f0 : 初期解, 非空な fps か mint を入れる
// g : (g(f), g'(f)) を返す
template <typename fps, typename F>
auto newton_method(F&& calc_g, typename fps::value_type f0, int deg)
    -> enable_if_t<is_invocable_r_v<pair<fps, fps>, F&, fps, int>, fps> {
  return newton_method<fps>(std::forward<F>(calc_g), fps{f0}, deg);
}

/**
 * @brief ニュートン法
 */
