---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: dp/golden-section-search.hpp
    title: "\u9EC4\u91D1\u5206\u5272\u63A2\u7D22"
  - icon: ':heavy_check_mark:'
    path: dp/monge-shortest-path.hpp
    title: "monge \u30B0\u30E9\u30D5\u4E0A\u306E\u6700\u77ED\u8DEF"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-yuki/yuki-0952.test.cpp
    title: verify/verify-yuki/yuki-0952.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "monge \u30B0\u30E9\u30D5\u4E0A\u306E d-\u8FBA\u6700\u77ED\u8DEF"
    links: []
  bundledCode: "#line 2 \"dp/monge-d-edge-shortest-path.hpp\"\n\n#include <cstdlib>\n\
    #include <functional>\n#include <type_traits>\n\n#line 2 \"dp/golden-section-search.hpp\"\
    \n\n#include <cassert>\n#line 6 \"dp/golden-section-search.hpp\"\n#include <utility>\n\
    using namespace std;\n\n// reference\uFF1Ahttps://twitter.com/noshi91/status/1399003086362865673\n\
    \nnamespace golden_section_search_impl {\n\nusing i64 = long long;\n\ntemplate\
    \ <typename T, bool get_min, typename F>\npair<i64, T> golden_section_search_body(F&\
    \ f, i64 min, i64 max) {\n  assert(min <= max);\n  i64 a = min - 1, x, b;\n  {\n\
    \    i64 s = 1, t = 2;\n    while (t < max - min + 2) swap(s += t, t);\n    x\
    \ = a + t - s, b = a + t;\n  }\n  T fx = std::invoke(f, x), fy;\n  while (a +\
    \ b != 2 * x) {\n    i64 y = a + b - x;\n    if (max < y ||\n        (fy = std::invoke(f,\
    \ y), get_min ? fx < fy : fx > fy)) {\n      b = a;\n      a = y;\n    } else\
    \ {\n      a = x;\n      x = y;\n      fx = fy;\n    }\n  }\n  return {x, fx};\n\
    }\n\n// [min, max] \u306F\u9589\u533A\u9593\u3092\u5165\u529B\u3059\u308B\ntemplate\
    \ <typename T, bool get_min = true, typename F = void>\nauto golden_section_search(F&&\
    \ f, i64 min, i64 max)\n    -> enable_if_t<is_invocable_r_v<T, F&, i64>, pair<i64,\
    \ T>> {\n  return golden_section_search_body<T, get_min>(f, min, max);\n}\n\n\
    template <bool get_min = true, typename F>\nauto golden_section_search(F&& f,\
    \ i64 min, i64 max)\n    -> enable_if_t<is_invocable_v<F&, i64>,\n           \
    \        pair<i64, invoke_result_t<F&, i64>>> {\n  using T = invoke_result_t<F&,\
    \ i64>;\n  return golden_section_search_body<T, get_min>(f, min, max);\n}\n\n\
    }  // namespace golden_section_search_impl\n\nusing golden_section_search_impl::golden_section_search;\n\
    \n/*\n  @brief \u9EC4\u91D1\u5206\u5272\u63A2\u7D22\n*/\n#line 2 \"dp/monge-shortest-path.hpp\"\
    \n\n#line 5 \"dp/monge-shortest-path.hpp\"\n#include <vector>\nusing namespace\
    \ std;\n\n// https://noshi91.hatenablog.com/entry/2023/02/18/005856\n// \u8FBA\
    \u30B3\u30B9\u30C8\u304C monge \u3067\u3042\u308B DAG \u306E 0 - i \u6700\u77ED\
    \u8DEF\ntemplate <typename T, typename F>\nauto monge_shortest_path(int N, F&&\
    \ f)\n    -> enable_if_t<is_invocable_r_v<T, F&, int, int>, vector<T>> {\n  T\
    \ INF = (T{1} << (sizeof(T) * 8 - 2)) - 1;\n  vector<T> dp(N + 1, INF);\n  vector<int>\
    \ x(N + 1, 0);\n  auto check = [&](int from, int to) {\n    if (from >= to) return;\n\
    \    T cost = std::invoke(f, from, to);\n    if (dp[from] + cost < dp[to]) dp[to]\
    \ = dp[from] + cost, x[to] = from;\n  };\n  auto dfs = [&](auto rc, int l, int\
    \ r) -> void {\n    if (l + 1 >= r) return;\n    int m = (l + r) / 2;\n    for\
    \ (int i = x[l]; i <= x[r]; i++) check(i, m);\n    rc(rc, l, m);\n    for (int\
    \ i = l + 1; i <= m; i++) check(i, r);\n    rc(rc, m, r);\n  };\n  dp[0] = 0,\
    \ check(0, N), dfs(dfs, 0, N);\n  return dp;\n}\n\n/**\n * @brief monge \u30B0\
    \u30E9\u30D5\u4E0A\u306E\u6700\u77ED\u8DEF\n */\n#line 9 \"dp/monge-d-edge-shortest-path.hpp\"\
    \n\n// \u8FBA\u30B3\u30B9\u30C8\u304C monge \u3067\u3042\u308B DAG \u306E D \u8FBA\
    \ 0-N \u6700\u77ED\u8DEF\n// f : from -> to \u306E\u30B3\u30B9\u30C8 (long long)\n\
    // upper : max abs(\u8FBA\u6570\u3092 1 \u5897\u6E1B\u3055\u305B\u305F\u3068\u304D\
    \u306E\u30B3\u30B9\u30C8\u306E\u5909\u5316)\n// (\u5185\u90E8\u3067 int128 \u3067\
    \u8A08\u7B97\u3057\u3066\u3044\u308B\u306E\u3067 upper \u306F 1e18 \u3067\u3082\
    \u58CA\u308C\u306A\u3044)\ntemplate <typename F>\nauto monge_d_edge_shortest_path(int\
    \ N, int D, long long upper, F&& f)\n    -> std::enable_if_t<std::is_invocable_r_v<long\
    \ long, F&, int, int>,\n                        long long> {\n  using T = __int128_t;\n\
    \  upper = std::abs(upper);\n  auto dp = [&](long long x) -> T {\n    auto g =\
    \ [&](int from, int to) -> T { return std::invoke(f, from, to) + x; };\n    T\
    \ cost = monge_shortest_path<T>(N, g)[N];\n    return cost - T{1} * D * x;\n \
    \ };\n  auto [_, res] = golden_section_search<T, false>(dp, -upper, upper);\n\
    \  return res;\n}\n\n/**\n * @brief monge \u30B0\u30E9\u30D5\u4E0A\u306E d-\u8FBA\
    \u6700\u77ED\u8DEF\n */\n"
  code: "#pragma once\n\n#include <cstdlib>\n#include <functional>\n#include <type_traits>\n\
    \n#include \"golden-section-search.hpp\"\n#include \"monge-shortest-path.hpp\"\
    \n\n// \u8FBA\u30B3\u30B9\u30C8\u304C monge \u3067\u3042\u308B DAG \u306E D \u8FBA\
    \ 0-N \u6700\u77ED\u8DEF\n// f : from -> to \u306E\u30B3\u30B9\u30C8 (long long)\n\
    // upper : max abs(\u8FBA\u6570\u3092 1 \u5897\u6E1B\u3055\u305B\u305F\u3068\u304D\
    \u306E\u30B3\u30B9\u30C8\u306E\u5909\u5316)\n// (\u5185\u90E8\u3067 int128 \u3067\
    \u8A08\u7B97\u3057\u3066\u3044\u308B\u306E\u3067 upper \u306F 1e18 \u3067\u3082\
    \u58CA\u308C\u306A\u3044)\ntemplate <typename F>\nauto monge_d_edge_shortest_path(int\
    \ N, int D, long long upper, F&& f)\n    -> std::enable_if_t<std::is_invocable_r_v<long\
    \ long, F&, int, int>,\n                        long long> {\n  using T = __int128_t;\n\
    \  upper = std::abs(upper);\n  auto dp = [&](long long x) -> T {\n    auto g =\
    \ [&](int from, int to) -> T { return std::invoke(f, from, to) + x; };\n    T\
    \ cost = monge_shortest_path<T>(N, g)[N];\n    return cost - T{1} * D * x;\n \
    \ };\n  auto [_, res] = golden_section_search<T, false>(dp, -upper, upper);\n\
    \  return res;\n}\n\n/**\n * @brief monge \u30B0\u30E9\u30D5\u4E0A\u306E d-\u8FBA\
    \u6700\u77ED\u8DEF\n */\n"
  dependsOn:
  - dp/golden-section-search.hpp
  - dp/monge-shortest-path.hpp
  isVerificationFile: false
  path: dp/monge-d-edge-shortest-path.hpp
  requiredBy: []
  timestamp: '2026-06-05 19:46:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-yuki/yuki-0952.test.cpp
documentation_of: dp/monge-d-edge-shortest-path.hpp
layout: document
redirect_from:
- /library/dp/monge-d-edge-shortest-path.hpp
- /library/dp/monge-d-edge-shortest-path.hpp.html
title: "monge \u30B0\u30E9\u30D5\u4E0A\u306E d-\u8FBA\u6700\u77ED\u8DEF"
---
