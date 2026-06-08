---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/geometry-base.hpp
    title: geometry/geometry-base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u5186\u304A\u3088\u3073 2 \u5186\u306E\u4EA4\u70B9\u306E\u5B58\
      \u5728\u5224\u5B9A"
    links: []
  bundledCode: "#line 2 \"geometry/circle.hpp\"\n\n#line 2 \"geometry/geometry-base.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <complex>\n\
    #include <iostream>\n#include <vector>\nusing namespace std;\n\nusing Real = long\
    \ double;\nconstexpr Real EPS = 1e-10;\nconstexpr Real pi = 3.141592653589793238462643383279L;\n\
    bool equals(Real a, Real b) { return fabs(b - a) < EPS; }\nint sign(Real a) {\
    \ return equals(a, 0) ? 0 : a > 0 ? 1 : -1; }\n\ntemplate <typename R>\nstruct\
    \ PointBase {\n  using P = PointBase;\n  R x, y;\n  PointBase() : x(0), y(0) {}\n\
    \  PointBase(R _x, R _y) : x(_x), y(_y) {}\n  template <typename T, typename U>\n\
    \  PointBase(const pair<T, U>& p) : x(p.first), y(p.second) {}\n\n  P operator+(const\
    \ P& r) const { return {x + r.x, y + r.y}; }\n  P operator-(const P& r) const\
    \ { return {x - r.x, y - r.y}; }\n  P operator*(R r) const { return {x * r, y\
    \ * r}; }\n  P operator/(R r) const { return {x / r, y / r}; }\n\n  P& operator+=(const\
    \ P& r) { return (*this) = (*this) + r; }\n  P& operator-=(const P& r) { return\
    \ (*this) = (*this) - r; }\n  P& operator*=(R r) { return (*this) = (*this) *\
    \ r; }\n  P& operator/=(R r) { return (*this) = (*this) / r; }\n\n  bool operator<(const\
    \ P& r) const { return x != r.x ? x < r.x : y < r.y; }\n  bool operator==(const\
    \ P& r) const { return x == r.x and y == r.y; }\n  bool operator!=(const P& r)\
    \ const { return !((*this) == r); }\n\n  P rotate(R rad) const {\n    return {x\
    \ * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)};\n  }\n\n  R real()\
    \ const { return x; }\n  R imag() const { return y; }\n  friend R real(const P&\
    \ p) { return p.x; }\n  friend R imag(const P& p) { return p.y; }\n  friend R\
    \ dot(const P& l, const P& r) { return l.x * r.x + l.y * r.y; }\n  friend R cross(const\
    \ P& l, const P& r) { return l.x * r.y - l.y * r.x; }\n  friend R abs(const P&\
    \ p) { return sqrt(p.x * p.x + p.y * p.y); }\n  friend R norm(const P& p) { return\
    \ p.x * p.x + p.y * p.y; }\n  friend R arg(const P& p) { return atan2(p.y, p.x);\
    \ }\n\n  friend istream& operator>>(istream& is, P& p) {\n    R a, b;\n    is\
    \ >> a >> b;\n    p = P{a, b};\n    return is;\n  }\n  friend ostream& operator<<(ostream&\
    \ os, const P& p) {\n    return os << p.x << \" \" << p.y;\n  }\n};\nusing Point\
    \ = PointBase<Real>;\nusing Points = vector<Point>;\n\n// ccw, \u70B9\u306E\u9032\
    \u884C\u65B9\u5411\nint ccw(const Point& a, const Point& b, const Point& c) {\n\
    \  Point x = b - a, y = c - a;\n  if (cross(x, y) > EPS) return +1;          \
    \       // \u53CD\u6642\u8A08\u56DE\u308A\n  if (cross(x, y) < -EPS) return -1;\
    \                // \u6642\u8A08\u56DE\u308A\n  if (min(norm(x), norm(y)) < EPS\
    \ * EPS) return 0;  // c=a \u307E\u305F\u306F c=b\n  if (dot(x, y) < EPS) return\
    \ +2;                   // c-a-b \u306E\u9806\u3067\u4E00\u76F4\u7DDA\n  if (norm(x)\
    \ < norm(y)) return -2;                 // a-b-c \u306E\u9806\u3067\u4E00\u76F4\
    \u7DDA\n  return 0;                                         // a-c-b \u306E\u9806\
    \u3067\u4E00\u76F4\u7DDA\n}\n#line 4 \"geometry/circle.hpp\"\n\nstruct Circle\
    \ {\n  Point p;\n  Real r;\n\n  Circle() = default;\n  Circle(Point _p, Real _r)\
    \ : p(_p), r(_r) {}\n};\n\nusing Circles = vector<Circle>;\n\nint intersect(Circle\
    \ c1, Circle c2) {\n  if (c1.r < c2.r) swap(c1, c2);\n  Real d = abs(c1.p - c2.p);\n\
    \  if (c1.r + c2.r < d) return 4;\n  if (equals(c1.r + c2.r, d)) return 3;\n \
    \ if (c1.r - c2.r < d) return 2;\n  if (equals(c1.r - c2.r, d)) return 1;\n  return\
    \ 0;\n}\n\npair<Point, Point> crosspoint(const Circle& c1, const Circle& c2) {\n\
    \  Real d = abs(c1.p - c2.p);\n  Real x = (c1.r * c1.r + d * d - c2.r * c2.r)\
    \ / (2 * c1.r * d);\n  if (abs(x) > 1) x = (x > 0 ? 1.0 : -1.0);\n  Real a = acos(x);\n\
    \  Real t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());\n  Point\
    \ p1 = c1.p + Point(cos(t + a) * c1.r, sin(t + a) * c1.r);\n  Point p2 = c1.p\
    \ + Point(cos(t - a) * c1.r, sin(t - a) * c1.r);\n  return {p1, p2};\n}\n\n/**\n\
    \ * @brief \u5186\u304A\u3088\u3073 2 \u5186\u306E\u4EA4\u70B9\u306E\u5B58\u5728\
    \u5224\u5B9A\n */\n"
  code: "#pragma once\n\n#include \"geometry-base.hpp\"\n\nstruct Circle {\n  Point\
    \ p;\n  Real r;\n\n  Circle() = default;\n  Circle(Point _p, Real _r) : p(_p),\
    \ r(_r) {}\n};\n\nusing Circles = vector<Circle>;\n\nint intersect(Circle c1,\
    \ Circle c2) {\n  if (c1.r < c2.r) swap(c1, c2);\n  Real d = abs(c1.p - c2.p);\n\
    \  if (c1.r + c2.r < d) return 4;\n  if (equals(c1.r + c2.r, d)) return 3;\n \
    \ if (c1.r - c2.r < d) return 2;\n  if (equals(c1.r - c2.r, d)) return 1;\n  return\
    \ 0;\n}\n\npair<Point, Point> crosspoint(const Circle& c1, const Circle& c2) {\n\
    \  Real d = abs(c1.p - c2.p);\n  Real x = (c1.r * c1.r + d * d - c2.r * c2.r)\
    \ / (2 * c1.r * d);\n  if (abs(x) > 1) x = (x > 0 ? 1.0 : -1.0);\n  Real a = acos(x);\n\
    \  Real t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());\n  Point\
    \ p1 = c1.p + Point(cos(t + a) * c1.r, sin(t + a) * c1.r);\n  Point p2 = c1.p\
    \ + Point(cos(t - a) * c1.r, sin(t - a) * c1.r);\n  return {p1, p2};\n}\n\n/**\n\
    \ * @brief \u5186\u304A\u3088\u3073 2 \u5186\u306E\u4EA4\u70B9\u306E\u5B58\u5728\
    \u5224\u5B9A\n */\n"
  dependsOn:
  - geometry/geometry-base.hpp
  isVerificationFile: false
  path: geometry/circle.hpp
  requiredBy: []
  timestamp: '2026-06-08 17:59:24+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/circle.hpp
