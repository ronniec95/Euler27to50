#include "stdafx.h"
#include <algorithm>
#include <doctest/doctest.h>
#include <memory>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

typedef std::pair<int, int> weapon_pos;

auto find_adj(const weapon_pos &node, const std::vector<weapon_pos> nodes, const int width,
              const int height) {
    using namespace std;
    const auto x = get<0>(node);
    const auto y = get<1>(node);
    weapon_pos right{-1, -1}, bottom{-1, -1};
    for (const auto &node : nodes) {
        const auto nx = get<0>(node);
        const auto ny = get<1>(node);
        if (nx > x && ny == y) {
            right = node; // copy
            break;
        }
    }

    for (const auto &node : nodes) {
        const auto nx = get<0>(node);
        const auto ny = get<1>(node);
        if (nx == x && ny > y) {
            bottom = node; // copy
            break;
        }
    }
    printf("%d %d   %d %d", get<0>(right), get<1>(right), get<0>(bottom), get<1>(bottom));
}

void load_weapons() {
    using namespace std;
    string     node_map[] = {{"0.0...0"}, {"..0...."}, {"......."}, {"0.0...."}};
    const auto width = node_map->size(), height = sizeof(node_map) / sizeof(node_map[0]);
    vector<pair<int, int>> nodes;
    for (auto j = 0; j < height; j++) {
        auto &row = node_map[j];
        for (auto i = 0; i < width; i++) {
            if (row[i] == '0') nodes.emplace_back(i, j);
        }
    }
    for (const auto &node : nodes) {
        printf("Node %d %d:", get<0>(node), get<1>(node));
        find_adj(node, nodes, width, height);
        printf("\n");
    }
}

#if 0

// dfs search
void find_path(SKNode &current, const int end, std::vector<SKNode> &nodes,
               std::vector<SKNode> &path) {
    if (current.id_ == end) {
        path.emplace_back(current);
        return;
        }
    for (auto child_id : current.children_) {
        auto it = std::find_if(std::begin(nodes), std::end(nodes),
                               [&child_id](auto &node) { return node.id_ == child_id; });
        if (it == nodes.end()) return;
        // Check if this node is already in the path, in which case it's a cycle
        auto cycle = std::find_if(std::begin(path), std::end(path),
                                  [&it](const auto &node) { return it->id_ == node.id_; });
        if (cycle != path.end()) {
            // Cycle detected
            } else
            path.emplace_back(*it);
            find_path(*it, end, nodes, path);
        }
    }

// bfs search for shortest path
auto bfs_search(SKNode &root, const int end, std::vector<SKNode> &nodes) {
    std::queue<SKNode> bfs_queue;
    bfs_queue.push(root);
    while (!bfs_queue.empty()) {
        auto node = bfs_queue.front();
        if (node.id_ == end) {
            bfs_queue.push(node);
            break;
            }
        bfs_queue.pop();
        for (auto &child : node.children_) {
            auto it = std::find_if(std::begin(nodes), std::end(nodes),
                                   [&child](const auto &node) { return node.id_ == child; });
            if (it != nodes.end()) { bfs_queue.push(*it); }
            }
        }
    return bfs_queue;
    }
#endif

struct SKNode {
    int              id_ = -1;
    std::vector<int> children_;

    SKNode(){};
    SKNode(int id, int child) : id_(id) { children_.emplace_back(child); }
    auto add(int id) { children_.emplace_back(id); }
    auto find_child(int id) const {
        auto it = std::find_if(std::begin(children_), std::end(children_),
                               [&id](const auto &node_id) { return node_id == id; });
        return (it == children_.end()) ? -1 : (*it);
    }
};

auto get_child_nodes(const int id, const std::vector<std::shared_ptr<SKNode>> &nodes) {
    if (nodes.empty() || nodes.size() == 1) return nodes;
    std::vector<std::shared_ptr<SKNode>> results;
    const auto                           it =
        std::find_if(std::begin(nodes), std::end(nodes),
                     [&id](const std::shared_ptr<SKNode> &node) { return node->id_ == id; });
    // first add directly refrenced children
    if (it != nodes.end()) {
        results.emplace_back(*it);
        results = std::accumulate(std::begin(nodes), std::end(nodes), results,
                                  [&id](auto &acc, const std::shared_ptr<SKNode> &node) {
                                      const auto it = std::find(std::begin(node->children_),
                                                                std::end(node->children_), id);
                                      if (it != node->children_.end()) { acc.emplace_back(node); }
                                      return acc;
                                  });
    }
    return results;
}

bool is_terminal(const int id, const SKNode &node) {
    if (id == node.id_) return true;
    return (!(std::find(std::begin(node.children_), std::end(node.children_), id) ==
              node.children_.end()));
}

