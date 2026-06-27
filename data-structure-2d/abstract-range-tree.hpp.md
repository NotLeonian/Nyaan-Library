---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: internal/internal-function.hpp
    title: internal/internal-function.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-yosupo-ds/yosupo-point-add-rectangle-sum-abstract-range-tree.test.cpp
    title: verify/verify-yosupo-ds/yosupo-point-add-rectangle-sum-abstract-range-tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u62BD\u8C61\u5316\u9818\u57DF\u6728"
    links: []
  bundledCode: "#line 2 \"data-structure-2d/abstract-range-tree.hpp\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <functional>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\nusing namespace std;\n\n#line 2 \"internal/internal-function.hpp\"\
    \n\n#include <cstddef>\n#line 5 \"internal/internal-function.hpp\"\n#include <memory>\n\
    #line 8 \"internal/internal-function.hpp\"\n\nnamespace nyaan_internal {\n\ntemplate\
    \ <class>\nclass function_ref;\n\ntemplate <class R, class... Args>\nclass function_ref<R(Args...)>\
    \ {\n  void* obj_ = nullptr;\n  R (*call_obj_)(void*, Args...) = nullptr;\n  R\
    \ (*func_)(Args...) = nullptr;\n\n public:\n  function_ref() noexcept = default;\n\
    \  function_ref(std::nullptr_t) noexcept {}\n  function_ref(R (*f)(Args...)) noexcept\
    \ : func_(f) {}\n\n  template <\n      class F, class Fn = std::remove_reference_t<F>,\n\
    \      class = std::enable_if_t<\n          std::is_lvalue_reference_v<F&&> &&\n\
    \          !std::is_same_v<std::decay_t<F>, function_ref> &&\n          !std::is_pointer_v<std::decay_t<F>>\
    \ && !std::is_function_v<Fn> &&\n          std::is_invocable_r_v<R, Fn&, Args...>>>\n\
    \  function_ref(F&& f) noexcept {\n    obj_ = const_cast<void*>(static_cast<const\
    \ void*>(std::addressof(f)));\n    call_obj_ = [](void* p, Args... args) -> R\
    \ {\n      return std::invoke(*static_cast<Fn*>(p), std::forward<Args>(args)...);\n\
    \    };\n  }\n\n  R operator()(Args... args) const {\n    if (call_obj_) {\n \
    \     return call_obj_(obj_, std::forward<Args>(args)...);\n    }\n    if (!func_)\
    \ throw std::bad_function_call();\n    return func_(std::forward<Args>(args)...);\n\
    \  }\n\n  explicit operator bool() const noexcept {\n    return call_obj_ != nullptr\
    \ || func_ != nullptr;\n  }\n};\n\ntemplate <class, std::size_t Capacity = 32,\n\
    \          std::size_t Align = alignof(std::max_align_t)>\nclass inplace_function;\n\
    \ntemplate <class R, class... Args, std::size_t Capacity, std::size_t Align>\n\
    class inplace_function<R(Args...), Capacity, Align> {\n  using storage_t = typename\
    \ std::aligned_storage<Capacity, Align>::type;\n\n  storage_t storage_;\n  R (*invoke_)(void*,\
    \ Args&&...) = nullptr;\n  void (*copy_)(void*, const void*) = nullptr;\n  void\
    \ (*move_)(void*, void*) = nullptr;\n  void (*destroy_)(void*) = nullptr;\n\n\
    \  template <class F>\n  static R invoke_impl(void* p, Args&&... args) {\n   \
    \ return std::invoke(*static_cast<F*>(p), std::forward<Args>(args)...);\n  }\n\
    \n  template <class F>\n  static void copy_impl(void* dst, const void* src) {\n\
    \    new (dst) F(*static_cast<const F*>(src));\n  }\n\n  template <class F>\n\
    \  static void move_impl(void* dst, void* src) {\n    if constexpr (std::is_move_constructible_v<F>)\
    \ {\n      new (dst) F(std::move(*static_cast<F*>(src)));\n    } else {\n    \
    \  new (dst) F(*static_cast<F*>(src));\n    }\n  }\n\n  template <class F>\n \
    \ static void destroy_impl(void* p) {\n    static_cast<F*>(p)->~F();\n  }\n\n\
    \  template <class F>\n  void emplace(F&& f) {\n    using Fn = std::decay_t<F>;\n\
    \n    static_assert(std::is_invocable_r_v<R, Fn&, Args...>,\n                \
    \  \"inplace_function target is not invocable with this signature\");\n    static_assert(sizeof(Fn)\
    \ <= Capacity,\n                  \"inplace_function target is too large; increase\
    \ Capacity\");\n    static_assert(alignof(Fn) <= Align,\n                  \"\
    inplace_function target alignment is too strict; increase Align\");\n    static_assert(std::is_copy_constructible_v<Fn>,\n\
    \                  \"inplace_function target must be copy constructible\");\n\n\
    \    if constexpr (std::is_pointer_v<Fn>) {\n      if (f == nullptr) return;\n\
    \    }\n\n    if constexpr (std::is_move_constructible_v<Fn> ||\n            \
    \      std::is_lvalue_reference_v<F>) {\n      new (&storage_) Fn(std::forward<F>(f));\n\
    \    } else {\n      new (&storage_) Fn(f);\n    }\n    invoke_ = &invoke_impl<Fn>;\n\
    \    copy_ = &copy_impl<Fn>;\n    move_ = &move_impl<Fn>;\n    destroy_ = &destroy_impl<Fn>;\n\
    \  }\n\n public:\n  inplace_function() noexcept = default;\n  inplace_function(std::nullptr_t)\
    \ noexcept {}\n\n  ~inplace_function() { reset(); }\n\n  inplace_function(const\
    \ inplace_function& other) {\n    if (other) {\n      other.copy_(&storage_, &other.storage_);\n\
    \      invoke_ = other.invoke_;\n      copy_ = other.copy_;\n      move_ = other.move_;\n\
    \      destroy_ = other.destroy_;\n    }\n  }\n\n  inplace_function(inplace_function&&\
    \ other) {\n    if (other) {\n      other.move_(&storage_, &other.storage_);\n\
    \      invoke_ = other.invoke_;\n      copy_ = other.copy_;\n      move_ = other.move_;\n\
    \      destroy_ = other.destroy_;\n      other.reset();\n    }\n  }\n\n  template\
    \ <\n      class F, class Fn = std::decay_t<F>,\n      class = std::enable_if_t<!std::is_same_v<Fn,\
    \ inplace_function> &&\n                               !std::is_same_v<Fn, std::nullptr_t>>>\n\
    \  inplace_function(F&& f) {\n    emplace(std::forward<F>(f));\n  }\n\n  inplace_function&\
    \ operator=(const inplace_function& other) {\n    if (this == &other) return *this;\n\
    \    reset();\n    if (other) {\n      other.copy_(&storage_, &other.storage_);\n\
    \      invoke_ = other.invoke_;\n      copy_ = other.copy_;\n      move_ = other.move_;\n\
    \      destroy_ = other.destroy_;\n    }\n    return *this;\n  }\n\n  inplace_function&\
    \ operator=(inplace_function&& other) {\n    if (this == &other) return *this;\n\
    \    reset();\n    if (other) {\n      other.move_(&storage_, &other.storage_);\n\
    \      invoke_ = other.invoke_;\n      copy_ = other.copy_;\n      move_ = other.move_;\n\
    \      destroy_ = other.destroy_;\n      other.reset();\n    }\n    return *this;\n\
    \  }\n\n  template <\n      class F, class Fn = std::decay_t<F>,\n      class\
    \ = std::enable_if_t<!std::is_same_v<Fn, inplace_function> &&\n              \
    \                 !std::is_same_v<Fn, std::nullptr_t>>>\n  inplace_function& operator=(F&&\
    \ f) {\n    reset();\n    emplace(std::forward<F>(f));\n    return *this;\n  }\n\
    \n  inplace_function& operator=(std::nullptr_t) noexcept {\n    reset();\n   \
    \ return *this;\n  }\n\n  void reset() noexcept {\n    if (destroy_) destroy_(&storage_);\n\
    \    invoke_ = nullptr;\n    copy_ = nullptr;\n    move_ = nullptr;\n    destroy_\
    \ = nullptr;\n  }\n\n  explicit operator bool() const noexcept { return invoke_\
    \ != nullptr; }\n\n  R operator()(Args... args) const {\n    if (!invoke_) throw\
    \ std::bad_function_call();\n    return invoke_(\n        const_cast<void*>(static_cast<const\
    \ void*>(&storage_)),\n        std::forward<Args>(args)...);\n  }\n};\n\n}  //\
    \ namespace nyaan_internal\n\nusing nyaan_internal::function_ref;\nusing nyaan_internal::inplace_function;\n\
    #line 12 \"data-structure-2d/abstract-range-tree.hpp\"\n\n// DS ... data_structure_type\n\
    // S ... size_type\n// T ... value_type\ntemplate <typename DS, typename S, typename\
    \ T,\n          typename NewFunc = nyaan_internal::inplace_function<DS*(int),\
    \ 64>,\n          typename AddFunc = nyaan_internal::inplace_function<void(DS&,\
    \ int, T), 64>,\n          typename SumFunc = nyaan_internal::inplace_function<T(DS&,\
    \ int, int), 64>,\n          typename MergeFunc = nyaan_internal::inplace_function<T(T,\
    \ T), 64>>\nstruct RangeTree {\n  using NEW = NewFunc;\n  using ADD = AddFunc;\n\
    \  using SUM = SumFunc;\n  using MRG = MergeFunc;\n  using P = pair<S, S>;\n\n\
    \  static_assert(is_invocable_r_v<DS*, NEW&, int>,\n                \"RangeTree\
    \ NEW must be callable as DS*(int)\");\n  static_assert(is_invocable_r_v<void,\
    \ ADD&, DS&, int, T>,\n                \"RangeTree ADD must be callable as void(DS&,\
    \ int, T)\");\n  static_assert(is_invocable_r_v<T, SUM&, DS&, int, int>,\n   \
    \             \"RangeTree SUM must be callable as T(DS&, int, int)\");\n  static_assert(is_invocable_r_v<T,\
    \ MRG&, T, T>,\n                \"RangeTree MRG must be callable as T(T, T)\"\
    );\n\n  S N, M;\n  NEW ds_new;\n  ADD ds_add;\n  SUM ds_sum;\n  MRG t_merge;\n\
    \  const T ti;\n  vector<DS*> ds;\n  vector<vector<S>> ys;\n  vector<P> ps;\n\n\
    \  template <typename FNew, typename FAdd, typename FSum, typename FMerge>\n \
    \ RangeTree(FNew&& nw, FAdd&& ad, FSum&& sm, FMerge&& mrg, const T& ti_)\n   \
    \   : ds_new(std::forward<FNew>(nw)),\n        ds_add(std::forward<FAdd>(ad)),\n\
    \        ds_sum(std::forward<FSum>(sm)),\n        t_merge(std::forward<FMerge>(mrg)),\n\
    \        ti(ti_) {}\n\n  void add_point(S x, S y) { ps.push_back(make_pair(x,\
    \ y)); }\n\n  void build() {\n    sort(begin(ps), end(ps));\n    ps.erase(unique(begin(ps),\
    \ end(ps)), end(ps));\n    N = ps.size();\n    ds.resize(2 * N, nullptr);\n  \
    \  ys.resize(2 * N);\n    for (int i = 0; i < N; ++i) {\n      ys[i + N].push_back(ps[i].second);\n\
    \      ds[i + N] = std::invoke(ds_new, 1);\n    }\n    for (int i = N - 1; i >\
    \ 0; --i) {\n      ys[i].resize(ys[i << 1].size() + ys[(i << 1) | 1].size());\n\
    \      merge(begin(ys[(i << 1) | 0]), end(ys[(i << 1) | 0]),\n            begin(ys[(i\
    \ << 1) | 1]), end(ys[(i << 1) | 1]), begin(ys[i]));\n      ys[i].erase(unique(begin(ys[i]),\
    \ end(ys[i])), end(ys[i]));\n      ds[i] = std::invoke(ds_new, ys[i].size());\n\
    \    }\n  }\n\n  int id(S x) const {\n    return lower_bound(\n              \
    \ begin(ps), end(ps), make_pair(x, S()),\n               [](const P& a, const\
    \ P& b) { return a.first < b.first; }) -\n           begin(ps);\n  }\n\n  int\
    \ id(int i, S y) const {\n    return lower_bound(begin(ys[i]), end(ys[i]), y)\
    \ - begin(ys[i]);\n  }\n\n  void add(S x, S y, T a) {\n    int i = lower_bound(begin(ps),\
    \ end(ps), make_pair(x, y)) - begin(ps);\n    assert(ps[i] == make_pair(x, y));\n\
    \    for (i += N; i; i >>= 1) std::invoke(ds_add, *ds[i], id(i, y), a);\n  }\n\
    \n  T sum(S xl, S yl, S xr, S yr) {\n    T L = ti, R = ti;\n    int a = id(xl),\
    \ b = id(xr);\n    for (a += N, b += N; a < b; a >>= 1, b >>= 1) {\n      if (a\
    \ & 1)\n        L = std::invoke(t_merge, L,\n                        std::invoke(ds_sum,\
    \ *ds[a], id(a, yl), id(a, yr))),\n        ++a;\n      if (b & 1)\n        --b,\n\
    \            R = std::invoke(t_merge,\n                            std::invoke(ds_sum,\
    \ *ds[b], id(b, yl), id(b, yr)),\n                            R);\n    }\n   \
    \ return std::invoke(t_merge, L, R);\n  }\n};\n\n/*\n * @brief \u62BD\u8C61\u5316\
    \u9818\u57DF\u6728\n */\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\nusing namespace\
    \ std;\n\n#include \"../internal/internal-function.hpp\"\n\n// DS ... data_structure_type\n\
    // S ... size_type\n// T ... value_type\ntemplate <typename DS, typename S, typename\
    \ T,\n          typename NewFunc = nyaan_internal::inplace_function<DS*(int),\
    \ 64>,\n          typename AddFunc = nyaan_internal::inplace_function<void(DS&,\
    \ int, T), 64>,\n          typename SumFunc = nyaan_internal::inplace_function<T(DS&,\
    \ int, int), 64>,\n          typename MergeFunc = nyaan_internal::inplace_function<T(T,\
    \ T), 64>>\nstruct RangeTree {\n  using NEW = NewFunc;\n  using ADD = AddFunc;\n\
    \  using SUM = SumFunc;\n  using MRG = MergeFunc;\n  using P = pair<S, S>;\n\n\
    \  static_assert(is_invocable_r_v<DS*, NEW&, int>,\n                \"RangeTree\
    \ NEW must be callable as DS*(int)\");\n  static_assert(is_invocable_r_v<void,\
    \ ADD&, DS&, int, T>,\n                \"RangeTree ADD must be callable as void(DS&,\
    \ int, T)\");\n  static_assert(is_invocable_r_v<T, SUM&, DS&, int, int>,\n   \
    \             \"RangeTree SUM must be callable as T(DS&, int, int)\");\n  static_assert(is_invocable_r_v<T,\
    \ MRG&, T, T>,\n                \"RangeTree MRG must be callable as T(T, T)\"\
    );\n\n  S N, M;\n  NEW ds_new;\n  ADD ds_add;\n  SUM ds_sum;\n  MRG t_merge;\n\
    \  const T ti;\n  vector<DS*> ds;\n  vector<vector<S>> ys;\n  vector<P> ps;\n\n\
    \  template <typename FNew, typename FAdd, typename FSum, typename FMerge>\n \
    \ RangeTree(FNew&& nw, FAdd&& ad, FSum&& sm, FMerge&& mrg, const T& ti_)\n   \
    \   : ds_new(std::forward<FNew>(nw)),\n        ds_add(std::forward<FAdd>(ad)),\n\
    \        ds_sum(std::forward<FSum>(sm)),\n        t_merge(std::forward<FMerge>(mrg)),\n\
    \        ti(ti_) {}\n\n  void add_point(S x, S y) { ps.push_back(make_pair(x,\
    \ y)); }\n\n  void build() {\n    sort(begin(ps), end(ps));\n    ps.erase(unique(begin(ps),\
    \ end(ps)), end(ps));\n    N = ps.size();\n    ds.resize(2 * N, nullptr);\n  \
    \  ys.resize(2 * N);\n    for (int i = 0; i < N; ++i) {\n      ys[i + N].push_back(ps[i].second);\n\
    \      ds[i + N] = std::invoke(ds_new, 1);\n    }\n    for (int i = N - 1; i >\
    \ 0; --i) {\n      ys[i].resize(ys[i << 1].size() + ys[(i << 1) | 1].size());\n\
    \      merge(begin(ys[(i << 1) | 0]), end(ys[(i << 1) | 0]),\n            begin(ys[(i\
    \ << 1) | 1]), end(ys[(i << 1) | 1]), begin(ys[i]));\n      ys[i].erase(unique(begin(ys[i]),\
    \ end(ys[i])), end(ys[i]));\n      ds[i] = std::invoke(ds_new, ys[i].size());\n\
    \    }\n  }\n\n  int id(S x) const {\n    return lower_bound(\n              \
    \ begin(ps), end(ps), make_pair(x, S()),\n               [](const P& a, const\
    \ P& b) { return a.first < b.first; }) -\n           begin(ps);\n  }\n\n  int\
    \ id(int i, S y) const {\n    return lower_bound(begin(ys[i]), end(ys[i]), y)\
    \ - begin(ys[i]);\n  }\n\n  void add(S x, S y, T a) {\n    int i = lower_bound(begin(ps),\
    \ end(ps), make_pair(x, y)) - begin(ps);\n    assert(ps[i] == make_pair(x, y));\n\
    \    for (i += N; i; i >>= 1) std::invoke(ds_add, *ds[i], id(i, y), a);\n  }\n\
    \n  T sum(S xl, S yl, S xr, S yr) {\n    T L = ti, R = ti;\n    int a = id(xl),\
    \ b = id(xr);\n    for (a += N, b += N; a < b; a >>= 1, b >>= 1) {\n      if (a\
    \ & 1)\n        L = std::invoke(t_merge, L,\n                        std::invoke(ds_sum,\
    \ *ds[a], id(a, yl), id(a, yr))),\n        ++a;\n      if (b & 1)\n        --b,\n\
    \            R = std::invoke(t_merge,\n                            std::invoke(ds_sum,\
    \ *ds[b], id(b, yl), id(b, yr)),\n                            R);\n    }\n   \
    \ return std::invoke(t_merge, L, R);\n  }\n};\n\n/*\n * @brief \u62BD\u8C61\u5316\
    \u9818\u57DF\u6728\n */\n"
  dependsOn:
  - internal/internal-function.hpp
  isVerificationFile: false
  path: data-structure-2d/abstract-range-tree.hpp
  requiredBy: []
  timestamp: '2026-06-27 14:52:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-yosupo-ds/yosupo-point-add-rectangle-sum-abstract-range-tree.test.cpp
documentation_of: data-structure-2d/abstract-range-tree.hpp
layout: document
redirect_from:
- /library/data-structure-2d/abstract-range-tree.hpp
- /library/data-structure-2d/abstract-range-tree.hpp.html
title: "\u62BD\u8C61\u5316\u9818\u57DF\u6728"
---
