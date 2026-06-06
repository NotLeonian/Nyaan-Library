#pragma once

#include <cstdlib>

#include "../ntt/arbitrary-ntt.hpp"
#include "./formal-power-series.hpp"

template <typename mint>
void fps_set_fft_impl(FormalPowerSeries<mint>*, FPSBackendPriority<0>) {
  FormalPowerSeries<mint>::ntt_ptr = nullptr;
}

template <typename mint>
void fps_ntt_impl(FormalPowerSeries<mint>&, FPSBackendPriority<0>) {
  exit(1);
}

template <typename mint>
void fps_intt_impl(FormalPowerSeries<mint>&, FPSBackendPriority<0>) {
  exit(1);
}

template <typename mint>
void fps_ntt_doubling_impl(FormalPowerSeries<mint>&, FPSBackendPriority<0>) {
  exit(1);
}

template <typename mint>
int fps_ntt_pr_impl(FormalPowerSeries<mint>*, FPSBackendPriority<0>) {
  exit(1);
}

template <typename mint>
FormalPowerSeries<mint>& fps_multiply_impl(FormalPowerSeries<mint>& f,
                                           const FormalPowerSeries<mint>& r,
                                           FPSBackendPriority<0>) {
  auto ret = ArbitraryNTT::multiply(f, r);
  return f = FormalPowerSeries<mint>(ret.begin(), ret.end());
}

template <typename mint>
FormalPowerSeries<mint> fps_inv_impl(const FormalPowerSeries<mint>& f, int deg,
                                     FPSBackendPriority<0>) {
  assert(f[0] != mint(0));
  if (deg == -1) deg = f.size();
  FormalPowerSeries<mint> ret({mint(1) / f[0]});
  for (int i = 1; i < deg; i <<= 1)
    ret = (ret + ret - ret * ret * f.pre(i << 1)).pre(i << 1);
  return ret.pre(deg);
}

template <typename mint>
FormalPowerSeries<mint> fps_exp_impl(const FormalPowerSeries<mint>& f, int deg,
                                     FPSBackendPriority<0>) {
  assert(f.size() == 0 || f[0] == mint(0));
  if (deg == -1) deg = (int)f.size();
  FormalPowerSeries<mint> ret({mint(1)});
  for (int i = 1; i < deg; i <<= 1) {
    ret = (ret * (f.pre(i << 1) + mint(1) - ret.log(i << 1))).pre(i << 1);
  }
  return ret.pre(deg);
}
