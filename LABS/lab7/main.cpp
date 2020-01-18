#include <iostream>
#include <string>

const int MAX = 100;
uint64_t Palindrome(const std::string&);

int main(int argc, const char * argv[]) {
    std::string str;
    std::cin >> str;
    std::cout << Palindrome(str) << std::endl;
    return 0;
}

uint64_t Palindrome(const std::string& str) {
    int sizeStr = (int) str.size();
    if (!sizeStr) return 0;
    
    uint64_t plnd[MAX][MAX];
    for (int i = 0; i < sizeStr; ++i) {
        for (int j = 0; j < sizeStr; ++j) {
            if (i == j) {
                plnd[i][j] = 1;
            }
            else {
                plnd[i][j] = 0;
            }
        }
    }
    
    for (int len = 1; len < sizeStr; ++len) {
        for (int i = 0, j = len; i < sizeStr - len; ++i, ++j) {
            if (str[i] == str[j]) {
                plnd[i][j] = plnd[i][j-1] + plnd[i+1][j] + 1;
            }
            else {
                plnd[i][j] = plnd[i][j-1] + plnd[i+1][j] - plnd[i+1][j-1];
            }
        }
    }
    
    return plnd[0][sizeStr - 1];
}
