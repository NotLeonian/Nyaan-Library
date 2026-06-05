#pragma once

#include <functional>
#include <type_traits>

#include "formal-power-series.hpp"

// find f, saitsfying equation f' = g(f) mod x ^ deg
template <typename mint, typename G, typename GPrime>
auto DifferentialEquation(G&& g, GPrime&& gprime, mint f0, int deg)
    -> std::enable_if_t<
        std::is_invocable_r_v<FormalPowerSeries<mint>, G&,
                              FormalPowerSeries<mint>, int> &&
            std::is_invocable_r_v<FormalPowerSeries<mint>, GPrime&,
                                  FormalPowerSeries<mint>, int>,
        FormalPowerSeries<mint>> {
  using fps = FormalPowerSeries<mint>;
  fps f{f0};
  for (int i = 1; i < deg; i <<= 1) {
    fps gp = std::invoke(gprime, f, i << 1);
    fps r = (-gp).integral().exp(i << 1);
    fps h = ((std::invoke(g, f, i << 1) - gp * f) * r).pre(i << 1).integral();
    f = ((h + f0) * r.inv(i << 1)).pre(i << 1);
  }
  return f.pre(deg);
}

/**
 * @brief 常微分方程式
 * @docs docs/fps/differential-equation.md
 */
