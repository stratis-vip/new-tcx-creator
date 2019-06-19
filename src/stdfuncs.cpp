#include "stdfuncs.hpp"

size_t strToI(const std::string &a) {
  size_t rVal{0};
  for (size_t i = 0; i != a.size(); i++) {
    if (isdigit(a[i])) {
      size_t ord = static_cast<size_t>(a[i]) - 48UL;
      size_t mplyer = (a.size() - (i + 1));
      if (mplyer == 0)
        rVal += ord;
      else
        rVal += ord * tenPow(mplyer);
    } else {
      throw std::invalid_argument("Must be a digit");
    }
  }
  return rVal;
}

size_t intPow(const size_t base, const size_t toPower) {
  size_t rVal = static_cast<int>(pow(base, toPower));
  return rVal;
}

size_t tenPow(const size_t toPower) { return intPow(10, toPower); }

bool isNumeric(const string a, const char dot) {
  string temp(a);
  if (temp.size() == 0)
    return false;
  size_t hasDot{0};
  if (isNegativeString(temp))
    temp.erase(0, 1);
  for (auto ch : temp) {
    if (ch == dot) {
      hasDot++;
      if (hasDot > 1)
        return false;
    } else if (!isdigit(ch))
      return false;
  }
  return true;
}

bool isNegativeString(const string &a) {
  bool rVal = false;
  if (a[0] == '-') {
    rVal = true;
  }
  if (a[0] == '+') {
    rVal = false;
  }
  return rVal;
}

string trimLeftZero(const string &a) {
  string rVal{};
  size_t start{0};
  char prosimo = ' ';
  if (isNumeric(a)) {
    if (a[0] == '-' || a[0] == '+') {
      prosimo = a[0];
      start = 1;
    }
    while (a[start] == '0') {
      start++;
    }
    if (start == a.size())
      rVal = "0";
    else
      rVal = a.substr(start);
    if (prosimo != ' ')
      rVal = a[0] + rVal;
  } else {
    throw std::invalid_argument("invalid number!");
  }
  return rVal;
}

string trimRightZero(const string &a) {
  string rVal{};
  int start = a.size() - 1;
  if (isNumeric(a)) {
    while (start >= 0 && a[start] == '0') {
      start--;
    }
    start++;
    if (start == 0)
      rVal = "0";
    else
      rVal = a.substr(0, start);
  } else {
    throw std::invalid_argument("invalid number!");
  }
  return rVal;
}

void fillRightZero(string &a, size_t order) {
  if (order > a.size())
    for (auto i = a.size(); i != order; i++)
      a.push_back('0');
}

void fillLeftZero(string &a, size_t order) {
  if (order > a.size()) {
    size_t topValue = order - a.size();
    for (size_t i = 0; i != topValue; i++)
      a = '0' + a;
  }
}

