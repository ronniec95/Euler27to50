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

template <typename Out> void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) { *(result++) = item; }
}

template <typename Out> auto split(const std::string &s, char delim) -> Out {
    Out result;
    for (auto i = 0UL, start = 0UL; i < s.size(); i++) {
        if (s[i] == delim) {
            // Using emplace to directly construct the string 'in place', avoiding a temporary
            result.emplace_back(begin(s) + start, begin(s) + i);
            start = i + 1;
        }
        if (i == s.size() - 1) { result.emplace_back(begin(s) + start, end(s)); }
    }
    return result;
}

struct Node {
    Node(int v) : v_(v) {}
    Node *left_  = nullptr;
    Node *right_ = nullptr;
    int   v_;
    Node *addl(int v) {
        left_ = new Node(v);
        return left_;
    }
    Node *addr(int v) {
        right_ = new Node(v);
        return right_;
    }

    Node *find(int v) { return find_dfs(this, v); }

    Node *find_dfs(Node *node, int v) {
        if (node == nullptr) return node;
        if (node->v_ == v) return node;
        auto *l1 = find_dfs(node->left_, v);
        if (l1) return l1;
        auto *l2 = find_dfs(node->right_, v);
        if (l2) return l2;
        return nullptr;
    }
};

void amadeus() {
    printf("Test\n");
    Node *root = new Node(9);
    auto  l1   = root->addl(10);
    auto  r1   = root->addr(13);
    auto  l2   = l1->addl(19);
    l1->addr(21);
    r1->addr(14);
    r1->addl(15);
    auto res = root->find(15);
    if (res) printf("%d", res->v_);
}

TEST_CASE("Amadeus") { amadeus(); }
