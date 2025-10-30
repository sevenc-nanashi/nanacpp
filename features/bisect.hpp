#pragma once

#include "features/core.hpp"

template <typename F>
u64 bisect_first(u64 l, u64 r, F &&cond) {
  while (l < r) {
    u64 m = (l + r) / 2;
    if (cond(m)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  return l;
}

template <typename F>
u64 bisect_last(u64 l, u64 r, F &&cond) {
  while (l < r) {
    u64 m = (l + r) / 2;
    if (cond(m)) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  return l - 1;
}

