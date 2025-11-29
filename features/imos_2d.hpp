#pragma once

#include "features/core.hpp"

// 2 次元 Imos 法（差分配列）
template <typename T> class Imos2D {
private:
  usize height;
  usize width;
  std::vector<std::vector<T>> diff;
  std::vector<std::vector<T>> built_values;
  bool ready;

public:
  Imos2D(usize h, usize w)
      : height(h), width(w), diff(h + 1, std::vector<T>(w + 1, 0)),
        built_values(h, std::vector<T>(w, 0)), ready(false) {}

  usize rows() const { return height; }
  usize cols() const { return width; }

  // 長方形 [top, bottom) × [left, right) に value を加算
  void add(usize top, usize left, usize bottom, usize right, const T &value) {
    assert(top <= bottom);
    assert(left <= right);
    assert(bottom <= height);
    assert(right <= width);
    diff[top][left] += value;
    diff[bottom][left] -= value;
    diff[top][right] -= value;
    diff[bottom][right] += value;
    ready = false;
  }

  // 長方形 [top, bottom] × [left, right] に value を加算
  void add_closed(usize top, usize left, usize bottom, usize right,
                  const T &value) {
    assert(bottom < height);
    assert(right < width);
    add(top, left, bottom + 1, right + 1, value);
  }

  [[nodiscard]] const std::vector<std::vector<T>> &build() {
    if (!ready) {
      std::vector<std::vector<T>> acc(height + 1,
                                      std::vector<T>(width + 1, 0));
      for (usize y = 0; y <= height; ++y) {
        for (usize x = 0; x <= width; ++x) {
          T val = diff[y][x];
          if (y > 0) {
            val += acc[y - 1][x];
          }
          if (x > 0) {
            val += acc[y][x - 1];
          }
          if (y > 0 && x > 0) {
            val -= acc[y - 1][x - 1];
          }
          acc[y][x] = val;
          if (y < height && x < width) {
            built_values[y][x] = val;
          }
        }
      }
      ready = true;
    }
    return built_values;
  }

  [[nodiscard]] const std::vector<std::vector<T>> &values() const {
    assert(ready);
    return built_values;
  }

  const std::vector<T> &operator[](usize row) const {
    assert(ready);
    return built_values[row];
  }

  std::vector<std::vector<T>> applied(
      std::vector<std::vector<T>> base) {
    assert(base.size() == height);
    for (const auto &row : base) {
      assert(row.size() == width);
    }
    const auto &delta = build();
    for (usize y = 0; y < height; ++y) {
      for (usize x = 0; x < width; ++x) {
        base[y][x] += delta[y][x];
      }
    }
    return base;
  }
};
