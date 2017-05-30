#include "Euler23.h"
#include <stdint.h>
#include <vector>
#include <bitset>

using namespace std;

static uint64_t sumOfProperDivisors(const uint64_t num) {
    uint64_t totalSum = 1;
    if(num == 1)
        return 0;
    int factor = 2;
    // Check for a factor up to sqrt(num)
    uint64_t divided = num;
    while(factor * factor <= divided) {
        if(divided % factor ==0) {
            int sum = 1;
            while(divided % factor == 0) {
                sum *= factor;
                divided = divided / factor;
            }
            totalSum *= ((sum * factor) - 1) / (factor - 1);
        }
        factor++;
    }
    if(divided != 1) {
        totalSum *= 1+divided;
    }
    return totalSum;
}

uint64_t non_abundant_sum(){
	const int max = 28123;
	vector<int> abundant_numbers;
	for(int i = 12; i < max ; i++) {
		const int sumDivisors = sumOfProperDivisors(i) - i;
		if(sumDivisors > i)
			abundant_numbers.push_back(i);
	}
	bool bits[max] = {false};
	uint64_t sum = 0;
	for(int i = 0; i < abundant_numbers.size();++i) {
		for(int j = 0 ; j <= i ;++j) {
			const int idx = abundant_numbers[i] + abundant_numbers[j];
			if(idx >= max)
				continue;
			bits[idx] = true;
		}
	}
	for(int i = 1; i < max;i++)
		if(bits[i] == false)
			sum+=i;
	return sum;
}