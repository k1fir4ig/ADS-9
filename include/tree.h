// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
 public:
  struct Node {
    char value;
    std::vector<std::unique_ptr<Node>> children;
    
    explicit Node(char val) : value(val) {}
  };

  explicit PMTree(const std::vector<char>& elements);
  ~PMTree() = default;

  const Node* getRoot() const { return root.get(); }
  size_t getPermutationsCount() const { return total_permutations; }

 private:
  std::unique_ptr<Node> root;
  size_t total_permutations;
    
  void buildTree(Node* parent, const std::vector<char>& remaining);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
