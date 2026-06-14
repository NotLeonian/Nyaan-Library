#pragma once
#include "./formal-power-series.hpp"

template <typename frac>
frac sum_of_rational_functions(vector<frac> v) {
  if (v.empty()) return frac{};
  while ((int)v.size() >= 2) {
    vector<frac> nx;
    nx.reserve((v.size() + 1) / 2);
    for (int i = 0; i + 1 < (int)v.size(); i += 2)
      nx.push_back(v[i] + v[i + 1]);
    if (v.size() % 2) nx.push_back(v.back());
    v = nx;
  }
  return v.back();
}
