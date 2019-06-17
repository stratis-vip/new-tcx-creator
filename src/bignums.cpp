#include "bignums.hpp"
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <vector>
// #include <iostream>

BigNum BigNum::operator+(const BigNum &vl)
{
    BigNum retVal;
    BigNum b = vl;

    //υπολογίζω την τάξη μεγέθους για το κρατούμενο
    const size_t taksi = b.fractionalPart.size() >= fractionalPart.size() ? b.fractionalPart.size() : fractionalPart.size();
    for (auto i = b.fractionalPart.size(); i != taksi; i++)
        b.fractionalPart.push_back('0');

    for (auto i = fractionalPart.size(); i != taksi; i++)
        fractionalPart.push_back('0');

    std::ostringstream os{};
    int aValue, bValue;

    aValue = strToI(fractionalPart);
    if (isNegative)
        aValue *= -1;
    bValue = strToI(b.fractionalPart);
    if (b.isNegative)
        bValue *= -1;
    os << aValue + bValue;
    retVal.fractionalPart = os.str();

    os.str("");
    aValue = strToI(integerPart);
    if (isNegative)
        aValue *= -1;
    bValue = strToI(b.integerPart);
    if (b.isNegative)
        bValue *= -1;
    os << aValue + bValue;
    retVal.integerPart = os.str();

    //TODO: έλεγχος αν είναι αρνητικό να βρούμε το πρόσημο.
    //TODO: έλεγχος για το κρατούμενο
    return retVal;
};

string BigNum::value() const
{
    std::ostringstream os{""};
    if (isNegative)
        os << '-';
    os << integerPart << '.' << fractionalPart;
    return os.str();
}

bool checkProsimo(string &a)
{
    bool rVal = false;
    if (a[0] == '-')
    {
        a.erase(0, 1);
        rVal = true;
    }
    if (a[0] == '+')
    {
        a.erase(0, 1);
        rVal = false;
    }
    return rVal;
}

BigNum getValueFromString(string a, const char dot)
{
    BigNum rVal{};
    string integerPart{"0"};
    string fractionalPart{"0"};
    bool isNegative = checkProsimo(a);

    std::vector<string> parts{};
    size_t dotPos = a.find(dot);
    do
    {
        string buffer = a.substr(0, dotPos);
        if (isNumeric(buffer))
            parts.push_back(a.substr(0, dotPos));
        else
        {
            parts.push_back("");
        }

        a.erase(0, dotPos + 1);
        dotPos = a.find(dot);

    } while (dotPos != string::npos);
    if (a.size() > 0)
        parts.push_back(a);

    switch (parts.size())
    {
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

size_t strToI(const std::string a)
{
    size_t rVal{0};
    for (auto i = 0; i != a.size(); i++)
    {
        if (isdigit(a[i]))
        {
            size_t ord = a[i] - 48;
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
    size_t rVal = pow(base, toPower);
    return rVal;
}

size_t tenPow(const size_t toPower)
{
    return intPow(10, toPower);
}

bool isNumeric(const string a, const char dot)
{
    string temp(a);
    if (temp.size() == 0)
        return false;
    size_t hasDot{0};
    checkProsimo(temp);
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