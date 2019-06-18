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
bool isNumeric(const string, const char dot = '.');
string trimLeftZero(const string &a);
string trimRightZero(const string &a);
void fillRightZero(string &a, size_t order);
void fillLeftZero(string &a, size_t order);

string stringAdd(const string &, const string &);
bool stringBigger(const string &, const string &);
size_t prepare2Strings(string &a, string &b);

size_t getOrder(const string &, const string &);

#endif
