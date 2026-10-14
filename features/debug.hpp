#pragma once

#include "features/core.hpp"
#include <string>

fn operator<<(std::ostream &os, const u128 &v)->std::ostream & {
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

fn operator<<(std::ostream &os, const i128 &v)->std::ostream & {
  if (v >= 0) {
    return os << static_cast<u128>(v);
  } else {
    os << '-';
    return os << static_cast<u128>(-v);
  }
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
    constexpr auto _dbg_format =                                               \
        std::is_convertible_v<decltype(_dbg_x), std::string_view> ? "{:?}"     \
                                                                  : "{}";      \
    std::cerr << std::format(_dbg_format, _dbg_x) << std::endl;                \
    return _dbg_x;                                                             \
  }())
#define dbg2(x)                                                                \
  ([&]() {                                                                     \
    auto _dbg_x = (x);                                                         \
    std::cerr << "[[dbg L" << __LINE__ << "]] " << #x << " = ";                \
    constexpr auto _dbg_format =                                               \
        std::is_convertible_v<decltype(_dbg_x), std::string_view> ? "{:?}"     \
                                                                  : "{}";      \
    std::cerr << std::format(_dbg_format, _dbg_x) << std::endl;                \
    return _dbg_x;                                                             \
  }())
#define dbg3(x)                                                                \
  ([&]() {                                                                     \
    auto _dbg_x = (x);                                                         \
    std::cerr << "[[[dbg L" << __LINE__ << "]]] " << #x << " = ";              \
    constexpr auto _dbg_format =                                               \
        std::is_convertible_v<decltype(_dbg_x), std::string_view> ? "{:?}"     \
                                                                  : "{}";      \
    std::cerr << std::format(_dbg_format, _dbg_x) << std::endl;                \
    return _dbg_x;                                                             \
  }())
#endif
