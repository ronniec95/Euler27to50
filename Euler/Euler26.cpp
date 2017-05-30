#include "Euler26.h"

int findLongestFraction(int z) {
	// n^p = n mod p
	// Find:-
	// 1/d where d < 1000
	// with longest recurring cycle

	// If p is prime, n^ p-1 = 1 mod p
	// 10^997-1 = 1
    int i, n, len, maxlen = 0, ans;
    int j = 1, k;
 
    for(n = 997; n > 1; n -= 2){
        j = 1;
        for(i = 0; i < n; i++)
            j = (j*10) % n;
        k = j;
        len = 0;
        do{
            j = (j*10) % n;
            len++;
        }while(j != k);
        if(len > maxlen){
            ans = n;
            maxlen = len;
        }
    }
	return ans;
}
