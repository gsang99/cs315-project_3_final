//
// Created by Gemma on 10/17/2025.
//

#ifndef P3_PART1_PRIORITYQUEUE_H
#define P3_PART1_PRIORITYQUEUE_H
#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include <iostream>
#include "TreeNode.h"
#include "utils.hpp"

class PriorityQueue {
public:
    explicit PriorityQueue(std::vector<TreeNode*> nodes); // sort internally //done
    ~PriorityQueue() = default;

    [[nodiscard]] int size() const noexcept; //done
    [[nodiscard]] bool empty() const noexcept; //done

    [[nodiscard]] TreeNode* findMin() const noexcept; // items_.back() or nullptr //done
    TreeNode* extractMin() noexcept;                  // pop_back() or nullptr // done
    void deleteMin() noexcept;                        // pop_back() if present //done

    void insert(TreeNode* node);  // keeps (freq desc, key_word asc) invariant
    void print(std::ostream& os = std::cout) const;

    [[nodiscard]] std::pair<int,int> getFreq(); //gets the frequency of everything

private:
    std::vector<TreeNode*> items_; // **does not own pointers**
    static bool higherPriority(const TreeNode* a, const TreeNode* b) noexcept;
    std::vector<std::pair<std::string ,int>> priority_q;
    bool isSorted() const; // for asserts/tests

    int Min;
    int Max;



};


#endif //P3_PART1_PRIORITYQUEUE_H
