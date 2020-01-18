#ifndef TBOR_H
#define TBOR_H

#include <vector>
#include <string>
#include <map>
#include <memory>

class TAhoCorasick {
private:
    class TBorNode {
    public:
        TBorNode();
        ~TBorNode() {};
        
        std::shared_ptr<TBorNode> failLink;
        std::map<unsigned long, std::shared_ptr<TBorNode>> links;
        std::vector<int> out;
    };
    
    std::shared_ptr<TBorNode> root;
    std::vector<int> lengthSubstr; //length of substrings
    int withoutJoker; //quantity of substrings without '?' in pattern
    
public:
    TAhoCorasick();
    ~TAhoCorasick() {};
    
    void Create(const std::vector<std::string>&);
    void CreateFailLinks();
    void Search(const std::vector<unsigned long>&, const unsigned long, std::vector< std::pair<int, int>>);
};


#endif
