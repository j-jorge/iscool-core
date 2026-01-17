// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstddef>
#include <type_traits>

namespace iscool
{
  struct none_t;

  template <typename T>
  class optional
  {
  public:
    optional();
    optional(T&& that);
    optional(const T& that);
    optional(const optional<T>& that);

    template <typename U>
    optional(const optional<U>& that);

    optional(optional<T>&& that);
    optional(const none_t&);

    ~optional();

    explicit operator bool() const;

    T& operator*();
    const T& operator*() const;

    T* operator->();
    const T* operator->() const;

    optional<T>& operator=(const T& that);
    optional<T>& operator=(const optional<T>& that);
    optional<T>& operator=(optional<T>&& that);
    optional<T>& operator=(const none_t&);

    bool operator==(const none_t&) const;
    bool operator!=(const none_t&) const;

    template <typename... Args>
    void emplace(Args&&... args);

    void reset();
    void swap(optional<T>& that);

  private:
    T* get();
    const T* get() const;

  private:
    alignas(T) std::byte _storage[sizeof(T)];
    bool _initialized;
  };

  template <typename T>
  class optional<T&>
  {
  public:
    optional();
    optional(T& that);
    optional(const optional<T&>& that);

    template <typename U>
    optional(const optional<U&>& that);

    optional(optional<T&>&& that);
    optional(const none_t&);

    ~optional();

    explicit operator bool() const;

    T& operator*();
    const T& operator*() const;

    T* operator->();
    const T* operator->() const;

    optional<T&>& operator=(T& that);
    optional<T&>& operator=(const optional<T&>& that);
    optional<T&>& operator=(optional<T&>&& that);
    optional<T&>& operator=(const none_t&);

    bool operator==(const none_t&) const;
    bool operator!=(const none_t&) const;

    void emplace(T& that);
    void reset();
    void swap(optional<T&>& that);

  private:
    T* _value;
  };

  template <typename T>
  bool operator==(const none_t&, const optional<T>& value);

  template <typename T>
  bool operator!=(const none_t&, const optional<T>& value);

  template <typename T>
  iscool::optional<T> make_optional(T value);
}

extern template class iscool::optional<bool>;
extern template class iscool::optional<char>;
extern template class iscool::optional<unsigned char>;
extern template class iscool::optional<int>;
extern template class iscool::optional<unsigned int>;
extern template class iscool::optional<long>;
extern template class iscool::optional<unsigned long>;
extern template class iscool::optional<long long>;
extern template class iscool::optional<unsigned long long>;
extern template class iscool::optional<float>;
extern template class iscool::optional<double>;
