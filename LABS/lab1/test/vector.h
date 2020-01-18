#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cstdint>

const int KEY_SIZE = 7;
//const long long MIN = -1;
const unsigned long long MAX = 18446744073709551615U;

typedef unsigned long long TVal;
typedef char TKey;

struct TKeyValue {
    TVal value;
    TKey key[KEY_SIZE];
};

template <typename T>
struct TMyVector {
    T *vector;
    size_t size;
    size_t capacity;
};

template <typename T>
void VecCreate(TMyVector<T> &vec, size_t size);

template <typename T>
void VecRead(TMyVector<T> &vec, TKeyValue data, size_t maxkey);

template <typename T>
void VecPushBack(TMyVector<T> &vec, TKey* k, TVal val);

template <typename T>
void VecPrint(TMyVector<T> &vec);

template <typename T>
void VecDestroy(TMyVector<T> &vec);

void CountingSort(TMyVector<TKeyValue> &v, size_t max);


template <typename T>
void VecCreate(TMyVector<T> &vec, size_t size) {
    vec.vector = new T[size + 1];
    vec.size = size;
    vec.capacity = size + 1;
}

template <typename T>
void VecPushBack(TMyVector<T> &vec, TKey* k, TVal val) {
    if (vec.size == vec.capacity) {
        vec.capacity *= 2;
        T *vect = new T[vec.capacity];
        for (int i = 0; i < vec.size; ++i)
            vect[i] = vec.vector[i];
        delete[] vec.vector;
        vec.vector = vect;
    }
    strcpy(vec.vector[vec.size].key, k);
    vec.vector[vec.size].value = val;
    ++vec.size;
}

template <typename T>
void VecDestroy(TMyVector<T> &vec) {
    delete[] vec.vector;
    vec.vector = NULL;
    vec.size = 0;
    vec.capacity = 0;
}

void CountingSort(TMyVector<TKeyValue> &v, size_t max) {
    if (v.size < 2) {return;}
    TMyVector<size_t> t;
    TMyVector<TKeyValue> v2;
    VecCreate(v2, v.size);
    VecCreate(t, max + 1);
    
    for (size_t i = 0; i < max + 1; ++i)
        t.vector[i] = 0;
    for (int i = 0; i < v.size ; ++i)
        ++t.vector[strtoul(v.vector[i].key, NULL, 10)];
    for (size_t i = 1; i < max + 1; ++i)
        t.vector[i] += t.vector[i - 1];
    for (size_t i = v.size; i > 0; --i) {
        v2.vector[t.vector[strtoul(v.vector[i - 1].key, NULL, 10)] - 1] = v.vector[i - 1];
        --t.vector[strtoul(v.vector[i - 1].key, NULL, 10)];
    }
    for(size_t i = 0; i < v.size; ++i)
        v.vector[i] = v2.vector[i];
    
    VecDestroy(v2);
    VecDestroy(t);
}

#endif
