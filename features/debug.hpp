#pragma once

#include "features/core.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
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

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &v) {
  os << "{";
  for (auto it = v.begin(); it != v.end(); ++it) {
    os << *it;
    auto next_it = it;
    ++next_it;
    if (next_it != v.end()) {
      os << " ";
    }
  }
  os << "}";
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T> &v) {
  os << "{";
  for (auto it = v.begin(); it != v.end(); ++it) {
    os << *it;
    auto next_it = it;
    ++next_it;
    if (next_it != v.end()) {
      os << " ";
    }
  }
  os << "}";
  return os;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::map<T, U> &m) {
  os << "{";
  for (auto it = m.begin(); it != m.end(); ++it) {
    os << it->first << ": " << it->second;
    auto next_it = it;
    ++next_it;
    if (next_it != m.end()) {
      os << ", ";
    }
  }
  os << "}";
  return os;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<T, U> &m) {
  os << "{";
  for (auto it = m.begin(); it != m.end(); ++it) {
    os << it->first << ": " << it->second;
    auto next_it = it;
    ++next_it;
    if (next_it != m.end()) {
      os << ", ";
    }
  }
  os << "}";
  return os;
}

#ifdef ONLINE_JUDGE
#define dbg(x) x
#define dbg2(x) x
#define dbg3(x) x
#else
#define dbg(x)                                                                 \
  ([&]() {                                                                     \
    auto _dbg_x = (x);                                                         \
    std::cerr << "[dbg L" << __LINE__ << "] " << #x << " = ";                  \
    std::cerr << _dbg_x << std::endl;                                          \
    return _dbg_x;                                                             \
  }())
#define dbg2(x)                                                                \
  ([&]() {                                                                     \
    auto _dbg_x = (x);                                                         \
    std::cerr << "[[dbg L" << __LINE__ << "]] " << #x << " = ";                \
    std::cerr << _dbg_x << std::endl;                                          \
    return _dbg_x;                                                             \
  }())
#define dbg3(x)                                                                \
  ([&]() {                                                                     \
    auto _dbg_x = (x);                                                         \
    std::cerr << "[[[dbg L" << __LINE__ << "]]] " << #x << " = ";              \
    std::cerr << _dbg_x << std::endl;                                          \
    return _dbg_x;                                                             \
  }())
#endif
