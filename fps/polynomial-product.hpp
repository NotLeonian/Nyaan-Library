#pragma once
#include "./formal-power-series.hpp"

template <typename fps>
fps Pi(vector<fps> v) {
  if (v.empty()) return fps{1};
  while ((int)v.size() >= 2) {
    vector<fps> nx;
    nx.reserve((v.size() + 1) / 2);
    for (int i = 0; i + 1 < (int)v.size(); i += 2)
      nx.push_back(v[i] * v[i + 1]);
    if (v.size() % 2) nx.push_back(v.back());
    v = nx;
  }
  return v[0];
}
