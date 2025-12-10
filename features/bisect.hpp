#pragma once

#include "features/core.hpp"

template <typename F>
/// Finds the first index `i` in the half-open range `[l, r)` such that
/// `cond(i)` is true. If no such index exists, returns `std::nullopt`.
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
/// Finds the first index `i` in the closed range `[l, r]` such that
/// `cond(i)` is true. If no such index exists, returns `std::nullopt`.
std::optional<i64> bisect_first_closed(i64 l, i64 r, F &&cond) {
  return bisect_first(l, r + 1, cond);
}

template <typename F>
/// Finds the last index `i` in the half-open range `[l, r)` such that
/// `cond(i)` is true. If no such index exists, returns `std::nullopt`.
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
/// Finds the last index `i` in the closed range `[l, r]` such that
/// `cond(i)` is true. If no such index exists, returns `std::nullopt`.
std::optional<i64> bisect_last_closed(i64 l, i64 r, F &&cond) {
  return bisect_last(l, r + 1, cond);
}
