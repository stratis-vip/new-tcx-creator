#include "stdfuncs.hpp"

size_t strToI(const std::string &a)
{
  size_t rVal{0};
  for (size_t i = 0; i != a.size(); i++)
  {
    if (isdigit(a[i]))
    {
      size_t ord = static_cast<size_t>(a[i]) - 48UL;
      size_t mplyer = (a.size() - (i + 1));
      if (mplyer == 0)
        rVal += ord;
      else
        rVal += ord * tenPow(mplyer);
    }
    else
    {
      throw std::invalid_argument("Must be a digit");
    }
  }
  return rVal;
}

size_t intPow(const size_t base, const size_t toPower)
{
  size_t rVal = static_cast<int>(pow(base, toPower));
  return rVal;
}

size_t tenPow(const size_t toPower) { return intPow(10, toPower); }

bool isNumeric(const string a, const char dot)
{
  string temp(a);
  if (temp.size() == 0)
    return false;
  size_t hasDot{0};
  if (isNegativeString(temp))
    temp.erase(0, 1);
  for (auto ch : temp)
  {
    if (ch == dot)
    {
      hasDot++;
      if (hasDot > 1)
        return false;
    }
    else if (!isdigit(ch))
      return false;
  }
  return true;
}

bool isNegativeString(const string &a)
{
  bool rVal = false;
  if (a[0] == '-')
  {
    rVal = true;
  }
  if (a[0] == '+')
  {
    rVal = false;
  }
  return rVal;
}

string trimLeftZero(const string &a)
{
  string rVal{};
  size_t start{0};
  char prosimo = ' ';
  if (isNumeric(a))
  {
    if (a[0] == '-' || a[0] == '+')
    {
      prosimo = a[0];
      start = 1;
    }
    while (a[start] == '0')
    {
      start++;
    }
    if (start == a.size())
      rVal = "0";
    else
      rVal = a.substr(start);
    if (prosimo != ' ')
      rVal = a[0] + rVal;
  }
  else
  {
    throw std::invalid_argument("invalid number!");
  }
  return rVal;
}

string trimRightZero(const string &a)
{
  string rVal{};
  int start = a.size() - 1;
  if (isNumeric(a))
  {
    while (start >= 0 && a[start] == '0')
    {
      start--;
    }
    start++;
    if (start == 0)
      rVal = "0";
    else
      rVal = a.substr(0, start);
  }
  else
  {
    throw std::invalid_argument("invalid number!");
  }
  return rVal;
}

void fillRightZero(string &a, size_t order)
{
  if (order > a.size())
    for (auto i = a.size(); i != order; i++)
      a.push_back('0');
}

void fillLeftZero(string &a, size_t order)
{
  if (order > a.size())
  {
    size_t topValue = order - a.size();
    for (auto i = 0; i != topValue; i++)
      a = '0' + a;
  }
}

string stringAdd(const string &a, const string &b)
{
  //calculate order
  string aTemp(a);
  bool aNeg = isNegativeString(aTemp);
  if (aNeg)
    aTemp.erase(0, 1);

  string bTemp(b);
  bool bNeg = isNegativeString(bTemp);
  if (bNeg)
    bTemp.erase(0, 1);
  
  size_t order = prepare2Strings(aTemp, bTemp);

  signed char kratoumeno;
  string rVal(order + 1, '0');
  for (size_t i = order - 1; i != -1; i--)
  {
    signed char aC = aTemp[i] - 48;
    signed char bC = bTemp[i] - 48;
    if (aNeg)
      aC *= -1;
    if (bNeg)
      bC *= -1;

    signed char sum = aC + bC;

    if (sum > 9)
    {
      sum -= 10;
      rVal[i + 1] = (sum + kratoumeno) + 48;
      kratoumeno = 1;
    }
    else
    {
      if (sum == 9 && kratoumeno == 1)
      {
        rVal[i + 1] = '0';
        kratoumeno = 1;
      }
      else
      {
        rVal[i + 1] = (sum + kratoumeno) + 48;
        kratoumeno = 0;
      }
    }
  }
  if (kratoumeno > 0)
  {
    rVal[0] = kratoumeno + 48;
  }
  aNeg = aNeg + bNeg;
  aTemp = a + b;

  return trimLeftZero(rVal);
}

bool stringBigger(const string &a, const string &b)
{
  string aTemp(trimLeftZero(a));
  string bTemp(trimLeftZero(b));
  size_t order = prepare2Strings(aTemp, bTemp);
  for (size_t i =0; i!= order; i++)
  {
    if (aTemp[i] < bTemp[i])
      return false;
  }
  return true;
}

size_t getOrder(const string &a, const string &b)
{
  size_t aOrder = a.size();
  size_t bOrder = b.size();
  return aOrder >= bOrder ? aOrder : bOrder;
}

size_t prepare2Strings(string &a, string &b){
  size_t order = getOrder(a,b);
  fillLeftZero(a, order);
  fillLeftZero(b, order);
  return order;
}