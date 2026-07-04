#pragma once

#include <bits/stdc++.h>

#define fn auto
#define let auto

#define each(x, a) for (auto &x : a)
#define each1(x, a) for (auto &x : a)
#define each2(x, y, a) for (auto &[x, y] : a)
#define each3(x, y, z, a) for (auto &[x, y, z] : a)
#define each4(w, x, y, z, a) for (auto &[w, x, y, z] : a)

#define enumerate(x, i, a)                                                     \
  for (usize i = 0; i < (usize)a.size(); ++i)                                  \
    if (auto &x = a[i]; true)
#define enumerate1(x, i, a)                                                    \
  for (usize i = 0; i < (usize)a.size(); ++i)                                  \
    if (auto &x = a[i]; true)
#define enumerate2(x, y, i, a)                                                 \
  for (usize i = 0; i < (usize)a.size(); ++i)                                  \
    if (auto &[x, y] = a[i]; true)
#define enumerate3(x, y, z, i, a)                                              \
  for (usize i = 0; i < (usize)a.size(); ++i)                                  \
    if (auto &[x, y, z] = a[i]; true)
#define enumerate4(w, x, y, z, i, a)                                           \
  for (usize i = 0; i < (usize)a.size(); ++i)                                  \
    if (auto &[w, x, y, z] = a[i]; true)

#define rep(i, a) for (int i = 0; i < (a); ++i)
#define range(i, l, r) for (int i = (l); i < (r); ++i)
#define rangei(i, l, r) for (int i = (l); i <= (r); ++i)

#define chmax(var, val) var = std::max(var, val)
#define chmin(var, val) var = std::min(var, val)

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) ((i64)(x).size())

using ll = long long;
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128;
using isize = std::make_signed<std::size_t>::type;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usize = std::make_unsigned<std::size_t>::type;
using f32 = float;
using f64 = double;

/// メモ：
/// Compareを(T a, T b) -> boolとしたとき、優先して取り出されるのは、Compare(a, b)がtrueとなるbである。
/// つまり、Compareには「bを優先する条件」をいれる。
template <typename T, typename Compare = std::less<T>>
using PriorityQueue = std::priority_queue<T, std::vector<T>, Compare>;

char eol[] = "\n";

template <typename T> using Vec = std::vector<T>;

template <typename T> using Vec2 = std::vector<std::vector<T>>;

template <typename T> using Vec3 = std::vector<std::vector<std::vector<T>>>;

template <typename T, typename U> using OrderedMap = std::map<T, U>;

template <typename T, typename U> using Map = std::unordered_map<T, U>;

template <typename T> using OrderedSet = std::set<T>;

template <typename T> using Set = std::unordered_set<T>;
