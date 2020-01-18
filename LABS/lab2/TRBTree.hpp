#ifndef TRBTree_hpp
#define TRBTree_hpp

#include <fstream>
#include <cstring>
#include <cctype>
#include <stdlib.h>

const int KEY_SIZE = 257;
typedef char TKey;
typedef unsigned long long TVal;
typedef bool TNodeColor;
const TNodeColor RED = true;
const TNodeColor BLACK = false;

class TNode {
public:
    TNode();
    TNode(TKey* key, TVal value, TNodeColor col);
    ~TNode();
    TNode* parent;
    TNode* left;
    TNode* right;
    TNodeColor color;
    TKey* key;
    TVal value;
};

class TRBTree {
public:
    TRBTree();
    ~TRBTree();
    TNode* nil;
    TNode* root;
    TNode* NodeSearch(TKey* key);
    bool Insertion(TKey* key, TVal value, TNodeColor color);
    void Deletion(TNode* node);
    void SavingTree(std::ofstream& output, TNode* root);
    void LoadingTree(std::ifstream& input, TRBTree* tree);
    
protected:
    TNode* MinValueNode(TNode* node);
    void Clear(TNode* node);
    void TransPlant(TNode* old, TNode* fresh);
    void FixInsert(TNode* node);
    void LeftRotate(TNode* node);
    void RightRotate(TNode* node);
    void FixDelete(TNode* node);
};

#endif
