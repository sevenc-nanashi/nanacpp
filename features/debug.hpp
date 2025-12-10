#pragma once

#include "features/core.hpp"
#include <string>

std::ostream &
operator<<(std::ostream &os, // NOLINT: いうて1ファイルにまとまるし...
           const u128 &v) {
  u128 temp = v;
  if (temp == 0) {
    os << '0';
    return os;
  }
  std::string digits;
  while (temp > 0) {
    digits.push_back(static_cast<char>('0' + (temp % 10)));
    temp /= 10;
  }
  std::reverse(digits.begin(), digits.end());
  os << digits;
  return os;
}

std::ostream &
operator<<(std::ostream &os, // NOLINT: いうて1ファイルにまとまるし...
           const i128 &v) {
  if (v >= 0) {
    return os << static_cast<u128>(v);
  } else {
    os << '-';
    return os << static_cast<u128>(-v);
  }
}

/// `std::vector` を可読なリスト形式で出力する。
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

/// `std::set` を空白区切りで出力する。
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

/// `std::unordered_set` を空白区切りで出力する。
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

/// `std::pair` を `(first, second)` 形式で出力する。
template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

/// `std::map` を `key: value` の並びで出力する。
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

/// `std::unordered_map` を `key: value` の並びで出力する。
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

/// ローカル実行時のみ変数を stderr に出力し、値をそのまま返すデバッグマクロ群。
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
