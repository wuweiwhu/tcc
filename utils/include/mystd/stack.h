#ifndef __MY_STACK_H__
#define __MY_STACK_H__
#include <cassert>
#include <stdlib.h>

namespace mystd {
template<class T>
class stack {
  T *m_pData;
  unsigned m_current;
  unsigned m_capacity;
public:
  stack(unsigned size = 200):m_current(0), m_capacity(size){
    m_pData = (T*)malloc(200 * sizeof(T));
  }
  ~stack() { free(m_pData); }
  void push(const T& ele) {
    if (m_current == m_capacity) {
      m_capacity *= 2;
      m_pData = (T *)realloc(m_pData, m_capacity);
    }
    m_pData[m_current++] = ele;
  }
  T top() const {
    assert(m_current && "stack is empty");
    return m_pData[m_current - 1];
  }
  T pop() {
    assert(m_current && "stack is empty");
    return m_pData[--m_current];
  }
  void clear() { m_current = 0; }
};
} // namespace mystd

#endif
