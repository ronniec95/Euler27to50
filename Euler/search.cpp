#include <array>
#include <cstdio>
#include <functional>
#include <numeric>
#include <queue>
#include <vector>

void dfs() {}

void algorithmic_crush() {
    int N, M;
    scanf("%d %d", &N, &M);

    std::vector<long long> arr(N + 1, 0);
    // Prefix sum
    for (auto count = 0; count < M; count++) {
        int a, b, k;
        scanf("%d %d %d", &a, &b, &k);
        arr[a] += k;
        if (b < N) arr[b + 1] -= k;
    }
    auto max = arr[1], sum = arr[1];
    for (int i = 2; i < N + 1; i++) {
        sum += arr[i];
        if (sum > max) max = sum;
    }
    printf("%lld", max);
}

struct node {
    int   data;
    node *left;
    node *right;
};

node *add_left(node *in, int val) {
    in->left = new node({val, nullptr, nullptr});
    return in->left;
}
node *add_right(node *in, int val) {
    in->right = new node({val, nullptr, nullptr});
    return in->right;
}

int max_height = 0;

auto tree_height(node *root, const int height) -> int {
    if (root == nullptr) {
        if (height > max_height) max_height = height;
        return height;
    }
    auto l = root->left;
    auto r = root->right;
    tree_height(l, height + 1);
    //	printf("%d ", root->data);
    tree_height(r, height + 1);
    return max_height;
}

void left_view(node *root) {
    if (root == nullptr) { return; }
    auto l = root->left;
    left_view(l);
    printf("%d ", root->data);
}

void right_view(node *root) {
    if (root == nullptr) { return; }
    auto r = root->right;
    printf("%d ", root->data);
    right_view(r);
}

void bfs(node *root) {
    std::queue<node *> q;
    q.push(root);
    while (!q.empty()) {
        auto n = q.front();
        q.pop();
        printf("%d ", n->data);

        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
}

void preorder() {
    node *root = new node({3, nullptr, nullptr});
    auto  l1   = add_left(root, 2);
    auto  l2   = add_left(l1, 1);

    auto r1   = add_right(root, 5);
    auto r1l1 = add_left(r1, 4);
    auto r2   = add_right(r1, 6);
    auto r3   = add_right(r2, 7);
    left_view(root);
    right_view(root->right);
}

// DFS delete tree
void delete_node(node *root) {
    if (root == nullptr) return;
    auto l = root->left;
    auto r = root->right;
    delete_node(l);
    delete_node(r);
    delete root;
}

node *find_dfs(node *node, int v) {
    if (node == nullptr) return node;
    if (node->data == v) return node;
    auto l1 = find_dfs(node->left, v);
    auto l2 = find_dfs(node->right, v);
    if (l1) return l1;
    if (l2) return l2;
    return nullptr;
}

node *find(node *root, int v) { return find_dfs(root, v); }

node *setup() {
    node *root = new node({3, nullptr, nullptr});
    auto  l1   = add_left(root, 2);
    auto  l2   = add_left(l1, 1);

    auto r1   = add_right(root, 5);
    auto r1l1 = add_left(r1, 4);
    auto r2   = add_right(r1, 6);
    auto r3   = add_right(r2, 7);

    return root;
}
