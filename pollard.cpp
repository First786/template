#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdint>

using namespace std;

using u64 = uint64_t;
using u128 = __uint128_t; //

// Быстрое умножение по модулю без переполнения
u64 mulmod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

// Быстрое возведение в степень по модулю
u64 powmod(u64 base, u64 exp, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// GCD (беззнаковый)
u64 gcd(u64 a, u64 b) {
    while (b != 0) {
        u64 tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// Miller-Rabin для 64-битных чисел (гарантированно корректный)
bool is_prime(u64 n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;

    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    // Детерминированные базы для uint64_t
    for (u64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= n) break;
        u64 x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int r = 1; r < s; ++r) {
            x = mulmod(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

// Алгоритм Полларда Ро
u64 pollard_rho(u64 n) {
    if (n % 2 == 0) return 2;
    if (is_prime(n)) return n;

    std::mt19937_64 rng(random_device{}());
    std::uniform_int_distribution<u64> dist(1, n - 1);

    while (true) {
        u64 c = dist(rng);
        u64 x = dist(rng);
        u64 y = x;
        u64 d = 1;

        auto f = [&](u64 v) { return (mulmod(v, v, n) + c) % n; };

        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = gcd(x > y ? x - y : y - x, n);
        }

        if (d != n) return d; // нашли делитель
    }
}

// Факторизация числа на простые множители
void factor(u64 n, vector<u64>& factors) {
    if (n <= 1) return;
    if (is_prime(n)) {
        factors.push_back(n);
        return;
    }
    u64 d = pollard_rho(n);
    factor(d, factors);
    factor(n / d, factors);
}

// Удобный интерфейс
vector<u64> factorize(u64 n) {
    vector<u64> res;
    factor(n, res);
    sort(res.begin(), res.end());
    return res;
}
