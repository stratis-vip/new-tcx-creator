#include "bignums.hpp"

// #include <iostream>

long getValue(const string part, const bool neg) {
  long aValue = strToI(part);
  if (neg)
    aValue *= -1;
  return aValue;
}

string addFPart(const BigNum a, const BigNum b) {
  std::ostringstream os{};
  int aValue, bValue;
  aValue = getValue(a.fPart(), a.isNegative());
  bValue = getValue(b.fPart(), b.isNegative());
  os << aValue + bValue;
  return os.str();
}

string addIPart(const BigNum a, const BigNum b) {
  std::ostringstream os{};
  int aValue, bValue;
  aValue = getValue(a.iPart(), a.isNegative());
  bValue = getValue(b.iPart(), b.isNegative());
  os << aValue + bValue;
  return os.str();
}

BigNum BigNum::operator+(const BigNum &vl) {
  BigNum retVal;
  BigNum b = vl;

  //υπολογίζω την τάξη μεγέθους για το κρατούμενο
  const size_t order = b.order() >= this->order() ? b.order() : this->order();
  if (order > b.order())
    for (auto i = b._fractionalPart.size(); i != order; i++)
      b._fractionalPart.push_back('0');
  if (order > this->order())
    for (auto i = _fractionalPart.size(); i != order; i++)
      _fractionalPart.push_back('0');

  retVal._fractionalPart = addFPart(*this, vl);
  retVal.integerPart = addIPart(*this, vl);
  size_t kratoumeno = tenPow(order);
  if (strToI(retVal._fractionalPart) > kratoumeno) {
    retVal._fractionalPart =
        std::to_string(strToI(retVal._fractionalPart) - kratoumeno);
    retVal.integerPart = std::to_string(strToI(retVal.integerPart) + 1);
  }
  return retVal;
}

string BigNum::value() const {
  std::ostringstream os{""};
  if (_isNegative)
    os << '-';
  os << integerPart << '.' << _fractionalPart;
  return os.str();
}

BigNum getValueFromString(string a, const char dot) {
  BigNum rVal{};
  string integerPart{"0"};
  string fractionalPart{"0"};
  bool isNegative = isNegativeString(a);
  if (isNegative)
    a.erase(0, 1);

  std::vector<string> parts{};
  size_t dotPos = a.find(dot);
  do {
    string buffer = a.substr(0, dotPos);
    if (isNumeric(buffer))
      parts.push_back(a.substr(0, dotPos));
    else {
      parts.push_back("");
    }

    a.erase(0, dotPos + 1);
    dotPos = a.find(dot);

  } while (dotPos != string::npos);
  if (a.size() > 0)
    parts.push_back(a);

  switch (parts.size()) {
  case 1:
    integerPart = parts[0];
    break;
  case 2:
    integerPart = parts[0];
    fractionalPart = parts[1];
    break;
  default:
    fractionalPart = integerPart = "0";
  }
  return BigNum{integerPart, fractionalPart, isNegative};
}
