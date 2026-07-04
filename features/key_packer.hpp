#pragma once

#include "features/core.hpp"

/// 複数の非負整数を、各値の最大値に基づいて1つの整数キーへ変換する。
template <typename T = i64> class KeyPacker {
private:
  std::vector<T> maxes;

public:
  explicit KeyPacker(const std::vector<T> &maxes) : maxes(maxes) {
    each(max, this->maxes) {
      if (max < 0) {
        throw std::invalid_argument("max must be non-negative");
      }
    }
  }

  KeyPacker(std::initializer_list<T> maxes)
      : KeyPacker(std::vector<T>(maxes)) {}

  /// 各次元の最大値への参照を返す。
  fn limits() const -> const std::vector<T> & { return maxes; }

  /// 値列が各次元の範囲内に収まるかを返す。
  fn within_range(const std::vector<T> &values) const -> bool {
    if (values.size() != maxes.size()) {
      throw std::invalid_argument(
          "number of values must match number of maxes");
    }

    enumerate(value, i, values) {
      const T max = maxes[i];
      if (value < 0 || value > max) {
        return false;
      }
    }
    return true;
  }

  fn within_range(std::initializer_list<T> values) const -> bool {
    return within_range(std::vector<T>(values));
  }

  template <typename... Args> fn within_range(Args... values) const -> bool {
    return within_range(std::vector<T>{static_cast<T>(values)...});
  }

  /// 値列を1つの整数キーに変換する。
  fn pack(const std::vector<T> &values) const -> T {
    if (values.size() != maxes.size()) {
      throw std::invalid_argument(
          "number of values must match number of maxes");
    }

    T key = 0;
    T multiplier = 1;
    enumerate(value, i, values) {
      const T max = maxes[i];
      if (value < 0 || value > max) {
        throw std::invalid_argument("value exceeds max");
      }

      key += value * multiplier;
      multiplier *= max + 1;
    }
    return key;
  }

  fn pack(std::initializer_list<T> values) const -> T {
    return pack(std::vector<T>(values));
  }

  template <typename... Args> fn pack(Args... values) const -> T {
    return pack(std::vector<T>{static_cast<T>(values)...});
  }

  /// 整数キーを元の値列に戻す。
  fn unpack(T key) const -> std::vector<T> {
    if (key < 0) {
      throw std::invalid_argument("key must be non-negative");
    }

    std::vector<T> values;
    values.reserve(maxes.size());

    T multiplier = 1;
    each(max, maxes) {
      values.push_back((key / multiplier) % (max + 1));
      multiplier *= max + 1;
    }
    return values;
  }
};
