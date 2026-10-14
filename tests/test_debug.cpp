#include "features/debug.hpp"

#include <cassert>
#include <sstream>

int main() {
  std::ostringstream oss;

  auto *previous = std::cerr.rdbuf(oss.rdbuf());
  auto check_output = [&](const std::string &expected) {
    assert(oss.str().ends_with(" = " + expected + "\n"));
    oss.str("");
    oss.clear();
  };

  const char *literal = "Hello, World!";
  assert(dbg(literal) == literal);
  check_output(R"("Hello, World!")");

  std::string text = "line\n\t\"quoted\"\\";
  assert(dbg2(text) == text);
  check_output(R"("line\n\t\"quoted\"\\")");

  std::string_view view = "view\n";
  assert(dbg3(view) == view);
  check_output(R"("view\n")");

  dbg("");
  check_output(R"("")");

  char mutable_text[] = "mutable";
  dbg(mutable_text);
  check_output(R"("mutable")");

  assert(dbg2(42) == 42);
  check_output("42");

  assert(dbg3(-42LL) == -42LL);
  check_output("-42");

  assert(dbg(3.5) == 3.5);
  check_output("3.5");

  assert(dbg(true));
  check_output("true");

  assert(dbg('x') == 'x');
  check_output("x");

  dbg((u128{1} << 64));
  check_output("18446744073709551616");

  dbg(-static_cast<i128>(u128{1} << 64));
  check_output("-18446744073709551616");

  dbg((std::pair<int, std::string>{1, "one"}));
  check_output(R"((1, "one"))");

  dbg(std::make_tuple(1, "two", true));
  check_output(R"((1, "two", true))");

  dbg((Vec<std::string>{"one", "two\n"}));
  check_output(R"(["one", "two\n"])");

  dbg((Vec<Vec<int>>{{1, 2}, {3}}));
  check_output("[[1, 2], [3]]");

  dbg(Vec<int>{});
  check_output("[]");

  dbg((std::set<int>{2, 1}));
  check_output("{1, 2}");

  dbg((std::map<int, std::string>{{1, "one"}, {2, "two"}}));
  check_output(R"({1: "one", 2: "two"})");

  std::cerr.rdbuf(previous);

  oss.str("");
  oss.clear();
  u128 big = u128{1} << 64;
  oss << big;
  assert(oss.str() == "18446744073709551616");

  oss.str("");
  oss.clear();
  oss << u128{0};
  assert(oss.str() == "0");

  oss.str("");
  oss.clear();
  oss << static_cast<i128>(big + 42);
  assert(oss.str() == "18446744073709551658");

  oss.str("");
  oss.clear();
  oss << -static_cast<i128>(big + 99);
  assert(oss.str() == "-18446744073709551715");

  return 0;
}
