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

struct Node {
    Node(char v) : v_(v) {}
    void                     add_child(shared_ptr<Node> n) { children.emplace_back(n); }
    char                     v_ = 0;
    vector<shared_ptr<Node>> children;
};

void add_child(shared_ptr<Node> root, int n, int depth, const map<char, vector<char>> &combo) {
    if (depth == n) return;
    auto ch = root->v_;
    auto it = combo.find(ch);
    for (auto ch : it->second) {
        printf("Adding to %c to %c\n", ch, root->v_);
        root->add_child(make_shared<Node>(ch));
    }
    ++depth;
    for (auto &child : root->children) { add_child(child, n, depth, combo); }
}

int count_leaf(shared_ptr<Node> root) {
    if (root->children.size() == 0) return 0;
    int sum = 0;
    for (auto &child : root->children) sum += count_leaf(child);
    return sum > 0 ? sum : root->children.size();
}
void password_combination() {
    // a->i
    // i->ae
    // o->aeiu
    // u->a

    int n = 3;

    map<char, vector<char>> combo;
    combo.insert(make_pair('a', vector<char>{'i', 'e'}));
    combo.insert(make_pair('e', vector<char>{'i', 'o'}));
    combo.insert(make_pair('i', vector<char>{'a', 'e', 'o'}));
    combo.insert(make_pair('u', vector<char>{'a', 'e', 'i', 'o'}));
    combo.insert(make_pair('o', vector<char>{'i', 'u', 'o'}));

    // Create a N depth tree and count leaves
    // Count all children until n = 3;
    auto root  = make_shared<Node>(0);
    int  depth = 0;
    for (auto &c : combo) { root->add_child(make_shared<Node>(c.first)); }
    for (auto child : root->children) { add_child(child, n, depth, combo); }
    printf("%d\n", count_leaf(root));
}
TEST_CASE("password_combination") { password_combination(); }
