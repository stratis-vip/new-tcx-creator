#ifndef BIGNUMS_HPP
#define BIGNUMS_HPP

#include <string>
using std::string;

size_t strToI(const std::string);
size_t intPow(const size_t, const size_t);
size_t tenPow(const size_t);
bool isNumeric(const string, const char dot = '.');

class BigNum
{
public:
    BigNum()
    {
        integerPart = "";
        fractionalPart = "";
        isNegative = false;
    };
    BigNum(const string iPart, const string fPart, const bool isNeg = false) : integerPart(iPart),
                                                                               fractionalPart(fPart), isNegative(isNeg){};
    BigNum(const int iP, const int fP, const bool isNeg = false):integerPart(std::to_string(iP)),
                                                                               fractionalPart(std::to_string(fP)), isNegative(isNeg){};
    BigNum(const BigNum &b)
    {
        integerPart = b.integerPart;
        fractionalPart = b.fractionalPart;
        isNegative = b.isNegative;
    }

    string value() const;

    void setDotCharacter(const char dot)
    {
        dotCharacter = dot;
    }

    BigNum operator+(const BigNum &val);

private:
    size_t intValue() const { return strToI(integerPart); }
    size_t fracValue() const { return strToI(fractionalPart); }
    string integerPart;
    string fractionalPart;
    bool isNegative{false};
    char dotCharacter{'.'};
};

BigNum getValueFromString(string, const char dot = '.');

#endif