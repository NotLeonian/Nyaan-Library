---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: prime/prime-enumerate.hpp
    title: prime/prime-enumerate.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: multiplicative-function/count-square-free.hpp
    title: "\u7121\u5E73\u65B9\u6570\u306E\u6570\u3048\u4E0A\u3052"
  - icon: ':heavy_check_mark:'
    path: multiplicative-function/mf-famous-series.hpp
    title: "\u6709\u540D\u306A\u4E57\u6CD5\u7684\u95A2\u6570"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-unit-test/mf.test.cpp
    title: verify/verify-unit-test/mf.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/verify-unit-test/sum-of-mf.test.cpp
    title: verify/verify-unit-test/sum-of-mf.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/verify-yosupo-math/yosupo-count-squarefrees.test.cpp
    title: verify/verify-yosupo-math/yosupo-count-squarefrees.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E57\u6CD5\u7684\u95A2\u6570\u306E\u5217\u6319"
    links: []
  bundledCode: "#line 2 \"multiplicative-function/enamurate-multiplicative-function.hpp\"\
    \n\n#include <vector>\nusing namespace std;\n\n#line 2 \"prime/prime-enumerate.hpp\"\
    \n\n#include <cmath>\n#line 5 \"prime/prime-enumerate.hpp\"\nusing namespace std;\n\
    \n// Prime Sieve {2, 3, 5, 7, 11, 13, 17, ...}\nvector<int> prime_enumerate(int\
    \ N) {\n  vector<bool> sieve(N / 3 + 1, 1);\n  for (int p = 5, d = 4, i = 1, sqn\
    \ = sqrt(N); p <= sqn; p += d = 6 - d, i++) {\n    if (!sieve[i]) continue;\n\
    \    for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,\n  \
    \           qe = sieve.size();\n         q < qe; q += r = s - r)\n      sieve[q]\
    \ = 0;\n  }\n  vector<int> ret{2, 3};\n  for (int p = 5, d = 4, i = 1; p <= N;\
    \ p += d = 6 - d, i++)\n    if (sieve[i]) ret.push_back(p);\n  while (!ret.empty()\
    \ && ret.back() > N) ret.pop_back();\n  return ret;\n}\n#line 7 \"multiplicative-function/enamurate-multiplicative-function.hpp\"\
    \n\n// f(n, p, c) : n = pow(p, c), f is multiplicative function\n\ntemplate <typename\
    \ T, T (*f)(int, int, int)>\nstruct enamurate_multiplicative_function {\n  enamurate_multiplicative_function(int\
    \ _n)\n      : ps(prime_enumerate(_n)), a(_n + 1, T()), n(_n), p(ps.size()) {}\n\
    \n  vector<T> run() {\n    a[1] = 1;\n    dfs(-1, 1, 1);\n    return a;\n  }\n\
    \n private:\n  vector<int> ps;\n  vector<T> a;\n  int n, p;\n  void dfs(int i,\
    \ long long x, T y) {\n    a[x] = y;\n    if (y == T()) return;\n    for (int\
    \ j = i + 1; j < p; j++) {\n      long long nx = x * ps[j];\n      long long dx\
    \ = ps[j];\n      if (nx > n) break;\n      for (int c = 1; nx <= n; nx *= ps[j],\
    \ dx *= ps[j], ++c) {\n        dfs(j, nx, y * f(dx, ps[j], c));\n      }\n   \
    \ }\n  }\n};\n\n/**\n * @brief \u4E57\u6CD5\u7684\u95A2\u6570\u306E\u5217\u6319\
    \n */\n"
  code: "#pragma once\n\n#include <vector>\nusing namespace std;\n\n#include \"../prime/prime-enumerate.hpp\"\
    \n\n// f(n, p, c) : n = pow(p, c), f is multiplicative function\n\ntemplate <typename\
    \ T, T (*f)(int, int, int)>\nstruct enamurate_multiplicative_function {\n  enamurate_multiplicative_function(int\
    \ _n)\n      : ps(prime_enumerate(_n)), a(_n + 1, T()), n(_n), p(ps.size()) {}\n\
    \n  vector<T> run() {\n    a[1] = 1;\n    dfs(-1, 1, 1);\n    return a;\n  }\n\
    \n private:\n  vector<int> ps;\n  vector<T> a;\n  int n, p;\n  void dfs(int i,\
    \ long long x, T y) {\n    a[x] = y;\n    if (y == T()) return;\n    for (int\
    \ j = i + 1; j < p; j++) {\n      long long nx = x * ps[j];\n      long long dx\
    \ = ps[j];\n      if (nx > n) break;\n      for (int c = 1; nx <= n; nx *= ps[j],\
    \ dx *= ps[j], ++c) {\n        dfs(j, nx, y * f(dx, ps[j], c));\n      }\n   \
    \ }\n  }\n};\n\n/**\n * @brief \u4E57\u6CD5\u7684\u95A2\u6570\u306E\u5217\u6319\
    \n */\n"
  dependsOn:
  - prime/prime-enumerate.hpp
  isVerificationFile: false
  path: multiplicative-function/enamurate-multiplicative-function.hpp
  requiredBy:
  - multiplicative-function/count-square-free.hpp
  - multiplicative-function/mf-famous-series.hpp
  timestamp: '2026-06-06 19:38:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-yosupo-math/yosupo-count-squarefrees.test.cpp
  - verify/verify-unit-test/mf.test.cpp
  - verify/verify-unit-test/sum-of-mf.test.cpp
documentation_of: multiplicative-function/enamurate-multiplicative-function.hpp
layout: document
redirect_from:
- /library/multiplicative-function/enamurate-multiplicative-function.hpp
- /library/multiplicative-function/enamurate-multiplicative-function.hpp.html
title: "\u4E57\u6CD5\u7684\u95A2\u6570\u306E\u5217\u6319"
---