layout: document
title: "\u5186\u304A\u3088\u3073 2 \u5186\u306E\u4EA4\u70B9\u306E\u5B58\u5728\u5224\
  \u5B9A"
---

## 円および 2 円の交点の存在判定

#### 使い方

- `Circle(Point _p, Real _r)`: コンストラクタ。`_p` を中心、`_r` を半径とする円を構築する。
- `int intersect(Circle c1, Circle c2)`: 円 `c1` と `c2` の交点の存在判定を行う関数。厳密には交点の存在判定ではなく、内接・外接も含めた分類を行う。
  - `c1` と `c2` の関係によってそれぞれ以下のような値が返る。
    - 小さい円が大きい円の内部に完全に含まれる場合: 0
    - 片方の円がもう片方の円に内接している（もしくは同一円である）場合: 1
    - 2 円が 2 点で交わる場合: 2
    - 片方の円がもう片方の円に外接している場合: 3
    - 2 円が外部で離れている場合: 4
  - `c1` と `c2` が異なる円であれば、返り値は `c1` と `c2` の共通接線の個数と一致する。ただし、`c1` と `c2` が同一円である場合は共通接線は無限個存在するが、返り値は 1 である。
  - `c1` と `c2` が 1 個以上の交点を持つのは、返り値が 1, 2, 3 のどれかの場合である。1 または 3 であれば交点は 1 点、2 であれば交点は 2 点である（`c1` と `c2` が同一円である場合を除く）。
- `pair<Point, Point> crosspoint(const Circle& c1, const Circle& c2)`: 円 `c1` と `c2` の交点 2 点を返す関数。
  - 必ず 2 点の組を返す。ただし、`intersect(c1, c2)` の返り値によっては、同じ点 2 点からなる組や実際には `c1` と `c2` の交点でない点を含む組が返る可能性がある。
    - `intersect(c1, c2)` の返り値が 2 であれば、`c1` と `c2` の交点 2 点の組を返す。
    - `c1` と `c2` が同一円ではなく、`intersect(c1, c2)` の返り値が 1 または 3 であれば、`first` と `second` が等しく、両方とも `c1` と `c2` の唯一の交点となる点（接点）である組を返す。
    - 同心円、同一円や半径 0 の円を与えると 0 除算や `NaN` が発生しうる。そのような `c1` と `c2` を与えることや、返り値を交点として使用することは推奨されない。
