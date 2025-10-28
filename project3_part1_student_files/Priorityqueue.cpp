//
// Created by Gemma on 10/17/2025.
//

#include "Priorityqueue.h"
#include <algorithm>
#include <iostream>


PriorityQueue::PriorityQueue(std::vector<TreeNode *> nodes)
{
    //we iterate through nodes
    for (int i = 0; i < nodes.size(); i++)
    {
        //at every iteration we store & compare what is inside of nodes
        if (nodes.at(i) != nullptr) {
            items_.push_back(nodes[i]);
        }
    }
    // Sort them by the comparator
    std::stable_sort(items_.begin(), items_.end(), higherPriority);


}

int PriorityQueue::size() const noexcept
{
    //we just need to know the size
    return items_.size();
}

bool PriorityQueue::empty() const noexcept
{
    //if the items list is empty then we return true; if its not, then we return false
    if (items_.size() == 0 )
    {
        return true;
    }
    return false;
}

TreeNode *PriorityQueue::findMin() const noexcept {

    //check if its empty
   if (std::empty(items_))
   {
       return nullptr;
   }

    //if its not empty, then look all the way at the end of the vector
    return items_.back();
}

TreeNode *PriorityQueue::extractMin() noexcept
{

    //check if its empty
    if (std::empty(items_))
    {
        return nullptr;
    }


    //check the end of the last minimum item
    //then store it
    TreeNode* storeItems = items_.back();
    //then remove it
    items_.pop_back();
    // then return it

    return storeItems;
}

void PriorityQueue::deleteMin() noexcept
{
    //check if its empty
    if (std::empty(items_))
    {
        return;
    }

    // popback the item
    items_.pop_back();

}

void PriorityQueue::insert(TreeNode *node)
{
    //check if the priority queue is empty
    if (node == nullptr)
    {
        return;
    }
    //if it is then push it
    if (items_.empty())
    {
        items_.push_back(node);
        return;
    }


    //if its not then we sort based off of higher priority
    int i = items_.size() - 1 ;
    while (i >= 0 && higherPriority( node, items_.at(i)))
    {
        //so which ever has the higher count goes first, then alphabetically is organized
        //now that we have checked we just decrement
        i--;
    }

    items_.insert(items_.begin() + i + 1, node );
}

void PriorityQueue::print(std::ostream &os) const
{
    // if empty, print message
        if (std::empty(items_))
        {
            os << "empty priority queue\n";
            return;
        }

        // otherwise, print key word and frequnecy
        os << "Priority Queue (highest freq first):\n";
        for (int i = 0; i < items_.size(); i++)
        {
            TreeNode* tempNode = items_.at(i);
            os << "  " << tempNode->key_word << " : " << tempNode->freq << '\n';
        }

}

bool PriorityQueue::higherPriority(const TreeNode* a, const TreeNode* b) noexcept {
    if (a->freq != b->freq)
    {
        return a->freq > b->freq;   // higher freq first
    }
    return a->key_word < b->key_word;
}

std::pair<int, int> PriorityQueue::getFreq() {
    Min = std::get<1>(priority_q.front());
    Max = std::get<1>(priority_q.back());

    return {Min,Max};
}


