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
  static
      typename Base::size_type normalize_index(Index index,
                                               typename Base::size_type size) {
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
};
