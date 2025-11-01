#pragma once

#include "features/core.hpp"

template <typename F>
/// Finds the first index `i` in the range `[l, r]` such that `cond(i)` is true.
/// If no such index exists, returns `r + 1`.
i64 bisect_first(i64 l, i64 r, F &&cond) {
  i64 left = l;
  i64 right = r + 1;
  while (left < right) {
    i64 mid = left + (right - left) / 2;
    if (cond(mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}

template <typename F>
/// Finds the last index `i` in the range `[l, r]` such that `cond(i)` is true.
/// If no such index exists, returns `l - 1`.
i64 bisect_last(i64 l, i64 r, F &&cond) {
  i64 left = l - 1;
  i64 right = r;
  while (left < right) {
    i64 mid = left + (right - left + 1) / 2;
    if (cond(mid)) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }
  return left;
}
