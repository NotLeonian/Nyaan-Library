---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint/barrett-reduction.hpp
    title: modint/barrett-reduction.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-yosupo-math/yosupo-binomial-coefficient.test.cpp
    title: verify/verify-yosupo-math/yosupo-binomial-coefficient.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4EFB\u610Fmod\u4E8C\u9805\u4FC2\u6570"
    links: []
  bundledCode: "#line 2 \"modulo/arbitrary-mod-binomial.hpp\"\n\n#include <vector>\n\
    \n#line 1 \"atcoder/math.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <tuple>\n#line 8 \"atcoder/math.hpp\"\n\n#line 1 \"atcoder/internal_math.hpp\"\
    \n\n\n\n#include <utility>\n\n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\n\
    namespace atcoder {\n\nnamespace internal {\n\n// @param m `1 <= m`\n// @return\
    \ x mod m\nconstexpr long long safe_mod(long long x, long long m) {\n    x %=\
    \ m;\n    if (x < 0) x += m;\n    return x;\n}\n\n// Fast modular multiplication\
    \ by barrett reduction\n// Reference: https://en.wikipedia.org/wiki/Barrett_reduction\n\
    // NOTE: reconsider after Ice Lake\nstruct barrett {\n    unsigned int _m;\n \
    \   unsigned long long im;\n\n    // @param m `1 <= m`\n    explicit barrett(unsigned\
    \ int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}\n\n    // @return m\n\
    \    unsigned int umod() const { return _m; }\n\n    // @param a `0 <= a < m`\n\
    \    // @param b `0 <= b < m`\n    // @return `a * b % m`\n    unsigned int mul(unsigned\
    \ int a, unsigned int b) const {\n        // [1] m = 1\n        // a = b = im\
    \ = 0, so okay\n\n        // [2] m >= 2\n        // im = ceil(2^64 / m)\n    \
    \    // -> im * m = 2^64 + r (0 <= r < m)\n        // let z = a*b = c*m + d (0\
    \ <= c, d < m)\n        // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64\
    \ + c*r + d*im\n        // c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64\
    \ + m * (m + 1) < 2^64 * 2\n        // ((ab * im) >> 64) == c or c + 1\n     \
    \   unsigned long long z = a;\n        z *= b;\n#ifdef _MSC_VER\n        unsigned\
    \ long long x;\n        _umul128(z, im, &x);\n#else\n        unsigned long long\
    \ x =\n            (unsigned long long)(((unsigned __int128)(z)*im) >> 64);\n\
    #endif\n        unsigned long long y = x * _m;\n        return (unsigned int)(z\
    \ - y + (z < y ? _m : 0));\n    }\n};\n\n// @param n `0 <= n`\n// @param m `1\
    \ <= m`\n// @return `(x ** n) % m`\nconstexpr long long pow_mod_constexpr(long\
    \ long x, long long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m\
    \ = (unsigned int)(m);\n    unsigned long long r = 1;\n    unsigned long long\
    \ y = safe_mod(x, m);\n    while (n) {\n        if (n & 1) r = (r * y) % _m;\n\
    \        y = (y * y) % _m;\n        n >>= 1;\n    }\n    return r;\n}\n\n// Reference:\n\
    // M. Forisek and J. Jancina,\n// Fast Primality Testing for Integers That Fit\
    \ into a Machine Word\n// @param n `0 <= n`\nconstexpr bool is_prime_constexpr(int\
    \ n) {\n    if (n <= 1) return false;\n    if (n == 2 || n == 7 || n == 61) return\
    \ true;\n    if (n % 2 == 0) return false;\n    long long d = n - 1;\n    while\
    \ (d % 2 == 0) d /= 2;\n    constexpr long long bases[3] = {2, 7, 61};\n    for\
    \ (long long a : bases) {\n        long long t = d;\n        long long y = pow_mod_constexpr(a,\
    \ t, n);\n        while (t != n - 1 && y != 1 && y != n - 1) {\n            y\
    \ = y * y % n;\n            t <<= 1;\n        }\n        if (y != n - 1 && t %\
    \ 2 == 0) {\n            return false;\n        }\n    }\n    return true;\n}\n\
    template <int n> constexpr bool is_prime = is_prime_constexpr(n);\n\n// @param\
    \ b `1 <= b`\n// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x\
    \ < b/g\nconstexpr std::pair<long long, long long> inv_gcd(long long a, long long\
    \ b) {\n    a = safe_mod(a, b);\n    if (a == 0) return {b, 0};\n\n    // Contracts:\n\
    \    // [1] s - m0 * a = 0 (mod b)\n    // [2] t - m1 * a = 0 (mod b)\n    //\
    \ [3] s * |m1| + t * |m0| <= b\n    long long s = b, t = a;\n    long long m0\
    \ = 0, m1 = 1;\n\n    while (t) {\n        long long u = s / t;\n        s -=\
    \ t * u;\n        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b\n\n        // [3]:\n\
    \        // (s - t * u) * |m1| + t * |m0 - m1 * u|\n        // <= s * |m1| - t\
    \ * u * |m1| + t * (|m0| + |m1| * u)\n        // = s * |m1| + t * |m0| <= b\n\n\
    \        auto tmp = s;\n        s = t;\n        t = tmp;\n        tmp = m0;\n\
    \        m0 = m1;\n        m1 = tmp;\n    }\n    // by [3]: |m0| <= b/g\n    //\
    \ by g != b: |m0| < b/g\n    if (m0 < 0) m0 += b / s;\n    return {s, m0};\n}\n\
    \n// Compile time primitive root\n// @param m must be prime\n// @return primitive\
    \ root (and minimum in now)\nconstexpr int primitive_root_constexpr(int m) {\n\
    \    if (m == 2) return 1;\n    if (m == 167772161) return 3;\n    if (m == 469762049)\
    \ return 3;\n    if (m == 754974721) return 11;\n    if (m == 998244353) return\
    \ 3;\n    int divs[20] = {};\n    divs[0] = 2;\n    int cnt = 1;\n    int x =\
    \ (m - 1) / 2;\n    while (x % 2 == 0) x /= 2;\n    for (int i = 3; (long long)(i)*i\
    \ <= x; i += 2) {\n        if (x % i == 0) {\n            divs[cnt++] = i;\n \
    \           while (x % i == 0) {\n                x /= i;\n            }\n   \
    \     }\n    }\n    if (x > 1) {\n        divs[cnt++] = x;\n    }\n    for (int\
    \ g = 2;; g++) {\n        bool ok = true;\n        for (int i = 0; i < cnt; i++)\
    \ {\n            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {\n    \
    \            ok = false;\n                break;\n            }\n        }\n \
    \       if (ok) return g;\n    }\n}\ntemplate <int m> constexpr int primitive_root\
    \ = primitive_root_constexpr(m);\n\n// @param n `n < 2^32`\n// @param m `1 <=\
    \ m < 2^32`\n// @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)\nunsigned\
    \ long long floor_sum_unsigned(unsigned long long n,\n                       \
    \               unsigned long long m,\n                                      unsigned\
    \ long long a,\n                                      unsigned long long b) {\n\
    \    unsigned long long ans = 0;\n    while (true) {\n        if (a >= m) {\n\
    \            ans += n * (n - 1) / 2 * (a / m);\n            a %= m;\n        }\n\
    \        if (b >= m) {\n            ans += n * (b / m);\n            b %= m;\n\
    \        }\n\n        unsigned long long y_max = a * n + b;\n        if (y_max\
    \ < m) break;\n        // y_max < m * (n + 1)\n        // floor(y_max / m) <=\
    \ n\n        n = (unsigned long long)(y_max / m);\n        b = (unsigned long\
    \ long)(y_max % m);\n        std::swap(m, a);\n    }\n    return ans;\n}\n\n}\
    \  // namespace internal\n\n}  // namespace atcoder\n\n\n#line 10 \"atcoder/math.hpp\"\
    \n\nnamespace atcoder {\n\nlong long pow_mod(long long x, long long n, int m)\
    \ {\n    assert(0 <= n && 1 <= m);\n    if (m == 1) return 0;\n    internal::barrett\
    \ bt((unsigned int)(m));\n    unsigned int r = 1, y = (unsigned int)(internal::safe_mod(x,\
    \ m));\n    while (n) {\n        if (n & 1) r = bt.mul(r, y);\n        y = bt.mul(y,\
    \ y);\n        n >>= 1;\n    }\n    return r;\n}\n\nlong long inv_mod(long long\
    \ x, long long m) {\n    assert(1 <= m);\n    auto z = internal::inv_gcd(x, m);\n\
    \    assert(z.first == 1);\n    return z.second;\n}\n\n// (rem, mod)\nstd::pair<long\
    \ long, long long> crt(const std::vector<long long>& r,\n                    \
    \                const std::vector<long long>& m) {\n    assert(r.size() == m.size());\n\
    \    int n = int(r.size());\n    // Contracts: 0 <= r0 < m0\n    long long r0\
    \ = 0, m0 = 1;\n    for (int i = 0; i < n; i++) {\n        assert(1 <= m[i]);\n\
    \        long long r1 = internal::safe_mod(r[i], m[i]), m1 = m[i];\n        if\
    \ (m0 < m1) {\n            std::swap(r0, r1);\n            std::swap(m0, m1);\n\
    \        }\n        if (m0 % m1 == 0) {\n            if (r0 % m1 != r1) return\
    \ {0, 0};\n            continue;\n        }\n        // assume: m0 > m1, lcm(m0,\
    \ m1) >= 2 * max(m0, m1)\n\n        // (r0, m0), (r1, m1) -> (r2, m2 = lcm(m0,\
    \ m1));\n        // r2 % m0 = r0\n        // r2 % m1 = r1\n        // -> (r0 +\
    \ x*m0) % m1 = r1\n        // -> x*u0*g = r1-r0 (mod u1*g) (u0*g = m0, u1*g =\
    \ m1)\n        // -> x = (r1 - r0) / g * inv(u0) (mod u1)\n\n        // im = inv(u0)\
    \ (mod u1) (0 <= im < u1)\n        long long g, im;\n        std::tie(g, im) =\
    \ internal::inv_gcd(m0, m1);\n\n        long long u1 = (m1 / g);\n        // |r1\
    \ - r0| < (m0 + m1) <= lcm(m0, m1)\n        if ((r1 - r0) % g) return {0, 0};\n\
    \n        // u1 * u1 <= m1 * m1 / g / g <= m0 * m1 / g = lcm(m0, m1)\n       \
    \ long long x = (r1 - r0) / g % u1 * im % u1;\n\n        // |r0| + |m0 * x|\n\
    \        // < m0 + m0 * (u1 - 1)\n        // = m0 + m0 * m1 / g - m0\n       \
    \ // = lcm(m0, m1)\n        r0 += x * m0;\n        m0 *= u1;  // -> lcm(m0, m1)\n\
    \        if (r0 < 0) r0 += m0;\n    }\n    return {r0, m0};\n}\n\nlong long floor_sum(long\
    \ long n, long long m, long long a, long long b) {\n    assert(0 <= n && n < (1LL\
    \ << 32));\n    assert(1 <= m && m < (1LL << 32));\n    unsigned long long ans\
    \ = 0;\n    if (a < 0) {\n        unsigned long long a2 = internal::safe_mod(a,\
    \ m);\n        ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);\n        a = a2;\n\
    \    }\n    if (b < 0) {\n        unsigned long long b2 = internal::safe_mod(b,\
    \ m);\n        ans -= 1ULL * n * ((b2 - b) / m);\n        b = b2;\n    }\n   \
    \ return ans + internal::floor_sum_unsigned(n, m, a, b);\n}\n\n}  // namespace\
    \ atcoder\n\n\n#line 2 \"modint/barrett-reduction.hpp\"\n\n#line 4 \"modint/barrett-reduction.hpp\"\
    \nusing namespace std;\n\nstruct Barrett {\n  using u32 = unsigned int;\n  using\
    \ i64 = long long;\n  using u64 = unsigned long long;\n  u32 m;\n  u64 im;\n \
    \ Barrett() : m(), im() {}\n  Barrett(int n) : m(n), im(u64(-1) / m + 1) {}\n\
    \  constexpr inline i64 quo(u64 n) {\n    u64 x = u64((__uint128_t(n) * im) >>\
    \ 64);\n    u32 r = n - x * m;\n    return m <= r ? x - 1 : x;\n  }\n  constexpr\
    \ inline i64 rem(u64 n) {\n    u64 x = u64((__uint128_t(n) * im) >> 64);\n   \
    \ u32 r = n - x * m;\n    return m <= r ? r + m : r;\n  }\n  constexpr inline\
    \ pair<i64, int> quorem(u64 n) {\n    u64 x = u64((__uint128_t(n) * im) >> 64);\n\
    \    u32 r = n - x * m;\n    if (m <= r) return {x - 1, r + m};\n    return {x,\
    \ r};\n  }\n  constexpr inline i64 pow(u64 n, i64 p) {\n    u32 a = rem(n), r\
    \ = m == 1 ? 0 : 1;\n    while (p) {\n      if (p & 1) r = rem(u64(r) * a);\n\
    \      a = rem(u64(a) * a);\n      p >>= 1;\n    }\n    return r;\n  }\n};\n#line\
    \ 7 \"modulo/arbitrary-mod-binomial.hpp\"\n\nusing namespace std;\n\n#define PRIME_POWER_BINOMIAL_M_MAX\
    \ ((1LL << 30) - 1)\n#define PRIME_POWER_BINOMIAL_N_MAX 20000000\n\nstruct prime_power_binomial\
    \ {\n  int p, q, M;\n  vector<int> fac, ifac, inv;\n  int delta;\n  Barrett bm,\
    \ bp;\n\n  prime_power_binomial(int _p, int _q) : p(_p), q(_q) {\n    assert(1\
    \ < p && p <= PRIME_POWER_BINOMIAL_M_MAX);\n    assert(_q > 0);\n    long long\
    \ m = 1;\n    while (_q--) {\n      m *= p;\n      assert(m <= PRIME_POWER_BINOMIAL_M_MAX);\n\
    \    }\n    M = m;\n    bm = Barrett(M), bp = Barrett(p);\n    enumerate();\n\
    \    delta = (p == 2 && q >= 3) ? 1 : M - 1;\n  }\n\n  void enumerate() {\n  \
    \  int MX = min<int>(M, PRIME_POWER_BINOMIAL_N_MAX + 10);\n    fac.resize(MX);\n\
    \    ifac.resize(MX);\n    inv.resize(MX);\n    fac[0] = ifac[0] = inv[0] = 1;\n\
    \    fac[1] = ifac[1] = inv[1] = 1;\n    for (int i = 2; i < MX; i++) {\n    \
    \  if (i % p == 0) {\n        fac[i] = fac[i - 1];\n        fac[i + 1] = bm.rem(1LL\
    \ * fac[i - 1] * (i + 1));\n        i++;\n      } else {\n        fac[i] = bm.rem(1LL\
    \ * fac[i - 1] * i);\n      }\n    }\n    ifac[MX - 1] = bm.pow(fac[MX - 1], M\
    \ / p * (p - 1) - 1);\n    for (int i = MX - 2; i > 1; --i) {\n      if (i % p\
    \ == 0) {\n        ifac[i] = bm.rem(1LL * ifac[i + 1] * (i + 1));\n        ifac[i\
    \ - 1] = ifac[i];\n        i--;\n      } else {\n        ifac[i] = bm.rem(1LL\
    \ * ifac[i + 1] * (i + 1));\n      }\n    }\n  }\n\n  long long Lucas(long long\
    \ n, long long m) {\n    int res = 1;\n    while (n) {\n      int n0, m0;\n  \
    \    tie(n, n0) = bp.quorem(n);\n      tie(m, m0) = bp.quorem(m);\n      if (n0\
    \ < m0) return 0;\n      res = bm.rem(1LL * res * fac[n0]);\n      int buf = bm.rem(1LL\
    \ * ifac[n0 - m0] * ifac[m0]);\n      res = bm.rem(1LL * res * buf);\n    }\n\
    \    return res;\n  }\n\n  long long C(long long n, long long m) {\n    if (n\
    \ < m || n < 0 || m < 0) return 0;\n    if (q == 1) return Lucas(n, m);\n    long\
    \ long r = n - m;\n    int e0 = 0, eq = 0, i = 0;\n    int res = 1;\n    while\
    \ (n) {\n      res = bm.rem(1LL * res * fac[bm.rem(n)]);\n      res = bm.rem(1LL\
    \ * res * ifac[bm.rem(m)]);\n      res = bm.rem(1LL * res * ifac[bm.rem(r)]);\n\
    \      n = bp.quo(n);\n      m = bp.quo(m);\n      r = bp.quo(r);\n      int eps\
    \ = n - m - r;\n      e0 += eps;\n      if (e0 >= q) return 0;\n      if (++i\
    \ >= q) eq += eps;\n    }\n    if (eq & 1) res = bm.rem(1LL * res * delta);\n\
    \    res = bm.rem(1LL * res * bm.pow(p, e0));\n    return res;\n  }\n};\n\n//\
    \ constraints:\n// (M <= 1e7 and max(N) <= 1e18) or (M < 2^30 and max(N) <= 2e7)\n\
    struct arbitrary_mod_binomial {\n  int mod;\n  vector<int> M;\n  vector<prime_power_binomial>\
    \ cs;\n\n  arbitrary_mod_binomial(long long md) : mod(md) {\n    assert(1 <= md);\n\
    \    assert(md <= PRIME_POWER_BINOMIAL_M_MAX);\n    for (int i = 2; i * i <= md;\
    \ i++) {\n      if (md % i == 0) {\n        int j = 0, k = 1;\n        while (md\
    \ % i == 0) md /= i, j++, k *= i;\n        M.push_back(k);\n        cs.emplace_back(i,\
    \ j);\n        assert(M.back() == cs.back().M);\n      }\n    }\n    if (md !=\
    \ 1) {\n      M.push_back(md);\n      cs.emplace_back(md, 1);\n    }\n    assert(M.size()\
    \ == cs.size());\n  }\n\n  long long C(long long n, long long m) {\n    if (mod\
    \ == 1) return 0;\n    vector<long long> rem, d;\n    for (int i = 0; i < (int)cs.size();\
    \ i++) {\n      rem.push_back(cs[i].C(n, m));\n      d.push_back(M[i]);\n    }\n\
    \    return atcoder::crt(rem, d).first;\n  }\n};\n\n#undef PRIME_POWER_BINOMIAL_M_MAX\n\
    #undef PRIME_POWER_BINOMIAL_N_MAX\n\n/**\n * @brief \u4EFB\u610Fmod\u4E8C\u9805\
    \u4FC2\u6570\n */\n"
  code: "#pragma once\n\n#include <vector>\n\n#include \"../atcoder/math.hpp\"\n#include\
    \ \"../modint/barrett-reduction.hpp\"\n\nusing namespace std;\n\n#define PRIME_POWER_BINOMIAL_M_MAX\
    \ ((1LL << 30) - 1)\n#define PRIME_POWER_BINOMIAL_N_MAX 20000000\n\nstruct prime_power_binomial\
    \ {\n  int p, q, M;\n  vector<int> fac, ifac, inv;\n  int delta;\n  Barrett bm,\
    \ bp;\n\n  prime_power_binomial(int _p, int _q) : p(_p), q(_q) {\n    assert(1\
    \ < p && p <= PRIME_POWER_BINOMIAL_M_MAX);\n    assert(_q > 0);\n    long long\
    \ m = 1;\n    while (_q--) {\n      m *= p;\n      assert(m <= PRIME_POWER_BINOMIAL_M_MAX);\n\
    \    }\n    M = m;\n    bm = Barrett(M), bp = Barrett(p);\n    enumerate();\n\
    \    delta = (p == 2 && q >= 3) ? 1 : M - 1;\n  }\n\n  void enumerate() {\n  \
    \  int MX = min<int>(M, PRIME_POWER_BINOMIAL_N_MAX + 10);\n    fac.resize(MX);\n\
    \    ifac.resize(MX);\n    inv.resize(MX);\n    fac[0] = ifac[0] = inv[0] = 1;\n\
    \    fac[1] = ifac[1] = inv[1] = 1;\n    for (int i = 2; i < MX; i++) {\n    \
    \  if (i % p == 0) {\n        fac[i] = fac[i - 1];\n        fac[i + 1] = bm.rem(1LL\
    \ * fac[i - 1] * (i + 1));\n        i++;\n      } else {\n        fac[i] = bm.rem(1LL\
    \ * fac[i - 1] * i);\n      }\n    }\n    ifac[MX - 1] = bm.pow(fac[MX - 1], M\
    \ / p * (p - 1) - 1);\n    for (int i = MX - 2; i > 1; --i) {\n      if (i % p\
    \ == 0) {\n        ifac[i] = bm.rem(1LL * ifac[i + 1] * (i + 1));\n        ifac[i\
    \ - 1] = ifac[i];\n        i--;\n      } else {\n        ifac[i] = bm.rem(1LL\
    \ * ifac[i + 1] * (i + 1));\n      }\n    }\n  }\n\n  long long Lucas(long long\
    \ n, long long m) {\n    int res = 1;\n    while (n) {\n      int n0, m0;\n  \
    \    tie(n, n0) = bp.quorem(n);\n      tie(m, m0) = bp.quorem(m);\n      if (n0\
    \ < m0) return 0;\n      res = bm.rem(1LL * res * fac[n0]);\n      int buf = bm.rem(1LL\
    \ * ifac[n0 - m0] * ifac[m0]);\n      res = bm.rem(1LL * res * buf);\n    }\n\
    \    return res;\n  }\n\n  long long C(long long n, long long m) {\n    if (n\
    \ < m || n < 0 || m < 0) return 0;\n    if (q == 1) return Lucas(n, m);\n    long\
    \ long r = n - m;\n    int e0 = 0, eq = 0, i = 0;\n    int res = 1;\n    while\
    \ (n) {\n      res = bm.rem(1LL * res * fac[bm.rem(n)]);\n      res = bm.rem(1LL\
    \ * res * ifac[bm.rem(m)]);\n      res = bm.rem(1LL * res * ifac[bm.rem(r)]);\n\
    \      n = bp.quo(n);\n      m = bp.quo(m);\n      r = bp.quo(r);\n      int eps\
    \ = n - m - r;\n      e0 += eps;\n      if (e0 >= q) return 0;\n      if (++i\
    \ >= q) eq += eps;\n    }\n    if (eq & 1) res = bm.rem(1LL * res * delta);\n\
    \    res = bm.rem(1LL * res * bm.pow(p, e0));\n    return res;\n  }\n};\n\n//\
    \ constraints:\n// (M <= 1e7 and max(N) <= 1e18) or (M < 2^30 and max(N) <= 2e7)\n\
    struct arbitrary_mod_binomial {\n  int mod;\n  vector<int> M;\n  vector<prime_power_binomial>\
    \ cs;\n\n  arbitrary_mod_binomial(long long md) : mod(md) {\n    assert(1 <= md);\n\
    \    assert(md <= PRIME_POWER_BINOMIAL_M_MAX);\n    for (int i = 2; i * i <= md;\
    \ i++) {\n      if (md % i == 0) {\n        int j = 0, k = 1;\n        while (md\
    \ % i == 0) md /= i, j++, k *= i;\n        M.push_back(k);\n        cs.emplace_back(i,\
    \ j);\n        assert(M.back() == cs.back().M);\n      }\n    }\n    if (md !=\
    \ 1) {\n      M.push_back(md);\n      cs.emplace_back(md, 1);\n    }\n    assert(M.size()\
    \ == cs.size());\n  }\n\n  long long C(long long n, long long m) {\n    if (mod\
    \ == 1) return 0;\n    vector<long long> rem, d;\n    for (int i = 0; i < (int)cs.size();\
    \ i++) {\n      rem.push_back(cs[i].C(n, m));\n      d.push_back(M[i]);\n    }\n\
    \    return atcoder::crt(rem, d).first;\n  }\n};\n\n#undef PRIME_POWER_BINOMIAL_M_MAX\n\
    #undef PRIME_POWER_BINOMIAL_N_MAX\n\n/**\n * @brief \u4EFB\u610Fmod\u4E8C\u9805\
    \u4FC2\u6570\n */\n"
  dependsOn:
  - modint/barrett-reduction.hpp
  isVerificationFile: false
  path: modulo/arbitrary-mod-binomial.hpp
  requiredBy: []
  timestamp: '2026-06-08 17:59:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-yosupo-math/yosupo-binomial-coefficient.test.cpp
