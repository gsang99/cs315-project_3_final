//
// Created by Gemma on 10/26/2025.
//
#include "HuffmanTree.h"
#include <utility>
#include <map>


//NOTE Helper functions are all at the top

void HuffmanTree::destroy(TreeNode *n) noexcept
{
    //if its null
    if (n == nullptr)
    {
        return;
    }

    //if it isn't null
    //go to left subtree and delete
    destroy(n -> left);

    //go to the right subtree and delete
    destroy(n -> right);
    //go to the parent and delete
    delete(n);
}

void HuffmanTree::assignCodesDFS(const TreeNode *n, std::string &prefix,
                                 std::vector<std::pair<std::string, std::string>> &out) {

    //check if null
    if (n == nullptr)
    {
        return;
    }
    //is root a leaf
    if( !n -> left && !n-> right )
    {
        std::string code;
        //check if empty
        if (prefix.empty())
        {
            code += "0";
        }
        else{
            code = prefix;
        }


        //pushing changes to our output
        out.push_back({n->word, code});
        return;
    }
    //where are we going
    //we go left?
        //use 0
    prefix += "0";
    assignCodesDFS(n->left, prefix, out);
    prefix.pop_back();
    // we go right?
        //use 1
    prefix += "1";
    assignCodesDFS(n->right, prefix, out);
    prefix.pop_back();

}



void HuffmanTree::writeHeaderPreorder(const TreeNode *n, std::ostream &os, std::string &prefix)
{
    // Null check
    if (n == nullptr) {
        return;
    }

    // write to stream
    if (!n->left && !n->right) {
        std::string code = prefix.empty() ? "0" : prefix;
        os << n->word << " " << code << "\n";
        return;
    }

    // Internal: recurse
    prefix += "0";
    writeHeaderPreorder(n->left, os, prefix);
    prefix.pop_back();

    prefix += "1";
    writeHeaderPreorder(n->right, os, prefix);
    prefix.pop_back();
}





//Regular functions are all below
bool HuffmanTree::higherPriority(const TreeNode *a, const TreeNode *b) noexcept {
    if (a->freq != b->freq)
    {
        return a->freq > b->freq;   // higher freq first
    }
    return a->key_word < b->key_word;
}

HuffmanTree HuffmanTree::buildFromCounts(const std::vector<std::pair<std::string, int>> &counts) {

    HuffmanTree tree;
    //making the huffman tree
    std::vector<TreeNode *> leaves;

    // if its null
    if (std::empty(counts)) {
        tree.root_ = nullptr;
        return tree;

    }

    for (int i = 0; i < counts.size(); i++) {

        TreeNode *leaf = new TreeNode(counts.at(i).first);  //grabbing the string
        leaf->freq = counts.at(i).second; //grabs the integer
        leaves.push_back(leaf); //now we are populating leaves

    }


    // is there just one node?
    if (leaves.size() == 1) {
        tree.root_ = leaves.front();
        return tree;
    }

    //continously sorting
    std::stable_sort(leaves.begin(), leaves.end(), higherPriority);


    // combine until one remains
    while (leaves.size() > 1) {
        TreeNode *a = leaves.back();
        leaves.pop_back();
        TreeNode *b = leaves.back();
        leaves.pop_back();

        TreeNode *parent = new TreeNode("");
        parent->left = a;
        parent->right = b;
        parent->freq = a->freq + b->freq;
        parent->word.clear();             // no word
        parent->key_word = std::min(a->key_word, b->key_word); // tie-break rep

        auto pos = std::upper_bound(leaves.begin(), leaves.end(), parent, higherPriority);
        leaves.insert(pos, parent);
    }

    tree.root_ = leaves.front();

    return tree;
}
HuffmanTree::~HuffmanTree()
{
    destroy(root_);
}

void HuffmanTree::assignCodes(std::vector<std::pair<std::string, std::string>> &out) const
{

    if (root_ == nullptr)
    {return;}
    std::string prefix;
    assignCodesDFS(root_, prefix, out);
}

error_type HuffmanTree::writeHeader(std::ostream &os) const {

    if (!os) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }
    std::vector<std::pair<std::string, std::string>> codes;
    assignCodes(codes);

    for (int i = 0; i < codes.size(); i++) {
        os << codes.at(i).first << " " << codes.at(i).second << "\n";
    }

    if (os.fail()) {
        return FAILED_TO_WRITE_FILE;
    }

    return NO_ERROR;
}

error_type HuffmanTree::encode(const std::vector<std::string> &tokens, std::ostream &os_bits, int wrap_cols) const {

    if (!os_bits) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    // Build codebook
    std::vector<std::pair<std::string, std::string>> codesList;
    assignCodes(codesList);

    std::map<std::string, std::string> codebook;
    for (int i = 0; i < codesList.size(); i++) {
        codebook[codesList[i].first] = codesList[i].second;
    }

    // Track column position
    int col = 0;

    // Encode each token
    for (int i = 0; i < tokens.size(); i++) {
        // Look up the code for token
        auto it = codebook.find(tokens[i]);  // ← FIX: Use tokens[i], not 'word'

        if (it == codebook.end()) {
            // Word not found in codebook - error!
            return FAILED_TO_WRITE_FILE;
        }

        const std::string &code = it->second;


        // Write each bit of the code
        for (int j = 0; j < code.length(); j++) {  // ← FIX: Use 'j' not 'i' (avoid shadowing)
            os_bits << code.at(j);
            col++;

            // Wrap at wrap_cols characters
            if (col >= wrap_cols) {
                os_bits << "\n";
                col = 0;
            }
        }


    }

    if (col > 0) {
        os_bits << "\n";
    }

    // Check if writing succeeded
    if (os_bits.fail()) {
        return FAILED_TO_WRITE_FILE;
    }

    // Return success
    return NO_ERROR;
}

