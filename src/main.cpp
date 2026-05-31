// Copyright 2022 NNTU-CS
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"
int main() {
    // Демонстрация работы для {1,2,3}
    std::vector<char> demo = {'1','2','3'};
    PMTree demoTree(demo);
    std::cout << "Все перестановки:\n";
    auto perms = getAllPerms(demoTree);
    for (auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << "  ";
    }
    std::cout << "\n\n";
    std::cout << "getPerm1(1): ";
    auto p1 = getPerm1(demoTree, 1);
    for (char c : p1) std::cout << c;
    std::cout << "\n";
    std::cout << "getPerm2(2): ";
    auto p2 = getPerm2(demoTree, 2);
    for (char c : p2) std::cout << c;
    std::cout << "\n\n";
    // Замеры времени для n = 3..8
    std::cout << "n;getAllPerms(s);getPerm1(s);getPerm2(s)\n";
    for (int n = 3; n <= 8; ++n) {
        std::vector<char> letters;
        for (int i = 0; i < n; ++i) letters.push_back('a' + i);
        PMTree tree(letters);
        std::mt19937 gen(42);
        std::uniform_int_distribution<> dist(1, static_cast<int>(fact(n)));
        int target = dist(gen);
        auto t0 = std::chrono::high_resolution_clock::now();
        getAllPerms(tree);
        auto t1 = std::chrono::high_resolution_clock::now();
        getPerm1(tree, target);
        auto t2 = std::chrono::high_resolution_clock::now();
        getPerm2(tree, target);
        auto t3 = std::chrono::high_resolution_clock::now();
        double d1 = std::chrono::duration<double>(t1 - t0).count();
        double d2 = std::chrono::duration<double>(t2 - t1).count();
        double d3 = std::chrono::duration<double>(t3 - t2).count();
        std::cout << n << ";"
                  << std::fixed << std::setprecision(6) << d1 << ";"
                  << d2 << ";"
                  << d3 << std::endl;
    }
    return 0;
}
