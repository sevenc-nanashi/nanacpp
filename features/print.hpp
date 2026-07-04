#pragma once

#include "features/core.hpp"

#ifdef ONLINE_JUDGE
#define NANACPP_PRINT_EOL '\n'
#else
#define NANACPP_PRINT_EOL std::endl
#endif

void print() { std::cout << NANACPP_PRINT_EOL; }
void print(const std::string &s) { std::cout << s << NANACPP_PRINT_EOL; }
void print(const char *s) { std::cout << s << NANACPP_PRINT_EOL; }
template <typename T> void print(const T &value) { std::cout << value << NANACPP_PRINT_EOL; }
template <typename T> void print(const std::vector<T> &vec) {
  enumerate(x, i, vec) {
    std::cout << x;
    if (i + 1 != vec.size()) {
      std::cout << " ";
    }
  }
  std::cout << NANACPP_PRINT_EOL;
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
  std::cout << first;
  if constexpr (sizeof...(args) > 0) {
    std::cout << " ";
    print(args...);
  } else {
    std::cout << NANACPP_PRINT_EOL;
  }
}
template <typename T>
void print(const std::vector<T> &vec, const std::string &sep) {
  enumerate(x, i, vec) {
    std::cout << x;
    if (i + 1 != vec.size()) {
      std::cout << sep;
    }
  }
  std::cout << NANACPP_PRINT_EOL;
}
