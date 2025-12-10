#include "features/interval_set.hpp"

#include <cassert>

int main() {
  IntervalSet<int> segs;
  assert(segs.add(2, 5) == 3);
  assert(segs.add(8, 10) == 2);
  assert(segs.add(4, 9) == 3); // [2, 10) にマージ

  const auto &merged = segs.intervals();
  assert(merged.size() == 1);
  assert(((*merged.begin()) == std::pair<int, int>{2, 10}));

  let found = segs.find(6);
  assert(found.has_value());
  assert(found->first == 2);
  assert(found->second == 10);
  assert(!segs.find(11).has_value());

  // 隣接する区間もまとめて扱う
  assert(segs.add(10, 12) == 2);
  assert(((*segs.intervals().begin()) == std::pair<int, int>{2, 12}));

  // 削除で分割されるケース
  IntervalSet<int> removed;
  removed.add(0, 5);
  removed.add(10, 15);

  assert(removed.remove(3, 12) == 4);
  const auto &after_remove = removed.intervals();
  assert(after_remove.size() == 2);
  auto it = after_remove.begin();
  assert(((*it) == std::pair<int, int>{0, 3}));
  ++it;
  assert(((*it) == std::pair<int, int>{12, 15}));

  // 1つの区間が2つに割れるケース
  IntervalSet<int> split;
  split.add(5, 15);
  assert(split.remove(7, 12) == 5);
  const auto &after_split = split.intervals();
  assert(after_split.size() == 2);
  auto sit = after_split.begin();
  assert(((*sit) == std::pair<int, int>{5, 7}));
  ++sit;
  assert(((*sit) == std::pair<int, int>{12, 15}));

  // 完全に含まれる追加は被覆長を変えない
  assert(split.add(6, 6) == 0);
  assert(split.add(5, 7) == 0);

  return 0;
}
