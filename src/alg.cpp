// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <algorithm>
#include  <stdexcept>
#include  <vector>
#include  "tree.h"

int factorial(int n) {
  if (n < 0) throw std::invalid_argument("n must be non-negative");
  int res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

PMTree::PMTree(const std::vector<char>& elements) {
  root = new PMNode('\0');
  buildTree(root, elements);
}

PMTree::~PMTree() { freeTree(root); }

void PMTree::buildTree(PMNode* node, const std::vector<char>& elements) {
  if (elements.empty()) return;

  for (char el : elements) {
    PMNode* child = new PMNode(el);
    node->children.push_back(child);

    std::vector<char> remaining(elements);
    remaining.erase(std::remove(remaining.begin(), remaining.end(), el),
                    remaining.end());
    buildTree(child, remaining);
  }
}

void PMTree::freeTree(PMNode* node) {
  for (auto child : node->children) freeTree(child);
  delete node;
}

void getAllPermsHelper(PMTree::PMNode* node, std::vector<char>& current,
                       std::vector<std::vector<char>>& perms) {
  if (node->children.empty()) {
    perms.push_back(current);
    return;
  }
  for (PMTree::PMNode* child : node->children) {
    current.push_back(child->key);
    getAllPermsHelper(child, current, perms);
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> perms;
  std::vector<char> current;
  getAllPermsHelper(tree.getRoot(), current, perms);
  return perms;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto perms = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(perms.size())) return {};
  return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result;
  PMTree::PMNode* current = tree.getRoot();
  std::vector<PMTree::PMNode*> nodes = current->children;

  int n = static_cast<int>(nodes.size());
  int totalPerms = factorial(n);

  if (num < 1 || num > totalPerms) return {};

  --num;

  while (!nodes.empty()) {
    int blockSize = totalPerms / static_cast<int>(nodes.size());
    int index = num / blockSize;
    result.push_back(nodes[index]->key);
    nodes.erase(nodes.begin() + index);
    num %= blockSize;
    totalPerms = blockSize;
  }
  return result;
}
