#pragma once

#include "features/core.hpp"

/// 区間の和集合を `std::set` で管理するデータ構造。
template <typename T> class IntervalSet {
private:
  std::set<std::pair<T, T>> segs;

public:
  IntervalSet() = default;

  /// 現在保持している非交差の区間集合への参照を返す。
  const std::set<std::pair<T, T>> &intervals() const { return segs; }

  /// 点 `x` を含む区間を返す。存在しない場合は `std::nullopt`。
  std::optional<std::pair<T, T>> find(T x) const {
    auto it = segs.upper_bound({x, std::numeric_limits<T>::max()});
    if (it == segs.begin()) {
      return std::nullopt;
    }
    --it;
    if (it->first <= x && x < it->second) {
      return *it;
    }
    return std::nullopt;
  }

  /// 半開区間 `[l, r)` を追加し、新たに被覆された長さを返す。
  /// `l >= r` の場合は何もせず 0 を返す。
  T add(T l, T r) {
    if (l >= r) {
      return static_cast<T>(0);
    }

    T added = r - l;
    auto it = segs.lower_bound({l, l});
    if (it != segs.begin()) {
      auto prev = std::prev(it);
      if (prev->second >= l) {
        it = prev;
      }
    }

    std::vector<typename std::set<std::pair<T, T>>::iterator> erase_list;
    T nl = l;
    T nr = r;

    for (; it != segs.end() && it->first <= nr; ++it) {
      nl = std::min(nl, it->first);
      nr = std::max(nr, it->second);

      T left = std::max(l, it->first);
      T right = std::min(r, it->second);
      if (left < right) {
        added -= right - left;
      }
      erase_list.push_back(it);
    }

    for (auto e : erase_list) {
      segs.erase(e);
    }
    segs.emplace(nl, nr);
    return added;
  }

  /// 半開区間 `[l, r)` を削除し、減少した被覆長を返す。
  /// `l >= r` の場合は何もせず 0 を返す。
  T remove(T l, T r) {
    if (l >= r) {
      return static_cast<T>(0);
    }

    auto it = segs.lower_bound({l, l});
    if (it != segs.begin()) {
      auto prev = std::prev(it);
      if (prev->second > l) {
        it = prev;
      }
    }

    std::vector<std::pair<T, T>> add_back;
    std::vector<typename std::set<std::pair<T, T>>::iterator> erase_list;
    T removed = 0;

    for (; it != segs.end() && it->first < r; ++it) {
      auto [il, ir] = *it;
      if (ir <= l) {
        continue;
      }

      T left = std::max(l, il);
      T right = std::min(r, ir);
      if (left >= right) {
        continue;
      }

      removed += right - left;
      if (il < left) {
        add_back.emplace_back(il, left);
      }
      if (right < ir) {
        add_back.emplace_back(right, ir);
      }
      erase_list.push_back(it);
    }

    for (auto e : erase_list) {
      segs.erase(e);
    }
    for (auto [il, ir] : add_back) {
      segs.emplace(il, ir);
    }
    return removed;
  }
};
