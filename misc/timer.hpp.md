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
  - icon: ':x:'
    path: misc/all.hpp
    title: misc/all.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/verify-unit-test/arbitrary-ntt-mod18446744069414584321.test.cpp
    title: verify/verify-unit-test/arbitrary-ntt-mod18446744069414584321.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/bigint-gcd.test.cpp
    title: verify/verify-unit-test/bigint-gcd.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/bigint2.test.cpp
    title: verify/verify-unit-test/bigint2.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/bigint3.test.cpp
    title: verify/verify-unit-test/bigint3.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/composite-exp.test.cpp
    title: verify/verify-unit-test/composite-exp.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/fast-bs.test.cpp
    title: verify/verify-unit-test/fast-bs.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/fast-inv-o1.test.cpp
    title: verify/verify-unit-test/fast-inv-o1.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/fast-inv.test.cpp
    title: verify/verify-unit-test/fast-inv.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/garner-bigint.test.cpp
    title: verify/verify-unit-test/garner-bigint.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/mf.test.cpp
    title: verify/verify-unit-test/mf.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/multipoint-binomial-sum.test.cpp
    title: verify/verify-unit-test/multipoint-binomial-sum.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/radix-sort.test.cpp
    title: verify/verify-unit-test/radix-sort.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/rbst-segment-tree.test.cpp
    title: verify/verify-unit-test/rbst-segment-tree.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/sa-manager.test.cpp
    title: verify/verify-unit-test/sa-manager.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/simulated-annealing.test.cpp
    title: verify/verify-unit-test/simulated-annealing.test.cpp
  - icon: ':x:'
    path: verify/verify-unit-test/strassen.test.cpp
    title: verify/verify-unit-test/strassen.test.cpp
  - icon: ':x:'
    path: verify/verify-yosupo-math/yosupo-division-of-hex.test.cpp
    title: verify/verify-yosupo-math/yosupo-division-of-hex.test.cpp
  - icon: ':x:'
    path: verify/verify-yuki/yuki-0952.test.cpp
    title: verify/verify-yuki/yuki-0952.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"misc/timer.hpp\"\n\n#include <chrono>\nusing namespace std;\n\
    \nstruct Timer {\n  chrono::high_resolution_clock::time_point st;\n\n  Timer()\
    \ { reset(); }\n  void reset() { st = chrono::high_resolution_clock::now(); }\n\
    \n  long long elapsed() {\n    auto ed = chrono::high_resolution_clock::now();\n\
    \    return chrono::duration_cast<chrono::milliseconds>(ed - st).count();\n  }\n\
    \  long long operator()() { return elapsed(); }\n};\n"
  code: "#pragma once\n\n#include <chrono>\nusing namespace std;\n\nstruct Timer {\n\
    \  chrono::high_resolution_clock::time_point st;\n\n  Timer() { reset(); }\n \
    \ void reset() { st = chrono::high_resolution_clock::now(); }\n\n  long long elapsed()\
    \ {\n    auto ed = chrono::high_resolution_clock::now();\n    return chrono::duration_cast<chrono::milliseconds>(ed\
    \ - st).count();\n  }\n  long long operator()() { return elapsed(); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: misc/timer.hpp
  requiredBy:
  - misc/all.hpp
  - marathon/sa-manager.hpp
  - marathon/simulated-annealing.hpp
  timestamp: '2026-05-19 18:11:32+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/verify-unit-test/bigint2.test.cpp
  - verify/verify-unit-test/composite-exp.test.cpp
  - verify/verify-unit-test/strassen.test.cpp
  - verify/verify-unit-test/radix-sort.test.cpp
  - verify/verify-unit-test/fast-inv.test.cpp
  - verify/verify-unit-test/multipoint-binomial-sum.test.cpp
  - verify/verify-unit-test/mf.test.cpp
  - verify/verify-unit-test/fast-inv-o1.test.cpp
  - verify/verify-unit-test/fast-bs.test.cpp
  - verify/verify-unit-test/bigint3.test.cpp
  - verify/verify-unit-test/rbst-segment-tree.test.cpp
  - verify/verify-unit-test/sa-manager.test.cpp
  - verify/verify-unit-test/simulated-annealing.test.cpp
  - verify/verify-unit-test/arbitrary-ntt-mod18446744069414584321.test.cpp
  - verify/verify-unit-test/garner-bigint.test.cpp
  - verify/verify-unit-test/bigint-gcd.test.cpp
  - verify/verify-yosupo-math/yosupo-division-of-hex.test.cpp
  - verify/verify-yuki/yuki-0952.test.cpp
documentation_of: misc/timer.hpp
layout: document
redirect_from:
- /library/misc/timer.hpp
- /library/misc/timer.hpp.html
title: misc/timer.hpp
---
