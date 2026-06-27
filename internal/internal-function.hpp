#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

namespace nyaan_internal {

template <class>
class function_ref;

template <class R, class... Args>
class function_ref<R(Args...)> {
  void* obj_ = nullptr;
  R (*call_obj_)(void*, Args...) = nullptr;
  R (*func_)(Args...) = nullptr;

 public:
  function_ref() noexcept = default;
  function_ref(std::nullptr_t) noexcept {}
  function_ref(R (*f)(Args...)) noexcept : func_(f) {}

  template <
      class F, class Fn = std::remove_reference_t<F>,
      class = std::enable_if_t<
          std::is_lvalue_reference_v<F&&> &&
          !std::is_same_v<std::decay_t<F>, function_ref> &&
          !std::is_pointer_v<std::decay_t<F>> && !std::is_function_v<Fn> &&
          std::is_invocable_r_v<R, Fn&, Args...>>>
  function_ref(F&& f) noexcept {
    obj_ = const_cast<void*>(static_cast<const void*>(std::addressof(f)));
    call_obj_ = [](void* p, Args... args) -> R {
      return std::invoke(*static_cast<Fn*>(p), std::forward<Args>(args)...);
    };
  }

  R operator()(Args... args) const {
    if (call_obj_) {
      return call_obj_(obj_, std::forward<Args>(args)...);
    }
    if (!func_) throw std::bad_function_call();
    return func_(std::forward<Args>(args)...);
  }

  explicit operator bool() const noexcept {
    return call_obj_ != nullptr || func_ != nullptr;
  }
};

template <class, std::size_t Capacity = 32,
          std::size_t Align = alignof(std::max_align_t)>
class inplace_function;

template <class R, class... Args, std::size_t Capacity, std::size_t Align>
class inplace_function<R(Args...), Capacity, Align> {
  using storage_t = typename std::aligned_storage<Capacity, Align>::type;

  storage_t storage_;
  R (*invoke_)(void*, Args&&...) = nullptr;
  void (*copy_)(void*, const void*) = nullptr;
  void (*move_)(void*, void*) = nullptr;
  void (*destroy_)(void*) = nullptr;

  template <class F>
  static R invoke_impl(void* p, Args&&... args) {
    return std::invoke(*static_cast<F*>(p), std::forward<Args>(args)...);
  }

  template <class F>
  static void copy_impl(void* dst, const void* src) {
    new (dst) F(*static_cast<const F*>(src));
  }

  template <class F>
  static void move_impl(void* dst, void* src) {
    if constexpr (std::is_move_constructible_v<F>) {
      new (dst) F(std::move(*static_cast<F*>(src)));
    } else {
      new (dst) F(*static_cast<F*>(src));
    }
  }

  template <class F>
  static void destroy_impl(void* p) {
    static_cast<F*>(p)->~F();
  }

  template <class F>
  void emplace(F&& f) {
    using Fn = std::decay_t<F>;

    static_assert(std::is_invocable_r_v<R, Fn&, Args...>,
                  "inplace_function target is not invocable with this signature");
    static_assert(sizeof(Fn) <= Capacity,
                  "inplace_function target is too large; increase Capacity");
    static_assert(alignof(Fn) <= Align,
                  "inplace_function target alignment is too strict; increase Align");
    static_assert(std::is_copy_constructible_v<Fn>,
                  "inplace_function target must be copy constructible");

    if constexpr (std::is_pointer_v<Fn>) {
      if (f == nullptr) return;
    }

    if constexpr (std::is_move_constructible_v<Fn> ||
                  std::is_lvalue_reference_v<F>) {
      new (&storage_) Fn(std::forward<F>(f));
    } else {
      new (&storage_) Fn(f);
    }
    invoke_ = &invoke_impl<Fn>;
    copy_ = &copy_impl<Fn>;
    move_ = &move_impl<Fn>;
    destroy_ = &destroy_impl<Fn>;
  }

 public:
  inplace_function() noexcept = default;
  inplace_function(std::nullptr_t) noexcept {}

  ~inplace_function() { reset(); }

  inplace_function(const inplace_function& other) {
    if (other) {
      other.copy_(&storage_, &other.storage_);
      invoke_ = other.invoke_;
      copy_ = other.copy_;
      move_ = other.move_;
      destroy_ = other.destroy_;
    }
  }

  inplace_function(inplace_function&& other) {
    if (other) {
      other.move_(&storage_, &other.storage_);
      invoke_ = other.invoke_;
      copy_ = other.copy_;
      move_ = other.move_;
      destroy_ = other.destroy_;
      other.reset();
    }
  }

  template <
      class F, class Fn = std::decay_t<F>,
      class = std::enable_if_t<!std::is_same_v<Fn, inplace_function> &&
                               !std::is_same_v<Fn, std::nullptr_t>>>
  inplace_function(F&& f) {
    emplace(std::forward<F>(f));
  }

  inplace_function& operator=(const inplace_function& other) {
    if (this == &other) return *this;
    reset();
    if (other) {
      other.copy_(&storage_, &other.storage_);
      invoke_ = other.invoke_;
      copy_ = other.copy_;
      move_ = other.move_;
      destroy_ = other.destroy_;
    }
    return *this;
  }

  inplace_function& operator=(inplace_function&& other) {
    if (this == &other) return *this;
    reset();
    if (other) {
      other.move_(&storage_, &other.storage_);
      invoke_ = other.invoke_;
      copy_ = other.copy_;
      move_ = other.move_;
      destroy_ = other.destroy_;
      other.reset();
    }
    return *this;
  }

  template <
      class F, class Fn = std::decay_t<F>,
      class = std::enable_if_t<!std::is_same_v<Fn, inplace_function> &&
                               !std::is_same_v<Fn, std::nullptr_t>>>
  inplace_function& operator=(F&& f) {
    reset();
    emplace(std::forward<F>(f));
    return *this;
  }

  inplace_function& operator=(std::nullptr_t) noexcept {
    reset();
    return *this;
  }

  void reset() noexcept {
    if (destroy_) destroy_(&storage_);
    invoke_ = nullptr;
    copy_ = nullptr;
    move_ = nullptr;
    destroy_ = nullptr;
  }

  explicit operator bool() const noexcept { return invoke_ != nullptr; }

  R operator()(Args... args) const {
    if (!invoke_) throw std::bad_function_call();
    return invoke_(
        const_cast<void*>(static_cast<const void*>(&storage_)),
        std::forward<Args>(args)...);
  }
};

}  // namespace nyaan_internal

using nyaan_internal::function_ref;
using nyaan_internal::inplace_function;
