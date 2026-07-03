#pragma once

#include "features/core.hpp"

void print() { std::cout << "\n"; }
void print(const std::string &s) { std::cout << s << "\n"; }
void print(const char *s) { std::cout << s << "\n"; }
template <typename T> void print(const T &value) { std::cout << value << "\n"; }
template <typename T> void print(const std::vector<T> &vec) {
  enumerate(x, i, vec) {
    std::cout << x;
    if (i + 1 != vec.size()) {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
  std::cout << first;
  if constexpr (sizeof...(args) > 0) {
    std::cout << " ";
    print(args...);
  } else {
    std::cout << "\n";
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
  std::cout << "\n";
}
