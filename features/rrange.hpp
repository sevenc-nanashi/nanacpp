#pragma once

#include "features/core.hpp"
#include "features/rarray.hpp"

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

    fn operator*() const->T { return value; }

    fn operator++()->Iterator & {
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

    friend fn operator!=(const Iterator &it, const Sentinel &sentinel)->bool {
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

  static fn inclusive(T first, T last) -> RRange { return RRange(first, last); }

  static fn exclusive(T first, T last) -> RRange {
    return RRange(first, last, true);
  }

  fn first() const -> T { return first_value; }

  fn last() const -> T { return last_value; }

  fn exclude_last() const -> bool { return exclude_last_value; }

  fn empty() const -> bool {
    if (first_value > last_value) {
      return true;
    }
    return exclude_last_value && first_value == last_value;
  }

  fn include(T value) const -> bool {
    if (value < first_value) {
      return false;
    }
    if (exclude_last_value) {
      return value < last_value;
    }
    return value <= last_value;
  }

  fn overlaps(const RRange &other) const -> bool {
    if (empty() || other.empty()) {
      return false;
    }
    return !(last_value < other.first_value ||
             (exclude_last_value && last_value == other.first_value) ||
             (other.exclude_last_value && other.last_value == first_value) ||
             other.last_value < first_value);
  }

  fn size() const -> usize {
    if (empty()) {
      return 0;
    }

    i128 count = static_cast<i128>(last_value) - static_cast<i128>(first_value);
    if (!exclude_last_value) {
      ++count;
    }
    return static_cast<usize>(count);
  }

  fn to_vec() const -> std::vector<T> {
    std::vector<T> result;
    result.reserve(size());
    for (T value : *this) {
      result.push_back(value);
    }
    return result;
  }

  fn to_rarray() const -> RArray<T> {
    RArray<T> result;
    result.reserve(size());
    for (T value : *this) {
      result.push_back(value);
    }
    return result;
  }

  fn begin() const -> Iterator { return Iterator(first_value); }

  fn end() const -> Sentinel {
    return Sentinel(last_value, exclude_last_value);
  }
};

/// [first, last] の範囲を表す RRange を作成する。
template <typename T> fn rrange(T first, T last) -> RRange<T> {
  return RRange<T>::inclusive(first, last);
}

/// [first, last) の範囲を表す RRange を作成する。
template <typename T> fn rexrange(T first, T last) -> RRange<T> {
  return RRange<T>::exclusive(first, last);
}
