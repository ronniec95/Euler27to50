#include <stdint.h>
#include <math.h>

int fibSize(int x) {
	// F(n) = phi^n / sqrt(5)
	// 10^999 - thousand digit
	// x = phi^n / sqrt(5)
	// Log(10)
	//log(x) = n log phi - 1/2 log 5
	// log(x) + 1/2 log 5 = n log phi
	// (log(x) + 1/2 log5) / log(phi) = n
	const double phi = (1.0 + sqrtf(5.0)) / 2.0;
	const double a = x-1;
	const double b = 0.5 * log10f(5.0);
	const double c = log10f(phi);
	const double n = (a+b) / c;
	return n;
}
