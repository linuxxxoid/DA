#include <iostream>
#include <fstream>
#include "vector.h"


int main () {
    TMyVector<TKeyValue> vec;
    TKeyValue data;
    size_t maxkey = 0;
    
    VecCreate(vec, 0);

    std::ofstream fout("testsort1.txt", std::ios_base::out | std::ios_base::trunc);
    if (!fout.is_open()) {
        std::cout << "Error!\n";
        return 1; 
    }
    srand(time(0));
    for (size_t i = 0; i < 10000; ++i) {
        data.value = 1 + rand() % MAX;
        for (int j = 0; j < KEY_SIZE - 1; ++j) {
            data.key[j] = rand() % 10 + '0';
        }

        if (strtoul(data.key, NULL, 10) > maxkey)
            maxkey = strtoul(data.key, NULL, 10);
        VecPushBack(vec, data.key, data.value);
    }
    
    //CountingSort(vec, maxkey);
    //std::cout<<vec.size<<std::endl;
    for (size_t i = vec.size - 1; i >= 1; --i){
        fout << vec.vector[i].key << "\t" << vec.vector[i].value << std::endl;
    }
    fout << vec.vector[0].key << "\t" << vec.vector[0].value << std::endl;
    VecDestroy(vec);
    fout.close();
    
    return 0;
}

