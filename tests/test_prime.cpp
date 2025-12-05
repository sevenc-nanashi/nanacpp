#include "features/prime.hpp"

#include <cassert>
#include <vector>

int main() {
  static_assert(!std::is_copy_constructible_v<PrimeSieve>);
  static_assert(!std::is_copy_assignable_v<PrimeSieve>);

  PrimeSieve sieve(100);

  assert(!sieve.is_prime(0));
  assert(!sieve.is_prime(1));
  assert(sieve.is_prime(2));
  assert(!sieve.is_prime(75));
  assert(sieve.is_prime(97));

  const auto &primes = sieve.primes();
  std::vector<int> expected_primes{2,  3,  5,  7,  11, 13, 17, 19, 23,
                                   29, 31, 37, 41, 43, 47, 53, 59, 61,
                                   67, 71, 73, 79, 83, 89, 97};
  assert(primes == expected_primes);

  assert(sieve.least_factor(1) == 1);
  assert(sieve.least_factor(60) == 2);
  assert(sieve.least_factor(97) == 97);

  auto bounded = sieve.factorize_bounded(60);
  std::vector<std::pair<int, int>> expected_bounded{{2, 2}, {3, 1}, {5, 1}};
  assert(bounded == expected_bounded);

  auto bounded_prime = sieve.factorize_bounded(97);
  std::vector<std::pair<int, int>> expected_single{{97, 1}};
  assert(bounded_prime == expected_single);

  auto general = sieve.factorize(9801);
  std::vector<std::pair<long long, int>> expected_general{{3, 4}, {11, 2}};
  assert(general == expected_general);

  auto one = sieve.factorize(1);
  assert(one.empty());

  return 0;
}
