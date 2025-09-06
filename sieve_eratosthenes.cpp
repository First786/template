#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------------------------

std::vector<int> eratosthenesSieve(int n) {
    std::vector<bool> is_prime(n + 1, true);
    std::vector<int> primes;

    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p <= n; ++p) {
        if (is_prime[p]) {
            for (int multiple = p * p; multiple <= n; multiple += p) {
                is_prime[multiple] = false;
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (is_prime[i])
            primes.push_back(i);
    }

    return primes;
}