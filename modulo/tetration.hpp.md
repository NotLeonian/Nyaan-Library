---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/verify-yosupo-math/yosupo-tetration-mod.test.cpp
    title: verify/verify-yosupo-math/yosupo-tetration-mod.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: docs/modulo/tetration.md
    document_title: tetration
    links: []
  bundledCode: "#line 2 \"modulo/tetration.hpp\"\n\n\n\ntemplate <typename T = uint32_t,\
    \ typename U = uint64_t, T MAX = 1000000000>\nT tetration(uint64_t a, uint64_t\
    \ b, uint64_t m) {\n  auto prime_table = [](T m) -> vector<int> {\n    T thres\
    \ = sqrt(m) + 1;\n    vector<bool> flg(thres + 1);\n    for (T i = 2; i * i <=\
    \ thres; ++i) {\n      if (!flg[i])\n        for (T j = i * i; j <= thres; j +=\
    \ i) flg[j] = 1;\n    }\n    vector<int> ret;\n    for (T i = 2; i <= thres; i++)\n\
    \      if (!flg[i]) ret.push_back(i);\n    return ret;\n  };\n\n  static const\
    \ vector<int> ps = prime_table(MAX);\n\n  auto totient = [&](T n) -> T {\n   \
    \ T ret = n;\n    for (auto& p : ps) {\n      if (p * p > n) break;\n      if\
    \ (n % p == 0) {\n        ret = ret / p * (p - 1);\n        while (n % p == 0)\
    \ n /= p;\n      }\n    }\n    if (n != 1) ret = ret / n * (n - 1);\n    return\
    \ ret;\n  };\n\n  auto mpow = [](U a, U p, T m) -> pair<T, int> {\n    U ret =\
    \ 1 % m;\n    int flg = true;\n    for (; p; p >>= 1) {\n      if (p & 1)\n  \
    \      if ((ret *= a) >= m) flg = 0, ret %= m;\n      if (p == 1) break;\n   \
    \   if ((a *= a) >= m) flg = 0, a %= m;\n    }\n    return {ret, flg};\n  };\n\
    \n  auto calc = [&](auto rec, T a, U b, T m) -> pair<T, int> {\n    if (a == 0)\
    \ return {!(b & 1), true};\n    if (a == 1) return {1, true};\n    if (m == 1)\
    \ return {0, false};\n    if (b == 0) return {1, true};\n    if (b == 1) return\
    \ {a % m, a < m};\n    T phi_m = totient(m), pre, ret;\n    int flg1, flg2;\n\
    \    tie(pre, flg1) = rec(rec, a, b - 1, phi_m);\n    tie(ret, flg2) = mpow(a\
    \ % m, U(pre) + (flg1 ? 0 : phi_m), m);\n    return {ret, flg1 && flg2};\n  };\n\
    \n  return calc(calc, a, b, m).first % m;\n}\n\n/**\n * @brief tetration\n * @docs\
    \ docs/modulo/tetration.md\n */\n"
  code: "#pragma once\n\n\n\ntemplate <typename T = uint32_t, typename U = uint64_t,\
    \ T MAX = 1000000000>\nT tetration(uint64_t a, uint64_t b, uint64_t m) {\n  auto\
    \ prime_table = [](T m) -> vector<int> {\n    T thres = sqrt(m) + 1;\n    vector<bool>\
    \ flg(thres + 1);\n    for (T i = 2; i * i <= thres; ++i) {\n      if (!flg[i])\n\
    \        for (T j = i * i; j <= thres; j += i) flg[j] = 1;\n    }\n    vector<int>\
    \ ret;\n    for (T i = 2; i <= thres; i++)\n      if (!flg[i]) ret.push_back(i);\n\
    \    return ret;\n  };\n\n  static const vector<int> ps = prime_table(MAX);\n\n\
    \  auto totient = [&](T n) -> T {\n    T ret = n;\n    for (auto& p : ps) {\n\
    \      if (p * p > n) break;\n      if (n % p == 0) {\n        ret = ret / p *\
    \ (p - 1);\n        while (n % p == 0) n /= p;\n      }\n    }\n    if (n != 1)\
    \ ret = ret / n * (n - 1);\n    return ret;\n  };\n\n  auto mpow = [](U a, U p,\
    \ T m) -> pair<T, int> {\n    U ret = 1 % m;\n    int flg = true;\n    for (;\
    \ p; p >>= 1) {\n      if (p & 1)\n        if ((ret *= a) >= m) flg = 0, ret %=\
    \ m;\n      if (p == 1) break;\n      if ((a *= a) >= m) flg = 0, a %= m;\n  \
    \  }\n    return {ret, flg};\n  };\n\n  auto calc = [&](auto rec, T a, U b, T\
    \ m) -> pair<T, int> {\n    if (a == 0) return {!(b & 1), true};\n    if (a ==\
    \ 1) return {1, true};\n    if (m == 1) return {0, false};\n    if (b == 0) return\
    \ {1, true};\n    if (b == 1) return {a % m, a < m};\n    T phi_m = totient(m),\
    \ pre, ret;\n    int flg1, flg2;\n    tie(pre, flg1) = rec(rec, a, b - 1, phi_m);\n\
    \    tie(ret, flg2) = mpow(a % m, U(pre) + (flg1 ? 0 : phi_m), m);\n    return\
    \ {ret, flg1 && flg2};\n  };\n\n  return calc(calc, a, b, m).first % m;\n}\n\n\
    /**\n * @brief tetration\n * @docs docs/modulo/tetration.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: modulo/tetration.hpp
  requiredBy: []
  timestamp: '2026-05-19 18:11:32+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/verify-yosupo-math/yosupo-tetration-mod.test.cpp
