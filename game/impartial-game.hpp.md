---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: internal/internal-function.hpp
    title: internal/internal-function.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/verify-yuki/yuki-0002.test.cpp
    title: verify/verify-yuki/yuki-0002.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/verify-yuki/yuki-0102.test.cpp
    title: verify/verify-yuki/yuki-0102.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/verify-yuki/yuki-0361.test.cpp
    title: verify/verify-yuki/yuki-0361.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E0D\u504F\u30B2\u30FC\u30E0"
    links: []
  bundledCode: "#line 2 \"game/impartial-game.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdlib>\n#include <functional>\n#include <map>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\nusing namespace std;\n\
    \n#line 2 \"internal/internal-function.hpp\"\n\n#include <cstddef>\n#line 5 \"\
    internal/internal-function.hpp\"\n#include <memory>\n#line 8 \"internal/internal-function.hpp\"\
    \n\nnamespace nyaan_internal {\n\ntemplate <class>\nclass function_ref;\n\ntemplate\
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
    \ namespace nyaan_internal\n\nusing nyaan_internal::function_ref;\nusing nyaan_internal::inplace_function;\n\
    #line 14 \"game/impartial-game.hpp\"\n\n/**\n * \u30B2\u30FC\u30E0\u306E\u9077\
    \u79FB\u304C DAG \u3067\u8868\u305B\u308B\u4E0D\u504F\u30B2\u30FC\u30E0\u306E\
    \ solver\n *\n * Board\uFF1A\u76E4\u9762\u306E\u578B\n * Move \u306F\u7740\u624B\
    \u306E\u578B or void\n * Game \u306F\n *\n * - splittable = true \u306E\u5834\u5408\
    \u306F vector<Board> (\u30B2\u30FC\u30E0\u306E\u5206\u5272\u306B\u5BFE\u5FDC)\n\
    \ * - splittable = false\u306E\u5834\u5408\u306F Board\n *\n * State \u306F\u6B21\
    \n *\n * - Move \u304C void \u3067\u3042\u308B\u5834\u5408, Game\n * - Move \u304C\
    \ void \u3067\u306A\u3044\u5834\u5408, pair<Game, Move>\n *\n * States \u306F\
    \ vector<State>\n *\n * F \u306F Board \u3092\u5F15\u6570, States \u3092\u8FD4\
    \u308A\u5024\u306B\u53D6\u308B callable\u3002\u3064\u307E\u308A\n *\n * - \u30C7\
    \u30D5\u30A9\u30EB\u30C8\u306E\u5834\u5408   : vector<Board>(Board)\n * - splittable\
    \ \u306E\u5834\u5408 : vector<vector<Board>>(Board)\n * - Move != void \u306E\u5834\
    \u5408\u306F\u8FD4\u308A\u5024\u306E value_type \u304C pair(*, move) \u306B\u306A\
    \u308B\n *\n * \u96D1\u306B\u30B2\u30FC\u30E0\u306E\u52DD\u6557\u3092\u77E5\u308A\
    \u305F\u3044\u3068\u304D\u306F\u30C7\u30D5\u30A9\u30EB\u30C8\u3067\u3088\u3044\
    \n * \u6700\u5584\u624B\u306E\u60C5\u5831\u304C\u6B32\u3057\u3044\u3068\u304D\u306F\
    \ Move \u306E\u5F15\u6570\u3092\u5909\u3048\u3066\u9811\u5F35\u308B\n */\n\ntemplate\
    \ <typename Board, typename Move = void, bool splittable = false>\nstruct ImpartialGameSolver\
    \ {\n  using Boards = vector<Board>;\n  using Game = conditional_t<splittable,\
    \ vector<Board>, Board>;\n  using State = conditional_t<is_void_v<Move>, Game,\
    \ pair<Game, Move>>;\n  using States = vector<State>;\n  using Nimber = long long;\n\
    \  using F = nyaan_internal::inplace_function<States(Board), 64>;\n\n  map<Board,\
    \ Nimber> mp;\n  F f;\n\n  ImpartialGameSolver() = default;\n  ImpartialGameSolver(const\
    \ F& _f) : f(_f) {}\n\n  template <typename Func,\n            typename = enable_if_t<is_invocable_r_v<States,\
    \ Func&, Board>>>\n  ImpartialGameSolver(Func&& _f) : f(std::forward<Func>(_f))\
    \ {}\n\n  void set_func(const F& _f) { f = _f; }\n\n  template <typename Func>\n\
    \  auto set_func(Func&& _f)\n      -> enable_if_t<is_invocable_r_v<States, Func&,\
    \ Board>, void> {\n    f = std::forward<Func>(_f);\n  }\n\n  template <typename\
    \ T>\n  Nimber get(const T& t) {\n    if constexpr (is_same_v<T, Board>) {\n \
    \     if (mp.count(t)) return mp[t];\n      return mp[t] = _get(t);\n    } else\
    \ if constexpr (is_same_v<T, Boards>) {\n      Nimber n = 0;\n      for (const\
    \ Board& s : t) n ^= get(s);\n      return n;\n    } else {\n      static_assert(is_same_v<T,\
    \ pair<Game, Move>>);\n      return get(t.first);\n    }\n  }\n\n  // \u8CA0\u3051\
    \u5C40\u9762\u3067\u547C\u3076\u3068 RE \u3059\u308B\n  template <typename T>\n\
    \  conditional_t<is_same_v<T, Board>, Move, pair<int, Move>> get_best_move(\n\
    \      const T& t) {\n    static_assert(is_void_v<Move> == false);\n    Nimber\
    \ n = get(t);\n    assert(n != 0 and \"No Best Move.\");\n    if constexpr (is_same_v<T,\
    \ Board>) {\n      auto res = change_x(t, n);\n      if (res.first) return res.second;\n\
    \    } else {\n      static_assert(is_same_v<T, Boards>);\n      for (int i =\
    \ 0; i < (int)t.size(); i++) {\n        auto res = change_x(t[i], n);\n      \
    \  if (res.first) return {i, res.second};\n      }\n    }\n    assert(false and\
    \ \"Error in get_best_move().\");\n    exit(1);\n  }\n\n private:\n  Nimber _get(const\
    \ Board& b) {\n    States gs = std::invoke(f, b);\n    if (gs.empty()) return\
    \ {};\n    vector<Nimber> ns;\n    for (State& st : gs) ns.push_back(get(st));\n\
    \    sort(begin(ns), end(ns));\n    ns.erase(unique(begin(ns), end(ns)), end(ns));\n\
    \    for (int i = 0; i < (int)ns.size(); i++) {\n      if (ns[i] != i) return\
    \ i;\n    }\n    return ns.size();\n  }\n\n  // nimber \u304C x \u5909\u308F\u308B\
    \u3088\u3046\u306A\u7740\u624B\u3092\u8FD4\u3059\n  pair<bool, Move> change_x(const\
    \ Board& b, Nimber x) {\n    assert(is_void_v<Move> == false);\n    Nimber n =\
    \ get(b);\n    for (auto& st : std::invoke(f, b)) {\n      if (get(st) == (x ^\
    \ n)) return {true, st.second};\n    }\n    return {false, Move{}};\n  }\n};\n\
    \n/**\n * @brief \u4E0D\u504F\u30B2\u30FC\u30E0\n */\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <cstdlib>\n\
    #include <functional>\n#include <map>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\nusing namespace std;\n\n#include \"../internal/internal-function.hpp\"\
    \n\n/**\n * \u30B2\u30FC\u30E0\u306E\u9077\u79FB\u304C DAG \u3067\u8868\u305B\u308B\
    \u4E0D\u504F\u30B2\u30FC\u30E0\u306E solver\n *\n * Board\uFF1A\u76E4\u9762\u306E\
    \u578B\n * Move \u306F\u7740\u624B\u306E\u578B or void\n * Game \u306F\n *\n *\
    \ - splittable = true \u306E\u5834\u5408\u306F vector<Board> (\u30B2\u30FC\u30E0\
    \u306E\u5206\u5272\u306B\u5BFE\u5FDC)\n * - splittable = false\u306E\u5834\u5408\
    \u306F Board\n *\n * State \u306F\u6B21\n *\n * - Move \u304C void \u3067\u3042\
    \u308B\u5834\u5408, Game\n * - Move \u304C void \u3067\u306A\u3044\u5834\u5408\
    , pair<Game, Move>\n *\n * States \u306F vector<State>\n *\n * F \u306F Board\
    \ \u3092\u5F15\u6570, States \u3092\u8FD4\u308A\u5024\u306B\u53D6\u308B callable\u3002\
    \u3064\u307E\u308A\n *\n * - \u30C7\u30D5\u30A9\u30EB\u30C8\u306E\u5834\u5408\
    \   : vector<Board>(Board)\n * - splittable \u306E\u5834\u5408 : vector<vector<Board>>(Board)\n\
    \ * - Move != void \u306E\u5834\u5408\u306F\u8FD4\u308A\u5024\u306E value_type\
    \ \u304C pair(*, move) \u306B\u306A\u308B\n *\n * \u96D1\u306B\u30B2\u30FC\u30E0\
    \u306E\u52DD\u6557\u3092\u77E5\u308A\u305F\u3044\u3068\u304D\u306F\u30C7\u30D5\
    \u30A9\u30EB\u30C8\u3067\u3088\u3044\n * \u6700\u5584\u624B\u306E\u60C5\u5831\u304C\
    \u6B32\u3057\u3044\u3068\u304D\u306F Move \u306E\u5F15\u6570\u3092\u5909\u3048\
    \u3066\u9811\u5F35\u308B\n */\n\ntemplate <typename Board, typename Move = void,\
    \ bool splittable = false>\nstruct ImpartialGameSolver {\n  using Boards = vector<Board>;\n\
    \  using Game = conditional_t<splittable, vector<Board>, Board>;\n  using State\
    \ = conditional_t<is_void_v<Move>, Game, pair<Game, Move>>;\n  using States =\
    \ vector<State>;\n  using Nimber = long long;\n  using F = nyaan_internal::inplace_function<States(Board),\
    \ 64>;\n\n  map<Board, Nimber> mp;\n  F f;\n\n  ImpartialGameSolver() = default;\n\
    \  ImpartialGameSolver(const F& _f) : f(_f) {}\n\n  template <typename Func,\n\
    \            typename = enable_if_t<is_invocable_r_v<States, Func&, Board>>>\n\
    \  ImpartialGameSolver(Func&& _f) : f(std::forward<Func>(_f)) {}\n\n  void set_func(const\
    \ F& _f) { f = _f; }\n\n  template <typename Func>\n  auto set_func(Func&& _f)\n\
    \      -> enable_if_t<is_invocable_r_v<States, Func&, Board>, void> {\n    f =\
    \ std::forward<Func>(_f);\n  }\n\n  template <typename T>\n  Nimber get(const\
    \ T& t) {\n    if constexpr (is_same_v<T, Board>) {\n      if (mp.count(t)) return\
    \ mp[t];\n      return mp[t] = _get(t);\n    } else if constexpr (is_same_v<T,\
    \ Boards>) {\n      Nimber n = 0;\n      for (const Board& s : t) n ^= get(s);\n\
    \      return n;\n    } else {\n      static_assert(is_same_v<T, pair<Game, Move>>);\n\
    \      return get(t.first);\n    }\n  }\n\n  // \u8CA0\u3051\u5C40\u9762\u3067\
    \u547C\u3076\u3068 RE \u3059\u308B\n  template <typename T>\n  conditional_t<is_same_v<T,\
    \ Board>, Move, pair<int, Move>> get_best_move(\n      const T& t) {\n    static_assert(is_void_v<Move>\
    \ == false);\n    Nimber n = get(t);\n    assert(n != 0 and \"No Best Move.\"\
    );\n    if constexpr (is_same_v<T, Board>) {\n      auto res = change_x(t, n);\n\
    \      if (res.first) return res.second;\n    } else {\n      static_assert(is_same_v<T,\
    \ Boards>);\n      for (int i = 0; i < (int)t.size(); i++) {\n        auto res\
    \ = change_x(t[i], n);\n        if (res.first) return {i, res.second};\n     \
    \ }\n    }\n    assert(false and \"Error in get_best_move().\");\n    exit(1);\n\
    \  }\n\n private:\n  Nimber _get(const Board& b) {\n    States gs = std::invoke(f,\
    \ b);\n    if (gs.empty()) return {};\n    vector<Nimber> ns;\n    for (State&\
    \ st : gs) ns.push_back(get(st));\n    sort(begin(ns), end(ns));\n    ns.erase(unique(begin(ns),\
    \ end(ns)), end(ns));\n    for (int i = 0; i < (int)ns.size(); i++) {\n      if\
    \ (ns[i] != i) return i;\n    }\n    return ns.size();\n  }\n\n  // nimber \u304C\
    \ x \u5909\u308F\u308B\u3088\u3046\u306A\u7740\u624B\u3092\u8FD4\u3059\n  pair<bool,\
    \ Move> change_x(const Board& b, Nimber x) {\n    assert(is_void_v<Move> == false);\n\
    \    Nimber n = get(b);\n    for (auto& st : std::invoke(f, b)) {\n      if (get(st)\
    \ == (x ^ n)) return {true, st.second};\n    }\n    return {false, Move{}};\n\
    \  }\n};\n\n/**\n * @brief \u4E0D\u504F\u30B2\u30FC\u30E0\n */\n"
  dependsOn:
  - internal/internal-function.hpp
  isVerificationFile: false
  path: game/impartial-game.hpp
  requiredBy: []
  timestamp: '2026-06-27 14:52:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/verify-yuki/yuki-0002.test.cpp
  - verify/verify-yuki/yuki-0361.test.cpp
  - verify/verify-yuki/yuki-0102.test.cpp
documentation_of: game/impartial-game.hpp
layout: document
redirect_from:
- /library/game/impartial-game.hpp
- /library/game/impartial-game.hpp.html
title: "\u4E0D\u504F\u30B2\u30FC\u30E0"
---
