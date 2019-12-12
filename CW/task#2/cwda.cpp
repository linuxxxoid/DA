
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <utility>

std::mutex mtx_;

bool ReadFile(std::ifstream& file, std::vector<int64_t>& vec1) {
    if (file.is_open() && file.peek() != EOF) {
        int64_t number;
        int64_t size = 1;
        bool flag = true;
        while (size) {
            file >> number;
            if (file.eof()) { break; }
            if (flag) {
                size = number;
                flag = false;
            } else {
                vec1.emplace_back(number);
                --size;
            }
        }
    } else {
        return false;
    }

    file.close();
    return true;
}

void Reader(std::vector<int64_t>& vec1) {
    int64_t number, size;
    std::cin >> size;
    while (size) {
        std::cin >> number;
        vec1.emplace_back(number);
        --size;
    }
}

void OrdinaryMerge(std::vector<int64_t>& tmp, int64_t l1, int64_t r1, int64_t l2, int64_t r2, std::vector<int64_t>& res, int64_t lres) {
    int64_t rres = lres + (r1 - l1) + (r2 - l2) + 1;
    while (lres <= rres) {
        if (l1 > r1) {
            res[lres] = tmp[l2++];
        } else if (l2 > r2) {
            res[lres] = tmp[l1++];
        } else {
            res[lres] = (tmp[l1] < tmp[l2]) ? tmp[l1++] : tmp[l2++];
        }
        ++lres;
    }
}


void OrdinaryMergeSort(std::vector<int64_t>& tmp, int64_t l1, int64_t r1, std::vector<int64_t>& res) {
       if (l1 >= r1) { return; }

       int64_t mid = (l1 + r1) / 2;

       OrdinaryMergeSort(res, l1, mid, tmp);
       OrdinaryMergeSort(res, mid + 1, r1, tmp);

       OrdinaryMerge(tmp, l1, mid, mid + 1, r1, res, l1);

   }


int64_t BinarySearch(int64_t key, std::vector<int64_t>& vec, int64_t l, int64_t r) {
    std::unique_lock<std::mutex> locker(mtx_);
    r = std::max(l, r + 1);
    while (l < r ) {
        int64_t mid = (l + r) / 2;
        if (vec[mid] < key) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    locker.unlock();
    return l;
}


void Merge(std::vector<int64_t>& tmp, int64_t l1, int64_t r1, int64_t l2, int64_t r2, std::vector<int64_t>& res, int64_t lres, int64_t depth) {
    int64_t n1 = r1 - l1 + 1;
    int64_t n2 = r2 - l2 + 1;
    if (depth <= 0) {
        OrdinaryMerge(tmp, l1, r1, l2, r2, res, lres);
        return;
    }
    if (n1 < n2) {
        Merge(tmp, l2, r2, l1, r1, res, lres, depth);
    }
    if (n1 == 0) { return; }
    int64_t mid1 = (l1 + r1) / 2;
    int64_t mid2 = BinarySearch(tmp[mid1], tmp, l2, r2);
    int64_t midres = lres + (mid1 - l1) + (mid2 - l2) ;

    std::unique_lock<std::mutex> locker(mtx_);
    res[midres] = tmp[mid1];
    locker.unlock();

    --depth;
    std::thread tt1(Merge, std::ref(tmp), l1, mid1 - 1, l2, mid2 - 1, std::ref(res), lres, depth);
    std::thread tt2(Merge, std::ref(tmp), mid1 + 1, r1, mid2, r2, std::ref(res), midres + 1, depth);
    tt1.join();
    tt2.join();
}


void MergeSortForOne(std::vector<int64_t>& tmp, int64_t l1, int64_t r1, std::vector<int64_t>& res, int64_t depth) {
    if (depth <= 0) {
        OrdinaryMergeSort(tmp, l1, r1, res);
        return;
    }
    if (l1 >= r1) {
        return;
    } else {
        int64_t mid = (l1 + r1) / 2;

        --depth;
        std::thread t1(MergeSortForOne, std::ref(res), l1, mid, std::ref(tmp), depth);
        std::thread t2(MergeSortForOne, std::ref(res), mid + 1, r1, std::ref(tmp), depth);
        t1.join();
        t2.join();
        Merge(tmp, l1, mid, mid + 1, r1, res, l1, depth);
    }
}


int main (int argc, char const *argv[]) {
    std::vector<int64_t> vec1;
    try {
        if (argc == 2) {
            std::string filename = argv[1];
            std::ifstream file(filename);

            if (!ReadFile(file, vec1)) {
                Reader(vec1);
            }
        } else {
            Reader(vec1);
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    int64_t l1 = 0, r1 = vec1.size() - 1;

    std::vector<int64_t> tmp1_1(vec1.size());
    tmp1_1.assign(vec1.begin(), vec1.end());

    int64_t depth = std::thread::hardware_concurrency();

    try {
        std::thread t1(MergeSortForOne, std::ref(tmp1_1), l1, r1, std::ref(vec1), depth);
        t1.join();
    } catch (std::runtime_error &ex) {
        std::cerr << ex.what();
    }


    if (argc == 2) {
        std::string filename = "output";
        std::ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < vec1.size(); ++i) {
                file << vec1[i] << std::endl;
          }
          file << '\n';
        }
        file.close();
    } else {
        for (int i = 0; i < vec1.size(); ++i) {
            std::cout << vec1[i] << ' ';
        }
        std::cout << "\n";
    }
    return 0;
}
