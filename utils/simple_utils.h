#ifndef __SIMPLE_UTILS_H__
#define __SIMPLE_UTILS_H__
#include <sstream>
#include <type_traits>
template <class T>
static typename std::enable_if<std::is_arithmetic<T>::value, T>::type
convertTo(const std::string &s) {
  std::stringstream ss(s);
  T value;
  ss >> value;
  return value;
}
#endif
