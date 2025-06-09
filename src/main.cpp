// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

void printVector(const std::vector<char>& vec) {
    for (char c : vec) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

void runExperiment() {
    std::ofstream data_file("result/data.csv");
    data_file << "n,getAllPerms,getPerm1,getPerm2\n";
    
    const int max_n = 10;
    const int samples = 5;
    
    for (int n = 1; n <= max_n; ++n) {
        std::vector<char> in;
        for (int i = 0; i < n; ++i) {
            in.push_back('1' + i);
        }

        PMTree tree(in);

        auto start = std::chrono::high_resolution_clock::now();
        auto all_perms = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_all = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(1, all_perms.size());

        double duration_perm1 = 0;
        for (int i = 0; i < samples; ++i) {
            int rand_num = distr(gen);
            start = std::chrono::high_resolution_clock::now();
            auto perm1 = getPerm1(tree, rand_num);
            end = std::chrono::high_resolution_clock::now();
            duration_perm1 += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        duration_perm1 /= samples;
        
        double duration_perm2 = 0;
        for (int i = 0; i < samples; ++i) {
            int rand_num = distr(gen);
            start = std::chrono::high_resolution_clock::now();
            auto perm2 = getPerm2(tree, rand_num);
            end = std::chrono::high_resolution_clock::now();
            duration_perm2 += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        duration_perm2 /= samples;
        
        data_file << n << "," << duration_all << "," << duration_perm1 << "," << duration_perm2 << "\n";
        std::cout << "Замер для n=" << n << " завершен" << std::endl;
    }
    
    data_file.close();
    
    std::cout << "Данные эксперимента сохранены в result/data.csv" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Ru");
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
    
    std::cout << "\nЗапуск эксперимента..." << std::endl;
    runExperiment();
    
    return 0;
}
