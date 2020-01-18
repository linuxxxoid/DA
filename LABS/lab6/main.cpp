#include <iostream>
#include <ctime>
#include "TLongArithm.hpp"



int main(int argc, const char * argv[]) {
    clock_t start, end;
    std::string str1, str2;
    char operation;
    start = clock();

    while (std::cin >> str1 >> str2 >> operation) {
        TLongArithm num1(str1);
        TLongArithm num2(str2);
        if (operation == '+') {
            std::cout << num1 + num2 << "\n";
            continue;
        }
        if (operation == '-') {
            if (num2 > num1) {
                std::cout << "Error\n";
            } else {
                std::cout << num1 - num2 << "\n";
            }
            continue;
        }
        if (operation == '*') {
            std::cout << num1 * num2 << std::endl;
            continue;
        }
        if (operation == '/') {
            if (num2 == TLongArithm(0)) {
                std::cout << "Error\n";
            } else {
                std::cout << num1 / num2 << "\n";
            }
            continue;
        }
        if (operation == '^') {
            if (num1 == TLongArithm(0)) {
                if (num2 == TLongArithm(0))
                    std::cout << "Error\n";
                else
                    std::cout << "0\n";
            } else if (num1 == TLongArithm(1)) {
                std::cout << "1\n";
            }
            else {
                std::cout << num1.Power(num1, num2) << "\n";
            }
            continue;
        }
        if (operation == '<') {
            std::cout << ((num1 < num2) ? "true" : "false") << "\n";
            continue;
        }
        if (operation == '>') {
            std::cout << ((num1 > num2) ? "true" : "false") << "\n";
            continue;
        }
        if (operation == '=') {
            std::cout << ((num1 == num2) ? "true" : "false") << "\n";
            continue;
        }
    }
    end = clock();
    std::cout << "C++ time: " << (double)(end - start) / CLOCKS_PER_SEC << " sec." << std::endl;
    return 0;
}
