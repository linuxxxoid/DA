#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <utility>



int64_t ConvertStringToInt64(const std::string& str) {
   if (str.size() == 0 ) {
       throw std::runtime_error("empty argument");
   }
   int64_t number = 0;
   size_t i = 0;
   char sign;
   if (str[0] == '-') {
       ++i;
       sign = str[0];
   }
   std::size_t size = str.size();
   while (i < size) {
      if (str[i] < '0' || str[i] > '9') {
          throw std::runtime_error("invalid argument");
      }
      number = number * 10 + str[i] - '0';
      ++i;
   }
   return sign == '-' ? -number : number;
}


bool ReadingFromFile(std::ifstream& file, std::vector<int64_t>& vec1, std::vector<int64_t>& vec2) {
    if (file.is_open() && file.peek() != EOF) {
      char sym;
      int64_t number = 0;
      std::string buffer;
      std::cout << "READ\n";
      while (1) {
          file.read(&sym, 1);
          if (sym == '\n') {
              if (!buffer.empty()) {
                  number = ConvertStringToInt64(buffer);
                  vec1.emplace_back(number);
                  buffer.clear();
              }
              break;
          }
          if ((sym == ' ') || (file.eof())) {
              if (!buffer.empty()) {
                  number = ConvertStringToInt64(buffer);
                  vec1.emplace_back(number);
                  buffer.clear();
              }
          } else {
              buffer += sym;
          }
      }
      while (1) {
          file.read(&sym, 1);
          if (sym == '\n' || file.eof()) {
              if (!buffer.empty()) {
                  number = ConvertStringToInt64(buffer);
                  vec2.emplace_back(number);
                  buffer.clear();

              }
              break;
          }
          if ((sym == ' ') || file.eof()) {
              if (!buffer.empty()) {
                  number = ConvertStringToInt64(buffer);
                  vec2.emplace_back(number);
                  buffer.clear();
              }
          } else {
              buffer += sym;
          }
      }
      file.close();
      return true;
    } else {
      return false;
    }
    return true;
}


void Reading(std::vector<int64_t>& a, std::vector<int64_t>& b) {
    int64_t number = 0;
    bool flag = true;
    while (std::cin >> number) {
        a.emplace_back(number);
        if (std::cin.get() == '\n') { break; }
    }
    while (std::cin >> number) {
         b.emplace_back(number);
         if (std::cin.get() == '\n') { break; }
    }
    return;
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


void Merge(std::vector<int64_t>& tmp, int64_t l1, int64_t r1, int64_t l2, int64_t r2, std::vector<int64_t>& res, int64_t lres) {
    int64_t n1 = r1 - l1 + 1;
    int64_t n2 = r2 - l2 + 1;
    if (n1 < n2) {
        Merge(tmp, l2, r2, l1, r1, res, lres);
    }
    if (n1 == 0) { return; }
    int64_t mid1 = (l1 + r1) / 2;
    int64_t mid2 = BinarySearch(tmp[mid1], tmp, l2, r2);
    int64_t midres = lres + (mid1 - l1) + (mid2 - l2) ;

    res[midres] = tmp[mid1];

    std::thread tt1(Merge, std::ref(tmp), l1, mid1 - 1, l2, mid2 - 1, std::ref(res), lres);
    std::thread tt2(Merge, std::ref(tmp), mid1 + 1, r1, mid2, r2, std::ref(res), midres + 1);
    tt1.join();
    tt2.join();
    //Merge(tmp, l1, mid1 - 1, l2, mid2 - 1, res, lres);
    //Merge(tmp, mid1 + 1, r1, mid2, r2, res, midres + 1);
}


void MergeSortForOne(std::vector<int64_t>& tmp, int64_t l1, int64_t r1, std::vector<int64_t>& res, int64_t lres) {
    if (l1 >= r1) { return; }
    if ((r1 - l1 + 1) == 1) {
        res[lres] = tmp[l1];
        return;
    } else {
        int mid = (l1 + r1) / 2;
        int mid2 = mid - l1 + 1;

        std::thread t1(MergeSortForOne, std::ref(res), l1, mid, std::ref(tmp), 0);
        //MergeSortForOne(res, l1, mid, tmp, 0);
        std::thread t2(MergeSortForOne, std::ref(res), mid + 1, r1, std::ref(tmp), mid2);
        //MergeSortForOne(res, mid + 1, r1, tmp, mid2);
        t1.join();
        t2.join();
        Merge(tmp, l1, mid, mid + 1, r1, res, l1);
    }
}


int main (int argc, char const *argv[]) {
    std::vector<int64_t> vec1;
    std::vector<int64_t> vec2;
    int64_t number = 0;
    std::cout << argc << '\n';
    try {
        if (argc == 2) {
            std::string filename = argv[1];
            std::ifstream file(filename);

            if (!ReadingFromFile(file, vec1, vec2)) {
                Reading(vec1, vec2);
            }
        } else {
            Reading(vec1, vec2);
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    for (int i = 0; i < vec1.size(); ++i) {
      std::cout << vec1[i] << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < vec2.size(); ++i) {
      std::cout << vec2[i] << ' ';
    }
    std::cout << '\n';

    int64_t l1 = 0, r1 = vec1.size() - 1;
    int64_t l2 = 0, r2 = vec2.size() - 1;

    std::vector<int64_t> tmp1_1(vec1.size());
    tmp1_1.assign(vec1.begin(), vec1.end());

    std::vector<int64_t> tmp2_1(vec2.size());
    tmp2_1.assign(vec2.begin(), vec2.end());

    //MergeSortForOne(tmp1_1, l1, r1, vec1, 0);
    //MergeSortForOne(tmp2_1, l2, r2, vec2, 0);
    std::thread t1(MergeSortForOne, std::ref(tmp1_1), l1, r1, std::ref(vec1), 0);
    std::thread t2(MergeSortForOne, std::ref(tmp2_1), l2, r2, std::ref(vec2), 0);
    t1.join();
    t2.join();

    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    tmp1_1.clear();
    tmp1_1.assign(vec1.begin(), vec1.end());
    l1 = 0, r1 = vec1.size() - 1;
    MergeSortForOne(tmp1_1, l1, r1, vec1, 0);

    if (argc == 2) {
        std::string filename = argv[1];
        std::ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < vec1.size(); ++i) {
                file << vec1[i] << ' ';
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
