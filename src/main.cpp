// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include "tree.h"

void printVector(const std::vector<char>& vec) {
    for (char c : vec) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::cout << "All permutations:" << std::endl;
    auto all_perms = getAllPerms(tree);
    for (const auto& perm : all_perms) {
        printVector(perm);
    }

    std::cout << "\nPermutation 1: ";
    printVector(getPerm1(tree, 1));

    std::cout << "Permutation 2: ";
    printVector(getPerm2(tree, 2));

    std::cout << "Permutation 3: ";
    printVector(getPerm2(tree, 3));

    std::cout << "Permutation 4: ";
    printVector(getPerm2(tree, 4));

    std::cout << "Permutation 5: ";
    printVector(getPerm2(tree, 5));

    std::cout << "Permutation 6: ";
    printVector(getPerm2(tree, 6));

    return 0;
}
