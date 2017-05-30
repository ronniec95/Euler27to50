#pragma once
uint64_t spiral_sum(const int i);

constexpr uint64_t spiral_sum2(const int i) {
	return i == 0 ? 1 : (4 * (2 * i + 1) * (2 * i + 1)) - (12 * i) + spiral_sum2(i - 1);
}