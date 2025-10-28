//
// Created by Gemma on 10/26/2025.
//

#ifndef P3_PART1_HUFFMANTREE_H
#define P3_PART1_HUFFMANTREE_H

#endif //P3_PART1_HUFFMANTREE_H
#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include <iostream>
#include "TreeNode.h"
#include "utils.hpp"
#include "algorithm"
class HuffmanTree {
public:
    // Build from BST output (lexicographic vector of (word, count)).
    static HuffmanTree buildFromCounts(const std::vector<std::pair<std::string,int>>& counts); //this horrific thing is done

    HuffmanTree() = default;
    ~HuffmanTree();                         // deletes the entire Huffman tree //done

    // Build a vector of (word, code) pairs by traversing the Huffman tree
    // (left=0, right=1; visit left before right).
    void assignCodes(std::vector<std::pair<std::string,std::string>>& out) const; //done with this frick as thing

    // Header writer (pre-order over leaves; "word<space>code"; newline at end).
    error_type writeHeader(std::ostream& os) const;

    // Encode a sequence of tokens using the codebook derived from this tree.
    // Writes ASCII '0'/'1' and wraps lines to wrap_cols (80 by default).
    error_type encode(const std::vector<std::string>& tokens,
                      std::ostream& os_bits,
                      int wrap_cols = 80) const;

private:
    TreeNode* root_ = nullptr; // owns the full Huffman tree

    static bool higherPriority(const TreeNode* a, const TreeNode* b) noexcept; //helper for the constructor

    // helpers (decl only; defs in .cpp)
    static void destroy(TreeNode* n) noexcept; //done
    static void assignCodesDFS(const TreeNode* n,
                               std::string& prefix,
                               std::vector<std::pair<std::string,std::string>>& out); //thank god I am done
    static void writeHeaderPreorder(const TreeNode* n, std::ostream& os,
                                    std::string& prefix);

};