#pragma once

#include "features/core.hpp"
#include <source_location>

/// Ruby風の配列。
template <typename T, typename Allocator = std::allocator<T>>
class RArray : public std::vector<T, Allocator> {
private:
  using Base = std::vector<T, Allocator>;

  [[noreturn]] static void
  throw_out_of_range(typename Base::size_type index,
                     typename Base::size_type size,
                     const std::source_location &location) {
    std::ostringstream oss;
    oss << "BacktraceVec index out of range: index=" << index
        << ", size=" << size << ", called from " << location.file_name() << ":"
        << location.line() << ":" << location.column() << " in "
        << location.function_name();
    throw std::out_of_range(oss.str());
  }

public:
  using typename Base::allocator_type;
  using typename Base::const_reference;
  using typename Base::reference;
  using typename Base::size_type;
  using typename Base::value_type;

  using Base::Base;

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
};
