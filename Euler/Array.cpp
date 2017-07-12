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

class heap {
  public:
};
class treap {
  public:
};

void test_heap() {
    // add
    // remove
    // top
    // front
    // begin
    // end
    // size
    // empty
    // max
    // min
    // pop_front
    // pop_back
    // erase
}

void test_treap() {}

struct NodeD {
    int           data;
    struct NodeD *next = nullptr;
    NodeD(const int n) : data(n) {}
    NodeD *add(const int n) {
        next = new NodeD(n);
        return next;
    }
};

void remove_duplicates() {
    NodeD *head = new NodeD(1);
    head->add(2)->add(2)->add(3)->add(3)->add(3)->add(4);

    auto *current = head;
    while (nullptr != current) {
        while (nullptr != current->next && current->data == current->next->data) {
            current->next = current->next->next;
        }
        current = current->next;
    }

    // Print
    current = head;
    while (current != nullptr) {
        printf("%d,", current->data);
        current = current->next;
    }
}

bool cycle_detect() {
    NodeD *head = new NodeD(0);
    NodeD *five = head->add(1)->add(2)->add(3)->add(4)->add(5);
    // five->next  = head->next->next; // points to 2;

    // 2 pointers, fast,slow, if fast == slow then cycle
    if (head == nullptr) return false;
    auto *fast = head, *slow = head;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) return true;
    }
    return false;
}

bool merge_points() {
    NodeD *nodeA       = new NodeD(0);
    NodeD *merge_point = nodeA->add(1)->add(2)->add(3)->add(4)->add(5);
    merge_point->add(6);
    NodeD *nodeB = (new NodeD(100))->add(101)->add(102)->add(103)->add(104);
    nodeB->next  = merge_point;

    // We know nodeA/nodeB is not null
    auto *fast = nodeA, *slow = nodeB;
    while (fast != nullptr) {
        if (fast == slow) return true;
        if (fast->next == nullptr) fast->next = nodeB;
        if (slow->next == nullptr) slow->next == nodeA;

        fast = fast->next->next;
        slow = slow->next;
    }
    return false;
}

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

// TEST_CASE("Dynamic Array") { dynamic_array(); }
TEST_CASE("Remove duplicates") { remove_duplicates(); }
TEST_CASE("Detect_cycles") { cycle_detect(); }
TEST_CASE("Merge_points") { merge_points(); }

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
