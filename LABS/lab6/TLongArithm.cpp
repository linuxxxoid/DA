#include "TLongArithm.hpp"


TLongArithm::TLongArithm(std::string& is) {
    std::stringstream ss;

    if (is[0] == '0') {
        size_t zeros = 1;
        while (is[zeros] == '0') {
            ++zeros;
        }
        is = (zeros == (int) is.size()) ? "0" : is.substr(zeros);
    }
    
    digits.clear();
    
    for (int i = (int) is.size() - 1; i >= 0; i -= digLength) {
        int start = i - digLength + 1;
        start = (start < 0) ? 0 : start;
        int end = i - start + 1;
        ss << is.substr(start, end);
        int tmp = 0;
        ss >> tmp;
        digits.emplace_back(tmp);
        ss.clear();
    }
}


TLongArithm::TLongArithm(int num) {
    if (num < base) {
        digits.emplace_back(num);
    } else {
        while (num) {
            digits.emplace_back(num % base);
            num /= base;
        }
    }
}


std::ostream& operator<<(std::ostream& os, const TLongArithm& num) {
    for (auto i = num.digits.rbegin(); i != num.digits.rend(); ++i) {
        if (i != num.digits.rbegin()) {
            os << std::setfill('0') << std::setw(digLength);
        }
        os << *i;
    }
    return os;
}


bool operator==(const TLongArithm& num1, const TLongArithm& num2) {
    if (num1.digits.size() != num2.digits.size()) { return false; }
    for (size_t i = 0; i < num1.digits.size(); ++i) {
        if (num1.digits[i] != num2.digits[i]) { return false; }
    }
    return true;
}


bool operator<(const TLongArithm& num1, const TLongArithm& num2) {
    if (num1.digits.size() != num2.digits.size()) {
        return num1.digits.size() < num2.digits.size();
    }
    return std::lexicographical_compare(num1.digits.rbegin(), num1.digits.rend(), num2.digits.rbegin(), num2.digits.rend());
}


bool operator>(const TLongArithm& num1, const TLongArithm& num2) {
    if (num1.digits.size() != num2.digits.size()) {
        return num1.digits.size() > num2.digits.size();
    }
    return std::lexicographical_compare(num2.digits.rbegin(), num2.digits.rend(), num1.digits.rbegin(), num1.digits.rend());
}


bool operator<=(const TLongArithm& num1, const TLongArithm& num2) {
    return (num1 < num2) || (num1 == num2);
}


TLongArithm operator+(const TLongArithm& num1, const TLongArithm& num2) {
    TLongArithm res;
    bool remainder = 0;
    for (size_t i = 0; i < std::max(num1.digits.size(), num2.digits.size()) || remainder; ++i) {
        size_t first = i < (size_t) num1.digits.size() ? num1.digits[i] : 0;
        size_t second = i < (size_t) num2.digits.size() ? num2.digits[i] : 0;
        res.digits.emplace_back(first + second + remainder);
        remainder = res.digits.back() >= base;
        if (remainder) res.digits.back() -= base;
    }
    return res;
}


TLongArithm operator-(const TLongArithm& num1, const TLongArithm& num2) {
    TLongArithm res;
    bool remainder = 0;
    for (size_t i = 0; i < num1.digits.size(); ++i) {
        size_t first = (size_t) i < num1.digits.size() ? num1.digits[i] : 0;
        size_t second = (size_t) i < num2.digits.size() ? num2.digits[i] : 0;
        res.digits.emplace_back(first - second - remainder);
        remainder = res.digits.back() < 0;
        if (remainder) res.digits.back() += base;
    }
    res.RemoveZeros();
    return res;
}


TLongArithm operator*(const TLongArithm& num1, const TLongArithm& num2) {
    size_t num1Size = num1.digits.size();
    size_t num2Size = num2.digits.size();
    TLongArithm res;
    res.digits.resize(num1Size + num2Size);

    for (size_t i = 0; i < num1Size; ++i) {
        int remainder = 0;
        for (size_t j = 0; j < num2Size || remainder; ++j) {
            size_t second = j < num2Size ? num2.digits[j] : 0;
            res.digits[i + j] += num1.digits[i] * second + remainder;
            remainder = res.digits[i + j] / base;
            res.digits[i + j] -= remainder * base;
        }
    }
    res.RemoveZeros();
    return res;
}


TLongArithm operator/(const TLongArithm& num1, const TLongArithm& num2) {
    
    TLongArithm result, current;
    size_t num1Size = num1.digits.size();
    result.digits.resize(num1Size);
    for (int i = (int) num1Size - 1; i >= 0; --i) {
        current.digits.insert(current.digits.begin(), num1.digits[i]);
        if (!current.digits.back()) current.digits.pop_back();
        
        int digit = 0, low = 0, high = base;
        
        while (low <= high) {
            int middle = (low + high) / 2;
            TLongArithm tmp(num2 * TLongArithm(middle));
            if (tmp <= current) {
                digit = middle;
                low = middle + 1;
            } else {
                high = middle - 1;
            }
        }
        result.digits[i] = digit;
        current = current - num2 * TLongArithm(digit);
    }
    
    result.RemoveZeros();
    
    return result;
}


TLongArithm TLongArithm::Power(TLongArithm& num1, TLongArithm& power) {
    TLongArithm res(1);
    while (power) {
        if (power.unEven()) {
            res = res * num1;
        }
        num1 = num1 * num1;
        power = power / TLongArithm(2);
    }
    return res;
}


void TLongArithm::RemoveZeros(void) {
    if (digits.size() == 1) { return; }
    size_t cnt = 0;
    for (int i = (int) digits.size() - 1; i >= 0; --i) {
        if (digits[i] != 0) { break; }
        ++cnt;
    }
    digits.resize(digits.size() - cnt);
    if (digits.empty()) digits.emplace_back(0);
}


bool TLongArithm::unEven() const {
    return digits[0] & 1;
}

TLongArithm::operator bool() const {
    if ((digits.size() > 1) || (digits[0] > 0)) return true;
    else return false;
}