void find_bfs_paths(const int start, const int end,
                    const std::vector<std::shared_ptr<SKNode>> &nodes) {
    std::queue<std::shared_ptr<SKNode>> bq;
    if (nodes.empty()) return;
    bq.push(nodes.front());
    while (!bq.empty()) {
        const auto &node = bq.front();
        printf("%d,", node->id_);
        if (is_terminal(end, *node)) break;
        bq.pop();
        // Any child nodes off this
        auto ref_nodes = get_child_nodes(node->id_, nodes);
        std::for_each(std::begin(ref_nodes), std::end(ref_nodes), [&bq](const auto &node) {
            // Don't duplicate adds to bq
            const auto id = node->id_;
            if (!std::any_of(std::begin(bq._Get_container()), std::end(bq._Get_container()),
                             [&id](const auto &node) { return id == node->id_; }))
                bq.push(node);
        });
    }
}

void sever_link(std::vector<std::shared_ptr<SKNode>> &potential_nodes, const int agent,
                const std::vector<int>& exit_points) {
    if (potential_nodes.empty()) return;
    for (auto exit_point : exit_points) {
        const auto target_node = std::find_if(
            std::begin(potential_nodes), std::end(potential_nodes), [&](std::shared_ptr<SKNode> node) {
            if (node->id_ == exit_point) return true;
            auto children = node->children_;
            return !(std::find(std::begin(children), std::end(children), exit_point) ==
                     children.end());
            });
        if (target_node != potential_nodes.end()) {
            auto       children = (*target_node)->children_;
            const auto it = std::find_if(std::begin(children), std::end(children),
                                         [&](const int id) { return id == agent || id == exit_point; });
            if (it != children.end()) {
                printf("%d %d\n", exit_point, agent);
                children.erase(it);
                if (children.empty()) potential_nodes.erase(target_node);
                return;
                }
            }
        }
    // Delete the first node's first child
    const auto random_node = potential_nodes.begin();
    printf("%d %d\n", (*random_node)->id_, (*random_node)->children_.front());
    (*random_node)->children_.erase((*random_node)->children_.begin());
}
// find shortest path to exit
void skynet_revolution() {
    using namespace std;
    /*const int node_map[][2] = {{11, 6}, {0, 9},  {1, 2}, {0, 1}, {10, 1}, {11, 5}, {2, 3},  {4,
       5},
                               {8, 9},  {6, 7},  {7, 8}, {0, 6}, {3, 4},  {0, 2},  {11, 7}, {0, 8},
                               {0, 4},  {9, 10}, {0, 5}, {0, 7}, {0, 3},  {0, 10}, {5, 6}};
    */
    // const int node_map[][2] = {{1, 2}, {1, 0}};
    // const int node_map[][2] = {{1, 3}, {2, 3}, {0, 1}, {0, 2}};
    const int node_map[][2] = {
        {28, 36}, {0, 2},   {3, 34},  {29, 21}, {37, 35}, {28, 32}, {0, 10},  {37, 2},  {4, 5},
        {13, 14}, {34, 35}, {27, 19}, {28, 34}, {30, 31}, {18, 26}, {0, 9},   {7, 8},   {18, 24},
        {18, 23}, {0, 5},   {16, 17}, {29, 30}, {10, 11}, {0, 12},  {15, 16}, {0, 11},  {0, 17},
        {18, 22}, {23, 24}, {0, 7},   {35, 23}, {22, 23}, {1, 2},   {0, 13},  {18, 27}, {25, 26},
        {32, 33}, {28, 31}, {24, 25}, {28, 35}, {21, 22}, {4, 33},  {28, 29}, {36, 22}, {18, 25},
        {37, 23}, {18, 21}, {5, 6},   {19, 20}, {0, 14},  {35, 36}, {9, 10},  {0, 6},   {20, 21},
        {0, 3},   {33, 34}, {14, 15}, {28, 33}, {11, 12}, {12, 13}, {17, 1},  {18, 19}, {36, 29},
        {0, 4},   {0, 15},  {0, 1},   {18, 20}, {2, 3},   {0, 16},  {8, 9},   {0, 8},   {26, 27},
        {28, 30}, {3, 4},   {31, 32}, {6, 7},   {37, 1},  {37, 24}, {35, 2}};
    // Adjacency list for nodes
    vector<std::shared_ptr<SKNode>> nodes;
    for (auto n : node_map) {
        auto id = n[0];
        auto it = find_if(begin(nodes), end(nodes), [&id](auto &node) { return node->id_ == id; });
        if (it == nodes.end()) {
            nodes.emplace_back(std::make_shared<SKNode>(id, n[1]));
        } else
            (*it)->children_.emplace_back(n[1]);
    }
    auto EI = { 0, 28, 18 };
    for (auto SI : { 37,2,35,28 }) {
        auto potential_exits = get_child_nodes(SI, nodes);
        sever_link(potential_exits, SI, EI);
    }
}
// Find nearest neighbour
// 0.0...0
// ..0....
// .......
// 0.0....
// NN is to right and below only
TEST_CASE("Loading weapons") { load_weapons(); }
TEST_CASE("Skynet rev") { skynet_revolution(); }