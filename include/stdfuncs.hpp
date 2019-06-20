#ifndef STDFUNCS_HPP
#define STDFUNCS_HPP

#include <cmath>
#include <stdexcept>
#include <string>

using std::string;

bool isNegativeString(const string &);
size_t strToI(const string &);
size_t intPow(const size_t, const size_t);
size_t tenPow(const size_t);
bool isNumeric(const string &, const char dot = '.');
string trimLeftZero(const string &a);
string trimRightZero(const string &a);
void fillRightZero(string &a, size_t order);
string reverse(const string &a);
void fillLeftZero(string &a, size_t order);

string stringAdd(const string &, const string &);
string stringRemove(const string &, const string &);
bool stringBigger(const string &, const string &);
bool stringEqual(const string &, const string &);
bool stringSmaller(const string &, const string &);
string makeNegative(string &);
string makePositive(string &);
string alterSign(string &);

size_t prepare2Strings(string &a, string &b);

size_t getOrder(const string &, const string &);

template <class T> void swap(T &a, T &b) {
  T temp = b;
  b = a;
  a = temp;
}

#endif
