//
// Created by Gemma on 10/17/2025.
//

#include "BinSearchTree.h"
#include <algorithm>
#include <iostream>


//helper functions go at the top
void BinSearchTree::destroy(TreeNode *root_) {

    if (root_ == nullptr){
        //nothing is returned bc its void
        return;
    };

    destroy( root_ -> left);
    destroy(root_ -> right);
    delete root_;

}

//helper insert
BinSearchTree::TreeNode *BinSearchTree::insert(BinSearchTree::TreeNode *root_, const std::string &word)
{
    if( root_ == nullptr )
        return new TreeNode( word );

    else if( word < root_-> word )
    {
        root_ -> left = insert( root_->left, word );
    }


    else if(word > root_-> word)
    {

        root_ -> right = insert( root_->right, word );

    }

    else
    {
        // if theyre equal to each other, then increase the number of their frequency
        root_ -> freq ++;


    }

    return root_;

}
//helper for in order
void BinSearchTree::inorderHelper(const BinSearchTree::TreeNode *root_, std::vector<std::pair<std::string, int >> &out)
{


    //then we come up with a base case, if the tree is nullptr
    if ( root_ == nullptr)
    {
        return;
    }
    //traverse left
    inorderHelper(root_ ->left, out);
    //push it into the vecotr
    out.emplace_back(root_ ->word, root_ -> freq);

    //traverse right
    inorderHelper(root_ ->right, out );

}

//size Helper
int BinSearchTree::sizeHelper(const BinSearchTree::TreeNode *root_) noexcept {

    if (root_ == nullptr)
    {
        return 0;
    }

    return 1+ sizeHelper(root_ -> left) + sizeHelper(root_-> right);
}

//height helper
unsigned BinSearchTree::heightHelper(const BinSearchTree::TreeNode *root_) noexcept {

    //check if its null
    if (root_ == nullptr)
    {
        return 0;
    }
    //return 0 if it is


    //otherwise return the max of the heights of left and right subtree including the root
    return 1 + std::max(heightHelper(root_->left), heightHelper(root_->right));
}



//all of the actual functions of the public interface are called below
BinSearchTree::~BinSearchTree()
{

    destroy(root_);

}

void BinSearchTree::insert(const std::string &word)
{
    root_ = insert(root_, word);
}

void BinSearchTree::bulkInsert(const std::vector<std::string> &words)
{
    int i = 0;
    //calling the insert function repeatedly to check a few things

    while (i < words.size())
    {
        insert(words.at(i));
        i++;

    }

}

bool BinSearchTree::contains(std::string_view word) const noexcept
{
    //making a copy of the actual root
    TreeNode* copyRoot = root_;

    //we are searching the tree if the value exists within the binary search tree

    //if we reach the end of the thing and its null then return false
    while (copyRoot != nullptr)
    {
        //if the word is equal to the what we are searching for then we return true

        if (word == copyRoot-> word)
        {
            return true;
        }

        //if the word is less than the root, go left
        if(word < copyRoot -> word)
        {
            copyRoot = copyRoot -> left;
        }


        //if word is more than the root, go right
        if (word > copyRoot -> word)
        {
            copyRoot = copyRoot -> right;
        }

    }

    //if the root isn't in the list then return false
    return false;
}

std::optional<int> BinSearchTree::countOf(std::string_view word) const noexcept {

    //make a copy of the root like we did eaerlier

    TreeNode* copyRoot = root_;

    //iterating through the bst
    while (copyRoot != nullptr)
    {
        //first thing we check is if the word even exists
        //if it does exist then we return optional with its frequency amount
        if ( word == copyRoot -> word)
        {
            return copyRoot ->freq;
        }

        //otherwise we check the rest of the trees to make sure its not in one of the leafs
        if (word < copyRoot ->word)
        {
            copyRoot = copyRoot -> left;
        }

        if(word > copyRoot -> word)
        {
            copyRoot = copyRoot -> right;
        }

    }

    //if it doesnt exist within the tree we return the nullptr
    return std::nullopt;
}

void BinSearchTree::inorderCollect(std::vector<std::pair<std::string, int>> &out) const
{

    inorderHelper(root_, out);


}

int BinSearchTree::size() const noexcept
{
    return sizeHelper(root_);
}

unsigned BinSearchTree::height() const noexcept {
    return heightHelper(root_);
}










