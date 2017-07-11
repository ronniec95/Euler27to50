#include "stdafx.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdio>
#include <doctest/doctest.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
double linear_interp(int q, vector<int> quantity, vector<double> prices) {
    if (quantity.empty()) return 0.0;
    auto       it     = lower_bound(begin(quantity), end(quantity), q);
    const auto it_top = upper_bound(begin(quantity), end(quantity), q);
    double     q0, q1, p0, p1;
    if (it == quantity.end()) {
        // We know that the value is above the highest value in quantity
        // In which case take last number, find unit quantity and extrapolate
        p1 = prices[prices.size() - 1];
        p0 = prices[prices.size() - 2];
        q0 = quantity[quantity.size() - 2];
        q1 = quantity[quantity.size() - 1];
    } else if (it == quantity.begin()) {
        p1 = prices[0];
        p0 = prices[1];
        q0 = quantity[0];
        q1 = quantity[1];
    } else if (*it == q) { // exact match, as lower bound may have been below quantity
        const auto pos = distance(begin(quantity), it);
        return prices[pos];
    } else if (it_top == quantity.end()) { // no value which means we are at the bottom of the range
        p1 = prices[1];
        p0 = prices[0];
        q0 = quantity[0];
        q1 = quantity[1];
    }
    // If we get this far then we must be inbetween values
    else if (it == it_top) {
        it--;
        const auto pos_low  = distance(begin(quantity), it);
        const auto pos_high = distance(begin(quantity), it_top);
        p0                  = prices[pos_low];
        p1                  = prices[pos_high];
        q1                  = quantity[pos_high];
        q0                  = quantity[pos_low];
    }
    // Unit price
    const auto interp_q = static_cast<float>(q - q0) / static_cast<float>(q1 - q0);
    const auto result   = p0 + interp_q * (p1 - p0);
    return result;
}

TEST_CASE("linear_interp") {

    int            q = 20;
    vector<int>    quantity{5, 15, 22, 35, 50, 90};
    vector<double> prices{2.35, 2.20, 2.10, 1.95, 1.50, 1.40};
    SUBCASE("Match") { linear_interp(35, quantity, prices); }
    SUBCASE("between 2 prices") { linear_interp(65, quantity, prices); }
    SUBCASE("above top price") { linear_interp(120, quantity, prices); }
    SUBCASE("below bottomprice") { linear_interp(1, quantity, prices); }
}