#pragma once

#include "features/core.hpp"

/// 2 次元配列の累積和を保持し、長方形領域の総和を O(1) で取得するクラス。
template <typename T> class CumulativeSum2D {
private:
  usize height;
  usize width;
  std::vector<std::vector<T>> prefix;

public:
  /// `grid` の累積和を構築する。行ごとの幅が一致していることを前提とする。
  explicit CumulativeSum2D(const std::vector<std::vector<T>> &grid)
      : height(grid.size()), width(height ? grid[0].size() : 0),
        prefix(height + 1, std::vector<T>(width + 1, 0)) {
    for (usize y = 0; y < height; ++y) {
      assert(grid[y].size() == width);
      for (usize x = 0; x < width; ++x) {
        prefix[y + 1][x + 1] =
            grid[y][x] + prefix[y][x + 1] + prefix[y + 1][x] -
            prefix[y][x];
      }
    }
  }

  /// 行数を返す。
  usize rows() const { return height; }

  /// 列数を返す。
  usize cols() const { return width; }

  /// 長方形 [top, bottom) × [left, right) の和を返す。
  T sum(usize top, usize left, usize bottom, usize right) const {
    assert(top <= bottom);
    assert(left <= right);
    assert(bottom <= height);
    assert(right <= width);
    return prefix[bottom][right] - prefix[top][right] -
           prefix[bottom][left] + prefix[top][left];
  }

  /// 長方形 [top, bottom] × [left, right] の和を返す。
  T sum_closed(usize top, usize left, usize bottom, usize right) const {
    assert(bottom < height);
    assert(right < width);
    return sum(top, left, bottom + 1, right + 1);
  }
};
