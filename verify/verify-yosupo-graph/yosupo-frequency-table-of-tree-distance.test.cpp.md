---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: internal/internal-type-traits.hpp
    title: internal/internal-type-traits.hpp
  - icon: ':heavy_check_mark:'
    path: misc/fastio.hpp
    title: misc/fastio.hpp
  - icon: ':heavy_check_mark:'
    path: ntt/arbitrary-ntt-mod18446744069414584321.hpp
    title: ntt/arbitrary-ntt-mod18446744069414584321.hpp
  - icon: ':heavy_check_mark:'
    path: template/bitop.hpp
    title: template/bitop.hpp
  - icon: ':heavy_check_mark:'
    path: template/debug.hpp
    title: template/debug.hpp
  - icon: ':heavy_check_mark:'
    path: template/inout.hpp
    title: template/inout.hpp
  - icon: ':heavy_check_mark:'
    path: template/macro.hpp
    title: template/macro.hpp
  - icon: ':heavy_check_mark:'
    path: template/template.hpp
    title: template/template.hpp
  - icon: ':heavy_check_mark:'
    path: template/util.hpp
    title: template/util.hpp
  - icon: ':heavy_check_mark:'
    path: tree/centroid-decomposition.hpp
    title: Centroid Decomposition
  - icon: ':heavy_check_mark:'
    path: tree/frequency-table-of-tree-distance.hpp
    title: "\u9802\u70B9\u9593\u306E\u8DDD\u96E2\u306E\u5EA6\u6570\u5206\u5E03"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
    links:
    - https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
  bundledCode: "#line 1 \"verify/verify-yosupo-graph/yosupo-frequency-table-of-tree-distance.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#line 2 \"template/template.hpp\"\nusing namespace std;\n\n// intrinstic\n\
    #include <immintrin.h>\n\n#include <algorithm>\n#include <array>\n#include <bitset>\n\
    #include <cassert>\n#include <cctype>\n#include <cfenv>\n#include <cfloat>\n#include\
    \ <chrono>\n#include <cinttypes>\n#include <climits>\n#include <cmath>\n#include\
    \ <complex>\n#include <cstdarg>\n#include <cstddef>\n#include <cstdint>\n#include\
    \ <cstdio>\n#include <cstdlib>\n#include <cstring>\n#include <deque>\n#include\
    \ <fstream>\n#include <functional>\n#include <initializer_list>\n#include <iomanip>\n\
    #include <ios>\n#include <iostream>\n#include <istream>\n#include <iterator>\n\
    #include <limits>\n#include <list>\n#include <map>\n#include <memory>\n#include\
    \ <new>\n#include <numeric>\n#include <ostream>\n#include <queue>\n#include <random>\n\
    #include <set>\n#include <sstream>\n#include <stack>\n#include <streambuf>\n#include\
    \ <string>\n#include <tuple>\n#include <type_traits>\n#include <typeinfo>\n#include\
    \ <unordered_map>\n#include <unordered_set>\n#include <utility>\n#include <vector>\n\
    \n// utility\n#line 3 \"template/util.hpp\"\n\nnamespace Nyaan {\nusing ll = long\
    \ long;\nusing i64 = long long;\nusing u64 = unsigned long long;\nusing i128 =\
    \ __int128_t;\nusing u128 = __uint128_t;\n\ntemplate <typename T>\nusing V = vector<T>;\n\
    template <typename T>\nusing VV = vector<vector<T>>;\nusing vi = vector<int>;\n\
    using vl = vector<long long>;\nusing vd = V<double>;\nusing vs = V<string>;\n\
    using vvi = vector<vector<int>>;\nusing vvl = vector<vector<long long>>;\ntemplate\
    \ <typename T>\nusing minpq = priority_queue<T, vector<T>, greater<T>>;\n\ntemplate\
    \ <typename T, typename U>\nstruct P : pair<T, U> {\n  template <typename... Args>\n\
    \  P(Args... args) : pair<T, U>(args...) {}\n\n  using pair<T, U>::first;\n  using\
    \ pair<T, U>::second;\n\n  P &operator+=(const P &r) {\n    first += r.first;\n\
    \    second += r.second;\n    return *this;\n  }\n  P &operator-=(const P &r)\
    \ {\n    first -= r.first;\n    second -= r.second;\n    return *this;\n  }\n\
    \  P &operator*=(const P &r) {\n    first *= r.first;\n    second *= r.second;\n\
    \    return *this;\n  }\n  template <typename S>\n  P &operator*=(const S &r)\
    \ {\n    first *= r, second *= r;\n    return *this;\n  }\n  P operator+(const\
    \ P &r) const { return P(*this) += r; }\n  P operator-(const P &r) const { return\
    \ P(*this) -= r; }\n  P operator*(const P &r) const { return P(*this) *= r; }\n\
    \  template <typename S>\n  P operator*(const S &r) const {\n    return P(*this)\
    \ *= r;\n  }\n  P operator-() const { return P{-first, -second}; }\n};\n\nusing\
    \ pl = P<ll, ll>;\nusing pi = P<int, int>;\nusing vp = V<pl>;\n\nconstexpr int\
    \ inf = 1001001001;\nconstexpr long long infLL = 4004004004004004004LL;\n\ntemplate\
    \ <typename T>\nint sz(const T &t) {\n  return t.size();\n}\n\ntemplate <typename\
    \ T, typename U>\ninline bool amin(T &x, U y) {\n  return (y < x) ? (x = y, true)\
    \ : false;\n}\ntemplate <typename T, typename U>\ninline bool amax(T &x, U y)\
    \ {\n  return (x < y) ? (x = y, true) : false;\n}\n\ntemplate <typename T>\ninline\
    \ T Max(const vector<T> &v) {\n  return *max_element(begin(v), end(v));\n}\ntemplate\
    \ <typename T>\ninline T Min(const vector<T> &v) {\n  return *min_element(begin(v),\
    \ end(v));\n}\ntemplate <typename T>\ninline long long Sum(const vector<T> &v)\
    \ {\n  return accumulate(begin(v), end(v), 0LL);\n}\n\ntemplate <typename T>\n\
    int lb(const vector<T> &v, const T &a) {\n  return lower_bound(begin(v), end(v),\
    \ a) - begin(v);\n}\ntemplate <typename T>\nint ub(const vector<T> &v, const T\
    \ &a) {\n  return upper_bound(begin(v), end(v), a) - begin(v);\n}\n\nconstexpr\
    \ long long TEN(int n) {\n  long long ret = 1, x = 10;\n  for (; n; x *= x, n\
    \ >>= 1) ret *= (n & 1 ? x : 1);\n  return ret;\n}\n\ntemplate <typename T, typename\
    \ U>\npair<T, U> mkp(const T &t, const U &u) {\n  return make_pair(t, u);\n}\n\
    \ntemplate <typename T>\nvector<T> mkrui(const vector<T> &v, bool rev = false)\
    \ {\n  vector<T> ret(v.size() + 1);\n  if (rev) {\n    for (int i = int(v.size())\
    \ - 1; i >= 0; i--) ret[i] = v[i] + ret[i + 1];\n  } else {\n    for (int i =\
    \ 0; i < int(v.size()); i++) ret[i + 1] = ret[i] + v[i];\n  }\n  return ret;\n\
    };\n\ntemplate <typename T>\nvector<T> mkuni(const vector<T> &v) {\n  vector<T>\
    \ ret(v);\n  sort(ret.begin(), ret.end());\n  ret.erase(unique(ret.begin(), ret.end()),\
    \ ret.end());\n  return ret;\n}\n\ntemplate <typename F>\nvector<int> mkord(int\
    \ N, F f) {\n  vector<int> ord(N);\n  iota(begin(ord), end(ord), 0);\n  sort(begin(ord),\
    \ end(ord), f);\n  return ord;\n}\n\ntemplate <typename T>\nvector<int> mkinv(vector<T>\
    \ &v) {\n  int max_val = *max_element(begin(v), end(v));\n  vector<int> inv(max_val\
    \ + 1, -1);\n  for (int i = 0; i < (int)v.size(); i++) inv[v[i]] = i;\n  return\
    \ inv;\n}\n\nvector<int> mkiota(int n) {\n  vector<int> ret(n);\n  iota(begin(ret),\
    \ end(ret), 0);\n  return ret;\n}\n\ntemplate <typename T>\nT mkrev(const T &v)\
    \ {\n  T w{v};\n  reverse(begin(w), end(w));\n  return w;\n}\n\ntemplate <typename\
    \ T>\nbool nxp(T &v) {\n  return next_permutation(begin(v), end(v));\n}\n\n//\
    \ \u8FD4\u308A\u5024\u306E\u578B\u306F\u5165\u529B\u306E T \u306B\u4F9D\u5B58\n\
    // i \u8981\u7D20\u76EE : [0, a[i])\ntemplate <typename T>\nvector<vector<T>>\
    \ product(const vector<T> &a) {\n  vector<vector<T>> ret;\n  vector<T> v;\n  auto\
    \ dfs = [&](auto rc, int i) -> void {\n    if (i == (int)a.size()) {\n      ret.push_back(v);\n\
    \      return;\n    }\n    for (int j = 0; j < a[i]; j++) v.push_back(j), rc(rc,\
    \ i + 1), v.pop_back();\n  };\n  dfs(dfs, 0);\n  return ret;\n}\n\n// F : void(T&),\
    \ mod \u3092\u53D6\u308B\u64CD\u4F5C\n// T : \u6574\u6570\u578B\u306E\u3068\u304D\
    \u306F\u30AA\u30FC\u30D0\u30FC\u30D5\u30ED\u30FC\u306B\u6CE8\u610F\u3059\u308B\
    \ntemplate <typename T, typename F>\nT Power(T a, long long n, const T &I, F &&f)\
    \ {\n  static_assert(std::is_invocable_r_v<void, F &, T &>,\n                \"\
    Power callback must be callable as void(T&)\");\n  T res = I;\n  for (; n; std::invoke(f,\
    \ a = a * a), n >>= 1) {\n    if (n & 1) std::invoke(f, res = res * a);\n  }\n\
    \  return res;\n}\n// T : \u6574\u6570\u578B\u306E\u3068\u304D\u306F\u30AA\u30FC\
    \u30D0\u30FC\u30D5\u30ED\u30FC\u306B\u6CE8\u610F\u3059\u308B\ntemplate <typename\
    \ T>\nT Power(T a, long long n, const T &I = T{1}) {\n  auto no_op = [](T &) ->\
    \ void {};\n  return Power(a, n, I, no_op);\n}\n\ntemplate <typename T>\nT Rev(const\
    \ T &v) {\n  T res = v;\n  reverse(begin(res), end(res));\n  return res;\n}\n\n\
    template <typename T>\nvector<T> Transpose(const vector<T> &v) {\n  using U =\
    \ typename T::value_type;\n  if(v.empty()) return {};\n  int H = v.size(), W =\
    \ v[0].size();\n  vector res(W, T(H, U{}));\n  for (int i = 0; i < H; i++) {\n\
    \    for (int j = 0; j < W; j++) {\n      res[j][i] = v[i][j];\n    }\n  }\n \
    \ return res;\n}\n\ntemplate <typename T>\nvector<T> Rotate(const vector<T> &v,\
    \ int clockwise = true) {\n  using U = typename T::value_type;\n  int H = v.size(),\
    \ W = v[0].size();\n  vector res(W, T(H, U{}));\n  for (int i = 0; i < H; i++)\
    \ {\n    for (int j = 0; j < W; j++) {\n      if (clockwise) {\n        res[W\
    \ - 1 - j][i] = v[i][j];\n      } else {\n        res[j][H - 1 - i] = v[i][j];\n\
    \      }\n    }\n  }\n  return res;\n}\n\n}  // namespace Nyaan\n#line 58 \"template/template.hpp\"\
    \n\n// bit operation\n#line 1 \"template/bitop.hpp\"\nnamespace Nyaan {\n__attribute__((target(\"\
    popcnt\"))) inline int popcnt(const u64 &a) {\n  return __builtin_popcountll(a);\n\
    }\ninline int lsb(const u64 &a) { return a ? __builtin_ctzll(a) : 64; }\ninline\
    \ int ctz(const u64 &a) { return a ? __builtin_ctzll(a) : 64; }\ninline int msb(const\
    \ u64 &a) { return a ? 63 - __builtin_clzll(a) : -1; }\ntemplate <typename T>\n\
    inline int gbit(const T &a, int i) {\n  return (a >> i) & 1;\n}\ntemplate <typename\
    \ T>\ninline void sbit(T &a, int i, bool b) {\n  if (gbit(a, i) != b) a ^= T(1)\
    \ << i;\n}\nconstexpr long long PW(int n) { return 1LL << n; }\nconstexpr long\
    \ long MSK(int n) { return (1LL << n) - 1; }\n}  // namespace Nyaan\n#line 61\
    \ \"template/template.hpp\"\n\n// inout\n#line 1 \"template/inout.hpp\"\nnamespace\
    \ Nyaan {\n\ntemplate <typename T, typename U>\nostream &operator<<(ostream &os,\
    \ const pair<T, U> &p) {\n  os << p.first << \" \" << p.second;\n  return os;\n\
    }\ntemplate <typename T, typename U>\nistream &operator>>(istream &is, pair<T,\
    \ U> &p) {\n  is >> p.first >> p.second;\n  return is;\n}\n\ntemplate <typename\
    \ T>\nostream &operator<<(ostream &os, const vector<T> &v) {\n  int s = (int)v.size();\n\
    \  for (int i = 0; i < s; i++) os << (i ? \" \" : \"\") << v[i];\n  return os;\n\
    }\ntemplate <typename T>\nistream &operator>>(istream &is, vector<T> &v) {\n \
    \ for (auto &x : v) is >> x;\n  return is;\n}\n\nistream &operator>>(istream &is,\
    \ __int128_t &x) {\n  string S;\n  is >> S;\n  x = 0;\n  int flag = 0;\n  for\
    \ (auto &c : S) {\n    if (c == '-') {\n      flag = true;\n      continue;\n\
    \    }\n    x *= 10;\n    x += c - '0';\n  }\n  if (flag) x = -x;\n  return is;\n\
    }\n\nistream &operator>>(istream &is, __uint128_t &x) {\n  string S;\n  is >>\
    \ S;\n  x = 0;\n  for (auto &c : S) {\n    x *= 10;\n    x += c - '0';\n  }\n\
    \  return is;\n}\n\nostream &operator<<(ostream &os, __int128_t x) {\n  if (x\
    \ == 0) return os << 0;\n  if (x < 0) os << '-', x = -x;\n  string S;\n  while\
    \ (x) S.push_back('0' + x % 10), x /= 10;\n  reverse(begin(S), end(S));\n  return\
    \ os << S;\n}\nostream &operator<<(ostream &os, __uint128_t x) {\n  if (x == 0)\
    \ return os << 0;\n  string S;\n  while (x) S.push_back('0' + x % 10), x /= 10;\n\
    \  reverse(begin(S), end(S));\n  return os << S;\n}\n\nvoid in() {}\ntemplate\
    \ <typename T, class... U>\nvoid in(T &t, U &...u) {\n  cin >> t;\n  in(u...);\n\
    }\n\nvoid out() { cout << \"\\n\"; }\ntemplate <typename T, class... U, char sep\
    \ = ' '>\nvoid out(const T &t, const U &...u) {\n  cout << t;\n  if (sizeof...(u))\
    \ cout << sep;\n  out(u...);\n}\n\nstruct IoSetupNya {\n  IoSetupNya() {\n   \
    \ cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed << setprecision(15);\n\
    \    cerr << fixed << setprecision(7);\n  }\n} iosetupnya;\n\n}  // namespace\
    \ Nyaan\n#line 64 \"template/template.hpp\"\n\n// debug\n#line 1 \"template/debug.hpp\"\
    \nnamespace DebugImpl {\n\ntemplate <typename U, typename = void>\nstruct is_specialize\
    \ : false_type {};\ntemplate <typename U>\nstruct is_specialize<\n    U, typename\
    \ conditional<false, typename U::iterator, void>::type>\n    : true_type {};\n\
    template <typename U>\nstruct is_specialize<\n    U, typename conditional<false,\
    \ decltype(U::first), void>::type>\n    : true_type {};\ntemplate <typename U>\n\
    struct is_specialize<U, enable_if_t<is_integral<U>::value, void>> : true_type\
    \ {\n};\n\nvoid dump(const char& t) { cerr << t; }\n\nvoid dump(const string&\
    \ t) { cerr << t; }\n\nvoid dump(const bool& t) { cerr << (t ? \"true\" : \"false\"\
    ); }\n\nvoid dump(__int128_t t) {\n  if (t == 0) cerr << 0;\n  if (t < 0) cerr\
    \ << '-', t = -t;\n  string S;\n  while (t) S.push_back('0' + t % 10), t /= 10;\n\
    \  reverse(begin(S), end(S));\n  cerr << S;\n}\n\nvoid dump(__uint128_t t) {\n\
    \  if (t == 0) cerr << 0;\n  string S;\n  while (t) S.push_back('0' + t % 10),\
    \ t /= 10;\n  reverse(begin(S), end(S));\n  cerr << S;\n}\n\ntemplate <typename\
    \ U,\n          enable_if_t<!is_specialize<U>::value, nullptr_t> = nullptr>\n\
    void dump(const U& t) {\n  cerr << t;\n}\n\ntemplate <typename T>\nvoid dump(const\
    \ T& t, enable_if_t<is_integral<T>::value>* = nullptr) {\n  string res;\n  if\
    \ (t == Nyaan::inf) res = \"inf\";\n  if constexpr (is_signed<T>::value) {\n \
    \   if (t == -Nyaan::inf) res = \"-inf\";\n  }\n  if constexpr (sizeof(T) == 8)\
    \ {\n    if (t == Nyaan::infLL) res = \"inf\";\n    if constexpr (is_signed<T>::value)\
    \ {\n      if (t == -Nyaan::infLL) res = \"-inf\";\n    }\n  }\n  if (res.empty())\
    \ res = to_string(t);\n  cerr << res;\n}\n\ntemplate <typename T, typename U>\n\
    void dump(const pair<T, U>&);\ntemplate <typename T>\nvoid dump(const pair<T*,\
    \ int>&);\n\ntemplate <typename T>\nvoid dump(const T& t,\n          enable_if_t<!is_void<typename\
    \ T::iterator>::value>* = nullptr) {\n  cerr << \"[ \";\n  for (auto it = t.begin();\
    \ it != t.end();) {\n    dump(*it);\n    cerr << (++it == t.end() ? \"\" : \"\
    , \");\n  }\n  cerr << \" ]\";\n}\n\ntemplate <typename T, typename U>\nvoid dump(const\
    \ pair<T, U>& t) {\n  cerr << \"( \";\n  dump(t.first);\n  cerr << \", \";\n \
    \ dump(t.second);\n  cerr << \" )\";\n}\n\ntemplate <typename T>\nvoid dump(const\
    \ pair<T*, int>& t) {\n  cerr << \"[ \";\n  for (int i = 0; i < t.second; i++)\
    \ {\n    dump(t.first[i]);\n    cerr << (i == t.second - 1 ? \"\" : \", \");\n\
    \  }\n  cerr << \" ]\";\n}\n\nvoid trace() { cerr << endl; }\ntemplate <typename\
    \ Head, typename... Tail>\nvoid trace(Head&& head, Tail&&... tail) {\n  cerr <<\
    \ \" \";\n  dump(head);\n  if (sizeof...(tail) != 0) cerr << \",\";\n  trace(std::forward<Tail>(tail)...);\n\
    }\n\n}  // namespace DebugImpl\n\n#ifdef NyaanDebug\n#define trc(...)        \
    \                    \\\n  do {                                      \\\n    cerr\
    \ << \"## \" << #__VA_ARGS__ << \" = \"; \\\n    DebugImpl::trace(__VA_ARGS__);\
    \          \\\n  } while (0)\n#else\n#define trc(...) (void(0))\n#endif\n\n#ifdef\
    \ NyaanLocal\n#define trc2(...)                           \\\n  do {         \
    \                             \\\n    cerr << \"## \" << #__VA_ARGS__ << \" =\
    \ \"; \\\n    DebugImpl::trace(__VA_ARGS__);          \\\n  } while (0)\n#else\n\
    #define trc2(...) (void(0))\n#endif\n#line 67 \"template/template.hpp\"\n\n//\
    \ macro\n#line 1 \"template/macro.hpp\"\n#define each(x, v) for (auto&& x : v)\n\
    #define each2(x, y, v) for (auto&& [x, y] : v)\n#define all(v) (v).begin(), (v).end()\n\
    #define rep(i, N) for (long long i = 0; i < (long long)(N); i++)\n#define repr(i,\
    \ N) for (long long i = (long long)(N)-1; i >= 0; i--)\n#define rep1(i, N) for\
    \ (long long i = 1; i <= (long long)(N); i++)\n#define repr1(i, N) for (long long\
    \ i = (N); (long long)(i) > 0; i--)\n#define reg(i, a, b) for (long long i = (a);\
    \ i < (b); i++)\n#define regr(i, a, b) for (long long i = (b)-1; i >= (a); i--)\n\
    #define fi first\n#define se second\n#define ini(...)   \\\n  int __VA_ARGS__;\
    \ \\\n  in(__VA_ARGS__)\n#define inl(...)         \\\n  long long __VA_ARGS__;\
    \ \\\n  in(__VA_ARGS__)\n#define ins(...)      \\\n  string __VA_ARGS__; \\\n\
    \  in(__VA_ARGS__)\n#define in2(s, t)                           \\\n  for (int\
    \ i = 0; i < (int)s.size(); i++) { \\\n    in(s[i], t[i]);                   \
    \      \\\n  }\n#define in3(s, t, u)                        \\\n  for (int i =\
    \ 0; i < (int)s.size(); i++) { \\\n    in(s[i], t[i], u[i]);                 \
    \  \\\n  }\n#define in4(s, t, u, v)                     \\\n  for (int i = 0;\
    \ i < (int)s.size(); i++) { \\\n    in(s[i], t[i], u[i], v[i]);             \\\
    \n  }\n#define die(...)             \\\n  do {                       \\\n    Nyaan::out(__VA_ARGS__);\
    \ \\\n    return;                  \\\n  } while (0)\n#line 70 \"template/template.hpp\"\
    \n\nnamespace Nyaan {\nvoid solve();\n}\nint main() { Nyaan::solve(); }\n#line\
    \ 4 \"verify/verify-yosupo-graph/yosupo-frequency-table-of-tree-distance.test.cpp\"\
    \n\n#line 2 \"misc/fastio.hpp\"\n\n#line 9 \"misc/fastio.hpp\"\n\nusing namespace\
    \ std;\n\n#line 2 \"internal/internal-type-traits.hpp\"\n\n#line 4 \"internal/internal-type-traits.hpp\"\
    \nusing namespace std;\n\nnamespace internal {\ntemplate <typename T>\nusing is_broadly_integral\
    \ =\n    typename conditional_t<is_integral_v<T> || is_same_v<T, __int128_t> ||\n\
    \                               is_same_v<T, __uint128_t>,\n                 \
    \          true_type, false_type>::type;\n\ntemplate <typename T>\nusing is_broadly_signed\
    \ =\n    typename conditional_t<is_signed_v<T> || is_same_v<T, __int128_t>,\n\
    \                           true_type, false_type>::type;\n\ntemplate <typename\
    \ T>\nusing is_broadly_unsigned =\n    typename conditional_t<is_unsigned_v<T>\
    \ || is_same_v<T, __uint128_t>,\n                           true_type, false_type>::type;\n\
    \n#define ENABLE_VALUE(x) \\\n  template <typename T> \\\n  constexpr bool x##_v\
    \ = x<T>::value;\n\nENABLE_VALUE(is_broadly_integral);\nENABLE_VALUE(is_broadly_signed);\n\
    ENABLE_VALUE(is_broadly_unsigned);\n#undef ENABLE_VALUE\n\n#define ENABLE_HAS_TYPE(var)\
    \                                   \\\n  template <class, class = void>     \
    \                          \\\n  struct has_##var : false_type {};           \
    \                 \\\n  template <class T>                                   \
    \        \\\n  struct has_##var<T, void_t<typename T::var>> : true_type {}; \\\
    \n  template <class T>                                           \\\n  constexpr\
    \ auto has_##var##_v = has_##var<T>::value;\n\n#define ENABLE_HAS_VAR(var)   \
    \                                  \\\n  template <class, class = void>      \
    \                          \\\n  struct has_##var : false_type {};           \
    \                  \\\n  template <class T>                                  \
    \          \\\n  struct has_##var<T, void_t<decltype(T::var)>> : true_type {};\
    \ \\\n  template <class T>                                            \\\n  constexpr\
    \ auto has_##var##_v = has_##var<T>::value;\n\n}  // namespace internal\n#line\
    \ 13 \"misc/fastio.hpp\"\n\nnamespace fastio {\nstatic constexpr int SZ = 1 <<\
    \ 17;\nstatic constexpr int offset = 64;\nchar inbuf[SZ], outbuf[SZ];\nint in_left\
    \ = 0, in_right = 0, out_right = 0;\n\nstruct Pre {\n  char num[40000];\n  constexpr\
    \ Pre() : num() {\n    for (int i = 0; i < 10000; i++) {\n      int n = i;\n \
    \     for (int j = 3; j >= 0; j--) {\n        num[i * 4 + j] = n % 10 + '0';\n\
    \        n /= 10;\n      }\n    }\n  }\n} constexpr pre;\n\nvoid load() {\n  int\
    \ len = in_right - in_left;\n  memmove(inbuf, inbuf + in_left, len);\n  in_right\
    \ = len + fread(inbuf + len, 1, SZ - len, stdin);\n  in_left = 0;\n}\nvoid flush()\
    \ {\n  fwrite(outbuf, 1, out_right, stdout);\n  out_right = 0;\n}\nvoid skip_space()\
    \ {\n  if (in_left + offset > in_right) load();\n  while (inbuf[in_left] <= '\
    \ ') in_left++;\n}\n\nvoid single_read(char& c) {\n  if (in_left + offset > in_right)\
    \ load();\n  skip_space();\n  c = inbuf[in_left++];\n}\nvoid single_read(string&\
    \ S) {\n  skip_space();\n  while (true) {\n    if (in_left == in_right) load();\n\
    \    int i = in_left;\n    for (; i != in_right; i++) {\n      if (inbuf[i] <=\
    \ ' ') break;\n    }\n    copy(inbuf + in_left, inbuf + i, back_inserter(S));\n\
    \    in_left = i;\n    if (i != in_right) break;\n  }\n}\ntemplate <typename T,\n\
    \          enable_if_t<internal::is_broadly_integral_v<T>>* = nullptr>\nvoid single_read(T&\
    \ x) {\n  if (in_left + offset > in_right) load();\n  skip_space();\n  char c\
    \ = inbuf[in_left++];\n  [[maybe_unused]] bool minus = false;\n  if constexpr\
    \ (internal::is_broadly_signed_v<T>) {\n    if (c == '-') minus = true, c = inbuf[in_left++];\n\
    \  }\n  x = 0;\n  while (c >= '0') {\n    x = x * 10 + (c & 15);\n    c = inbuf[in_left++];\n\
    \  }\n  if constexpr (internal::is_broadly_signed_v<T>) {\n    if (minus) x =\
    \ -x;\n  }\n}\nvoid rd() {}\ntemplate <typename Head, typename... Tail>\nvoid\
    \ rd(Head& head, Tail&... tail) {\n  single_read(head);\n  rd(tail...);\n}\n\n\
    void single_write(const char& c) {\n  if (out_right > SZ - offset) flush();\n\
    \  outbuf[out_right++] = c;\n}\nvoid single_write(const bool& b) {\n  if (out_right\
    \ > SZ - offset) flush();\n  outbuf[out_right++] = b ? '1' : '0';\n}\nvoid single_write(const\
    \ string& S) {\n  flush(), fwrite(S.data(), 1, S.size(), stdout);\n}\nvoid single_write(const\
    \ char* p) { flush(), fwrite(p, 1, strlen(p), stdout); }\ntemplate <typename T,\n\
    \          enable_if_t<internal::is_broadly_integral_v<T>>* = nullptr>\nvoid single_write(const\
    \ T& _x) {\n  if (out_right > SZ - offset) flush();\n  if (_x == 0) {\n    outbuf[out_right++]\
    \ = '0';\n    return;\n  }\n  T x = _x;\n  if constexpr (internal::is_broadly_signed_v<T>)\
    \ {\n    if (x < 0) outbuf[out_right++] = '-', x = -x;\n  }\n  constexpr int buffer_size\
    \ = sizeof(T) * 10 / 4;\n  char buf[buffer_size];\n  int i = buffer_size;\n  while\
    \ (x >= 10000) {\n    i -= 4;\n    memcpy(buf + i, pre.num + (x % 10000) * 4,\
    \ 4);\n    x /= 10000;\n  }\n  if (x < 100) {\n    if (x < 10) {\n      outbuf[out_right]\
    \ = '0' + x;\n      ++out_right;\n    } else {\n      uint32_t q = (uint32_t(x)\
    \ * 205) >> 11;\n      uint32_t r = uint32_t(x) - q * 10;\n      outbuf[out_right]\
    \ = '0' + q;\n      outbuf[out_right + 1] = '0' + r;\n      out_right += 2;\n\
    \    }\n  } else {\n    if (x < 1000) {\n      memcpy(outbuf + out_right, pre.num\
    \ + (x << 2) + 1, 3);\n      out_right += 3;\n    } else {\n      memcpy(outbuf\
    \ + out_right, pre.num + (x << 2), 4);\n      out_right += 4;\n    }\n  }\n  memcpy(outbuf\
    \ + out_right, buf + i, buffer_size - i);\n  out_right += buffer_size - i;\n}\n\
    void wt() {}\ntemplate <typename Head, typename... Tail>\nvoid wt(const Head&\
    \ head, const Tail&... tail) {\n  single_write(head);\n  wt(std::forward<const\
    \ Tail>(tail)...);\n}\ntemplate <typename... Args>\nvoid wtn(const Args&... x)\
    \ {\n  wt(std::forward<const Args>(x)...);\n  wt('\\n');\n}\n\nstruct Dummy {\n\
    \  Dummy() { atexit(flush); }\n} dummy;\n\n}  // namespace fastio\nusing fastio::rd;\n\
    using fastio::skip_space;\nusing fastio::wt;\nusing fastio::wtn;\n#line 6 \"verify/verify-yosupo-graph/yosupo-frequency-table-of-tree-distance.test.cpp\"\
    \n\n#line 2 \"tree/frequency-table-of-tree-distance.hpp\"\n\n#line 2 \"ntt/arbitrary-ntt-mod18446744069414584321.hpp\"\
    \n\n#line 7 \"ntt/arbitrary-ntt-mod18446744069414584321.hpp\"\nusing namespace\
    \ std;\n\nstruct ModInt18446744069414584321 {\n  using M = ModInt18446744069414584321;\n\
    \  using U = unsigned long long;\n  using U128 = __uint128_t;\n\n  static constexpr\
    \ U mod = 18446744069414584321uLL;\n  U x;\n\n  static constexpr U modulo(U128\
    \ y) {\n    U l = y & U(-1);\n    U m = (y >> 64) & unsigned(-1);\n    U h = y\
    \ >> 96;\n    U u = h + m + (m ? mod - (m << 32) : 0);\n    U v = mod <= l ? l\
    \ - mod : l;\n    return v - u + (v < u ? mod : 0);\n  }\n\n  ModInt18446744069414584321()\
    \ : x(0) {}\n  ModInt18446744069414584321(U _x) : x(_x) {}\n  U get() const {\
    \ return x; }\n  static U get_mod() { return mod; }\n\n  friend M operator+(const\
    \ M& l, const M& r) {\n    U y = l.x - (mod - r.x);\n    if (l.x < mod - r.x)\
    \ y += mod;\n    return M{y};\n  }\n  friend M operator-(const M& l, const M&\
    \ r) {\n    U y = l.x - r.x;\n    if (l.x < r.x) y += mod;\n    return M{y};\n\
    \  }\n  friend M operator*(const M& l, const M& r) {\n    return M{modulo(U128(l.x)\
    \ * r.x)};\n  }\n  friend M operator/(const M& l, const M& r) {\n    return M{modulo(U128(l.x)\
    \ * r.inverse().x)};\n  }\n\n  M& operator+=(const M& r) { return *this = *this\
    \ + r; }\n  M& operator-=(const M& r) { return *this = *this - r; }\n  M& operator*=(const\
    \ M& r) { return *this = *this * r; }\n  M& operator/=(const M& r) { return *this\
    \ = *this / r; }\n  M operator-() const { return M{x ? mod - x : 0uLL}; }\n  M\
    \ operator+() const { return *this; }\n\n  M pow(U e) const {\n    M res{1}, a{*this};\n\
    \    while (e) {\n      if (e & 1) res = res * a;\n      a = a * a;\n      e >>=\
    \ 1;\n    }\n    return res;\n  }\n  M inverse() const {\n    assert(x != 0);\n\
    \    return this->pow(mod - 2);\n  }\n\n  friend bool operator==(const M& l, const\
    \ M& r) { return l.x == r.x; }\n  friend bool operator!=(const M& l, const M&\
    \ r) { return l.x != r.x; }\n  friend ostream& operator<<(ostream& os, const M&\
    \ r) { return os << r.x; }\n};\n\nstruct NTT18446744069414584321 {\n  using mint\
    \ = ModInt18446744069414584321;\n  using U = typename mint::U;\n\n  static constexpr\
    \ U mod = mint::mod;\n  static constexpr U pr = 7;\n  static constexpr int level\
    \ = 32;\n  mint dw[level], dy[level];\n\n  void setwy(int k) {\n    mint w[level],\
    \ y[level];\n    w[k - 1] = mint(pr).pow((mod - 1) / (1LL << k));\n    y[k - 1]\
    \ = w[k - 1].inverse();\n    for (int i = k - 2; i > 0; --i)\n      w[i] = w[i\
    \ + 1] * w[i + 1], y[i] = y[i + 1] * y[i + 1];\n    dw[1] = w[1], dy[1] = y[1],\
    \ dw[2] = w[2], dy[2] = y[2];\n    for (int i = 3; i < k; ++i) {\n      dw[i]\
    \ = dw[i - 1] * y[i - 2] * w[i];\n      dy[i] = dy[i - 1] * w[i - 2] * y[i];\n\
    \    }\n  }\n\n  NTT18446744069414584321() { setwy(level); }\n\n  void fft(vector<mint>&\
    \ a, int k) {\n    if ((int)a.size() <= 1) return;\n    if (k == 1) {\n      mint\
    \ a1 = a[1];\n      a[1] = a[0] - a[1];\n      a[0] = a[0] + a1;\n      return;\n\
    \    }\n    if (k & 1) {\n      int v = 1 << (k - 1);\n      for (int j = 0; j\
    \ < v; ++j) {\n        mint ajv = a[j + v];\n        a[j + v] = a[j] - ajv;\n\
    \        a[j] += ajv;\n      }\n    }\n    int u = 1 << (2 + (k & 1));\n    int\
    \ v = 1 << (k - 2 - (k & 1));\n    mint one = mint(1);\n    mint imag = dw[1];\n\
    \    while (v) {\n      {\n        int j0 = 0;\n        int j1 = v;\n        int\
    \ j2 = j1 + v;\n        int j3 = j2 + v;\n        for (; j0 < v; ++j0, ++j1, ++j2,\
    \ ++j3) {\n          mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];\n  \
    \        mint t0p2 = t0 + t2, t1p3 = t1 + t3;\n          mint t0m2 = t0 - t2,\
    \ t1m3 = (t1 - t3) * imag;\n          a[j0] = t0p2 + t1p3, a[j1] = t0p2 - t1p3;\n\
    \          a[j2] = t0m2 + t1m3, a[j3] = t0m2 - t1m3;\n        }\n      }\n   \
    \   mint ww = one, xx = one * dw[2], wx = one;\n      for (int jh = 4; jh < u;)\
    \ {\n        ww = xx * xx, wx = ww * xx;\n        int j0 = jh * v;\n        int\
    \ je = j0 + v;\n        int j2 = je + v;\n        for (; j0 < je; ++j0, ++j2)\
    \ {\n          mint t0 = a[j0], t1 = a[j0 + v] * xx, t2 = a[j2] * ww,\n      \
    \         t3 = a[j2 + v] * wx;\n          mint t0p2 = t0 + t2, t1p3 = t1 + t3;\n\
    \          mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;\n          a[j0] = t0p2\
    \ + t1p3, a[j0 + v] = t0p2 - t1p3;\n          a[j2] = t0m2 + t1m3, a[j2 + v] =\
    \ t0m2 - t1m3;\n        }\n        xx *= dw[__builtin_ctzll((jh += 4))];\n   \
    \   }\n      u <<= 2;\n      v >>= 2;\n    }\n  }\n\n  void ifft(vector<mint>&\
    \ a, int k) {\n    if ((int)a.size() <= 1) return;\n    if (k == 1) {\n      mint\
    \ a1 = a[1];\n      a[1] = a[0] - a[1];\n      a[0] = a[0] + a1;\n      return;\n\
    \    }\n    int u = 1 << (k - 2);\n    int v = 1;\n    mint one = mint(1);\n \
    \   mint imag = dy[1];\n    while (u) {\n      {\n        int j0 = 0;\n      \
    \  int j1 = v;\n        int j2 = v + v;\n        int j3 = j2 + v;\n        for\
    \ (; j0 < v; ++j0, ++j1, ++j2, ++j3) {\n          mint t0 = a[j0], t1 = a[j1],\
    \ t2 = a[j2], t3 = a[j3];\n          mint t0p1 = t0 + t1, t2p3 = t2 + t3;\n  \
    \        mint t0m1 = t0 - t1, t2m3 = (t2 - t3) * imag;\n          a[j0] = t0p1\
    \ + t2p3, a[j2] = t0p1 - t2p3;\n          a[j1] = t0m1 + t2m3, a[j3] = t0m1 -\
    \ t2m3;\n        }\n      }\n      mint ww = one, xx = one * dy[2], yy = one;\n\
    \      u <<= 2;\n      for (int jh = 4; jh < u;) {\n        ww = xx * xx, yy =\
    \ xx * imag;\n        int j0 = jh * v;\n        int je = j0 + v;\n        int\
    \ j2 = je + v;\n        for (; j0 < je; ++j0, ++j2) {\n          mint t0 = a[j0],\
    \ t1 = a[j0 + v], t2 = a[j2], t3 = a[j2 + v];\n          mint t0p1 = t0 + t1,\
    \ t2p3 = t2 + t3;\n          mint t0m1 = (t0 - t1) * xx, t2m3 = (t2 - t3) * yy;\n\
    \          a[j0] = t0p1 + t2p3, a[j2] = (t0p1 - t2p3) * ww;\n          a[j0 +\
    \ v] = t0m1 + t2m3, a[j2 + v] = (t0m1 - t2m3) * ww;\n        }\n        xx *=\
    \ dy[__builtin_ctzll(jh += 4)];\n      }\n      u >>= 4;\n      v <<= 2;\n   \
    \ }\n    if (k & 1) {\n      u = 1 << (k - 1);\n      for (int j = 0; j < u; ++j)\
    \ {\n        mint ajv = a[j] - a[j + u];\n        a[j] += a[j + u];\n        a[j\
    \ + u] = ajv;\n      }\n    }\n  }\n\n  void ntt(vector<mint>& a) {\n    if ((int)a.size()\
    \ <= 1) return;\n    fft(a, __builtin_ctz(a.size()));\n  }\n\n  void intt(vector<mint>&\
    \ a) {\n    if ((int)a.size() <= 1) return;\n    ifft(a, __builtin_ctz(a.size()));\n\
    \    mint iv = mint(a.size()).inverse();\n    for (auto& x : a) x *= iv;\n  }\n\
    \n  vector<mint> multiply(const vector<mint>& a, const vector<mint>& b) {\n  \
    \  int l = a.size() + b.size() - 1;\n    if (min<int>(a.size(), b.size()) <= 40)\
    \ {\n      vector<mint> s(l);\n      for (int i = 0; i < (int)a.size(); ++i)\n\
    \        for (int j = 0; j < (int)b.size(); ++j) s[i + j] += a[i] * b[j];\n  \
    \    return s;\n    }\n    int k = 2, M = 4;\n    while (M < l) M <<= 1, ++k;\n\
    \    setwy(k);\n    vector<mint> s(M);\n    for (int i = 0; i < (int)a.size();\
    \ ++i) s[i] = a[i];\n    if (a == b) {\n      fft(s, k);\n      for (int i = 0;\
    \ i < M; i++) s[i] *= s[i];\n    } else {\n      vector<mint> t(M);\n      for\
    \ (int i = 0; i < (int)b.size(); ++i) t[i] = b[i];\n      fft(s, k), fft(t, k);\n\
    \      for (int i = 0; i < M; ++i) s[i] *= t[i];\n    }\n    ifft(s, k);\n   \
    \ s.resize(l);\n    mint invm = mint(M).inverse();\n    for (int i = 0; i < l;\
    \ ++i) s[i] *= invm;\n    return s;\n  }\n\n  // \u3059\u3079\u3066\u306E\u8981\
    \u7D20\u304C\u6B63, \u304B\u3064\u7B54\u3048\u306E\u5404\u6210\u5206\u304C mod\
    \ \u4EE5\u4E0B\u3067\u3042\u308B\u5FC5\u8981\u304C\u3042\u308B\n  template <typename\
    \ I, enable_if_t<is_integral_v<I>>* = nullptr>\n  vector<unsigned long long> multiply(const\
    \ vector<I>& a, const vector<I>& b) {\n    if (min<int>(a.size(), b.size()) <=\
    \ 40) {\n      vector<U> c(a.size() + b.size() - 1);\n      for (int i = 0; i\
    \ < (int)a.size(); ++i) {\n        for (int j = 0; j < (int)b.size(); ++j) c[i\
    \ + j] += U(a[i]) * U(b[j]);\n      }\n      return c;\n    }\n    vector<mint>\
    \ s(a.size()), t(b.size());\n    for (int i = 0; i < (int)a.size(); i++) s[i]\
    \ = a[i];\n    for (int i = 0; i < (int)b.size(); i++) t[i] = b[i];\n    auto\
    \ u = multiply(s, t);\n    vector<U> c(u.size());\n    for (int i = 0; i < (int)c.size();\
    \ i++) c[i] = u[i].x;\n    return c;\n  }\n\n  vector<int> bigint_mul_base_10_9(const\
    \ vector<int>& a, const vector<int>& b) {\n    constexpr int D = 1000000000;\n\
    \    constexpr int B = 1000000;\n    constexpr int C = 1000;\n    auto convert\
    \ = [&](const vector<int>& v) -> vector<mint> {\n      vector<mint> c((v.size()\
    \ * 3 + 1) / 2);\n      int i = 0;\n      for (; i * 2 + 1 < (int)v.size(); i++)\
    \ {\n        c[i * 3 + 0].x = v[i * 2 + 0] % B;\n        c[i * 3 + 1].x = v[i\
    \ * 2 + 0] / B + v[i * 2 + 1] % C * C;\n        c[i * 3 + 2].x = v[i * 2 + 1]\
    \ / C;\n      }\n      if (i * 2 + 1 == (int)v.size()) {\n        c[i * 3 + 0].x\
    \ = v[i * 2 + 0] % B;\n        c[i * 3 + 1].x = v[i * 2 + 0] / B;\n      }\n \
    \     return c;\n    };\n    auto revert = [&](const vector<mint>& v) -> vector<int>\
    \ {\n      vector<int> c(v.size() + 4);\n      int i = 0;\n      U s = 0;\n  \
    \    for (; i < (int)v.size(); i++) s += v[i].x, c[i] = s % B, s /= B;\n     \
    \ while (s) c[i] = s % B, s /= B, i++;\n      while (!c.empty() && c.back() ==\
    \ 0) c.pop_back();\n      i = 0;\n      for (; i * 3 + 0 < (int)c.size(); i++)\
    \ {\n        long long x = c[i * 3 + 0];\n        c[i * 3 + 0] = 0;\n        if\
    \ (i * 3 + 1 < (int)c.size()) {\n          x += 1LL * c[i * 3 + 1] * B;\n    \
    \      c[i * 3 + 1] = 0;\n        }\n        if (i * 3 + 2 < (int)c.size()) {\n\
    \          x += 1LL * c[i * 3 + 2] * (1LL * B * B);\n          c[i * 3 + 2] =\
    \ 0;\n        }\n        c[i * 2 + 0] = x % D;\n        if (i * 2 + 1 < (int)c.size())\
    \ c[i * 2 + 1] = x / D;\n      }\n      while (!c.empty() && c.back() == 0) c.pop_back();\n\
    \      return c;\n    };\n    return revert(multiply(convert(a), convert(b)));\n\
    \  }\n};\n\nNTT18446744069414584321 ntt18446744069414584321;\n\n/**\n *  mod 18446744069414584321\
    \ (= 2^64 - 2^32 + 1) \u4E0A\u306E\u6570\u8AD6\u5909\u63DB\n */\n#line 2 \"tree/centroid-decomposition.hpp\"\
    \n\n\n\ntemplate <typename G>\nstruct CentroidDecomposition {\n  const G &g;\n\
    \  vector<int> sub;\n  vector<bool> v;\n  vector<vector<int>> tree;\n  int root;\n\
    \n  CentroidDecomposition(const G &g_, int isbuild = true) : g(g_) {\n    sub.resize(g.size(),\
    \ 0);\n    v.resize(g.size(), false);\n    if (isbuild) build();\n  }\n\n  void\
    \ build() {\n    tree.resize(g.size());\n    root = build_dfs(0);\n  }\n\n  int\
    \ get_size(int cur, int par) {\n    sub[cur] = 1;\n    for (auto &dst : g[cur])\
    \ {\n      if (dst == par || v[dst]) continue;\n      sub[cur] += get_size(dst,\
    \ cur);\n    }\n    return sub[cur];\n  }\n\n  int get_centroid(int cur, int par,\
    \ int mid) {\n    for (auto &dst : g[cur]) {\n      if (dst == par || v[dst])\
    \ continue;\n      if (sub[dst] > mid) return get_centroid(dst, cur, mid);\n \
    \   }\n    return cur;\n  }\n\n  int build_dfs(int cur) {\n    int centroid =\
    \ get_centroid(cur, -1, get_size(cur, -1) / 2);\n    v[centroid] = true;\n   \
    \ for (auto &dst : g[centroid]) {\n      if (!v[dst]) {\n        int nxt = build_dfs(dst);\n\
    \        if (centroid != nxt) tree[centroid].emplace_back(nxt);\n      }\n   \
    \ }\n    v[centroid] = false;\n    return centroid;\n  }\n};\n\n/**\n * @brief\
    \ Centroid Decomposition\n * @docs docs/tree/centroid-decomposition.md\n */\n\
    #line 5 \"tree/frequency-table-of-tree-distance.hpp\"\n\ntemplate <typename G>\n\
    struct FrequencyTableOfTreeDistance : CentroidDecomposition<G> {\n  using CentroidDecomposition<G>::g;\n\
    \  using CentroidDecomposition<G>::v;\n  using CentroidDecomposition<G>::get_size;\n\
    \  using CentroidDecomposition<G>::get_centroid;\n\n  FrequencyTableOfTreeDistance(const\
    \ G &_g)\n      : CentroidDecomposition<G>(_g, false) {}\n\n  vector<long long>\
    \ count, self;\n\n  void dfs_depth(int cur, int par, int d) {\n    while ((int)count.size()\
    \ <= d) count.emplace_back(0);\n    while ((int)self.size() <= d) self.emplace_back(0);\n\
    \    ++count[d];\n    ++self[d];\n    for (int dst : g[cur]) {\n      if (par\
    \ == dst || v[dst]) continue;\n      dfs_depth(dst, cur, d + 1);\n    }\n  };\n\
    \n  vector<long long> get(int start = 0) {\n    queue<int> Q;\n    Q.push(get_centroid(start,\
    \ -1, get_size(start, -1) / 2));\n    vector<long long> ans;\n    ans.reserve(g.size());\n\
    \    count.reserve(g.size());\n    self.reserve(g.size());\n\n    while (!Q.empty())\
    \ {\n      int r = Q.front();\n      Q.pop();\n      count.clear();\n      v[r]\
    \ = 1;\n      for (auto &c : g[r]) {\n        if (v[c]) continue;\n        self.clear();\n\
    \        Q.emplace(get_centroid(c, -1, get_size(c, -1) / 2));\n        dfs_depth(c,\
    \ r, 1);\n        auto self2 = ntt18446744069414584321.multiply(self, self);\n\
    \        while (self2.size() > ans.size()) ans.emplace_back(0);\n        for (int\
    \ i = 0; i < (int)self2.size(); i++) ans[i] -= self2[i];\n      }\n      if (count.empty())\
    \ continue;\n      ++count[0];\n      auto count2 = ntt18446744069414584321.multiply(count,\
    \ count);\n      while (count2.size() > ans.size()) ans.emplace_back(0);\n   \
    \   for (int i = 0; i < (int)count2.size(); i++) ans[i] += count2[i];\n    }\n\
    \n    for (auto &x : ans) x >>= 1;\n    return ans;\n  }\n};\n\n/**\n * @brief\
    \ \u9802\u70B9\u9593\u306E\u8DDD\u96E2\u306E\u5EA6\u6570\u5206\u5E03\n * @docs\
    \ docs/tree/frequency-table-of-tree-distance.md\n */\n#line 8 \"verify/verify-yosupo-graph/yosupo-frequency-table-of-tree-distance.test.cpp\"\
    \n\nusing namespace Nyaan; void Nyaan::solve() {\n  int N;\n  rd(N);\n  vvi g(N);\n\
    \  rep(_, N - 1) {\n    int u, v;\n    rd(u, v);\n    g[u].push_back(v);\n   \
    \ g[v].push_back(u);\n  }\n  FrequencyTableOfTreeDistance<vvi> ft(g);\n  auto\
    \ d = ft.get();\n  d.resize(N);\n  rep1(i, N - 1) {\n    if (i != 1) wt(' ');\n\
    \    wt(d[i]);\n  }\n  wt('\\n');\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../misc/fastio.hpp\"\
    \n\n#include \"../../tree/frequency-table-of-tree-distance.hpp\"\n\nusing namespace\
    \ Nyaan; void Nyaan::solve() {\n  int N;\n  rd(N);\n  vvi g(N);\n  rep(_, N -\
    \ 1) {\n    int u, v;\n    rd(u, v);\n    g[u].push_back(v);\n    g[v].push_back(u);\n\
    \  }\n  FrequencyTableOfTreeDistance<vvi> ft(g);\n  auto d = ft.get();\n  d.resize(N);\n\
    \  rep1(i, N - 1) {\n    if (i != 1) wt(' ');\n    wt(d[i]);\n  }\n  wt('\\n');\n\
    }\n"
  dependsOn:
  - template/template.hpp
  - template/util.hpp
  - template/bitop.hpp
  - template/inout.hpp
  - template/debug.hpp
  - template/macro.hpp
  - misc/fastio.hpp
  - internal/internal-type-traits.hpp
  - tree/frequency-table-of-tree-distance.hpp
  - ntt/arbitrary-ntt-mod18446744069414584321.hpp
  - tree/centroid-decomposition.hpp
  isVerificationFile: true
  path: verify/verify-yosupo-graph/yosupo-frequency-table-of-tree-distance.test.cpp
  requiredBy: []
  timestamp: '2026-06-06 19:38:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/verify-yosupo-graph/yosupo-frequency-table-of-tree-distance.test.cpp
layout: document
redirect_from:
- /verify/verify/verify-yosupo-graph/yosupo-frequency-table-of-tree-distance.test.cpp
- /verify/verify/verify-yosupo-graph/yosupo-frequency-table-of-tree-distance.test.cpp.html
title: verify/verify-yosupo-graph/yosupo-frequency-table-of-tree-distance.test.cpp
---
