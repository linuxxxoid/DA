#include <cstdio>
#include <map>
#include <fstream>
#include <iostream>

void ToLower (std::string &buffer) {
    int index = 0;
    while (index < buffer.size()) {
        if (buffer[index] >= 'A' && buffer[index] <= 'Z') {
            buffer[index] += -'A' + 'a';
        }
        ++index;
    }
}

int main () {
    //std::ios::sync_with_stdio(false); //make_faster
   // std::ofstream fout("/Users/linuxoid/Desktop/map", std::ios::app);
    std::map <std::string, unsigned long long> map;
    std::string buffer;
    uint64_t data;
    char choice;

    clock_t start = clock();

    if (!std::cin.get(choice)) {
        return 0;
    }

    std::cin.putback(choice);

    while (std::cin >> choice) {
        switch (choice) {
            case '+': {
                std::cin >> buffer >> data;
                ToLower(buffer);

                if (map.count(buffer) == 0) {
                    map[buffer] = data;
                    printf("OK\n");
                } else {
                    printf("Exist\n");
                }
            }
                break;
            case '-': {
                std::cin >> buffer;
                ToLower(buffer);
                if (map[buffer] == 0) {
                    printf("NoSuchWord\n");
                } else {
                    map.erase(buffer);
                    printf("OK\n");
                }
                break;
            }
            default: {
                std::cin.putback(choice);
                std::cin >> buffer;
                ToLower(buffer);
                if (map[buffer] == 0) {
                    printf("NoSuchWord\n");
                } else {
                    printf("OK: %llu\n", map[buffer]);
                }
                break;
            }
        }

    }

    clock_t finish = clock();
    double time = (double) (finish - start) / CLOCKS_PER_SEC;
    printf("std::map time: %f\n", time);
    

    return 0;
}