documentation_of: modulo/arbitrary-mod-binomial.hpp
layout: document
title: "\u4EFB\u610Fmod\u4E8C\u9805\u4FC2\u6570"
---

## 任意mod二項係数

$\binom{n}{m} \mod M$を前計算$\mathrm{O}(\min(\frac{n\log M}{\log \log M},M))$、クエリ$\mathrm{O}(\frac{\log n \log M}{\log \log M})$で計算するライブラリ。

### 概要

[論文](https://github.com/rishirajsinghjhelumi/Coding-Templates/blob/master/Extras/BinCoeff.pdf)　[ferinさんの記事](https://ferin-tech.hatenablog.com/entry/2018/01/17/010829)　[hly1204さんの記事](https://hly1204.github.io/blog/1-12-2021-Lucas_theorem/)

$\binom{n}{m} \mod p^q$を計算出来ればCRTで$\binom{n}{m} \mod M$を復元できるので、ここでは素数冪に限定して議論する。

### $\binom{n}{m} \pmod p$の公式

$\binom{n}{m} \mod p$は比較的容易に計算できる。

#### Lucasの定理

> $\binom{n}{k} \mod p$は
> 
> $$n = a_r p^r + \cdots + a_1 p + a_0$$
> 
> $$k = b_r p^r + \cdots + b_1 p + b_0$$
>
>としたとき次の式で表される。
>
>$$\binom{n}{k} \equiv \prod_{i=0}^r \binom{a_i}{b_i} \pmod p$$
>

(証明)

$$(1+x)^n \equiv \prod_{i=0}^r ((1+x)^{p^i})^{a_i}$$

$$\equiv \prod_{i=0}^r (1 + x^{p^i})^{a_i} \equiv \prod_{i=0}^r \left(\sum_j \binom{a_i}{j} x^{jp^i}\right) \pmod p$$

と変形できるので、

$$\binom{n}{k} \equiv \lbrack x^k \rbrack (1 + x)^n$$

と合わせて上式を得る。

### $\binom{n}{m}\mod p^k$の公式

法が素数冪の場合は様々な定理を用いて計算する必要がある。

#### Willsonの定理

> 素数$p$に対して次の合同式が成り立つ。
>
> $$(p - 1)! \equiv -1 \pmod p$$

(証明) $\mod p$上で$1,\ldots,p-1$は逆元をただ一つ持つ。そのうち$a^2 \equiv 1 \pmod p \iff a \equiv \pm 1 \pmod p$を除いた$a=2,\ldots,p-2$は逆元を$2$から$p-2$の中に持つことから、$\prod_{a=2}^{p-2} a\equiv 1$を得る。よって$(p-1)! \equiv 1 \cdot (-1) \equiv -1 \pmod p$になる。

#### 補題1

> 整数$n$に対して$(n!)_p$を$p$の倍数を除いた$n$以下の正整数の総積と置く。このとき素数冪$p^q$に対して
> 
> $$(p^q !)_p \equiv \delta \pmod {p^q}$$
>
> が成り立つ。ただし$\delta$は$p=2,q\geq 3$の時は$1$、それ以外の時は$-1$とする。

(証明) Willsonの定理と同様に証明する。$\mod p^q$上で$p$と互いに素な数は唯一の逆元を持つため、$a^2 \not \equiv 1 \pmod {p^q}$である$a$の総積は$1$である。$a^2 \equiv 1 \pmod {p^q}$の解は

$$a=\left\lbrace
\begin{array}{cc} 
1 & p = 2 \wedge q = 1\newline
\pm 1, 2^{q-1} \pm 1 & p = 2 \wedge q \geq 3 \newline
\pm 1 & \mathrm{otherwise}
\end{array}
\right.
$$

であるから、$\delta$は$p=2,q\geq 3$のとき$1$でそれ以外は$-1$になる。

また、$n \geq p^q$である$n$に対して補題を適用すると、$n = N_0 \bmod{p^q}$とおいて

$$(n!)_p \equiv \delta ^{\lfloor n / p^q \rfloor} (N_0!)_p  \pmod{p ^ q}$$

という式が導かれる。

#### Legendreの定理ととKummerの定理

Legendreの定理とは次の有名な定理である。(証明略)

> $n!$が$p$で割り切れる回数$\nu_p(n!)$は次の式で表される。
> 
> $$\nu_p(n!) =\sum_{1 \leq i} \left\lfloor \frac{n}{p^i} \right\rfloor $$

ここで次の補題2を考える。

> $n$を$p$進数表示したときの各桁の和を$\sigma_p(n)$とおくと、$\sigma_p(n)$と$\nu_p(n!)$の間には次の関係式が成り立つ。
>
> $$ \nu_p(n!) = \frac{n - \sigma_p(n)}{p - 1}$$
>

証明は帰納的に行うことが出来る。

この補題を利用すると、次に説明するKummerの定理が証明できる。

>
> $\binom{n}{m}$が$p$で割り切れる回数は$n-m$と$m$を$p$進数表示で足し算した時の繰り上がりの回数と等しい。
>

(証明)

$r = n - m$とおき、$p$進表示を$n = \sum_i n_i p^i$のように表すとする。また、$\epsilon_j$を$j$桁目で繰り上がりが起きた時$1$、起きないとき$0$を表す数とする。このとき、

$$n_j = m_j + r_j + \epsilon _{j-1} - p \epsilon_j$$

であり、

$$\nu_p\left(\frac{n!}{m!r!}\right) = \nu_p(n!) - \nu_p(m!) - \nu_p(r!) $$

$$ = \frac{\sigma_p(m) + \sigma_p(r) - \sigma_p(n)}{p - 1} $$

$$= \sum_j \frac{m_j + r_j - n_j}{p - 1}$$

$$= \sum_j \frac{\epsilon_j - p\epsilon_{j-1}}{p - 1} = \sum_j \epsilon_j$$

を得る。なお、$\epsilon_j$は次の式によって得られる。(Kummerの定理から従う。)

$$\epsilon_j = \left\lfloor \frac{n}{p^{j+1}}\right\rfloor - \left\lfloor \frac{m}{p^{j+1}}\right\rfloor - \left\lfloor \frac{r}{p^{j+1}}\right\rfloor$$

#### $n! \pmod {p^q}$の公式

> 正整数$n$と素数冪$p^q$に対して次の関係式が成り立つ。
> 
> $${n!} / {p^{\sum_{j \geq 1} \lfloor n / p^j \rfloor }} \equiv \delta^{\sum_{j \geq q} \lfloor n / p^j \rfloor} \prod_{j \geq 0} (N_j !)_p \pmod{p^q}$$
>
> ただし$N_j$は$\lfloor n / p^j \rfloor$と$\mod p^q$で合同な最小の非負整数とする。

(証明)

$j \geq 0$のとき

$$\lfloor n / p^j \rfloor ! / (p ^ {\lfloor n / p^{j + 1} \rfloor } \lfloor n / p^{j + 1} \rfloor ! ) \equiv (\lfloor n / p^{j} \rfloor !)_p $$

$$\equiv \delta^{\lfloor n / p^{j + q} \rfloor} (N_j !)_p \pmod{p ^ q}$$

であるから、$j \geq 0$について上式を辺々掛ければ示せる。

#### $\binom{n}{m} \pmod {p^q}$の公式

上の式からただちに二項係数に対する以下の関係式が従う。

> 非負整数$n,m$と素数冪$p^q$について以下の式が成り立つ。
> 
> $$\frac{1}{p^{e_0}}\binom{n}{m} = \delta^{e_{q-1}} \prod_{j \geq 0} \frac{(N_j!)_p}{(M_j!)_p (R_j!)_p}$$
> 
> ただし$e_j$は$j$桁目以上で繰り上がりが発生した回数で、次の式で表される。
>
> $$e_j = \sum_{j \lt i}\left(\left\lfloor \frac{n}{p^{i}}\right\rfloor - \left\lfloor \frac{m}{p^{i}}\right\rfloor - \left\lfloor \frac{r}{p^{i}}\right\rfloor\right)$$

$a \lt \min(n,p^q)$に対して$(a!)_p \bmod{p^q}$と$(a!)_p^{-1} \bmod{p^q}$を前計算しておくことで上の式は$\mathrm{O}(\log n)$で計算できる。

### Barrett Reductionによる高速化

このライブラリではBarrett Reductionによる剰余算の高速化を行っているが、その正当性を示しておく。

[参考: AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/internal_math.hpp)

> $n \lt B = 2^{64}, 1 \lt m \leq 2^{30}$のとき、
>
> $$x = \left\lceil \frac{B}{m} \right\rceil$$
>
> とおくと
> 
> $$ \left\lfloor \frac{nx}{B} \right\rfloor = \left\lfloor \frac{n}{m} \right\rfloor + \varepsilon $$
>
> が成り立つ。($\varepsilon$は$0$または$1$)

(証明) $x$の定義より

$$xm = B + r\ (0 \leq r \lt M)$$

が成り立つので、

$$ 0 \gt \frac{n}{m} - \frac{nx}{B} = n\left(\frac{1}{m} - \frac{x}{B} \right)$$

$$=-\frac{n}{B}\cdot \frac{r}{M} \gt -1$$

であることから従う。(実用上は$m = 1$の時に$x$がオーバーフローすることに注意する必要がある。)
