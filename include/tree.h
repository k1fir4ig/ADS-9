// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
 public:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        explicit Node(char val) : value(val) {}
    };

    explicit PMTree(const std::vector<char>& elements);
    ~PMTree() = default;

    const std::shared_ptr<Node>& getRoot() const { return root; }
    size_t getPermutationsCount() const { return total_permutations; }

 private:
    std::shared_ptr<Node> root;
    size_t total_permutations;

void buildTree(const std::shared_ptr<Node>& parent, const std::vector<char>& remaining);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
