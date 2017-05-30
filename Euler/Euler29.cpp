
#include <set>
#include <vector>

int distinct_powers() {
	std::set<uint64_t> squares;

	int n = 0;
	for (auto a = 2UL; a <= 100; a++) {
		for (auto b = 2UL; b <= 100; b++) {
			auto results = static_cast<uint64_t>(log);
			squares.insert(results);
			printf("%llu\n", results);
		}
	}

	return squares.size();
}