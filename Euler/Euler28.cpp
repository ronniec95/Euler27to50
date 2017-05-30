#include <cstdint>

uint64_t spiral_sum(const int i) {
	// This is a sum that can be done on paper
	// Looking at a spiral of numbers we can see that the top right corner
	// for f(1) = (2n+1)^2 = 9.Then the other corners are (2n+1)^-2n, (2n+1)^-4n, (2n+1)^-6n, 
	// so total 4*(2n+1)^2 - 12n + f(n-1)
	// So constexpr this as it's recursive and we get a compile time calculation
	return i == 0 ? 1 : (4 * (2 * i + 1) * (2 * i + 1)) - (12 * i) + spiral_sum(i - 1);
	uint64_t sum = 0;
	for (int n = 1; n <= i; n++) {
		sum += (4 * (2 * n + 1) * (2 * n + 1)) - (12 * n);
	}
	return sum+1;
}