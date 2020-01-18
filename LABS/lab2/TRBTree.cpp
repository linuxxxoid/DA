#include "TRBTree.hpp"
#include <iostream>

TNode::TNode() {
    key = nullptr;
    value = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = RED;
}

TNode::TNode(TKey* key, TVal val, TNodeColor col) {
    this->key = new char[strlen(key) + 1];
    strcpy(this->key, key);
    value = val;
    color = col;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

TNode::~TNode() {
    if (key != nullptr) {
        delete[] key;
    }
}

TRBTree::TRBTree() {
    this->nil = new TNode();
    nil->color = BLACK;
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;
    root = nil;
}

TRBTree::~TRBTree() {
    if (root != nil) {
        Clear(root);
        if (nil != nullptr) {
            delete nil;
        }
    }
}

void TRBTree::Clear(TNode* node) {
    if (node->right != nullptr && node->right != nil) {
        Clear(node->right);
    }
    if (node->left != nullptr && node->left != nil) {
        Clear(node->left);
    }
    delete node;
}

bool TRBTree::Insertion(TKey* key, TVal value, TNodeColor color) {
    TNode* current = root;
    TNode* parent_node = nil;
    while (current != nil && current->key != nullptr) {
        parent_node = current;
        if (strcmp(current->key, key) > 0) {
            current = current->left;
        }
        else if (strcmp(current->key, key) == 0) {
            return false;
        }
        else {
            current = current->right;
        }
    }
    TNode* node = new TNode(key, value, color);
    node->parent = parent_node;
    if (parent_node == nil) {
        root = node;
    }
    else if (strcmp(parent_node->key, node->key) < 0) {
        parent_node->right = node;
    }
    else {
        parent_node->left = node;
    }
    node->left = nil;
    node->right = nil;
    FixInsert(node);
    return true;
}


TNode* TRBTree::MinValueNode(TNode* node) {
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

void TRBTree::TransPlant(TNode* old, TNode* fresh) {
    if (old->parent == nil) {
        root = fresh;
    }
    else if (old == old->parent->left) {
        old->parent->left = fresh;
    }
    else {
        old->parent->right = fresh;
    }
    fresh->parent = old->parent;
}

void TRBTree::Deletion(TNode* node) {
    TNode* trans_node = node;
    TNode* child_node = nil;
    TNodeColor orig_color = trans_node->color;
    if (node->left == nil) {
        child_node = node->right;
        TransPlant(node, node->right);
    }
    else if (node->right == nil) {
        child_node = node->left;
        TransPlant(node, node->left);
    }
    else {
        trans_node = MinValueNode(node->right);
        orig_color = trans_node->color;
        child_node = trans_node->right;
        if (trans_node->parent == node) {
            child_node->parent = trans_node;
        }
        else {
            TransPlant(trans_node, trans_node->right);
            trans_node->right = node->right;
            trans_node->right->parent = trans_node;
        }
        TransPlant(node, trans_node);
        trans_node->left = node->left;
        trans_node->left->parent = trans_node;
        trans_node->color = node->color;
    }
    if (orig_color == BLACK) {
        FixDelete(child_node);
    }
    delete node;
}

TNode* TRBTree::NodeSearch(TKey* key) {
    TNode* node = root;
    while (node != nil) {
        if (strcmp(node->key, key) == 0) {
            return node;
        }
        else {
            node = (strcmp(node->key, key) < 0) ? node->right : node->left;
        }
    }
    return node;
}

void TRBTree::RightRotate(TNode* node) {
    TNode* node_left = node->left;
    node->left = node_left->right;
    if (node_left->right != nil) {
        node_left->right->parent = node;
    }
    node_left->parent = node->parent;
    if (node->parent == nil) {
        root = node_left;
    }
    else if (node == node->parent->right) {
        node->parent->right = node_left;
    }
    else {
        node->parent->left = node_left;
    }
    node_left->right = node;
    node->parent = node_left;
    
}

void TRBTree::LeftRotate(TNode* node) {
    TNode* node_right = node->right;
    node->right = node_right->left;
    if (node_right->left != nil) {
        node_right->left->parent = node;
    }
    node_right->parent = node->parent;
    if (node->parent == nil) {
        root = node_right;
    }
    else if (node == node->parent->left) {
        node->parent->left = node_right;
    }
    else {
        node->parent->right = node_right;
    }
    node_right->left = node;
    node->parent = node_right;
    
}

void TRBTree::FixDelete(TNode* node) {
    while ((node != root) && (node->color == BLACK)) {
        if (node == node->parent->left) {
            TNode* sibling_node = node->parent->right;
            if (sibling_node->color == RED) {
                sibling_node->color = BLACK;
                node->parent->color = RED;
                LeftRotate(node->parent);
                sibling_node = node->parent->right;
            }
            if (sibling_node->right->color == BLACK
                && sibling_node->left->color == BLACK) {
                sibling_node->color = RED;
                node = node->parent;
            }
            else {
                if (sibling_node->right->color == BLACK) {
                    sibling_node->left->color = BLACK;
                    sibling_node->color = RED;
                    RightRotate(sibling_node);
                    sibling_node = node->parent->right;
                }
                sibling_node->color = node->parent->color;
                node->parent->color = BLACK;
                sibling_node->right->color = BLACK;
                LeftRotate(node->parent);
                node = root;
            }
        }
        else {
            TNode* sibling_node = node->parent->left;
            if (sibling_node->color == RED) {
                sibling_node->color = BLACK;
                node->parent->color = RED;
                RightRotate(node->parent);
                sibling_node = node->parent->left;
            }
            if (sibling_node->left->color == BLACK
                && sibling_node->right->color == BLACK) {
                sibling_node->color = RED;
                node = node->parent;
            }
            else {
                if (sibling_node->left->color == BLACK) {
                    sibling_node->right->color = BLACK;
                    sibling_node->color = RED;
                    LeftRotate(sibling_node);
                    sibling_node = node->parent->left;
                }
                sibling_node->color = node->parent->color;
                node->parent->color = BLACK;
                sibling_node->left->color = BLACK;
                RightRotate(node->parent);
                node = root;
            }
        }
    }
    node->color = BLACK;
}


void TRBTree::FixInsert(TNode* node) {
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            TNode* uncle_node = node->parent->parent->right;
            if (uncle_node->color == RED) {
                node->parent->color = BLACK;
                uncle_node->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    LeftRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RightRotate(node->parent->parent);
            }
        }
        else {
            if (node->parent == node->parent->parent->right) {
                TNode* uncle_node = node->parent->parent->left;
                if (uncle_node->color == RED) {
                    node->parent->color = BLACK;
                    uncle_node->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        RightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    LeftRotate(node->parent->parent);
                }
            }
        }
    }
    root->color = BLACK;
}

