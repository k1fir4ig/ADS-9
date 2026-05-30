// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 public:
  struct PMNode {
    char key;
    std::vector<PMNode*> children;
    explicit PMNode(char k) : key(k) {}
  };

 private:
  PMNode* root;

  void buildTree(PMNode* node, const std::vector<char>& elements);
  void freeTree(PMNode* node);

 public:
  explicit PMTree(const std::vector<char>& elements);
  ~PMTree();
  PMNode* getRoot() const { return root; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
