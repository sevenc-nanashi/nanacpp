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
  [[noreturn]] static void
  throw_out_of_range(Index index, typename Base::size_type size,
                     const std::source_location &location) {
    std::ostringstream oss;
    oss << "RArray index out of range: index=" << index << ", size=" << size
        << ", called from " << location.file_name() << ":" << location.line()
        << ":" << location.column() << " in " << location.function_name();
    throw std::out_of_range(oss.str());
  }
#else
  template <typename Index>
  [[noreturn]] static void throw_out_of_range(Index index,
                                              typename Base::size_type size) {
    std::ostringstream oss;
    oss << "RArray index out of range: index=" << index << ", size=" << size;
    throw std::out_of_range(oss.str());
  }
#endif

  template <typename Index>
  static typename Base::size_type
  normalize_index(Index index, typename Base::size_type size) {
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
  RArray slice_by_range(const Range &range,
                        const std::source_location &location) const {
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
  template <typename Range> RArray slice_by_range(const Range &range) const {
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
  reference
  operator[](size_type index,
             std::source_location location = std::source_location::current()) {
#ifndef ONLINE_JUDGE
    if (index >= this->size()) {
      throw_out_of_range(index, this->size(), location);
    }
#endif
    return Base::operator[](index);
  }

  const_reference operator[](
      size_type index,
      std::source_location location = std::source_location::current()) const {
#ifndef ONLINE_JUDGE
    if (index >= this->size()) {
      throw_out_of_range(index, this->size(), location);
    }
#endif
    return Base::operator[](index);
  }

  template <typename Index,
            typename = std::enable_if_t<std::is_signed_v<Index>>>
  reference
  operator[](Index index,
             std::source_location location = std::source_location::current()) {
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
  const_reference operator[](
      Index index,
      std::source_location location = std::source_location::current()) const {
    const size_type normalized_index = normalize_index(index, this->size());
#ifndef ONLINE_JUDGE
    if (normalized_index >= this->size()) {
      throw_out_of_range(index, this->size(), location);
    }
#endif
    return Base::operator[](normalized_index);
  }

  template <typename Range, typename = RangeLike<Range>>
  RArray operator[](
      const Range &range,
      std::source_location location = std::source_location::current()) const {
    return slice_by_range(range, location);
  }
#else
  reference operator[](size_type index) {
#ifndef ONLINE_JUDGE
    if (index >= this->size()) {
      throw_out_of_range(index, this->size());
    }
#endif
    return Base::operator[](index);
  }

  const_reference operator[](size_type index) const {
#ifndef ONLINE_JUDGE
    if (index >= this->size()) {
      throw_out_of_range(index, this->size());
    }
#endif
    return Base::operator[](index);
  }

  template <typename Index,
            typename = std::enable_if_t<std::is_signed<Index>::value>>
  reference operator[](Index index) {
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
  const_reference operator[](Index index) const {
    const size_type normalized_index = normalize_index(index, this->size());
#ifndef ONLINE_JUDGE
    if (normalized_index >= this->size()) {
      throw_out_of_range(index, this->size());
    }
#endif
    return Base::operator[](normalized_index);
  }

  template <typename Range, typename = RangeLike<Range>>
  RArray operator[](const Range &range) const {
    return slice_by_range(range);
  }
#endif

  std::optional<T> first() const {
    if (this->empty()) {
      return std::nullopt;
    }
    return Base::front();
  }

  std::optional<T> last() const {
    if (this->empty()) {
      return std::nullopt;
    }
    return Base::back();
  }

  bool include(const T &value) const {
    return std::find(this->begin(), this->end(), value) != this->end();
  }

  size_type count(const T &value) const {
    return static_cast<size_type>(
        std::count(this->begin(), this->end(), value));
  }

  RArray take(size_type count) const {
    const size_type take_count = std::min(count, this->size());
    return RArray(this->begin(), this->begin() + take_count);
  }

  RArray drop(size_type count) const {
    const size_type drop_count = std::min(count, this->size());
    return RArray(this->begin() + drop_count, this->end());
  }

  RArray reverse() const {
    RArray result(this->rbegin(), this->rend());
    return result;
  }

  RArray sort() const {
    RArray result = *this;
    std::sort(result.begin(), result.end());
    return result;
  }

  RArray sort_desc() const {
    RArray result = *this;
    std::sort(result.begin(), result.end(), std::greater<T>());
    return result;
  }

  template <typename F> RArray sort_by(F &&selector) const {
    RArray result = *this;
    std::sort(result.begin(), result.end(), [&](const auto &a, const auto &b) {
      return std::invoke(selector, a) < std::invoke(selector, b);
    });
    return result;
  }

  template <typename F> RArray sort_by_desc(F &&selector) const {
    RArray result = *this;
    std::sort(result.begin(), result.end(), [&](const auto &a, const auto &b) {
      return std::invoke(selector, a) > std::invoke(selector, b);
    });
    return result;
  }

  RArray dup() const { return RArray(this->begin(), this->end()); }

  Map<T, size_type> tally() const {
    Map<T, size_type> counts;
    for (const auto &value : *this) {
      ++counts[value];
    }
    return counts;
  }

  std::vector<T> to_vec() const {
    return std::vector<T>(this->begin(), this->end());
  }
  std::vector<T> into_vec() && {
    return std::vector<T>(std::make_move_iterator(this->begin()),
                          std::make_move_iterator(this->end()));
  }

  template <typename U = T, typename = Comparable<U>>
  std::optional<T> min() const {
    if (this->empty()) {
      return std::nullopt;
    }
    return *std::min_element(this->begin(), this->end());
  }

  template <typename U = T, typename = Comparable<U>>
  std::optional<T> max() const {
    if (this->empty()) {
      return std::nullopt;
    }
    return *std::max_element(this->begin(), this->end());
  }

  template <typename U = T, typename = Comparable<U>>
  std::optional<std::pair<T, T>> minmax() const {
    if (this->empty()) {
      return std::nullopt;
    }
    const auto [min_it, max_it] =
        std::minmax_element(this->begin(), this->end());
    return std::pair<T, T>{*min_it, *max_it};
  }

  template <typename U = T, typename = Numeric<U>> T sum() const {
    return std::accumulate(this->begin(), this->end(), static_cast<T>(0));
  }

  template <typename U = T, typename = Numeric<U>> T product() const {
    return std::accumulate(this->begin(), this->end(), static_cast<T>(1),
                           std::multiplies<T>());
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const RArray<T> &v) {
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
