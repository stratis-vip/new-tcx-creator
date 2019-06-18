#ifndef BIGNUMS_HPP
#define BIGNUMS_HPP

#include "stdfuncs.hpp"
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using std::string;

class BigNum {
public:
  BigNum() : _integerPart(""), _fractionalPart(""), _isNegative(false) {}

  BigNum(const string iPart, const string fPart, const bool isNeg = false)
      : _integerPart(iPart), _fractionalPart(fPart), _isNegative(isNeg) {}

  BigNum(const int iP, const int fP) : _fractionalPart(std::to_string(fP)) {
    if (iP < 0) {
      _isNegative = true;
      _integerPart = std::to_string(-iP);
    } else {
      _integerPart = std::to_string(iP);
      _isNegative = false;
    }
  }

  BigNum(const BigNum &b)
      : _integerPart(b._integerPart), _fractionalPart(b._fractionalPart),
        _isNegative(b._isNegative) {}

  string value() const;

  void setDotCharacter(const char dot) { dotCharacter = dot; }

  BigNum operator+(const BigNum &val);
  bool operator>(const BigNum &val);

  bool isNegative() const { return _isNegative; }

  string iPart() const { return _integerPart; }

  string fPart() const { return _fractionalPart; }

  size_t order() const { return _fractionalPart.size(); }

private:
  size_t intValue() const { return strToI(_integerPart); }

  size_t fracValue() const { return strToI(_fractionalPart); }

  string _integerPart;

  string _fractionalPart;

  bool _isNegative{false};

  char dotCharacter{'.'};
};

BigNum getValueFromString(string, const char dot = '.');

#endif
