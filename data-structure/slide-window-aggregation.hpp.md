---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/verify-yosupo-ds/yosupo-swag.test.cpp
    title: verify/verify-yosupo-ds/yosupo-swag.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: docs/data-structure/slide-window-aggregation.md
    document_title: Slide Window Aggrigation
    links: []
  bundledCode: "#line 2 \"data-structure/slide-window-aggregation.hpp\"\n\n#include\
    \ <vector>\nusing namespace std;\n\ntemplate <typename T, typename F>\nstruct\
    \ SlideWindowAggregation {\n  vector<T> a0, a1, r0, r1;\n  F f;\n  T I, f0, f1;\n\
    \n  SlideWindowAggregation(F _f, T _i) : f(_f), I(_i), f0(_i), f1(_i) {}\n\n private:\n\
    \  void push_s0(const T &x) {\n    a0.push_back(x);\n    r0.push_back(f0 = f(x,\
    \ f0));\n  }\n  void push_s1(const T &x) {\n    a1.push_back(x);\n    r1.push_back(f1\
    \ = f(f1, x));\n  }\n  void transfer() {\n    while (!a1.empty()) {\n      push_s0(a1.back());\n\
    \      a1.pop_back();\n    }\n    while (!r1.empty()) r1.pop_back();\n    f1 =\
    \ I;\n  }\n\n public:\n  void push(const T &x) {\n    if (a0.empty()) {\n    \
    \  push_s0(x);\n      transfer();\n    } else {\n      push_s1(x);\n    }\n  }\n\
    \  void pop() {\n    if (a0.empty()) transfer();\n    a0.pop_back();\n    r0.pop_back();\n\
    \    f0 = r0.empty() ? I : r0.back();\n  }\n  T query() { return f(f0, f1); }\n\
    };\n\n/**\n * @brief Slide Window Aggrigation\n * @docs docs/data-structure/slide-window-aggregation.md\n\
    \ */\n"
  code: "#pragma once\n\n#include <vector>\nusing namespace std;\n\ntemplate <typename\
    \ T, typename F>\nstruct SlideWindowAggregation {\n  vector<T> a0, a1, r0, r1;\n\
    \  F f;\n  T I, f0, f1;\n\n  SlideWindowAggregation(F _f, T _i) : f(_f), I(_i),\
    \ f0(_i), f1(_i) {}\n\n private:\n  void push_s0(const T &x) {\n    a0.push_back(x);\n\
    \    r0.push_back(f0 = f(x, f0));\n  }\n  void push_s1(const T &x) {\n    a1.push_back(x);\n\
    \    r1.push_back(f1 = f(f1, x));\n  }\n  void transfer() {\n    while (!a1.empty())\
    \ {\n      push_s0(a1.back());\n      a1.pop_back();\n    }\n    while (!r1.empty())\
    \ r1.pop_back();\n    f1 = I;\n  }\n\n public:\n  void push(const T &x) {\n  \
    \  if (a0.empty()) {\n      push_s0(x);\n      transfer();\n    } else {\n   \
    \   push_s1(x);\n    }\n  }\n  void pop() {\n    if (a0.empty()) transfer();\n\
    \    a0.pop_back();\n    r0.pop_back();\n    f0 = r0.empty() ? I : r0.back();\n\
    \  }\n  T query() { return f(f0, f1); }\n};\n\n/**\n * @brief Slide Window Aggrigation\n\
    \ * @docs docs/data-structure/slide-window-aggregation.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: data-structure/slide-window-aggregation.hpp
  requiredBy: []
  timestamp: '2026-05-19 18:11:32+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/verify-yosupo-ds/yosupo-swag.test.cpp
documentation_of: data-structure/slide-window-aggregation.hpp
layout: document
redirect_from:
- /library/data-structure/slide-window-aggregation.hpp
- /library/data-structure/slide-window-aggregation.hpp.html
title: Slide Window Aggrigation
---
## Slide Window Aggrigation

#### 概要

Slide Window Aggrigation は、モノイド$(S,\bullet,I)$の$S$の要素の列$A$に対して、以下の操作を高速に実行できる構造である。
- 末尾への要素の挿入
- 先頭の要素の削除
- $A$全体の集約値$A_0 \bullet A_1 \bullet A_2 \bullet \cdots \bullet A_{\vert A \vert -1}$の取得

構造は、挿入用と削除用の$2$つのスタックを持ち、削除用のスタックの中身が尽きたときに挿入用からすべての要素を移し替える。

#### 使い方

- テンプレート引数 `typename T`: $S$の要素の型。
- テンプレート引数 `typename F`: 演算$\bullet$を定義するオブジェクトの型。オブジェクトは`T f(const T& a,const T& b);`の形の関数として呼び出せて、$a \bullet b$の値を返す。
- `SlideWindowAggregation<F, T>(f_, I_)`: `f_`を演算、`I_`を単位元として設定し、$A$を空の列で初期化する。
- `push(x)`: 要素`x`を$A$の末尾に挿入する。計算量均し$\mathrm{O}(1)$。
- `pop()`: $A$から先頭の要素を削除する。計算量均し$\mathrm{O}(1)$。
- `query()`: 集約値$A_0 \bullet A_1 \bullet A_2 \bullet \cdots \bullet A_ {\vert A \vert -1}$を返す。計算量$\mathrm{O}(1)$。

#### 注意点

- $A$が空のときに`pop`を呼んではならない。
- 上記の計算量では`f_`の計算量を$\mathrm{O}(1)$と仮定している。
