#pragma once

#include "features/core.hpp"

#if __cplusplus >= 202002L
#include <source_location>
#define NANACPP_RARRAY_HAS_SOURCE_LOCATION 1
#else
#define NANACPP_RARRAY_HAS_SOURCE_LOCATION 0
#endif

/// Ruby風の配列。
template <typename T, typename Allocator = std::allocator<T>>
class RArray : public std::vector<T, Allocator> {
private:
  using Base = std::vector<T, Allocator>;

#if NANACPP_RARRAY_HAS_SOURCE_LOCATION
  template <typename Index>
  [[noreturn]] static fn
  throw_out_of_range(Index index, typename Base::size_type size,
                     const std::source_location &location) -> void {
    std::ostringstream oss;
    oss << "RArray index out of range: index=" << index << ", size=" << size
        << ", called from " << location.file_name() << ":" << location.line()
        << ":" << location.column() << " in " << location.function_name();
    throw std::out_of_range(oss.str());
  }
#else
  template <typename Index>
  [[noreturn]] static fn throw_out_of_range(Index index,
                                            typename Base::size_type size)
      -> void {
    std::ostringstream oss;
    oss << "RArray index out of range: index=" << index << ", size=" << size;
    throw std::out_of_range(oss.str());
  }
#endif

  template <typename Index>
  static fn normalize_index(Index index, typename Base::size_type size) ->
      typename Base::size_type {
    using difference_type = typename Base::difference_type;
    const difference_type signed_size = static_cast<difference_type>(size);
    const difference_type signed_index = static_cast<difference_type>(index);
    const difference_type normalized_index =
        signed_index < 0 ? signed_size + signed_index : signed_index;
    return static_cast<typename Base::size_type>(normalized_index);
  }

  template <typename Range>
  using RangeLike = std::void_t<decltype(std::declval<Range>().first()),
                                decltype(std::declval<Range>().last()),
                                decltype(std::declval<Range>().exclude_last())>;

  template <typename U>
  using Comparable =
      std::void_t<decltype(std::declval<U>() < std::declval<U>())>;

  template <typename U>
  using Numeric = std::enable_if_t<std::is_arithmetic<U>::value>;

#if NANACPP_RARRAY_HAS_SOURCE_LOCATION
  template <typename Range>
  fn slice_by_range(const Range &range,
                    const std::source_location &location) const -> RArray {
    if (range.empty()) {
      return RArray();
    }

    const size_type first_index = normalize_index(range.first(), this->size());
    const size_type last_index = normalize_index(range.last(), this->size());
    const size_type end_index =
        range.exclude_last() ? last_index : last_index + 1;
#ifndef ONLINE_JUDGE
    if (first_index >= this->size()) {
      throw_out_of_range(range.first(), this->size(), location);
    }
    if (end_index > this->size()) {
      throw_out_of_range(range.last(), this->size(), location);
    }
#endif
    if (first_index >= end_index) {
      return RArray();
    }
    return RArray(this->begin() + first_index, this->begin() + end_index);
  }
#else
  template <typename Range>
  fn slice_by_range(const Range &range) const -> RArray {
    if (range.empty()) {
      return RArray();
    }

    const size_type first_index = normalize_index(range.first(), this->size());
    const size_type last_index = normalize_index(range.last(), this->size());
    const size_type end_index =
        range.exclude_last() ? last_index : last_index + 1;
#ifndef ONLINE_JUDGE
    if (first_index >= this->size()) {
      throw_out_of_range(range.first(), this->size());
    }
    if (end_index > this->size()) {
      throw_out_of_range(range.last(), this->size());
    }
#endif
    if (first_index >= end_index) {
      return RArray();
    }
    return RArray(this->begin() + first_index, this->begin() + end_index);
  }
#endif

public:
  using typename Base::allocator_type;
  using typename Base::const_reference;
  using typename Base::reference;
  using typename Base::size_type;
  using typename Base::value_type;

  using Base::Base;

#if NANACPP_RARRAY_HAS_SOURCE_LOCATION
  fn operator[](size_type index,
                std::source_location location = std::source_location::current())
      ->reference {
#ifndef ONLINE_JUDGE
    if (index >= this->size()) {
      throw_out_of_range(index, this->size(), location);
    }
#endif
    return Base::operator[](index);
  }

  fn operator[](size_type index,
                std::source_location location =
                    std::source_location::current()) const->const_reference {
#ifndef ONLINE_JUDGE
    if (index >= this->size()) {
      throw_out_of_range(index, this->size(), location);
    }
#endif
    return Base::operator[](index);
  }

  template <typename Index,
            typename = std::enable_if_t<std::is_signed_v<Index>>>
  fn operator[](Index index,
                std::source_location location = std::source_location::current())
      ->reference {
    const size_type normalized_index = normalize_index(index, this->size());
#ifndef ONLINE_JUDGE
    if (normalized_index >= this->size()) {
      throw_out_of_range(index, this->size(), location);
    }
#endif
    return Base::operator[](normalized_index);
  }

  template <typename Index,
            typename = std::enable_if_t<std::is_signed_v<Index>>>
  fn operator[](Index index,
                std::source_location location =
                    std::source_location::current()) const->const_reference {
    const size_type normalized_index = normalize_index(index, this->size());
#ifndef ONLINE_JUDGE
    if (normalized_index >= this->size()) {
      throw_out_of_range(index, this->size(), location);
    }
#endif
    return Base::operator[](normalized_index);
  }

