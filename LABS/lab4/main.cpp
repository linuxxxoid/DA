#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <string>
#include "TBor.h"


int main(int argc, const char * argv[]) {
    std::vector<std::string> pattern;
    std::vector<unsigned long> text;
    std::vector<std::pair<int, int>> answer;
    std::string buffer, symb;
    TAhoCorasick bor;
    
    std::getline(std::cin, buffer);
    std::stringstream ptrn_strm(buffer);
    
    while (ptrn_strm >> symb) {
        pattern.emplace_back(std::string(symb));
    }
    
    int line = 1;
    int word = 1;
    
    while (std::getline(std::cin, buffer)) {
        std::stringstream txt_strm(buffer);
        while (txt_strm >> symb) {
            text.emplace_back(std::stoul(symb));
            answer.emplace_back(std::make_pair(line, word));
            ++word;
        }
        ++line;
        word = 1;
    }
    
    
    clock_t start, end;
    start = clock();
    bor.Create(pattern);
    bor.CreateFailLinks();
    bor.Search(text, pattern.size(), answer);
    end = clock();
    
    std::cout << "Aho-Corasick search time is: "
    << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
    start = clock();

 
    return 0;
}
