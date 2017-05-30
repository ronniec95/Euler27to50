#define BOOST_TEST_MODULE TestSuite 
#include <boost\test\unit_test.hpp>
#define __SSE4_2__
#include "Euler.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <boost/assign.hpp>
#include <boost/smart_ptr.hpp>
using namespace boost::assign;

BOOST_AUTO_TEST_CASE(Prime) {
	clock_t start = clock();
	calculate_primes();
	auto primes = load_primes(1000000);
	clock_t end = clock();
	printf("Time %2.4f", ((double)(end - start) / CLOCKS_PER_SEC));
}


BOOST_AUTO_TEST_CASE(Euler22) {
	clock_t start = clock();
	std::cout << nameScores() << std::endl;
	clock_t end = clock();
	printf("Time %2.4f", ((double)(end - start) / CLOCKS_PER_SEC));
}

BOOST_AUTO_TEST_CASE(Euler23) {
	clock_t start =clock();
	std::cout << non_abundant_sum() << std::endl;
	clock_t end =clock();
	printf("Time %2.4f", ((double) (end-start)/CLOCKS_PER_SEC));
}


BOOST_AUTO_TEST_CASE(Euler24) {
	clock_t start = clock();
	std::cout << nthPermutation(10,1000000) << std::endl;
	clock_t end = clock();
	printf("Time %2.4f", ((double) (end-start)/CLOCKS_PER_SEC));
}

BOOST_AUTO_TEST_CASE(Euler25) {
	clock_t start = clock();
	std::cout << fibSize(1000) << std::endl;
	clock_t end = clock();
	printf("Time %2.4f", ((double) (end-start)/CLOCKS_PER_SEC));
}

BOOST_AUTO_TEST_CASE(Euler26) {
	clock_t start = clock();
	std::cout << findLongestFraction(1000) << std::endl;
	clock_t end = clock();
	printf("Time %2.4f", ((double) (end-start)/CLOCKS_PER_SEC));
}

BOOST_AUTO_TEST_CASE(Euler27) {
	clock_t start = clock();
	TRACE(true, "%d", quadratic_primes());
	clock_t end = clock();
	printf("Time %2.4f", ((double)(end - start) / CLOCKS_PER_SEC));
}


BOOST_AUTO_TEST_CASE(Euler28) {
	clock_t start = clock();
	// This compiles to a constant due to constexpr
	std::cout << spiral_sum2(500) << std::endl;
	clock_t end = clock();
	printf("Time %2.4f", ((double)(end - start) / CLOCKS_PER_SEC));
}

BOOST_AUTO_TEST_CASE(Euler29) {
	clock_t start = clock();
	std::cout << distinct_powers() << std::endl;
	clock_t end = clock();
	printf("Time %2.4f", ((double)(end - start) / CLOCKS_PER_SEC));
}

 int getDiff1(std::vector<std::vector<int>>& nodeL,int indx1, int indx2) {
    int result = 0;
    int pplus, pminus, tmp;

    for (int k = 0; k < 128; k += 2) {
        pplus = nodeL[indx2][k] - nodeL[indx1][k];
        pminus = nodeL[indx1][k + 1] - nodeL[indx2][k + 1];

        tmp = max(pplus, pminus);
        if (tmp > result) {
            result = tmp;
        }
		//printf("%d,%d=%d\n",pplus,pminus,tmp);
    }
//	printf("\n");
    return result;
}
/************************************************
 * Compare Node
 ************************************************/
BOOST_AUTO_TEST_CASE(CompareNode) {
	std::vector<std::vector<int>> vec;
	
	for(int i = 0; i < 128;i++) {
		std::vector<int> vec2;
		for(int j = 0; j < 128; j++) {
			vec2.push_back(rand()%100);
		}
		vec.push_back(vec2);
	}
	clock_t start = clock();

	int result = true;
	for(int i = 0 ;i < 100;i++) {
		for(int j = 0 ; j <64;j++) {
			result = getDiff1(vec,j,j+1);
		}
	}
	printf("%d",result);
	clock_t end = clock();
	printf("Time for Compare Node %2.4f", ((double) (end-start)/CLOCKS_PER_SEC));
}

/************************************************
 * Vector
 ************************************************/
BOOST_AUTO_TEST_CASE(vec) {
	clock_t start = clock();
	std::vector<int> x;
	if(x.begin() == x.end())
		printf("OK");
	clock_t end = clock();
	printf("Time for Vector %2.4f", ((double) (end-start)/CLOCKS_PER_SEC));
}


