#include "features/debug.hpp"

#include <cassert>
#include <sstream>

int main() {
  std::ostringstream oss;

  oss << vector<int>{1, 2, 3};
  assert(oss.str() == "[1, 2, 3]");

  oss.str("");
  oss.clear();
  oss << std::set<int>{1, 2};
  assert(oss.str() == "{1 2}");

  oss.str("");
  oss.clear();
  oss << std::unordered_set<int>{3, 5};
  auto unordered_output = oss.str();
  assert(unordered_output == "{3 5}" || unordered_output == "{5 3}");

  oss.str("");
  oss.clear();
  oss << std::pair<int, int>{4, 7};
  assert(oss.str() == "(4, 7)");

  oss.str("");
  oss.clear();
  oss << std::map<int, int>{{1, 2}, {3, 4}};
  assert(oss.str() == "{1: 2, 3: 4}");

  oss.str("");
  oss.clear();
  oss << std::unordered_map<int, int>{{1, 5}, {2, 6}};
  auto umap_output = oss.str();
  assert(umap_output == "{1: 5, 2: 6}" || umap_output == "{2: 6, 1: 5}");

  return 0;
}

