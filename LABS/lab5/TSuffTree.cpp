#include "TSuffTree.hpp"
TSuffixTree::TSuffixTree(const std::string& str) : text(str), root(), remainder(0), sufflinkNeed(), activeNode(), activeLength(0), activeEdge() {
    text.push_back(term);
    root = std::make_shared<TNode>(text.end(), text.end());
    root->suffixLink = root;
    root->index = -1;
    activeEdge = text.begin();
    activeNode = sufflinkNeed = root;
    for (auto i = text.begin(); i != text.end(); ++i) {
        ExtendTree(i);
    }
    CountIndex(root, 0);
}

void TSuffixTree::ExtendTree(std::string::iterator add) {
    sufflinkNeed = root;
    ++remainder;
    while (remainder) {
        if (!activeLength) {
            activeEdge = add;
        }
        auto it = activeNode->to_edge.find(*activeEdge);
        std::shared_ptr<TNode> next = (it == activeNode->to_edge.end()) ? nullptr : it->second;
        if (!next) {
            std::shared_ptr<TNode> leaf = std::make_shared<TNode>(add, text.end());
            activeNode->to_edge[*activeEdge] = leaf;
            AddSuffLink(activeNode); //rule 2
        } else {
            if (WalkDown(add, next)) { //observation 2
                continue;
            }
            if (*(next->begin + activeLength) == *add) { //observation 1
                ++activeLength;
                AddSuffLink(activeNode); // observation 3
                break;
            }
            std::shared_ptr<TNode> split = std::make_shared<TNode> (next->begin, next->begin + activeLength - 1);
            std::shared_ptr<TNode> leaf = std::make_shared<TNode> (add, text.end());
            activeNode->to_edge[*activeEdge] = split;
            split->to_edge[*add] = leaf;
            next->begin += activeLength;
            split->to_edge[*next->begin] = next;
            AddSuffLink(split); //rule 2
        }
        --remainder;
        if (activeNode == root && activeLength) { //rule 1
            --activeLength;
            activeEdge = add - remainder + 1;
        } else if (activeNode != root) {
            activeNode = activeNode->suffixLink; //rule 3
        }
    }
}

void TSuffixTree::AddSuffLink(std::shared_ptr<TNode> node) {
    if (sufflinkNeed != root) {
        sufflinkNeed->suffixLink = node;
    }
    sufflinkNeed = node;
}

bool TSuffixTree::WalkDown(std::string::iterator iter, std::shared_ptr<TNode> node) {
    if (activeLength >= EdgeLength(node, iter)) {
        activeEdge += EdgeLength(node, iter);
        activeLength -= EdgeLength(node, iter);
        activeNode = node;
        return true;
    }
    return false;
}

size_t TSuffixTree::EdgeLength(std::shared_ptr<TNode> node, std::string::iterator pos) {
    return std::min(node->end, pos) + 1 - node->begin ;
}

void TSuffixTree::CountIndex(std::shared_ptr<TNode> node, size_t deep) {
    node->index += node->end - node->begin + deep + 1;
    for (auto it: node->to_edge) CountIndex(it.second, node->index);
}

void TSuffixTree::GetEntries(std::shared_ptr<TNode> current, std::vector<size_t>& entries) {
    if (current->to_edge.size() == 0) {
        entries.push_back(text.size() - current->index + 1);
    }
    for (auto it: current->to_edge) {
        GetEntries(it.second, entries);
    }
}

void TSuffixTree::Search(const std::string& pattern, size_t patNum) {
    std::shared_ptr<TNode> current = root;
    auto patternIter = pattern.begin();
    while (patternIter != pattern.end()) {
        auto find = current->to_edge.find(*patternIter);
        if (find != current->to_edge.end()) {
            current = find->second;
            auto textIter = current->begin;
            while (textIter <= current->end && patternIter != pattern.end()) {
                if (*textIter != *patternIter) return;
                ++textIter;
                ++patternIter;
            }
        }
        else return;
    }
    std::cout << patNum << ": ";
    bool flag = false;
    std::vector<size_t> ind;
    GetEntries(current, ind);
    std::sort(ind.begin(), ind.end());
    for (auto it: ind) {
        std::cout << (flag ? ", " : "") << it + 1;
        flag = true;
    }
    std::cout << "\n";
}
