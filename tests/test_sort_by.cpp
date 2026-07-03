#include "features/sort_by.hpp"

#include <cassert>
#include <string>

struct User {
  std::string name;
  int score;
};

int main() {
  Vec<std::pair<int, int>> pairs{{3, 30}, {1, 10}, {2, 20}};
  sort_by(pairs, [](const auto &p) { return p.first; });
  assert((pairs == Vec<std::pair<int, int>>{{1, 10}, {2, 20}, {3, 30}}));

  sort_by_desc(pairs, [](const auto &p) { return p.second; });
  assert((pairs == Vec<std::pair<int, int>>{{3, 30}, {2, 20}, {1, 10}}));

  Vec<User> users{{"alice", 30}, {"bob", 20}, {"carol", 40}};
  sort_by(users, &User::score);
  assert(users[0].name == "bob");
  assert(users[1].name == "alice");
  assert(users[2].name == "carol");

  sort_by(users, [](const User &user) { return user.name; });
  assert(users[0].score == 30);
  assert(users[1].score == 20);
  assert(users[2].score == 40);

  return 0;
}
