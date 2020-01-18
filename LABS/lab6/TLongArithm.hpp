#ifndef TLongArithm_hpp
#define TLongArithm_hpp

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>


const int base = 10000;
const int digLength = 4;

class TLongArithm {
public:
    TLongArithm() {};
    TLongArithm(std::string&);
    TLongArithm(int);
    ~TLongArithm() {};
        
    friend bool operator==(const TLongArithm&, const TLongArithm&);
    friend bool operator<(const TLongArithm&, const TLongArithm&);
    friend bool operator>(const TLongArithm&, const TLongArithm&);
    friend bool operator<=(const TLongArithm&, const TLongArithm&);
    
    operator bool() const;
    
    friend TLongArithm operator+(const TLongArithm&, const TLongArithm&);
    friend TLongArithm operator-(const TLongArithm&, const TLongArithm&);
    friend TLongArithm operator*(const TLongArithm&, const TLongArithm&);
    friend TLongArithm operator/(const TLongArithm&, const TLongArithm&);

    
    TLongArithm Power(TLongArithm&, TLongArithm&);
    bool unEven() const;
    
    friend std::ostream& operator<<(std::ostream&, const TLongArithm&);

private:
    void RemoveZeros(void);
    std::vector<int> digits;
};

#endif /* TLongArithm_hpp */
