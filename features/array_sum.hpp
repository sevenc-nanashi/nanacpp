#pragma once

#include "features/core.hpp"

template <typename T> class ArraySum {
private:
  usize n;
  std::vector<T> prefix_sum;

public:
  explicit ArraySum(const std::vector<T> &data) : n(data.size()), prefix_sum(n + 1, 0) {
    for (usize i = 0; i < n; ++i) {
      prefix_sum[i + 1] = prefix_sum[i] + data[i];
    }
  }

  T sum(size_t l, size_t r) const { return prefix_sum[r] - prefix_sum[l]; }
};