documentation_of: modulo/tetration.hpp
layout: document
redirect_from:
- /library/modulo/tetration.hpp
- /library/modulo/tetration.hpp.html
title: tetration
---
## Tetration

$a \uparrow \uparrow b \mod m$を$\mathrm{O}(\sqrt{M})$で計算するライブラリ。$a \uparrow \uparrow b$とは、

$$a \uparrow \uparrow b =\begin{cases} 1 & \mathrm{if}\ \ b = 0\newline a^{a \uparrow \uparrow (b-1)} & \mathrm{otherwise}\end{cases}$$

として定められる二項演算である。

#### 概要

(この内容は[koprickyさんのライブラリ](https://kopricky.github.io/code/Computation_Advanced/tetration.html)を参考に書きました。)

$a\uparrow \uparrow b$と$a\uparrow \uparrow (b-1)$の関係式を元に再帰的に計算する。

$a$と$m$が互いに素の時は、オイラーの定理$a ^ {\phi(m)}\equiv 1 \mod m$より、

$$a \uparrow \uparrow b \equiv a^{a \uparrow \uparrow (b-1)} \equiv a^{(a \uparrow \uparrow (b-1) \mod \phi(m))} \mod m$$

という関係式を得ることができる。

次に$a$と$m$が互いに素でない場合を考える。$m=kl$を$l$と$a$が互いに素で$k$が$a$の素因数の積で表されるように取る。

この時、$a^i \mod k$は$i$が十分に大きいときに$0$に等しくなり、$a^i \mod l$はオイラーの定理より$\phi(l)$周期を持つ。よって中国剰余定理と合わせて$a^i \mod m$は$i$が十分に大きい時に$\phi(m)$周期になることがわかる。

ここで具体的に$m=kl$を具体的に計算する必要はないことに留意する。というのも、トーシェント関数の乗法性より$a^i \mod m$は$\phi(m)$周期を持つためである。また、$\lfloor\log_2 m\rfloor \leq \phi(m)$ より$a^{\phi(m)} \equiv 0 \mod k$になることから、$i$が$\phi(m)$未満の時は愚直に計算して、それより$i$が大きいときは周期性を利用して計算すればよい。(実装の際は$a\uparrow \uparrow b$が$m$以上かどうかをフラグとして持っておけばよい。)

以上より、$a\uparrow \uparrow b \mod m$は$a\uparrow \uparrow (b-1) \mod \phi(m)$の値から導出できることがわかった。計算量はアルゴリズム全体でのトーシェント関数の計算量に依存するので、計算量を求めるために数列$m,\phi(m),\phi(\phi(m))\ldots$の性質を考察する。

ここで、$m$が偶数の時$\phi(m)$は$\frac{m}{2}$以下になる。また、$m$が奇数の時、$\phi(m)$は偶数なので$\phi(\phi(m))$は$\frac{\phi(m)}{2}$以下になる。以上より、上記の数列は少なくとも$2$個おきに半減して、$\mathrm{O}(\log_2 m)$回で$1$に収束する。よって全体の計算量は$T(m) = \mathrm{O}(\sqrt{m})+T(\frac{m}{2})$を解いて$\mathrm{O}(\sqrt{m})$となる。
