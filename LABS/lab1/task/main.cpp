#include <iostream>
#include "vector.h"


int main () {
    TMyVector<TKeyValue> vec;
    TKeyValue data;
    size_t maxkey = 0;
    VecCreate(vec, 0);
    
    while (std::cin >> data.key >> data.value) {
        if (strlen(data.key) == (KEY_SIZE - 1) && data.value + 1 > MIN && data.value <= MAX) {
            if (strtoul(data.key, NULL, 10) > maxkey) {
                maxkey = strtoul(data.key, NULL, 10);
            }
            VecPushBack(vec, data.key, data.value);
        }
        else return 1;
    }
    
    CountingSort(vec, maxkey);
    
    for (size_t i = 0; i < vec.size; ++i) {
        std::cout << vec.vector[i].key << "\t" << vec.vector[i].value <<  "\n";
    }
    
    VecDestroy(vec);
    return 0;
}
