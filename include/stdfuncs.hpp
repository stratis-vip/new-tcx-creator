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

#endif