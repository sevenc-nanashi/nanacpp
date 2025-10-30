#pragma once

#include "features/core.hpp"

template <typename T, typename U> class hpair {
public:
  T first;
  U second;
  hpair(const T &f, const U &s) : first(f), second(s) {}
  bool operator==(const hpair<T, U> &other) const {
    return first == other.first && second == other.second;
  }
};

namespace std {
template <typename T, typename U> struct hash<hpair<T, U>> {
  size_t operator()(const hpair<T, U> &p) const {
    return hash<T>()(p.first) ^ (hash<U>()(p.second) << 1);
  }
};
} // namespace std
