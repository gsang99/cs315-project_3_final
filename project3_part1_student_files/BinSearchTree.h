//
// Created by Gemma on 10/17/2025.
//

#ifndef P3_PART1_BINSEARCHTREE_H
#define P3_PART1_BINSEARCHTREE_H

#endif //P3_PART1_BINSEARCHTREE_H
#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include "TreeNode.h"
#include "utils.hpp"
class BinSearchTree {
public:
    BinSearchTree() = default;
    ~BinSearchTree(); // delete all nodes //all done sshhhaawwttyyy

    void insert(const std::string& word); //lets get this bad boy going //i did ittt
    void bulkInsert(const std::vector<std::string>& words); //onto the next one //i did it

    [[nodiscard]] bool contains(std::string_view word) const noexcept; //woot woot easy peasy
    [[nodiscard]] std::optional<int> countOf(std::string_view word) const noexcept; //starting //done dimadom johnson

    void inorderCollect(std::vector<std::pair<std::string,int>>& out) const; //starting //its done thank god

    [[nodiscard]] int size() const noexcept;  // distinct words //starting //done shawty
    [[nodiscard]] unsigned height() const noexcept;   // empty tree == 0 //starting //done



private:
    struct TreeNode { std::string word; int freq; TreeNode *left,*right; };
    TreeNode* root_ = nullptr;


    //helpers: destroy, insertHelper, findNode, inorderHelper, sizeHelper, heightHelper
    //delete helper
    void destroy (TreeNode *);

    //insert helper
    TreeNode* insert( TreeNode *, const std::string&);

    //inOrderHelper
    static void inorderHelper(const TreeNode*, std::vector<std::pair<std::string,int>>& out);

    //size helper
    static int sizeHelper(const TreeNode*) noexcept;

    //height helper
    static unsigned heightHelper (const TreeNode*) noexcept;


};
