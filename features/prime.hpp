#pragma once

#include "features/core.hpp"

class PrimeSieve {
private:
  int limit;
  std::vector<int> primes_vec;
  std::vector<int> least_prime;

  void build() {
    if (limit >= 0)
      least_prime[0] = 0;
    if (limit >= 1)
      least_prime[1] = 1;

    for (int i = 2; i <= limit; ++i) {
      if (least_prime[i] == 0) {
        least_prime[i] = i;
        primes_vec.push_back(i);
      }
      for (int p : primes_vec) {
        if (p > least_prime[i])
          break;
        ll mul = 1LL * i * p;
        if (mul > limit)
          break;
        least_prime[mul] = p;
      }
    }
  }

public:
  explicit PrimeSieve(int n)
      : limit(n), primes_vec(), least_prime(n + 1, 0) {
    assert(limit >= 0);
    build();
  }

  PrimeSieve(const PrimeSieve &) = delete;
  PrimeSieve &operator=(const PrimeSieve &) = delete;
  PrimeSieve(PrimeSieve &&) = default;
  PrimeSieve &operator=(PrimeSieve &&) = default;

  int max_n() const { return limit; }

  const std::vector<int> &primes() const { return primes_vec; }

  bool is_prime(int n) const {
    assert(0 <= n && n <= limit);
    return n >= 2 && least_prime[n] == n;
  }

  int least_factor(int n) const {
    assert(1 <= n && n <= limit);
    return least_prime[n];
  }

  std::vector<std::pair<int, int>> factorize_bounded(int n) const {
    assert(1 <= n && n <= limit);
    std::vector<std::pair<int, int>> factors;
    while (n > 1) {
      int p = least_prime[n];
      int cnt = 0;
      while (n % p == 0) {
        n /= p;
        ++cnt;
      }
      factors.push_back({p, cnt});
    }
    return factors;
  }

  /// n は limit^2 以下であること（sqrt(n) までの素数を持っている前提）
  std::vector<std::pair<ll, int>> factorize(ll n) const {
    assert(n >= 1);
    assert(1LL * limit * limit >= n);
    std::vector<std::pair<ll, int>> factors;
    ll cur = n;
    for (int p : primes_vec) {
      if (1LL * p * p > cur)
        break;
      if (cur % p != 0)
        continue;
      int cnt = 0;
      while (cur % p == 0) {
        cur /= p;
        ++cnt;
      }
      factors.push_back({p, cnt});
    }
    if (cur > 1) {
      factors.push_back({cur, 1});
    }
    return factors;
  }
};
