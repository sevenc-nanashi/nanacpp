#pragma once

#include "features/core.hpp"

#define input(type, var)                                                       \
  type var;                                                                    \
  cin >> var;
#define input_vec(type, var, n)                                                \
  std::vector<type> var(n);                                                    \
  for (usize i = 0; i < (usize)(n); ++i) {                                     \
    cin >> var[i];                                                             \
  }
#define input_array(type, var, n)                                              \
  std::array<type, n> var;                                                     \
  for (usize i = 0; i < (usize)(n); ++i) {                                     \
    cin >> var[i];                                                             \
  }
#define input_pair(type1, type2, var)                                          \
  std::pair<type1, type2> var;                                                 \
  cin >> var.first >> var.second;
#define input_hpair(type1, type2, var)                                         \
  hpair<type1, type2> var;                                                     \
  cin >> var.first >> var.second;
#define input_vec_pair(type1, type2, var, n)                                   \
  std::vector<std::pair<type1, type2>> var(n);                                 \
  for (usize i = 0; i < (usize)(n); ++i) {                                     \
    cin >> var[i].first >> var[i].second;                                      \
  }
#define input_vec_hpair(type1, type2, var, n)                                  \
  std::vector<hpair<type1, type2>> var(n);                                     \
  for (usize i = 0; i < (usize)(n); ++i) {                                     \
    cin >> var[i].first >> var[i].second;                                      \
  }
