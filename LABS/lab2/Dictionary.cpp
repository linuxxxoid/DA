#include "TRBTree.hpp"
#include <iostream>

void TRBTree::SavingTree(std::ofstream &output, TNode* root) {
    if (root == nil) {
        return;
    }
    output << root->key << " " << root->value << " " << root->color << " ";
    SavingTree(output, root->left);
    SavingTree(output, root->right);
}


void TRBTree::LoadingTree(std::ifstream &input, TRBTree* tree) {
    TVal val = 0;
    TNodeColor color;
    TKey* tmp = new char[KEY_SIZE];
    if (input.peek() == EOF) {
        return;
    }
    
    while (input >> tmp >> val >> color) {
        tree->Insertion(tmp, val, color);
    }
    delete[] tmp;
}
