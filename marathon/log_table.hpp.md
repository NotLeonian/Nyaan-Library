---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: marathon/sa-manager.hpp
    title: Multipoint Simulated Annealing
  - icon: ':x:'
    path: marathon/simulated-annealing.hpp
    title: Simulated Annealing
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/verify-unit-test/sa-manager.test.cpp
    title: verify/verify-unit-test/sa-manager.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/simulated-annealing.test.cpp
    title: verify/verify-unit-test/simulated-annealing.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"marathon/log_table.hpp\"\n\nstruct log_table {\n  static\
    \ constexpr int M = 65536;\n  static constexpr int mask = M - 1;\n  double l[M];\n\
    \  log_table() : l() {\n    unsigned long long x = 88172645463325252ULL;\n   \
    \ double log_u64max = log(2) * 64;\n    for (int i = 0; i < M; i++) {\n      x\
    \ = x ^ (x << 7);\n      x = x ^ (x >> 9);\n      l[i] = log(double(x)) - log_u64max;\n\
    \    }\n  }\n  double operator()(int i) const { return l[i & mask]; }\n};\n"
  code: "#pragma once\n\nstruct log_table {\n  static constexpr int M = 65536;\n \
    \ static constexpr int mask = M - 1;\n  double l[M];\n  log_table() : l() {\n\
    \    unsigned long long x = 88172645463325252ULL;\n    double log_u64max = log(2)\
    \ * 64;\n    for (int i = 0; i < M; i++) {\n      x = x ^ (x << 7);\n      x =\
    \ x ^ (x >> 9);\n      l[i] = log(double(x)) - log_u64max;\n    }\n  }\n  double\
    \ operator()(int i) const { return l[i & mask]; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: marathon/log_table.hpp
  requiredBy:
  - marathon/sa-manager.hpp
  - marathon/simulated-annealing.hpp
  timestamp: '2026-05-19 18:11:32+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/verify-unit-test/sa-manager.test.cpp
  - verify/verify-unit-test/simulated-annealing.test.cpp
documentation_of: marathon/log_table.hpp
layout: document
redirect_from:
- /library/marathon/log_table.hpp
- /library/marathon/log_table.hpp.html
title: marathon/log_table.hpp
---
