//Необходимо реализовать алгоритм Укконена построения суффиксного дерева за линейное время. Построив такое дерево для некоторых из входных строк, необходимо воспользоваться полученным суффиксным деревом для решения своего варианта задания.
//Алфавит строк: строчные буквы латинского алфавита (т.е., от a до z).
//Вариант 1: Поиск в известном тексте неизвестных заранее образцов
#include <iostream>
#include "TSuffTree.hpp"
int main(int argc, const char * argv[]) {
    std::string text, pattern;
    int patternNumber = 0;
    
    std::cin >> text;
    TSuffixTree tree(text);

    while (std::cin >> pattern) {
        tree.Search(pattern, ++patternNumber);
    }
    return 0;
}
