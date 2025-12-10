#pragma once

#include "features/core.hpp"

/// コンテナ内の要素に対してFを適用したものを返す。
template <typename T, typename F, typename V>
std::vector<T> vec_map(const V &vec, F &&func) {
  std::vector<T> result;
  result.reserve(sz(vec));
  each(x, vec) { result.push_back(func(x)); }
  return result;
}

/// コンテナ内の要素をFによって変換する。
template <typename F, typename V> void vec_map_inplace(V &vec, F &&func) {
  each(x, vec) { x = func(x); }
}
