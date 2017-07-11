#include "stdafx.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdio>
#include <doctest/doctest.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void dynamic_array() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> seqList(n, vector<int>());
    int                 lastAnswer = 0;
    for (int i = 0; i < q; i++) {
        int qtype, x, y;
        cin >> qtype >> x >> y;
        const auto idx = (x ^ lastAnswer) % n;
        switch (qtype) {
        case 1: {
            seqList[idx].emplace_back(y);
        } break;
        case 2: {
            lastAnswer = seqList[idx][y % (seqList[idx].size())];
            printf("%d\n", lastAnswer);
        } break;
        }
    }
}

TEST_CASE("Dynamic Array") { dynamic_array(); }

/*
Tuesday:idiocracy
Wednesday:28 days later/28 weeks later
Thursday: bloodsucking bosses
Sunday: breakdown
Monday: xmen apocalypse
Tuesday: captain america : civil war
Wednesday:minions
Thursday:jack reacher: never go back
Friday:Pan
*/
