// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <vector>

void printVector(const std::vector<char>& vec) {
  for (char c : vec) {
    std::cout << c << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  std::cout << "Все перестановки:" << std::endl;
  auto all_perms = getAllPerms(tree);
  for (const auto& perm : all_perms) {
    printVector(perm);
  }

  std::cout << "\nПерестановка 1: ";
  printVector(getPerm1(tree, 1));

  std::cout << "Перестановка 2: ";
  printVector(getPerm2(tree, 2));

  return 0;
}
