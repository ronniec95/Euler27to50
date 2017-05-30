#include "Euler24.h"
#include <boost/smart_ptr.hpp>

uint64_t factorial(int n) {
	uint64_t factorial = n;
	for(int i = n - 1 ; i >= 2; --i) {
		factorial *= i;
	}
	return factorial;
}


uint64_t nthPermutation(int size,const int n) {
	// Pre calculate factorials
	std::vector<int> indices;
	boost::scoped_array<uint64_t> fact(new uint64_t[size]);
	for(int i = 0;i < size;i++) {
		indices.push_back(i);
		fact[i] = factorial(i+1);
	}
	uint64_t remainder = n-1;
	for (int i = 1;i < size;i++) {
		const uint64_t factIdx = (fact[size-(i+1)]);
		int j = remainder / factIdx;
		remainder = remainder %  factIdx;
		printf("%d",indices[j]);
		indices.erase(indices.begin()+j);
		if(remainder == 0)
			break;
	}
	return 0;
}