string stringAdd(const string &a, const string &b) {
  bool negativeValue = false;
  string aTemp(a);
  string bTemp(b);
  makePositive(aTemp);
  makePositive(bTemp);
  string rVal1{};

  if (stringBigger(bTemp, aTemp) && isNegativeString(b)) {
    bTemp = b;
    aTemp = a;
    rVal1 = stringAdd(alterProsimo(bTemp), alterProsimo(aTemp));
    makeNegative(rVal1);
    return rVal1;
  }

  if (stringBigger(aTemp, bTemp) && isNegativeString(a)) {
    bTemp = b;
    aTemp = a;
    rVal1 = stringAdd(alterProsimo(aTemp), alterProsimo(bTemp));
    makeNegative(rVal1);
    return rVal1;
  }

  // calculate order
  aTemp = a;
  bool aNeg = isNegativeString(aTemp);
  if (aNeg)
    aTemp.erase(0, 1);

  bTemp = b;
  bool bNeg = isNegativeString(bTemp);
  if (bNeg)
    bTemp.erase(0, 1);

  if (aNeg && bNeg) {
    negativeValue = true;
    aNeg = bNeg = false;
  }

  size_t order = prepare2Strings(aTemp, bTemp);

  signed char kratoumeno{0};
  unsigned char ipolipoumeno{0};
  string rVal(order + 1, '0');

  while (order > 0) {
    size_t i = order - 1;
    signed char aC = aTemp[i] - 48;
    signed char bC = bTemp[i] - 48;
    if (aNeg)
      aC *= -1;
    if (bNeg)
      bC *= -1;

    // signed char sum = aC + bC;
    signed char sum = aC + bC - ipolipoumeno;

    if (sum > 9) {
      sum -= 10;
      rVal[i + 1] = (sum + kratoumeno) + 48;
      kratoumeno = 1;
    } else {
      if (sum == 9 && kratoumeno == 1) {
        rVal[i + 1] = '0';
        kratoumeno = 1;
      } else {
        if (sum < 0) {
          sum = aC + bC + 10 - ipolipoumeno;
          ipolipoumeno = 1;
          // sum = aC + bC + 10;
        } else {
          ipolipoumeno = 0;
        }
        rVal[i + 1] = (sum + kratoumeno) + 48;
        kratoumeno = 0;
      }
    }
    order--;
  }
  if (kratoumeno > 0) {
    rVal[0] = kratoumeno + 48;
  }
  if (negativeValue)
    makeNegative(rVal);
  return trimLeftZero(rVal);
}

string stringRemove(const string &a, const string &b) {
  string aTemp(a);
  string bTemp(b);
  return stringAdd(aTemp, alterProsimo(bTemp));
}

bool stringBigger(const string &a, const string &b) {
  string aTemp(trimLeftZero(a));
  string bTemp(trimLeftZero(b));
  size_t order = prepare2Strings(aTemp, bTemp);

  bool aNeg = isNegativeString(a);
  bool bNeg = isNegativeString(b);
  if (aNeg) {
    // a is negative
    if (bNeg) {
      // b is negative
      makePositive(aTemp);
      makePositive(bTemp);
      swap(aTemp, bTemp);
    } else {
      // b is positive
      return false;
    }

  } else {
    // a is positive
    if (bNeg) {
      // b is negative
      return true;
    }
  }
  for (size_t i = 0; i != order; i++) {
    if (aTemp[i] != bTemp[i]) {
      return aTemp[i] < bTemp[i] ? false : true;
    }
  }
  return true;
}

bool stringEqual(const string &a, const string &b) {
  string aTemp(trimLeftZero(a));
  string bTemp(trimLeftZero(b));
  size_t order = prepare2Strings(aTemp, bTemp);

  bool aNeg = isNegativeString(a);
  bool bNeg = isNegativeString(b);
  if (aNeg) {
    // a is negative
    if (bNeg) {
      // b is negative
      makePositive(aTemp);
    } else {
      // b is positive
      return false;
    }

  } else {
    // a is positive
    if (bNeg) {
      // b is negative
      return true;
    }
  }

  for (size_t i = 0; i != order; i++) {
    if (aTemp[i] != bTemp[i]) {
      return false;
    }
  }
  return true;
}

bool stringSmaller(const string &a, const string &b) {
  return stringBigger(b, a);
}

size_t getOrder(const string &a, const string &b) {
  size_t aOrder = a.size();
  size_t bOrder = b.size();
  return aOrder >= bOrder ? aOrder : bOrder;
}

size_t prepare2Strings(string &a, string &b) {
  size_t order = getOrder(a, b);
  fillLeftZero(a, order);
  fillLeftZero(b, order);
  return order;
}

string makeNegative(string &a) {
  string aTemp(trimLeftZero(a));
  if (!isNegativeString(aTemp))
    a = '-' + a;
  return a;
  string alterProsimo(string &);
}

string makePositive(string &a) {
  string aTemp(trimLeftZero(a));
  if (!isNegativeString(aTemp))
    return a;
  else {
    a.erase(0, 1);
    return a;
  }
}

string alterProsimo(string &a) {
  string aTemp(trimLeftZero(a));
  if (isNegativeString(aTemp))
    makePositive(aTemp);
  else
    makeNegative(aTemp);
  return aTemp;
}