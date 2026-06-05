---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: internal/internal-function.hpp
    title: internal/internal-function.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ntt/multivariate-circular-convolution.hpp
    title: "\u591A\u5909\u6570\u5DE1\u56DE\u7573\u307F\u8FBC\u307F"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-yosupo-ntt/yosupo-multivariate-circular-convolution.test.cpp
    title: verify/verify-yosupo-ntt/yosupo-multivariate-circular-convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/verify-yuki/yuki-1783.test.cpp
    title: verify/verify-yuki/yuki-1783.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u591A\u6B21\u5143FFT"
    links: []
  bundledCode: "#line 2 \"ntt/multidimensional-ntt.hpp\"\n\n#include <functional>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\nusing namespace\
    \ std;\n\n#line 2 \"internal/internal-function.hpp\"\n\n#include <cstddef>\n#line\
    \ 5 \"internal/internal-function.hpp\"\n#include <memory>\n#line 8 \"internal/internal-function.hpp\"\
    \n\nnamespace internal {\n\ntemplate <class>\nclass function_ref;\n\ntemplate\
    \ <class R, class... Args>\nclass function_ref<R(Args...)> {\n  void* obj_ = nullptr;\n\
    \  R (*call_obj_)(void*, Args...) = nullptr;\n  R (*func_)(Args...) = nullptr;\n\
    \n public:\n  function_ref() noexcept = default;\n  function_ref(std::nullptr_t)\
    \ noexcept {}\n  function_ref(R (*f)(Args...)) noexcept : func_(f) {}\n\n  template\
    \ <\n      class F, class Fn = std::remove_reference_t<F>,\n      class = std::enable_if_t<\n\
    \          std::is_lvalue_reference_v<F&&> &&\n          !std::is_same_v<std::decay_t<F>,\
    \ function_ref> &&\n          !std::is_pointer_v<std::decay_t<F>> && !std::is_function_v<Fn>\
    \ &&\n          std::is_invocable_r_v<R, Fn&, Args...>>>\n  function_ref(F&& f)\
    \ noexcept {\n    obj_ = const_cast<void*>(static_cast<const void*>(std::addressof(f)));\n\
    \    call_obj_ = [](void* p, Args... args) -> R {\n      return std::invoke(*static_cast<Fn*>(p),\
    \ std::forward<Args>(args)...);\n    };\n  }\n\n  R operator()(Args... args) const\
    \ {\n    if (call_obj_) {\n      return call_obj_(obj_, std::forward<Args>(args)...);\n\
    \    }\n    if (!func_) throw std::bad_function_call();\n    return func_(std::forward<Args>(args)...);\n\
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
    \ namespace internal\n\nusing internal::function_ref;\nusing internal::inplace_function;\n\
    #line 10 \"ntt/multidimensional-ntt.hpp\"\n\n// f(vector<mint>& a, bool rev) :\
    \ 1 \u6B21\u5143 DFT (rev \u306F\u9006\u5909\u63DB\u304B\u3069\u3046\u304B)\n\
    template <typename T,\n          typename DFT = internal::inplace_function<void(vector<T>&,\
    \ bool), 64>>\nstruct MultidimensionalFourierTransform {\n  static_assert(is_invocable_r_v<void,\
    \ DFT&, vector<T>&, bool>,\n                \"DFT must be callable as void(vector<T>&,\
    \ bool)\");\n\n  vector<int> base;\n  DFT dft1d;\n\n  template <typename F>\n\
    \  MultidimensionalFourierTransform(const vector<int>& bs, F&& f)\n      : base(bs),\
    \ dft1d(std::forward<F>(f)) {}\n\n  bool ascend(vector<int>& v) {\n    int i =\
    \ 0;\n    v[i] += 1;\n    while (v[i] == base[i]) {\n      if (i == (int)v.size()\
    \ - 1) return false;\n      v[i] = 0;\n      v[++i] += 1;\n    }\n    return true;\n\
    \  }\n\n  int operator()(vector<int>& a) {\n    int res = a[0], coeff = 1;\n \
    \   for (int i = 1; i < (int)a.size(); i++)\n      coeff *= base[i - 1], res +=\
    \ coeff * a[i];\n    return res;\n  }\n\n  void inner(vector<T>& a, int dim, bool\
    \ rev = false) {\n    int i = 0, shift = 1, n = base[dim];\n    vector<T> f(n);\n\
    \    vector<int> id(base.size());\n    for (int j = 0; j < dim; j++) shift *=\
    \ base[j];\n    do {\n      if (id[dim] != 0) continue;\n      for (int j = 0,\
    \ t = i; j < n; j++, t += shift) f[j] = a[t];\n      std::invoke(dft1d, f, rev);\n\
    \      for (int j = 0, t = i; j < n; j++, t += shift) a[t] = f[j];\n      id[dim]\
    \ = 0;\n    } while (++i && ascend(id));\n  }\n  void fft(vector<T>& a, bool rev\
    \ = false) {\n    if (!rev)\n      for (int i = 0; i < (int)base.size(); i++)\
    \ inner(a, i);\n    else\n      for (int i = (int)base.size(); i--;) inner(a,\
    \ i, true);\n  }\n};\n\n/**\n * @brief \u591A\u6B21\u5143FFT\n */\n"
  code: "#pragma once\n\n#include <functional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\nusing namespace std;\n\n#include \"../internal/internal-function.hpp\"\
    \n\n// f(vector<mint>& a, bool rev) : 1 \u6B21\u5143 DFT (rev \u306F\u9006\u5909\
    \u63DB\u304B\u3069\u3046\u304B)\ntemplate <typename T,\n          typename DFT\
    \ = internal::inplace_function<void(vector<T>&, bool), 64>>\nstruct MultidimensionalFourierTransform\
    \ {\n  static_assert(is_invocable_r_v<void, DFT&, vector<T>&, bool>,\n       \
    \         \"DFT must be callable as void(vector<T>&, bool)\");\n\n  vector<int>\
    \ base;\n  DFT dft1d;\n\n  template <typename F>\n  MultidimensionalFourierTransform(const\
    \ vector<int>& bs, F&& f)\n      : base(bs), dft1d(std::forward<F>(f)) {}\n\n\
    \  bool ascend(vector<int>& v) {\n    int i = 0;\n    v[i] += 1;\n    while (v[i]\
    \ == base[i]) {\n      if (i == (int)v.size() - 1) return false;\n      v[i] =\
    \ 0;\n      v[++i] += 1;\n    }\n    return true;\n  }\n\n  int operator()(vector<int>&\
    \ a) {\n    int res = a[0], coeff = 1;\n    for (int i = 1; i < (int)a.size();\
    \ i++)\n      coeff *= base[i - 1], res += coeff * a[i];\n    return res;\n  }\n\
    \n  void inner(vector<T>& a, int dim, bool rev = false) {\n    int i = 0, shift\
    \ = 1, n = base[dim];\n    vector<T> f(n);\n    vector<int> id(base.size());\n\
    \    for (int j = 0; j < dim; j++) shift *= base[j];\n    do {\n      if (id[dim]\
    \ != 0) continue;\n      for (int j = 0, t = i; j < n; j++, t += shift) f[j] =\
    \ a[t];\n      std::invoke(dft1d, f, rev);\n      for (int j = 0, t = i; j < n;\
    \ j++, t += shift) a[t] = f[j];\n      id[dim] = 0;\n    } while (++i && ascend(id));\n\
    \  }\n  void fft(vector<T>& a, bool rev = false) {\n    if (!rev)\n      for (int\
    \ i = 0; i < (int)base.size(); i++) inner(a, i);\n    else\n      for (int i =\
    \ (int)base.size(); i--;) inner(a, i, true);\n  }\n};\n\n/**\n * @brief \u591A\
    \u6B21\u5143FFT\n */\n"
  dependsOn:
  - internal/internal-function.hpp
  isVerificationFile: false
  path: ntt/multidimensional-ntt.hpp
  requiredBy:
  - ntt/multivariate-circular-convolution.hpp
  timestamp: '2026-06-05 19:46:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-yosupo-ntt/yosupo-multivariate-circular-convolution.test.cpp
  - verify/verify-yuki/yuki-1783.test.cpp
documentation_of: ntt/multidimensional-ntt.hpp
layout: document
redirect_from:
- /library/ntt/multidimensional-ntt.hpp
- /library/ntt/multidimensional-ntt.hpp.html
title: "\u591A\u6B21\u5143FFT"
---
