#pragma once

#include "features/core.hpp"

/// Imos 法（差分配列）で区間加算をまとめて反映するユーティリティ。
template <typename T> class Imos {
private:
  std::vector<T> diff;
  std::vector<T> built_values;
  bool ready;

public:
  /// 要素数 `n` の差分配列を初期化する。
  explicit Imos(usize n) : diff(n + 1, 0), built_values(n, 0), ready(false) {}

  /// 配列の長さを返す。
  fn size() const -> usize { return built_values.size(); }

  /// 区間 [l, r) に `value` を加算する。
  fn add(usize l, usize r, const T &value) -> void {
    assert(l <= r);
    assert(l <= size());
    assert(r <= size());
    diff[l] += value;
    diff[r] -= value;
    ready = false;
  }

  /// 区間 [l, r] に `value` を加算する。
  fn add_closed(usize l, usize r, const T &value) -> void {
    assert(l <= r);
    assert(r < size());
    add(l, r + 1, value);
  }

  /// 累積して最終的な配列を構築し、参照を返す。複数回呼ぶと結果をキャッシュする。
  [[nodiscard]] fn build() -> const std::vector<T> & {
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

  /// 構築済みの値を取得する。`build` を事前に呼ぶ必要がある。
  [[nodiscard]] fn values() const -> const std::vector<T> & {
    assert(ready);
    return built_values;
  }

  /// 構築済みの値へのランダムアクセス。`build` を事前に呼ぶ必要がある。
  [[nodiscard]] fn operator[](usize idx) const->const T & {
    assert(ready);
    return built_values[idx];
  }

  /// 基底配列に差分を適用した新しい配列を返す。
  fn applied(std::vector<T> base) -> std::vector<T> {
    assert(base.size() == size());
    const auto &delta = build();
    for (usize i = 0; i < size(); ++i) {
      base[i] += delta[i];
    }
    return base;
  }
};
