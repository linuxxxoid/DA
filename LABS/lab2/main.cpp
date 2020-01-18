#include "TRBTree.hpp"
#include <iostream>
#include <ctime>

char LowerCase(char symb);
void Parser(char &action, TKey* str, TVal &val);

int main(int argc, const char * argv[]) {
    TRBTree* tree = new TRBTree();
    TKey* str = new char[KEY_SIZE];
    char action;
    TVal val;
    
    while(1) {
        Parser(action, str, val);
        if (action == 'E') {
            break;
        }
        switch (action) {
            case '+': {
                if((tree->Insertion(str, val, RED)) == 1) {
                    printf("OK\n");
                }
                else {
                    printf("Exist\n");
                }
                break;
            }
            case '-': {
                TNode* node = tree->NodeSearch(str);
                if (node != tree->nil) {
                    tree->Deletion(node);
                    printf("OK\n");
                }
                else {
                    printf("NoSuchWord\n");
                }
                break;
            }
            case 'S': {
                std::ofstream output(str, std::ofstream::binary | std::ios::out);
                if (output) {
                    tree->SavingTree(output, tree->root);
                    printf("OK\n");
                }
                else {
                    printf("ERROR: Couldn't create file\n");
                }
                output.close();
                break;
            }
            case 'L': {
                std::ifstream input(str, std::ifstream::binary | std::ios::in);
                if (input) {
                    delete tree;
                    tree = new TRBTree();
                    tree->LoadingTree(input, tree);
                    printf("OK\n");
                }
                else {
                    printf("ERROR: Couldn't open file\n");
                }
                input.close();
                break;
            }
            case 'F': {
                TNode* word_node = tree->NodeSearch(str);
                if (word_node == tree->nil) {
                    printf("NoSuchWord\n");
                }
                else {
                    printf("OK: %llu\n", word_node->value);
                }
                break;
            }
        }
    }
    val = 0;
    action = 0;
    delete tree;
    delete[] str;
    return 0;
}

void Parser(char &action, TKey* str, TVal &val) {
    char symb;
    int i = 0;
    val = 0;
    
    symb = getchar_unlocked();
    if (symb == EOF || symb == ' ') {
        action = 'E';
        return;
    }
    
    switch (symb) {
        case '+': {
            i = 0;
            action = symb;
            getchar_unlocked();
            while ((symb = LowerCase(getchar_unlocked())) != ' ') {
                str[i++] = symb;
            }
            str[i] = '\0';
            while ((symb = getchar_unlocked()) != '\n') {
                val = val * 10 + symb - '0';
            }
            break;
        }
        case '-': {
            i = 0;
            action = symb;
            getchar_unlocked();
            while ((symb = LowerCase(getchar_unlocked())) != '\n') {
                str[i++] = symb;
            }
            str[i] = '\0';
            break;
        }
        case '!': {
            getchar_unlocked();
            action = getchar_unlocked();
            getchar_unlocked();
            getchar_unlocked();
            getchar_unlocked();
            getchar_unlocked();
            i = 0;
            while ((symb = LowerCase(getchar_unlocked())) != '\n') {
                str[i++] = symb;
            }
            str[i] = '\0';
            break;
        }
        default: {
            if (symb == '\n') {
                printf("NoSuchWord\n");
                return;
            }
            action = 'F';
            i = 1;
            str[0] = LowerCase(symb);
            while ((symb = LowerCase(getchar_unlocked())) != '\n') {
                str[i++] = symb;
            }
            str[i] = '\0';
        }
    }
}

char LowerCase(char symb) {
    return symb >= 'A' && symb <= 'Z' ? symb - 'A' + 'a' : symb;
}
