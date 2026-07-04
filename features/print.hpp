#pragma once

#include "features/core.hpp"

#ifdef ONLINE_JUDGE
#define NANACPP_PRINT_EOL '\n'
#else
#define NANACPP_PRINT_EOL std::endl
#endif

fn print() -> void { std::cout << NANACPP_PRINT_EOL; }
fn print(const std::string &s) -> void { std::cout << s << NANACPP_PRINT_EOL; }
fn print(const char *s) -> void { std::cout << s << NANACPP_PRINT_EOL; }
template <typename T> fn print(const T &value) -> void {
  std::cout << value << NANACPP_PRINT_EOL;
}
template <typename T> fn print(const std::vector<T> &vec) -> void {
  enumerate(x, i, vec) {
    std::cout << x;
    if (i + 1 != vec.size()) {
      std::cout << " ";
    }
  }
  std::cout << NANACPP_PRINT_EOL;
}
template <typename T, typename... Args>
fn print(const T &first, const Args &...args) -> void {
  std::cout << first;
  if constexpr (sizeof...(args) > 0) {
    std::cout << " ";
    print(args...);
  } else {
    std::cout << NANACPP_PRINT_EOL;
  }
}
template <typename T>
fn print(const std::vector<T> &vec, const std::string &sep) -> void {
  enumerate(x, i, vec) {
    std::cout << x;
    if (i + 1 != vec.size()) {
      std::cout << sep;
    }
  }
  std::cout << NANACPP_PRINT_EOL;
}
