#include <boost/range/irange.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/numeric.hpp>
#include <boost/fusion/algorithm/iteration/accumulate.hpp>

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

int findAmicableNumbers(int max) {

    // To filter the list, first get all the primes to num
    const int sum = boost::accumulate(boost::irange(220,max+1)
                                      | boost::adaptors::filtered([&](int p) {
        const uint64_t pDivisorSum = sumOfProperDivisors(p) - p;
        const uint64_t p2DivisorSum = sumOfProperDivisors(pDivisorSum) - pDivisorSum;
        return (p2DivisorSum == p && pDivisorSum != p2DivisorSum); }),0);
    return sum;
}