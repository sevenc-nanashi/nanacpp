#pragma once

#include "features/core.hpp"

// Imos 法（差分配列）を扱うユーティリティ
template <typename T> class Imos {
private:
  std::vector<T> diff;
  std::vector<T> built_values;
  bool ready;

public:
  explicit Imos(usize n) : diff(n + 1, 0), built_values(n, 0), ready(false) {}

  usize size() const { return built_values.size(); }

  // 区間 [l, r) に value を加算する
  void add(usize l, usize r, const T &value) {
    assert(l <= r);
    assert(l <= size());
    assert(r <= size());
    diff[l] += value;
    diff[r] -= value;
    ready = false;
  }

  // 区間 [l, r] に value を加算する
  void add_closed(usize l, usize r, const T &value) {
    assert(l <= r);
    assert(r < size());
    add(l, r + 1, value);
  }

  [[nodiscard]] const std::vector<T> &build() {
    if (!ready) {
      T run = 0;
      for (usize i = 0; i < size(); ++i) {
        run += diff[i];
        built_values[i] = run;
      }
      ready = true;
    }
    return built_values;
  }

  [[nodiscard]] const std::vector<T> &values() const {
    assert(ready);
    return built_values;
  }

  [[nodiscard]] const T &operator[](usize idx) const {
    assert(ready);
    return built_values[idx];
  }

  std::vector<T> applied(std::vector<T> base) {
    assert(base.size() == size());
    const auto &delta = build();
    for (usize i = 0; i < size(); ++i) {
      base[i] += delta[i];
    }
    return base;
  }
};
