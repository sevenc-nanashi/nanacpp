#pragma once

#include "features/core.hpp"

/// 1 次元配列の累積和を保持し、区間和を高速に計算するヘルパー。
template <typename T> class ArraySum {
private:
  usize n;
  std::vector<T> prefix_sum;

public:
  /// `data` から累積和を構築する。計算量は O(N)。
  explicit ArraySum(const std::vector<T> &data)
      : n(data.size()), prefix_sum(n + 1, 0) {
    for (usize i = 0; i < n; ++i) {
      prefix_sum[i + 1] = prefix_sum[i] + data[i];
    }
  }

  /// 区間 [l, r) の和を返す
  T sum(size_t l, size_t r) const { return prefix_sum[r] - prefix_sum[l]; }

  /// 区間 [l, r] の和を返す
  T sum_closed(size_t l, size_t r) const {
    return prefix_sum[r + 1] - prefix_sum[l];
  }
};
