#pragma once

#include "features/core.hpp"

/// エラトステネスの篩を用いた素数判定・素因数分解ユーティリティ。
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
  /// `n` 以下の整数を対象に篩を構築する。
  explicit PrimeSieve(int n)
      : limit(n), primes_vec(), least_prime(n + 1, 0) {
    assert(limit >= 0);
    build();
  }

  PrimeSieve(const PrimeSieve &) = delete;
  PrimeSieve &operator=(const PrimeSieve &) = delete;
  PrimeSieve(PrimeSieve &&) = default;
  PrimeSieve &operator=(PrimeSieve &&) = default;

  /// 篩の最大値（構築時の `n`）を返す。
  int max_n() const { return limit; }

  /// `n` 以下の素数リストを返す。
  const std::vector<int> &primes() const { return primes_vec; }

  /// `n` が素数か判定する。
  bool is_prime(int n) const {
    assert(0 <= n && n <= limit);
    return n >= 2 && least_prime[n] == n;
  }

  /// `n` の最小素因数を返す。
  int least_factor(int n) const {
    assert(1 <= n && n <= limit);
    return least_prime[n];
  }

  /// `n`（`n <= limit`）を素因数分解し、素因数と指数の組を返す。
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

  /// `n` を素因数分解する（`n <= limit^2` が前提）。
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
