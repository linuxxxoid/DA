#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <random>
#include <ctime>

int main (int argc, char const *argv[]) {

    std::size_t k = 150000;
    std::mt19937_64 gen(time(0));
    std::uniform_int_distribution<> uid(-9223372036854775808, 9223372036854775807);

    std::string filename = "test";
    std::ofstream file(filename);
    if (file.is_open()) {
        file << k << std::endl;
        for (int i = 0; i < k; ++i) {
            file << uid(gen) << std::endl;
       }
    }
    file.close();

    return 0;
}
