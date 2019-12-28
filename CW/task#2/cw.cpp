#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <chrono>


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
    r = std::max(l, r + 1);
    while (l < r ) {
        int64_t mid = (l + r) / 2;
        if (vec[mid] < key) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}


void MedianaSearch(int64_t key, std::vector<int64_t>& vec, int64_t l1, int64_t r1, int64_t l2, int64_t r2, std::vector<int64_t>& length) {

    uint64_t l = std::min(vec[l1], vec[l2]);
    uint64_t r = std::max(vec[r1], vec[r2]);
    int64_t infirst, insecond;
    int64_t mediana = (l + r) / 2;
    infirst = std::upper_bound(vec.begin() + l1, vec.begin() + r1, mediana) - vec.begin();
    insecond = std::upper_bound(vec.begin() + l2, vec.begin() + r2, mediana) - vec.begin();
     if (vec[infirst] > mediana && infirst != l1) {
         --infirst;
     } else if (vec[infirst] == mediana) {
         while (vec[infirst] == mediana && infirst < r1 ) {
             ++infirst;
         }
         if (vec[infirst] > mediana) {
             --infirst;
         }
     }
     if (vec[insecond] > mediana && insecond != l2) {
         --insecond;
     } else if (vec[insecond] == mediana) {
         while (vec[insecond] == mediana && insecond < r2) {
             ++insecond;
         }
         if (vec[insecond] > mediana) {
             --insecond;
         }
     }
     length.emplace_back(infirst - l1 + 1);//0
     length.emplace_back(infirst);//1
     length.emplace_back(insecond - l2 + 1);//2
     length.emplace_back(insecond);//3

    return ;
}


void Merge(std::vector<int64_t>& tmp, int64_t l1, int64_t r1, int64_t l2, int64_t r2, std::vector<int64_t>& res, int64_t lres, int64_t depth, bool limiter) {
    int64_t n1 = r1 - l1 + 1;
    int64_t n2 = r2 - l2 + 1;

    if (depth <= 0) {
        OrdinaryMerge(tmp, l1, r1, l2, r2, res, lres);
        return;
    }

    if (n1 < n2) {
        Merge(tmp, l2, r2, l1, r1, res, lres, depth, limiter);
    }
    if (n1 == 0) { return; }
    int64_t infirst, inffirst, insecond, total;
    if (limiter) {
        int64_t mid1 = (l1 + r1) / 2;
        int64_t mid2 = BinarySearch(tmp[mid1], tmp, l2, r2);
        total = lres + (mid1 - l1) + (mid2 - l2) ;

        res[total] = tmp[mid1];
        infirst = mid1 - 1 - l1;
        inffirst = mid1 - l1;
        insecond = mid2 - 1;
    } else {
        int64_t min, max;
        int64_t min_pos, max_pos;

        if (tmp[l1] > tmp[l2]) {
                min = tmp[l2];
                min_pos = l2;
        } else {
                min = tmp[l1];
                min_pos = l1;
        }
        if (tmp[r1] > tmp[r2]) {
                max = tmp[r1];
                max_pos = r1;
        } else {
                max = tmp[r2];
                max_pos = r2;
        }

        int64_t mediana = (min + max) / 2;
        int64_t answer;
        std::vector<int64_t> length;
        
        MedianaSearch(mediana, tmp, l1, r1, l2, r2, length);
        infirst = length[1];
        inffirst = length[1];
        insecond = length[3];

        total = length[0] + length[2] - 1;
        if (min_pos == l2) {
            answer = length[1] ;
        } else if (min_pos == l1) {
            answer = length[3];//element before answer are smaller
        }
        res[total] = tmp[answer];
    }
    --depth;


    std::thread tt1(Merge, std::ref(tmp), l1, l1 + infirst, l2, insecond , std::ref(res), lres, depth, limiter);
    std::thread tt2(Merge, std::ref(tmp),  l1 + inffirst + 1, r1, insecond + 1, r2, std::ref(res), total + 1 , depth, limiter);
    tt1.join();
    tt2.join();
}


void MergeSortForOne(std::vector<int64_t>& tmp, int64_t l1, int64_t r1, std::vector<int64_t>& res, int64_t depth, bool limiter) {

    if (depth <= 0) {
        OrdinaryMergeSort(tmp, l1, r1, res);
        return;
    }
    if (l1 >= r1) {
        return;
    } else {
        int64_t mid = (l1 + r1) / 2;

        --depth;
        std::thread t1(MergeSortForOne, std::ref(res), l1, mid, std::ref(tmp), depth, limiter);
        std::thread t2(MergeSortForOne, std::ref(res), mid + 1, r1, std::ref(tmp), depth, limiter);
        t1.join();
        t2.join();
        Merge(tmp, l1, mid, mid + 1, r1, res, l1, depth, limiter);
    }
}


void CountingSort(std::vector<int64_t>& array, int64_t n) {
    std::vector<int64_t>::iterator iter = std::max_element(array.begin(), array.end());
    int64_t index = std::distance(array.begin(), iter);
    int64_t k = array[index];
    std::vector<int64_t> second(n);
    std::vector<int64_t> c(k + 1, 0);
 
    for (int64_t i = 0; i < n; ++i) {
        ++c[array[i]];
    }
   
    for (int64_t i = 1; i < k + 1; ++i) {
       c[i] += c[i - 1];
    }
  
    for (int64_t i = n; i > 0; --i) {
        second[c[array[i - 1]] - 1] = array[i - 1];
        --c[array[i - 1]];
    }
    for(size_t i = 0; i < n; ++i) {
        array[i] = second[i];
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

    int64_t depth = log2(std::thread::hardware_concurrency());

    bool limiter = (depth == 2) ? false : true;
    //std::cout << depth;
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    OrdinaryMergeSort(tmp1_1, l1, r1, vec1);
//    try {
//        std::thread t1(MergeSortForOne, std::ref(tmp1_1), l1, r1, std::ref(vec1), depth, limiter);
//        t1.join();
//    } catch (std::runtime_error &ex) {
//        std::cerr << ex.what();
//    }
    //std::sort(vec1.begin(), vec1.end());
    
    end = std::chrono::system_clock::now();
    double elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout << "Working time: " << elapsed_milliseconds / 1000 << " seconds" << std::endl;
    
    bool flag = true;
    for (int i =0; i < vec1.size() - 1; ++i) {
        if (vec1[i+1]>=vec1[i]) { continue;}
        else {
            flag = false;
            break;
        }
    }
    if (flag) std::cout << "\nSORTED\n";
    else std::cout << "\nNOT SORTED\n";

    if (argc == 2) {
        std::string filename = "output";
        std::ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < vec1.size(); ++i) {
                file << i << "  " <<  vec1[i] << std::endl;
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

