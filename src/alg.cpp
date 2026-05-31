// Copyright 2022 NNTU-CS
#include <algorithm>
#include "tree.h"
PMTree::PMTree(const std::vector<char>& src) : base(src) {
    top = new Node(0);
    std::vector<char> sorted = src;
    std::sort(sorted.begin(), sorted.end());
    buildLevel(top, sorted);
}
PMTree::~PMTree() {
    destroyTree(top);
}
void PMTree::buildLevel(Node* parent, std::vector<char> remaining) {
    if (remaining.empty()) return;
    for (char ch : remaining) {
        Node* child = new Node(ch);
        parent->links.push_back(child);
        std::vector<char> next = remaining;
        next.erase(std::find(next.begin(), next.end(), ch));
        buildLevel(child, next);
    }
}
void PMTree::destroyTree(Node* node) {
    if (!node) return;
    for (Node* child : node->links) destroyTree(child);
    delete node;
}
static void collectPerms(PMTree::Node* node, std::vector<char>& current,
                         std::vector<std::vector<char>>& result, int depth, int total) {
    if (depth == total) {
        result.push_back(current);
        return;
    }
    for (PMTree::Node* child : node->links) {
        current.push_back(child->sym);
        collectPerms(child, current, result, depth + 1, total);
        current.pop_back();
    }
}
std::vector<std::vector<char>> getAllPerms(PMTree& obj) {
    std::vector<std::vector<char>> perms;
    std::vector<char> path;
    collectPerms(obj.top, path, perms, 0, obj.base.size());
    return perms;
}
std::vector<char> getPerm1(PMTree& obj, int pos) {
    auto all = getAllPerms(obj);
    if (pos < 1 || pos > static_cast<int>(all.size())) return {};
    return all[pos - 1];
}
size_t fact(int n) {
    size_t res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}
std::vector<char> getPerm2(PMTree& obj, int pos) {
    int n = obj.base.size();
    if (pos < 1 || static_cast<size_t>(pos) > fact(n)) return {};
    std::vector<char> result;
    int remainder = pos - 1;
    PMTree::Node* cur = obj.top;
    for (int step = 0; step < n; ++step) {
        size_t blockSize = fact(n - step - 1);
        int idx = static_cast<int>(remainder / blockSize);
        remainder %= blockSize;
        if (idx >= static_cast<int>(cur->links.size())) return {};
        cur = cur->links[idx];
        result.push_back(cur->sym);
    }
    return result;
}
