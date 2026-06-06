---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ntt/multivariate-circular-convolution.hpp
    title: "\u591A\u5909\u6570\u5DE1\u56DE\u7573\u307F\u8FBC\u307F"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-yosupo-ntt/yosupo-convolution-chirp-z.test.cpp
    title: verify/verify-yosupo-ntt/yosupo-convolution-chirp-z.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/verify-yosupo-ntt/yosupo-multipoint-evaluation-chirp-z.test.cpp
    title: verify/verify-yosupo-ntt/yosupo-multipoint-evaluation-chirp-z.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/verify-yosupo-ntt/yosupo-multivariate-circular-convolution.test.cpp
    title: verify/verify-yosupo-ntt/yosupo-multivariate-circular-convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Chirp Z-transform(Bluestein's algorithm)
    links: []
  bundledCode: "#line 2 \"ntt/chirp-z.hpp\"\n\n// f(A W^0), f(A W^1), ..., f(A W^{N-1})\
    \ \u3092\u8FD4\u3059\ntemplate <typename fps>\nfps ChirpZ(fps f, typename fps::value_type\
    \ W, int N = -1,\n           typename fps::value_type A = 1) {\n  using mint =\
    \ typename fps::value_type;\n  if (N == -1) N = f.size();\n  if (f.empty() or\
    \ N == 0) return fps(N, mint{});\n  int M = f.size();\n  if (A != 1) {\n    mint\
    \ x = 1;\n    for (int i = 0; i < M; i++) f[i] *= x, x *= A;\n  }\n  if (W ==\
    \ 0) {\n    fps F(N, f[0]);\n    for (int i = 1; i < M; i++) F[0] += f[i];\n \
    \   return F;\n  }\n  fps wc(N + M), iwc(max(N, M));\n  mint ws = 1, iW = W.inverse(),\
    \ iws = 1;\n  wc[0] = 1, iwc[0] = 1;\n  for (int i = 1; i < N + M; i++) wc[i]\
    \ = ws * wc[i - 1], ws *= W;\n  for (int i = 1; i < max(N, M); i++) iwc[i] = iws\
    \ * iwc[i - 1], iws *= iW;\n  for (int i = 0; i < M; i++) f[i] *= iwc[i];\n  reverse(begin(f),\
    \ end(f));\n  fps g = f * wc;\n  fps F{begin(g) + M - 1, begin(g) + M + N - 1};\n\
    \  for (int i = 0; i < N; i++) F[i] *= iwc[i];\n  return F;\n}\n\n/**\n * @brief\
    \ Chirp Z-transform(Bluestein's algorithm)\n */\n"
  code: "#pragma once\n\n// f(A W^0), f(A W^1), ..., f(A W^{N-1}) \u3092\u8FD4\u3059\
    \ntemplate <typename fps>\nfps ChirpZ(fps f, typename fps::value_type W, int N\
    \ = -1,\n           typename fps::value_type A = 1) {\n  using mint = typename\
    \ fps::value_type;\n  if (N == -1) N = f.size();\n  if (f.empty() or N == 0) return\
    \ fps(N, mint{});\n  int M = f.size();\n  if (A != 1) {\n    mint x = 1;\n   \
    \ for (int i = 0; i < M; i++) f[i] *= x, x *= A;\n  }\n  if (W == 0) {\n    fps\
    \ F(N, f[0]);\n    for (int i = 1; i < M; i++) F[0] += f[i];\n    return F;\n\
    \  }\n  fps wc(N + M), iwc(max(N, M));\n  mint ws = 1, iW = W.inverse(), iws =\
    \ 1;\n  wc[0] = 1, iwc[0] = 1;\n  for (int i = 1; i < N + M; i++) wc[i] = ws *\
    \ wc[i - 1], ws *= W;\n  for (int i = 1; i < max(N, M); i++) iwc[i] = iws * iwc[i\
    \ - 1], iws *= iW;\n  for (int i = 0; i < M; i++) f[i] *= iwc[i];\n  reverse(begin(f),\
    \ end(f));\n  fps g = f * wc;\n  fps F{begin(g) + M - 1, begin(g) + M + N - 1};\n\
    \  for (int i = 0; i < N; i++) F[i] *= iwc[i];\n  return F;\n}\n\n/**\n * @brief\
    \ Chirp Z-transform(Bluestein's algorithm)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: ntt/chirp-z.hpp
  requiredBy:
  - ntt/multivariate-circular-convolution.hpp
  timestamp: '2026-06-06 19:38:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-yosupo-ntt/yosupo-multipoint-evaluation-chirp-z.test.cpp
  - verify/verify-yosupo-ntt/yosupo-convolution-chirp-z.test.cpp
  - verify/verify-yosupo-ntt/yosupo-multivariate-circular-convolution.test.cpp
documentation_of: ntt/chirp-z.hpp
layout: document
redirect_from:
- /library/ntt/chirp-z.hpp
- /library/ntt/chirp-z.hpp.html
title: Chirp Z-transform(Bluestein's algorithm)
---
