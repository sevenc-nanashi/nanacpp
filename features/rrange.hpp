#pragma once

#include "features/rarray.hpp"
#include "features/core.hpp"

/// Ruby風の整数Range。
template <typename T> class RRange {
  static_assert(std::is_integral_v<T>, "RRange requires an integral type");

private:
  T first_value;
  T last_value;
  bool exclude_last_value;

  class Iterator {
  private:
    T value;

  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;

    explicit Iterator(T value) : value(value) {}

    T operator*() const { return value; }

    Iterator &operator++() {
      ++value;
      return *this;
    }
  };

  class Sentinel {
  private:
    T last_value;
    bool exclude_last_value;

  public:
    Sentinel(T last_value, bool exclude_last_value)
        : last_value(last_value), exclude_last_value(exclude_last_value) {}

    friend bool operator!=(const Iterator &it, const Sentinel &sentinel) {
      if (sentinel.exclude_last_value) {
        return *it < sentinel.last_value;
      }
      return *it <= sentinel.last_value;
    }
  };

public:
  RRange(T first, T last, bool exclude_last = false)
      : first_value(first), last_value(last), exclude_last_value(exclude_last) {
  }

  static RRange inclusive(T first, T last) { return RRange(first, last); }

  static RRange exclusive(T first, T last) { return RRange(first, last, true); }

  T first() const { return first_value; }

  T last() const { return last_value; }

  bool exclude_last() const { return exclude_last_value; }

  bool empty() const {
    if (first_value > last_value) {
      return true;
    }
    return exclude_last_value && first_value == last_value;
  }

  bool include(T value) const {
    if (value < first_value) {
      return false;
    }
    if (exclude_last_value) {
      return value < last_value;
    }
    return value <= last_value;
  }

  bool overlaps(const RRange &other) const {
    if (empty() || other.empty()) {
      return false;
    }
    return !(last_value < other.first_value ||
             (exclude_last_value && last_value == other.first_value) ||
             (other.exclude_last_value && other.last_value == first_value) ||
             other.last_value < first_value);
  }

  usize size() const {
    if (empty()) {
      return 0;
    }

    i128 count = static_cast<i128>(last_value) - static_cast<i128>(first_value);
    if (!exclude_last_value) {
      ++count;
    }
    return static_cast<usize>(count);
  }

  std::vector<T> to_vec() const {
    std::vector<T> result;
    result.reserve(size());
    for (T value : *this) {
      result.push_back(value);
    }
    return result;
  }

  RArray<T> to_rarray() const {
    RArray<T> result;
    result.reserve(size());
    for (T value : *this) {
      result.push_back(value);
    }
    return result;
  }

  Iterator begin() const { return Iterator(first_value); }

  Sentinel end() const { return Sentinel(last_value, exclude_last_value); }
};

/// [first, last] の範囲を表す RRange を作成する。
template <typename T> RRange<T> rrange(T first, T last) {
  return RRange<T>::inclusive(first, last);
}

/// [first, last) の範囲を表す RRange を作成する。
template <typename T> RRange<T> rexrange(T first, T last) {
  return RRange<T>::exclusive(first, last);
}
