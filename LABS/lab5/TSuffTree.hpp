#ifndef TSuffTree_hpp
#define TSuffTree_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>

const char term = '$';


class TNode {
public:
    std::map<char, std::shared_ptr<TNode>> to_edge;
    std::string::iterator begin, end; 
    std::shared_ptr<TNode> suffixLink;
    int index;
    TNode(std::string::iterator begin, std::string::iterator end) : to_edge(), begin(begin), end(end), index(0) {};
    ~TNode() {};
};

class TSuffixTree {
public:
    TSuffixTree(const std::string& str);
    void Search(const std::string&, size_t);
    ~TSuffixTree() {};
private:
    std::string text;
    std::shared_ptr<TNode> root;
    size_t remainder;
    std::shared_ptr<TNode> sufflinkNeed;
    std::shared_ptr<TNode> activeNode;
    size_t activeLength;
    std::string::iterator activeEdge;
    
    
    size_t EdgeLength(std::shared_ptr<TNode>, std::string::iterator);
    void CountIndex(std::shared_ptr<TNode>, size_t);
    void GetEntries(std::shared_ptr<TNode> current_node, std::vector<size_t>& entries);
    void ExtendTree(std::string::iterator);
    void AddSuffLink(std::shared_ptr<TNode>);
    bool WalkDown(std::string::iterator, std::shared_ptr<TNode>);
};

#endif
