---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-aoj-dpl/aoj-dpl-1-f-bandb.test.cpp
    title: verify/verify-aoj-dpl/aoj-dpl-1-f-bandb.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/verify-aoj-dpl/aoj-dpl-1-h-bandb.test.cpp
    title: verify/verify-aoj-dpl/aoj-dpl-1-h-bandb.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "0-1\u30CA\u30C3\u30D7\u30B5\u30C3\u30AF\u554F\u984C\u306E\u5206\
      \u679D\u9650\u5B9A\u6CD5\u306B\u3088\u308B\u89E3\u6CD5"
    links: []
  bundledCode: "#line 2 \"dp/branch-and-bound.hpp\"\n\ntemplate <typename V, typename\
    \ W, typename D = long double>\nstruct BranchAndBound {\n  vector<pair<V, W>>\
    \ c;\n  V best;\n\n  BranchAndBound(const vector<V>& v, const vector<W>& w) {\n\
    \    assert(v.size() == w.size());\n    vector<int> ord(v.size());\n    iota(begin(ord),\
    \ end(ord), 0);\n    sort(begin(ord), end(ord),\n         [&](int i, int j) {\
    \ return D(v[i]) * w[j] > D(v[j]) * w[i]; });\n    for (auto& i : ord) c.emplace_back(v[i],\
    \ w[i]);\n  }\n\n  pair<D, bool> relax(int i, V v, W w) {\n    D ret = v;\n  \
    \  bool f = true;\n    while (i < (int)c.size()) {\n      if (w == 0) break;\n\
    \      if (w >= c[i].second) {\n        w -= c[i].second, ret += c[i].first, ++i;\n\
    \        continue;\n      }\n      f = false, ret += (D(c[i].first) * w) / c[i].second;\n\
    \      break;\n    }\n    return make_pair(ret, f);\n  }\n\n  void dfs(int i,\
    \ V v, W w) {\n    if (i == (int)c.size()) {\n      best = max(v, best);\n   \
    \   return;\n    }\n    auto [rel, flg] = relax(i, v, w);\n    if (flg) {\n  \
    \    best = max(best, V(rel));\n      return;\n    }\n    if (V(rel) < best) return;\n\
    \    if (w >= c[i].second) dfs(i + 1, v + c[i].first, w - c[i].second);\n    dfs(i\
    \ + 1, v, w);\n    return;\n  }\n\n  V run(W w) {\n    dfs(0, best = 0, w);\n\
    \    return best;\n  }\n};\n\n/**\n * @brief 0-1\u30CA\u30C3\u30D7\u30B5\u30C3\
    \u30AF\u554F\u984C\u306E\u5206\u679D\u9650\u5B9A\u6CD5\u306B\u3088\u308B\u89E3\
    \u6CD5\n */\n"
  code: "#pragma once\n\ntemplate <typename V, typename W, typename D = long double>\n\
    struct BranchAndBound {\n  vector<pair<V, W>> c;\n  V best;\n\n  BranchAndBound(const\
    \ vector<V>& v, const vector<W>& w) {\n    assert(v.size() == w.size());\n   \
    \ vector<int> ord(v.size());\n    iota(begin(ord), end(ord), 0);\n    sort(begin(ord),\
    \ end(ord),\n         [&](int i, int j) { return D(v[i]) * w[j] > D(v[j]) * w[i];\
    \ });\n    for (auto& i : ord) c.emplace_back(v[i], w[i]);\n  }\n\n  pair<D, bool>\
    \ relax(int i, V v, W w) {\n    D ret = v;\n    bool f = true;\n    while (i <\
    \ (int)c.size()) {\n      if (w == 0) break;\n      if (w >= c[i].second) {\n\
    \        w -= c[i].second, ret += c[i].first, ++i;\n        continue;\n      }\n\
    \      f = false, ret += (D(c[i].first) * w) / c[i].second;\n      break;\n  \
    \  }\n    return make_pair(ret, f);\n  }\n\n  void dfs(int i, V v, W w) {\n  \
    \  if (i == (int)c.size()) {\n      best = max(v, best);\n      return;\n    }\n\
    \    auto [rel, flg] = relax(i, v, w);\n    if (flg) {\n      best = max(best,\
    \ V(rel));\n      return;\n    }\n    if (V(rel) < best) return;\n    if (w >=\
    \ c[i].second) dfs(i + 1, v + c[i].first, w - c[i].second);\n    dfs(i + 1, v,\
    \ w);\n    return;\n  }\n\n  V run(W w) {\n    dfs(0, best = 0, w);\n    return\
    \ best;\n  }\n};\n\n/**\n * @brief 0-1\u30CA\u30C3\u30D7\u30B5\u30C3\u30AF\u554F\
    \u984C\u306E\u5206\u679D\u9650\u5B9A\u6CD5\u306B\u3088\u308B\u89E3\u6CD5\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: dp/branch-and-bound.hpp
  requiredBy: []
  timestamp: '2026-06-08 17:59:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-aoj-dpl/aoj-dpl-1-h-bandb.test.cpp
  - verify/verify-aoj-dpl/aoj-dpl-1-f-bandb.test.cpp
documentation_of: dp/branch-and-bound.hpp
layout: document
title: "0-1\u30CA\u30C3\u30D7\u30B5\u30C3\u30AF\u554F\u984C\u306E\u5206\u679D\u9650\
  \u5B9A\u6CD5\u306B\u3088\u308B\u89E3\u6CD5"
---

## 0-1ナップサック問題の、分枝限定法による解法

### 概要

> 0-1ナップサック問題
>
> 品物が$N$個(品物$0$から品物$N-1$)あり、品物$i$は価値$v_i$重さ$w_i$である。重さの総和が$W$以下となるようにいくつかの品物を選んだとき、選んだ品物の価値の総和の最大値$V_{\max}$を求めよ。

いくつかの品物について選択が決まったとき、残りの品物で[有理ナップサック問題](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_15_B)を解いて最適解の上界とする。再帰関数で探索するが、現在のノードでの最適解の上界が既知の解以下になった場合は、その先の探索を行わない（分枝限定法）。

### 使い方

- `BranchAndBound<V,W>(v,w)`: コンストラクタ。数列$v=\{v_i\}$,$w=\{w_i\}$を与える。計算量$\mathrm{O}(N\log N)$
- `run(w)`: `w`で値$W$を与える。0-1ナップサック問題の解$V_{\max}$を返す。計算量$\mathrm{O}(2^N)$

### 注意点

- このライブラリは、弱いテストケースを狙う嘘解法での利用を想定したものである。
