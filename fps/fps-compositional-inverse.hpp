#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>
using namespace std;

#include "../modulo/binomial.hpp"
#include "formal-power-series.hpp"
#include "pow-enumerate.hpp"

// f を入力として, f(g(x)) = x を満たす g(x) mod x^{deg} を返す
template <typename mint>
FormalPowerSeries<mint> compositional_inverse(FormalPowerSeries<mint> f,
                                              int deg = -1) {
  using fps = FormalPowerSeries<mint>;
  assert((int)f.size() >= 2 and f[1] != 0);
  if (deg == -1) deg = f.size();
  if (deg < 2) return fps{0, f[1].inverse()}.pre(deg);
  int n = deg - 1;
  fps h = pow_enumerate(f) * n;
  for (int k = 1; k <= n; k++) h[k] /= k;
  h = h.rev();
  h *= h[0].inverse();
  fps g = (h.log() * mint{-n}.inverse()).exp();
  g *= f[1].inverse();
  return (g << 1).pre(deg);
}

namespace CompositionalInverseImpl {

template <typename fps, typename F>
fps compositional_inverse_impl(F& calc_f, int deg) {
  if (deg <= 2) {
    fps g = std::invoke(calc_f, fps{0, 1}, 2);
    assert(g[0] == 0 && g[1] != 0);
    g[1] = g[1].inverse();
    return g.pre(deg);
  }
  fps g = compositional_inverse_impl<fps>(calc_f, (deg + 1) / 2);
  fps fg = std::invoke(calc_f, g, deg + 1);
  fps fdg = (fg.diff() * g.diff().inv(deg)).pre(deg);
  return (g - (fg - fps{0, 1}) * fdg.inv()).pre(deg);
}

}  // namespace CompositionalInverseImpl

// f(g(x)) = x を満たす g(x) mod x^{deg} を返す
// calc_f(g, d) は f(g(x)) mod x^d を計算する関数
template <typename fps, typename F>
auto compositional_inverse(F&& calc_f, int deg)
    -> enable_if_t<is_invocable_r_v<fps, F&, fps, int>, fps> {
  return CompositionalInverseImpl::compositional_inverse_impl<fps>(calc_f,
                                                                   deg);
}

template <typename fps>
fps compositional_inverse(function<fps(fps, int)> calc_f, int deg) {
  return CompositionalInverseImpl::compositional_inverse_impl<fps>(calc_f,
                                                                   deg);
}

/*
 *  @brief 逆関数
 */
