
#include <set>
#include <vector>
#include <boost\multiprecision\cpp_int.hpp>
#include <boost/math/special_functions/pow.hpp> 

int distinct_powers() {
	namespace mp = boost::multiprecision;
	std::set<mp::cpp_int> squares;
	for (mp::cpp_int a = 2; a <= 100; a++) {
		for (auto b = 2; b <= 100; b++) {
			squares.insert(mp::pow(a, b));
		}
	}

	return squares.size();
}