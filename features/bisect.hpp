#pragma once

#include "features/core.hpp"

template <typename F>
/// 半開区間 `[l, r)` で `cond(i)` が真になる最初の `i` を返す。
/// 存在しなければ `std::nullopt` を返す。
std::optional<i64> bisect_first(i64 l, i64 r, F &&cond) {
  if (cond(l)) {
    return l;
  }
  if (!cond(r - 1)) {
    return std::nullopt;
  }

  i64 left = l - 1;
  i64 right = r;
  while (left + 1 < right) {
    i64 mid = left + (right - left) / 2;
    if (cond(mid)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return right;
}

template <typename F>
/// 閉区間 `[l, r]` で `cond(i)` が真になる最初の `i` を返す。
/// 存在しなければ `std::nullopt` を返す。
std::optional<i64> bisect_first_closed(i64 l, i64 r, F &&cond) {
  return bisect_first(l, r + 1, cond);
}

template <typename F>
/// 半開区間 `[l, r)` で `cond(i)` が真になる最後の `i` を返す。
/// 存在しなければ `std::nullopt` を返す。
std::optional<i64> bisect_last(i64 l, i64 r, F &&cond) {
  if (!cond(l)) {
    return std::nullopt;
  }
  if (cond(r - 1)) {
    return r - 1;
  }

  i64 left = l;
  i64 right = r;
  while (left + 1 < right) {
    i64 mid = left + (right - left) / 2;
    if (cond(mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

template <typename F>
/// 閉区間 `[l, r]` で `cond(i)` が真になる最後の `i` を返す。
/// 存在しなければ `std::nullopt` を返す。
std::optional<i64> bisect_last_closed(i64 l, i64 r, F &&cond) {
  return bisect_last(l, r + 1, cond);
}
