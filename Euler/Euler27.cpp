#include "Euler.h"
#include "prime.h"
#include <algorithm>

auto quadratic_primes() -> int {
	// n2 + an + b where | a | <1000 and | b | ≤1000
	
	// If n = 0, then b must be a prime and between 1 and 1000
	// So that reduces that search space.

	// If n = 1, then 1*1 + a*1 + b must be prime. Since b is an odd number and prime,
	// a must be odd to produce a prime number again reducing the search space
	// if a < 0 (neg), then b > -(n2 + an)
	// We are also told n2 + n - 41 returns 40 primes, thus any value of a,b must satisfy b > (-40^2+40a)

	auto primes = load_primes(750000);
	// The STD::find is slow so make into expanded vector
	auto primev = std::vector<uint64_t>(primes.back(),0);
	std::for_each(std::begin(primes), std::end(primes), [&primev](auto n) {
		primev[n-1] = 1;
	});


	// B is prime so reduce search space for b to primes below 1001
	auto b_primes = std::vector<uint64_t>();
	b_primes.reserve(500);
	std::for_each(std::begin(primes), std::end(primes), [&b_primes](auto n) {
		if (n < 1001)
			b_primes.emplace_back(n);
	});
	primes.clear();
	primes.shrink_to_fit();

	// Try to find an interesting combination of a,b
	auto running_count = 0 , a_max = 0, b_max = 0;
	for (auto a = -1000; a < 1001; a++) {
		for (auto bi = 1UL; bi < b_primes.size(); bi++) {
			auto c = 0, n = 0;
			const auto b = b_primes[bi];
			int64_t test_primality = n*n + a*n + b;


			while (test_primality > 0 && primev[test_primality-1] == 1) {
				c++, n++;
				test_primality = n*n + a*n + b;
			}
			if (c > running_count) {
				running_count = c;
				a_max = a;
				b_max = b;
				TRACE(true, "\nFound a possible candidate %d primes with %ld %ld\n", running_count, a_max, b_max);
			}
		}
	}
	return a_max  * b_max;
}
