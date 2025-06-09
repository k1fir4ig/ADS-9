// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <algorithm>
#include  <stack>
#include  <utility>
#include  <memory>
#include  <vector>
#include  <cstdlib>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
    if (elements.empty()) {
        root = nullptr;
        total_permutations = 0;
        return;
    }
    root = std::make_shared<Node>('\0');
    total_permutations = 1;
    for (size_t i = 2; i <= elements.size(); ++i) {
        total_permutations *= i;
    }
    buildTree(root, elements);
}
void PMTree::buildTree(const std::shared_ptr<Node>& parent, const std::vector<char>& remaining)
{
    if (remaining.empty()) return;
    for (char elem : remaining) {
        auto child = std::make_shared<Node>(elem);
        parent->children.push_back(child);
    }
    for (auto& child : parent->children) {
        std::vector<char> new_remaining;
        for (char elem : remaining) {
            if (elem != child->value) {
                new_remaining.push_back(elem);
            }
        }
        buildTree(child, new_remaining);
    }
}
void collectPermutations(const std::shared_ptr<PMTree::Node>& node,
                        std::vector<char>& current,
                        std::vector<std::vector<char>>& result) {
    if (!node) return;
    if (node->value != '\0') {
        current.push_back(node->value);
    }
    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            collectPermutations(child, current, result);
        }
    }
    if (node->value != '\0') {
        current.pop_back();
    }
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    auto root = tree.getRoot();
    if (!root) return result;
    for (const auto& child : root->children) {
        collectPermutations(child, current, result);
    }
    return result;
}
std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num < 1 || static_cast<size_t>(num) > tree.getPermutationsCount()) {
        return {};
    }
    auto all_perms = getAllPerms(tree);
    return all_perms[num - 1];
}
std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num < 1 || static_cast<size_t>(num) > tree.getPermutationsCount()) {
        return {};
    }
    std::vector<char> result;
    auto current = tree.getRoot();
    if (!current) return {};
    num--;
    std::stack<std::pair<std::shared_ptr<PMTree::Node>, int>> stack;
    stack.push({current, -1});
    while (!stack.empty()) {
        auto& [node, child_index] = stack.top();
        if (child_index >= 0 && child_index < static_cast<int>(node->children.size()))
        {
            result.pop_back();
        }
        child_index++;
        if (child_index >= static_cast<int>(node->children.size())) {
            stack.pop();
            continue;
        }
        auto child = node->children[child_index];
        result.push_back(child->value);
        if (child->children.empty()) {
            if (num == 0) {
                return result;
            }
            num--;
        } else {
            size_t subtree_size = 1;
            auto temp = child;
            while (!temp->children.empty()) {
                subtree_size *= temp->children.size();
                temp = temp->children[0];
            }
            if (num >= static_cast<int>(subtree_size)) {
                num -= subtree_size;
                result.pop_back();
            } else {
                stack.push({child, -1});
            }
        }
    }
    return {};
}
