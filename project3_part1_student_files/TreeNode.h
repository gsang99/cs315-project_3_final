#pragma once
#include <string>
#include <cstddef>

struct TreeNode {
    std::string word;
    std::size_t freq;
    std::string key_word;
    TreeNode* left;
    TreeNode* right;


    TreeNode(const std::string& w, std::size_t f = 1) : word(w), freq(f), key_word(w), left(nullptr), right(nullptr) {}

};
