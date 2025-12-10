#pragma once

#include "features/core.hpp"

/// コンテナ内の要素の総和を求める。
template <typename T, typename V> T sum(const V &vec) {
  T total = 0;
  each(x, vec) { total += x; }
  return total;
}
