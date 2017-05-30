#include "stdafx.h"
#include "prime.h"
#include <bitset>
#include <memory>
#include <thread>
#include <array>
#include <vector>

void calculate_primes() {
	// Calculate first 100,000 primes using sieve of erastosthene
	// Since we know primes cant be divisible by 2, each bit is an odd number, 1,3,5,7,9 etc..
	const auto SIEVE_SIZE = 2000000;
	auto sieve = std::make_unique<std::bitset<SIEVE_SIZE>>();
	sieve->flip();

	// for each value 2,3,5,7, mark as false
	std::vector<std::thread> sieve_tasks;
	for (auto n : { 2,3,5,7 }) {
		for (auto i = (n*n); i <= SIEVE_SIZE; i += n) {
			sieve->operator[](i - 1) = false;
		}
	}
	for (auto& thr : sieve_tasks)
		thr.join();
	sieve_tasks.clear();


	// Whatever is left, try trial division, which we only have to do to sqrt(n)
	for (auto pos = 0; pos < SIEVE_SIZE; pos++) {
		if (sieve->operator[](pos) == true) {
			const auto max_try = sqrt(pos + 1);
			for (auto trial = 11; trial < max_try; trial += 2) {
				if ((pos + 1) % trial == 0) {
					sieve->operator[](pos) = 0;
					break;
				}

			}
		}
	}
	for (auto& thr : sieve_tasks)
		thr.join();

	FILE *fp;
	fopen_s(&fp, "primes.bin", "wb");
	for (uint64_t i = 0; i < SIEVE_SIZE; i++) {
		if (sieve->operator[](i) == true) {
			auto n = i + 1;
			auto size = fwrite(&n, sizeof(uint64_t), 1 , fp);
		}
	}
	fclose(fp);

}


std::vector<uint64_t> load_primes(uint64_t upto) {
	std::vector<uint64_t> primes;
	primes.reserve(upto);
	FILE *fp;
	fopen_s(&fp, "primes.bin", "rb");
	std::array<uint64_t, 100 * 1024> buf;
	while (auto count = fread(buf.data(), sizeof(uint64_t), 100 * 1024, fp)) {
		for (int n = 0; n < count; n++) {
			primes.emplace_back(buf[n]);
		}
		if (primes.back() > upto)
			break;
	}
	fclose(fp);
	return primes;
}