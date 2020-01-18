#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <unordered_set>
#include <iomanip>

////const uint16_t MAX = 100;
////uint64_t Palindrome(std::string&);
////int binarySearch(std::string& str, int center, int shift);
////
////int main(int argc, const char * argv[]) {
////    std::string str;
////    std::cin >> str;
////    clock_t start = clock();
////    uint64_t count = 0;
////    count = Palindrome(str);
////    std::cout << count << std::endl;
////    clock_t finish = clock();
////    double time = (double) (finish - start) / CLOCKS_PER_SEC;
////    printf("Naive time: %f sec\n", time);
////    return 0;
////}
////
////int binarySearch(std::string& str, int center, int shift) {
////    //shift = 0 при поиске палиндрома нечётной длины, иначе shift = 1
////    int l = -1;
////    int r = std::min((long)center, (long)str.size() - center + shift);
////    int m = 0;
////   // std::hash<std::string> hash_fn;
////    size_t hash1, hash2;
////    std::string rev = str;
////
////    while (r - l != 1) {
////        m = l + (r - l) / 2;
////        //reversed_hash возвращает хэш развернутой строки s
////        std::string s1 = str.substr(center - m, center);
////        std::string s0 = rev.substr(center + shift, center + shift + m);
////        //std::string s2 = rev.substr(center + shift, center + shift + m);
////        std::reverse(s0.begin(), s0.end());
////        hash1 = std::hash<std::string>{}(s1);
////        hash2 = std::hash<std::string>{}(s0);
////        if (hash1 == hash2) l = m;
////        else r = m;
////    }
////    return r;
////}
////
////uint64_t Palindrome(std::string& str) {
////    uint64_t ans = 0;
////    int sizeStr = (int) str.size();
////    if (!sizeStr) return 0;
////
////    uint64_t plnd[MAX][MAX];
////    for (int i = 0; i < sizeStr; ++i) {
////        ans += binarySearch(str, i, 0) + binarySearch(str, i, 1);
////    }
////    return ans;
////}
//int oddCount(std::string & str)
//{
//    int cntPalindromes = 0;
//
//    for(int indMiddle = 0; indMiddle < str.length(); ++indMiddle)
//    {
//        int leftBorder = indMiddle - 1, rightBorder = indMiddle + 1;
//        while(leftBorder >= 0 && rightBorder < str.length() && str[leftBorder] == str[rightBorder])
//        {
//            ++cntPalindromes;
//            --leftBorder;
//            ++rightBorder;
//        }
//    }
//    return cntPalindromes;
//}
//
//int evenCount(std::string& str)
//{
//    int cntPalindromes = 0;
//    for(int indMiddle = 0; indMiddle < (int) str.length(); ++indMiddle)
//    {
//        int leftBorder = indMiddle, rightBorder = indMiddle + 1;
//        while(leftBorder >= 0 && rightBorder < str.length() && str[leftBorder] == str[rightBorder])
//        {
//            ++cntPalindromes;
//            --leftBorder;
//            ++rightBorder;
//        }
//    }
//    return cntPalindromes;
//}
//
//
//
//
//
//int main(void) {
//    std::string str;
//    std::cin >> str;
//    int cnt1 = evenCount(str);
//    int cnt2 = oddCount(str);
//    std::cout << cnt1 + cnt2 << std::endl;
//    return 0;
//}
void expandPalindromes(int& result, std::string& s, int i, int j) {
    while (i >= 0 && j < s.length() && s[i] == s[j]) {
        ++result;
        i--; j++;
    }
}

int palindromes(std::string& input) {
    int result = 0;
    for (int i = 0; i < input.length(); i++) {
        // expanding even length palindromes:
        expandPalindromes(result,input,i,i+1);
        // expanding odd length palindromes:
        expandPalindromes(result,input,i,i);
    }
    return result;
}



int main(void) {
    std::string str;
    std::cin >> str;
    int cnt = palindromes(str);
    std::cout << cnt << std::endl;
    return 0;
}
