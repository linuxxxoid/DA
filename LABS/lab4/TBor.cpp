#include <iostream>
#include <queue>
#include "TBor.h"

TAhoCorasick::TBorNode::TBorNode() : failLink(nullptr) {}

TAhoCorasick::TAhoCorasick() {
    root = std::make_shared<TBorNode>(TBorNode());
    root->failLink = root;
    withoutJoker = 0;
}

void TAhoCorasick::Create(const std::vector<std::string>& patterns) {
    int numberPattern = 0;//beginning position of pattern substring
    unsigned long lengthPattern = patterns.size();
    lengthSubstr.resize(lengthPattern);
    int i;
    
    auto currentNode = root;
    
    for (i = 0; i < lengthPattern; ++i) {
        if (patterns[i] == "?") {
            if (currentNode != root) {
                currentNode->out.emplace_back(numberPattern);
                lengthSubstr[numberPattern] = i - numberPattern; //length of pattern substring
                ++withoutJoker;
                currentNode = root;
            }
            numberPattern = i + 1;
            continue;
        }
        auto iter = currentNode->links.find(std::stoul(patterns[i]));
        if (iter != currentNode->links.end()) { //element exists in bor
            currentNode = iter->second;
        }
        else {
            auto newNode = std::make_shared<TBorNode>(TBorNode());
            currentNode->links[std::stoul(patterns[i])] = newNode;
            currentNode = newNode;
        }
    }
    if (currentNode != root) {
        currentNode->out.emplace_back(numberPattern);
        lengthSubstr[numberPattern] = i - numberPattern;
        ++withoutJoker;
    }
}

//suffix link for node U leads to node V which string is the max proper suffix of string U
void TAhoCorasick::CreateFailLinks() {
    std::queue<std::shared_ptr<TBorNode>> queue;
    std::map<unsigned long, std::shared_ptr<TBorNode>>::iterator iter;
    auto currentNode = root;
    queue.emplace(currentNode);
    while (!queue.empty()) {
        currentNode = queue.front();
        queue.pop();
            for (iter = currentNode->links.begin(); iter != currentNode->links.end(); ++iter) {
                auto child = iter->second;
                auto parentFail = currentNode->failLink;
                auto subPattern = iter->first;
                
                queue.emplace(child);
                
                while(1) {
                    auto it = parentFail->links.find(subPattern);
                    if (it != parentFail->links.end()) {
                        child->failLink = (it->second != child) ? it->second : root;
                        child->out.insert(child->out.end(), child->failLink->out.begin(), child->failLink->out.end());
                        break;
                    }
                    if (parentFail == root) {
                        child->failLink = root;
                        break;
                    }
                    else {
                        parentFail = parentFail->failLink;
                    }
                }
        }
    }
}

void TAhoCorasick::Search(const std::vector<unsigned long>& text, const unsigned long lengthPattern, std::vector<std::pair<int, int>> answer) {
    unsigned long lengthText = text.size();
    std::vector<int> entry(lengthText, 0);
    auto currentNode = root;
    int i;
    
    for (i = 0; i < lengthText; ++i) {
        auto iter = currentNode->links.find(text[i]);
        
        while (iter == currentNode->links.end()) {
            currentNode = currentNode->failLink;
            iter = currentNode->links.find(text[i]);
            if (currentNode == currentNode->failLink) {
                break;
            }
        }
        if (iter != currentNode->links.end()) { // find smth
            currentNode = iter->second;
            if (!currentNode->out.empty()) { // the end of the entrance
                std::vector<int>::iterator iter2;
                    for (iter2 = currentNode->out.begin(); iter2 != currentNode->out.end(); ++iter2) {
                    int patternId = i - lengthSubstr[*iter2] - *iter2 + 1;
                    if (patternId < 0) {
                        continue;
                    }
                    ++entry[patternId]; // found the entrance
                }
            }
        }
    }
    for (i = 0; i < lengthText; ++i) {
        if ((entry[i] == withoutJoker) && (i + lengthPattern <= lengthText)) {
            std::cout << answer[i].first << ", " << answer[i].second << std::endl;
        }
    }
}
