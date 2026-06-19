---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/enumerate-quotient.hpp
    title: "\u5546\u306E\u5217\u6319"
  - icon: ':heavy_check_mark:'
    path: math/isqrt.hpp
    title: math/isqrt.hpp
  - icon: ':heavy_check_mark:'
    path: multiplicative-function/enumerate-multiplicative-function.hpp
    title: "\u4E57\u6CD5\u7684\u95A2\u6570\u306E\u5217\u6319"
  - icon: ':heavy_check_mark:'
    path: multiplicative-function/mf-famous-series.hpp
    title: "\u6709\u540D\u306A\u4E57\u6CD5\u7684\u95A2\u6570"
  - icon: ':heavy_check_mark:'
    path: prime/prime-enumerate.hpp
    title: prime/prime-enumerate.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-yosupo-math/yosupo-count-squarefrees.test.cpp
    title: verify/verify-yosupo-math/yosupo-count-squarefrees.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7121\u5E73\u65B9\u6570\u306E\u6570\u3048\u4E0A\u3052"
    links: []
  bundledCode: "#line 2 \"multiplicative-function/count-square-free.hpp\"\n\n#include\
    \ <unordered_map>\n#include <vector>\nusing namespace std;\n\n#line 2 \"math/enumerate-quotient.hpp\"\
    \n\n#line 2 \"math/isqrt.hpp\"\n\n#include <cmath>\nusing namespace std;\n\n//\
    \ floor(sqrt(n)) \u3092\u8FD4\u3059 (\u305F\u3060\u3057 n \u304C\u8CA0\u306E\u5834\
    \u5408\u306F 0 \u3092\u8FD4\u3059)\nlong long isqrt(long long n) {\n  if (n <=\
    \ 0) return 0;\n  long long x = sqrt(n);\n  while ((x + 1) * (x + 1) <= n) x++;\n\
    \  while (x * x > n) x--;\n  return x;\n}\n#line 4 \"math/enumerate-quotient.hpp\"\
    \n\nnamespace EnumerateQuotientImpl {\nlong long fast_div(long long a, long long\
    \ b) { return 1.0 * a / b; };\nlong long slow_div(long long a, long long b) {\
    \ return a / b; };\n}  // namespace EnumerateQuotientImpl\n\n// { (q, l, r) :\
    \ forall x in (l,r], floor(N/x) = q }\n// \u3092\u5F15\u6570\u306B\u53D6\u308B\
    \u95A2\u6570f(q, l, r)\u3092\u6E21\u3059\u3002\u7BC4\u56F2\u304C\u5DE6\u306B\u534A\
    \u958B\u306A\u306E\u306B\u6CE8\u610F\n// \u5546\u306F\u5C0F\u3055\u3044\u65B9\u304B\
    \u3089\u8D70\u67FB\u3059\u308B\ntemplate <typename T, typename F>\nvoid enumerate_quotient(T\
    \ N, const F& f) {\n  T sq = isqrt(N);\n\n#define FUNC(d)                    \
    \   \\\n  T upper = N, quo = 0;               \\\n  while (upper > sq) {     \
    \           \\\n    T thres = d(N, (++quo + 1));      \\\n    f(quo, thres, upper);\
    \             \\\n    upper = thres;                    \\\n  }              \
    \                     \\\n  while (upper > 0) {                 \\\n    f(d(N,\
    \ upper), upper - 1, upper); \\\n    upper--;                          \\\n  }\n\
    \n  if (N <= 1e12) {\n    FUNC(EnumerateQuotientImpl::fast_div);\n  } else {\n\
    \    FUNC(EnumerateQuotientImpl::slow_div);\n  }\n#undef FUNC\n}\n\n/**\n *  @brief\
    \ \u5546\u306E\u5217\u6319\n */\n#line 2 \"multiplicative-function/mf-famous-series.hpp\"\
    \n\n#line 2 \"multiplicative-function/enumerate-multiplicative-function.hpp\"\n\
    \n#line 4 \"multiplicative-function/enumerate-multiplicative-function.hpp\"\n\
    using namespace std;\n\n#line 2 \"prime/prime-enumerate.hpp\"\n\n#line 5 \"prime/prime-enumerate.hpp\"\
    \nusing namespace std;\n\n// Prime Sieve {2, 3, 5, 7, 11, 13, 17, ...}\nvector<int>\
    \ prime_enumerate(int N) {\n  vector<bool> sieve(N / 3 + 1, 1);\n  for (int p\
    \ = 5, d = 4, i = 1, sqn = sqrt(N); p <= sqn; p += d = 6 - d, i++) {\n    if (!sieve[i])\
    \ continue;\n    for (int q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s =\
    \ 2 * p,\n             qe = sieve.size();\n         q < qe; q += r = s - r)\n\
    \      sieve[q] = 0;\n  }\n  vector<int> ret{2, 3};\n  for (int p = 5, d = 4,\
    \ i = 1; p <= N; p += d = 6 - d, i++)\n    if (sieve[i]) ret.push_back(p);\n \
    \ while (!ret.empty() && ret.back() > N) ret.pop_back();\n  return ret;\n}\n#line\
    \ 7 \"multiplicative-function/enumerate-multiplicative-function.hpp\"\n\n// f(n,\
    \ p, c) : n = pow(p, c), f is multiplicative function\n\ntemplate <typename T,\
    \ T (*f)(int, int, int)>\nstruct enumerate_multiplicative_function {\n  enumerate_multiplicative_function(int\
    \ _n)\n      : ps(prime_enumerate(_n)), a(_n + 1, T()), n(_n), p(ps.size()) {}\n\
    \n  vector<T> run() {\n    a[1] = 1;\n    dfs(-1, 1, 1);\n    return a;\n  }\n\
    \n private:\n  vector<int> ps;\n  vector<T> a;\n  int n, p;\n  void dfs(int i,\
    \ long long x, T y) {\n    a[x] = y;\n    if (y == T()) return;\n    for (int\
    \ j = i + 1; j < p; j++) {\n      long long nx = x * ps[j];\n      long long dx\
    \ = ps[j];\n      if (nx > n) break;\n      for (int c = 1; nx <= n; nx *= ps[j],\
    \ dx *= ps[j], ++c) {\n        dfs(j, nx, y * f(dx, ps[j], c));\n      }\n   \
    \ }\n  }\n};\n\ntemplate <typename T, T (*f)(int, int, int)>\nusing enamurate_multiplicative_function\
    \ =\n    enumerate_multiplicative_function<T, f>;\n\n/**\n * @brief \u4E57\u6CD5\
    \u7684\u95A2\u6570\u306E\u5217\u6319\n */\n#line 4 \"multiplicative-function/mf-famous-series.hpp\"\
    \n\nnamespace multiplicative_function {\ntemplate <typename T>\nT moebius(int,\
    \ int, int c) {\n  return c == 0 ? 1 : c == 1 ? -1 : 0;\n}\ntemplate <typename\
    \ T>\nT sigma0(int, int, int c) {\n  return c + 1;\n}\ntemplate <typename T>\n\
    T sigma1(int n, int p, int) {\n  return (n - 1) / (p - 1) + n;\n}\ntemplate <typename\
    \ T>\nT totient(int n, int p, int) {\n  return n - n / p;\n}\n}  // namespace\
    \ multiplicative_function\n\ntemplate <typename T>\nstatic constexpr vector<T>\
    \ mobius_function(int n) {\n  enumerate_multiplicative_function<T, multiplicative_function::moebius<T>>\
    \ em(\n      n);\n  return em.run();\n}\n\ntemplate <typename T>\nstatic constexpr\
    \ vector<T> sigma0(int n) {\n  enumerate_multiplicative_function<T, multiplicative_function::sigma0<T>>\
    \ em(\n      n);\n  return em.run();\n}\n\ntemplate <typename T>\nstatic constexpr\
    \ vector<T> sigma1(int n) {\n  enumerate_multiplicative_function<T, multiplicative_function::sigma1<T>>\
    \ em(\n      n);\n  return em.run();\n}\n\ntemplate <typename T>\nstatic constexpr\
    \ vector<T> totient(int n) {\n  enumerate_multiplicative_function<T, multiplicative_function::totient<T>>\
    \ em(\n      n);\n  return em.run();\n}\n\n/**\n * @brief \u6709\u540D\u306A\u4E57\
    \u6CD5\u7684\u95A2\u6570\n */\n#line 10 \"multiplicative-function/count-square-free.hpp\"\
    \n\nlong long count_square_free(long long N) {\n  long long B = pow(N, 0.4);\n\
    \n  auto pre = mobius_function<int>(B + 1);\n  for (int i = 1; i <= B; i++) pre[i]\
    \ += pre[i - 1];\n  unordered_map<long long, long long> dp;\n  auto mu = [&](auto\
    \ rc, long long n) -> long long {\n    if (n <= B) return pre[n];\n    if (dp.count(n))\
    \ return dp[n];\n    long long cur = 1;\n    enumerate_quotient(n, [&](long long\
    \ q, long long l, long long r) {\n      if (q != n) cur -= rc(rc, q) * (r - l);\n\
    \    });\n    return dp[n] = cur;\n  };\n\n  long long ans = 0;\n  long long upper\
    \ = isqrt(N);\n  for (long long i = 1; upper > B; i++) {\n    long long nxt =\
    \ isqrt(N / (i + 1));\n    ans += i * (mu(mu, upper) - mu(mu, nxt));\n    upper\
    \ = nxt;\n  }\n  while (upper > 0) {\n    ans += (pre[upper] - pre[upper - 1])\
    \ * (N / (upper * upper));\n    upper--;\n  }\n  return ans;\n}\n\n/**\n * @brief\
    \ \u7121\u5E73\u65B9\u6570\u306E\u6570\u3048\u4E0A\u3052\n */\n"
  code: "#pragma once\n\n#include <unordered_map>\n#include <vector>\nusing namespace\
    \ std;\n\n#include \"../math/enumerate-quotient.hpp\"\n#include \"../math/isqrt.hpp\"\
    \n#include \"mf-famous-series.hpp\"\n\nlong long count_square_free(long long N)\
    \ {\n  long long B = pow(N, 0.4);\n\n  auto pre = mobius_function<int>(B + 1);\n\
    \  for (int i = 1; i <= B; i++) pre[i] += pre[i - 1];\n  unordered_map<long long,\
    \ long long> dp;\n  auto mu = [&](auto rc, long long n) -> long long {\n    if\
    \ (n <= B) return pre[n];\n    if (dp.count(n)) return dp[n];\n    long long cur\
    \ = 1;\n    enumerate_quotient(n, [&](long long q, long long l, long long r) {\n\
    \      if (q != n) cur -= rc(rc, q) * (r - l);\n    });\n    return dp[n] = cur;\n\
    \  };\n\n  long long ans = 0;\n  long long upper = isqrt(N);\n  for (long long\
    \ i = 1; upper > B; i++) {\n    long long nxt = isqrt(N / (i + 1));\n    ans +=\
    \ i * (mu(mu, upper) - mu(mu, nxt));\n    upper = nxt;\n  }\n  while (upper >\
    \ 0) {\n    ans += (pre[upper] - pre[upper - 1]) * (N / (upper * upper));\n  \
    \  upper--;\n  }\n  return ans;\n}\n\n/**\n * @brief \u7121\u5E73\u65B9\u6570\u306E\
    \u6570\u3048\u4E0A\u3052\n */\n"
  dependsOn:
  - math/enumerate-quotient.hpp
  - math/isqrt.hpp
  - multiplicative-function/mf-famous-series.hpp
  - multiplicative-function/enumerate-multiplicative-function.hpp
  - prime/prime-enumerate.hpp
  isVerificationFile: false
  path: multiplicative-function/count-square-free.hpp
  requiredBy: []
  timestamp: '2026-06-19 18:03:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-yosupo-math/yosupo-count-squarefrees.test.cpp
documentation_of: multiplicative-function/count-square-free.hpp
layout: document
redirect_from:
- /library/multiplicative-function/count-square-free.hpp
- /library/multiplicative-function/count-square-free.hpp.html
title: "\u7121\u5E73\u65B9\u6570\u306E\u6570\u3048\u4E0A\u3052"
---
