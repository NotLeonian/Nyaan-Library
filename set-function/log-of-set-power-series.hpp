#pragma once

#include <cassert>
#include <vector>
using namespace std;

#include "subset-convolution.hpp"

template <typename mint, int MAX = 21>
vector<mint> log_of_set_power_series(int n, vector<mint> h) {
  assert(0 <= n && n <= MAX);
  static SubsetConvolution<mint, MAX> ss;
  h.resize(1 << n);
  assert(h[0] == 1);

  vector<mint> g{0}, inv{1};
  for (int k = 1; k <= n; k++) {
    auto a = ss.multiply(inv, {begin(h) + (1 << (k - 1)), begin(h) + (1 << k)});
    copy(begin(a), end(a), back_inserter(g));

    auto b = ss.multiply(a, inv);
    for (auto& x : b) x = -x;
    copy(begin(b), end(b), back_inserter(inv));
  }
  return g;
}

/**
 * @brief 集合冪級数の log
 */
