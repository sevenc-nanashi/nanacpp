#pragma once

#include "features/core.hpp"

/// コンテナを selector の結果で昇順ソートする。
template <typename V, typename F> void sort_by(V &vec, F &&selector) {
  std::sort(all(vec), [&](const auto &a, const auto &b) {
    return std::invoke(selector, a) < std::invoke(selector, b);
  });
}

/// コンテナを selector の結果で降順ソートする。
template <typename V, typename F> void sort_by_desc(V &vec, F &&selector) {
  std::sort(all(vec), [&](const auto &a, const auto &b) {
    return std::invoke(selector, a) > std::invoke(selector, b);
  });
}
