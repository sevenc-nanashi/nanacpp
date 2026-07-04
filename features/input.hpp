#pragma once

#include "features/core.hpp"

/// 1 変数を読み込む。
#define input(type, var)                                                       \
  type var;                                                                    \
  std::cin >> var;

/// 要素数 `n` のベクタを読み込む。
#define input_vec(type, var, n)                                                \
  std::vector<type> var(n);                                                    \
  for (usize i = 0; i < (usize)(n); ++i) {                                     \
    std::cin >> var[i];                                                        \
  }

/// 要素数 `n` のRArrayを読み込む。
#define input_rarray(type, var, n)                                             \
  RArray<type> var(n);                                                         \
  for (usize i = 0; i < (usize)(n); ++i) {                                     \
    std::cin >> var[i];                                                        \
  }

/// 要素数固定の `std::array` を読み込む。
#define input_array(type, var, n)                                              \
  std::array<type, n> var;                                                     \
  for (usize i = 0; i < (usize)(n); ++i) {                                     \
    std::cin >> var[i];                                                        \
  }

/// 2 要素の `std::pair` を読み込む。
#define input_pair(type1, type2, var)                                          \
  std::pair<type1, type2> var;                                                 \
  std::cin >> var.first >> var.second;

/// 2 要素の `hpair` を読み込む。
#define input_hpair(type1, type2, var)                                         \
  hpair<type1, type2> var;                                                     \
  std::cin >> var.first >> var.second;

/// 要素数 `n` の `std::pair` ベクタを読み込む。
#define input_vec_pair(type1, type2, var, n)                                   \
  std::vector<std::pair<type1, type2>> var(n);                                 \
  for (usize i = 0; i < (usize)(n); ++i) {                                     \
    std::cin >> var[i].first >> var[i].second;                                 \
  }

/// 要素数 `n` の `hpair` ベクタを読み込む。
#define input_vec_hpair(type1, type2, var, n)                                  \
  std::vector<hpair<type1, type2>> var(n);                                     \
  for (usize i = 0; i < (usize)(n); ++i) {                                     \
    std::cin >> var[i].first >> var[i].second;                                 \
  }

/// 2 次元配列を読み込む。
#define input_vec2(type, var, rows, cols)                                      \
  std::vector<std::vector<type>> var(rows, std::vector<type>(cols));           \
  for (usize i = 0; i < (usize)(rows); ++i) {                                  \
    for (usize j = 0; j < (usize)(cols); ++j) {                                \
      std::cin >> var[i][j];                                                   \
    }                                                                          \
  }

/// 2 次元 RArray を読み込む。
#define input_rarray2(type, var, rows, cols)                                   \
  RArray<RArray<type>> var(rows, RArray<type>(cols));                          \
  for (usize i = 0; i < (usize)(rows); ++i) {                                  \
    for (usize j = 0; j < (usize)(cols); ++j) {                                \
      std::cin >> var[i][j];                                                   \
    }                                                                          \
  }