  template <typename Range, typename = RangeLike<Range>>
  fn operator[](const Range &range,
                std::source_location location =
                    std::source_location::current()) const->RArray {
    return slice_by_range(range, location);
  }
#else
  fn operator[](size_type index)->reference {
#ifndef ONLINE_JUDGE
    if (index >= this->size()) {
      throw_out_of_range(index, this->size());
    }
#endif
    return Base::operator[](index);
  }

  fn operator[](size_type index) const->const_reference {
#ifndef ONLINE_JUDGE
    if (index >= this->size()) {
      throw_out_of_range(index, this->size());
    }
#endif
    return Base::operator[](index);
  }

  template <typename Index,
            typename = std::enable_if_t<std::is_signed<Index>::value>>
  fn operator[](Index index)->reference {
    const size_type normalized_index = normalize_index(index, this->size());
#ifndef ONLINE_JUDGE
    if (normalized_index >= this->size()) {
      throw_out_of_range(index, this->size());
    }
#endif
    return Base::operator[](normalized_index);
  }

  template <typename Index,
            typename = std::enable_if_t<std::is_signed<Index>::value>>
  fn operator[](Index index) const->const_reference {
    const size_type normalized_index = normalize_index(index, this->size());
#ifndef ONLINE_JUDGE
    if (normalized_index >= this->size()) {
      throw_out_of_range(index, this->size());
    }
#endif
    return Base::operator[](normalized_index);
  }

  template <typename Range, typename = RangeLike<Range>>
  fn operator[](const Range &range) const->RArray {
    return slice_by_range(range);
  }
#endif

  fn first() const -> std::optional<T> {
    if (this->empty()) {
      return std::nullopt;
    }
    return Base::front();
  }

  fn last() const -> std::optional<T> {
    if (this->empty()) {
      return std::nullopt;
    }
    return Base::back();
  }

  fn include(const T &value) const -> bool {
    return std::find(this->begin(), this->end(), value) != this->end();
  }

  fn count(const T &value) const -> size_type {
    return static_cast<size_type>(
        std::count(this->begin(), this->end(), value));
  }

  fn take(size_type count) const -> RArray {
    const size_type take_count = std::min(count, this->size());
    return RArray(this->begin(), this->begin() + take_count);
  }

  fn drop(size_type count) const -> RArray {
    const size_type drop_count = std::min(count, this->size());
    return RArray(this->begin() + drop_count, this->end());
  }

  fn reverse() const -> RArray {
    RArray result(this->rbegin(), this->rend());
    return result;
  }

  fn sort() const -> RArray {
    RArray result = *this;
    std::sort(result.begin(), result.end());
    return result;
  }

  fn sort_desc() const -> RArray {
    RArray result = *this;
    std::sort(result.begin(), result.end(), std::greater<T>());
    return result;
  }

  template <typename F> fn sort_by(F &&selector) const -> RArray {
    RArray result = *this;
    std::sort(result.begin(), result.end(), [&](const auto &a, const auto &b) {
      return std::invoke(selector, a) < std::invoke(selector, b);
    });
    return result;
  }

  template <typename F> fn sort_by_desc(F &&selector) const -> RArray {
    RArray result = *this;
    std::sort(result.begin(), result.end(), [&](const auto &a, const auto &b) {
      return std::invoke(selector, a) > std::invoke(selector, b);
    });
    return result;
  }

  fn dup() const -> RArray { return RArray(this->begin(), this->end()); }

  fn tally() const -> Map<T, size_type> {
    Map<T, size_type> counts;
    for (const auto &value : *this) {
      ++counts[value];
    }
    return counts;
  }

  fn to_vec() const -> std::vector<T> {
    return std::vector<T>(this->begin(), this->end());
  }
  fn into_vec() && -> std::vector<T> {
    return std::vector<T>(std::make_move_iterator(this->begin()),
                          std::make_move_iterator(this->end()));
  }

  template <typename U = T, typename = Comparable<U>>
  fn min() const -> std::optional<T> {
    if (this->empty()) {
      return std::nullopt;
    }
    return *std::min_element(this->begin(), this->end());
  }

  template <typename U = T, typename = Comparable<U>>
  fn max() const -> std::optional<T> {
    if (this->empty()) {
      return std::nullopt;
    }
    return *std::max_element(this->begin(), this->end());
  }

  template <typename U = T, typename = Comparable<U>>
  fn minmax() const -> std::optional<std::pair<T, T>> {
    if (this->empty()) {
      return std::nullopt;
    }
    const auto [min_it, max_it] =
        std::minmax_element(this->begin(), this->end());
    return std::pair<T, T>{*min_it, *max_it};
  }

  template <typename U = T, typename = Numeric<U>> fn sum() const -> T {
    return std::accumulate(this->begin(), this->end(), static_cast<T>(0));
  }

  template <typename U = T, typename = Numeric<U>> fn product() const -> T {
    return std::accumulate(this->begin(), this->end(), static_cast<T>(1),
                           std::multiplies<T>());
  }
};

template <typename T>
fn operator<<(std::ostream &os, const RArray<T> &v)->std::ostream & {
  os << "[";
  for (usize i = 0; i < v.size(); ++i) {
    os << v[i];
    if (i + 1 != v.size()) {
      os << ", ";
    }
  }
  os << "]";
  return os;
}

template <typename T> using RArray2 = RArray<RArray<T>>;
template <typename T> using RArray3 = RArray<RArray<RArray<T>>>;
