#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <random>
#include <ctime>

int main (int argc, char const *argv[]) {

    std::size_t k = 100000000;
    std::mt19937_64 gen(time(0));
    std::uniform_int_distribution<int> uid(-2147483648, 2147483647);

    std::string filename = "downtest100kk";
    std::ofstream file(filename);
    std::vector<int64_t> vector(k);
    for (int i = 0; i < k; ++i) {
        vector[i] = uid(gen);
    }
    
    std::stable_sort(vector.rbegin(), vector.rend());

    if (file.is_open()) {
        file << k << std::endl;
        for (int i = 0; i < k; ++i) {
            file << vector[i] << std::endl;
       }
    }
    file.close();

    return 0;
}
