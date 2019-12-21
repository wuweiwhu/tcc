#ifndef __SCANNER_H__
#define __SCANNER_H__
#include "mystd/stack.h"

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace front_end
{
#define BAD -1
enum token
{
  ZERO = 129,
  INT,
  FLOAT,
  EQ,
  IDENTIFIER,
  STR
};

using namespace std;
unordered_map<long, int> INT_C;
vector<long> CONST_INT;
unordered_map<double, int> FLOAT_C;
vector<double> CONST_FLOAT;
unordered_map<string, int> STR_C;
vector<string> CONST_STR;
unordered_map<string, int> ID_C;
vector<string> CONST_ID;
using Token = pair<int, int>;

class Scanner
{
  FILE *fp;
  char *buf;
  int buf_size;
  int pointer;
  int fence;
  bool end_of_file;
  mystd::stack<int> st;              // stack state
  char current;                      // current char lexed
  unsigned nu;                       // current line lexed
  unordered_map<int, int> terminate; // key is terminate state ,value is related token terminate
  inline void next_char()
  {
    current = buf[pointer];
    pointer = (pointer + 1) % buf_size;
    if (pointer % (buf_size >> 1) == 0)
    {
      if (end_of_file)
      {
        cout << "scan over" << endl;
        exit(0);
      }
      for(int i = pointer; i< buf_size >> 1;++i){
        buf[i]=' ';
      }
      if (NULL == fgets(buf + pointer, buf_size >> 1, fp))
      {
        end_of_file = true;
      }
      fence = (pointer + nu) % buf_size;
    }
  }

public:
  Scanner(const char *path, int buf_s = 32) : pointer(0),
                                              fence(0),
                                              nu(0),
                                              end_of_file(false),
                                              buf_size(buf_s)
  {
    fp = fopen(path, "r");
    if (nullptr == fp) {
      cout << "source file error:" << endl;
      exit(0);
    }
    if (buf_s % 2 == 1)
      buf_s++;
    buf = new char[buf_size];
    if (NULL == fgets(buf, buf_size >> 1, fp))
    {
      end_of_file = true;
    }
    terminate[1] = ZERO;
    terminate[3] = FLOAT;
    terminate[4] = INT;
    terminate[5] = -1; // for + - * /  > <  [  ] ( ) terminate is the char itself
    terminate[6] = -1; // for =
    terminate[7] = EQ;
    terminate[10] = STR;
    terminate[11] = IDENTIFIER;
  }
  void lex(vector<Token> &res)
  {
  s0:
    string lexeme;
    st.clear();
    st.push(BAD);
    next_char();
    if (current == ' ')
    {
      next_char();
    }
    if (current == '\n')
    {
      nu++;
      next_char();
    }
    lexeme += current;
    if (current == '+' ||
        current == '-' ||
        current == '*' ||
        current == '/' ||
        current == '^' ||
        current == '>' ||
        current == '<' ||
        current == '[' ||
        current == ']')
    {
      goto s5;
    }
    if (current == '0')
    {
      goto s1;
    }
    if (current >= '1' && current <= '9'){
      goto s4;
    }
    if (current == '='){
      goto s6;
    }
    if (current == '"'){
      goto s8;
    }
    if(
      (current >= 'a' && current <= 'z') ||
      (current >= 'A' && current <= 'Z') 
    ){
      goto s11;
    }
  s1:
    st.clear();
    st.push(1);
    next_char();
    lexeme += current;
    if (current == '.')
    {
      goto s2;
    }
    else
    {
      goto sout;
    }

  s2:
    st.push(2);
    next_char();
    lexeme += current;
    if ('0' <= current && current <= '9')
    {
      goto s3;
    }
    else
    {
      goto sout;
    }
  s3:
    st.clear();
    st.push(3);
    next_char();
    lexeme += current;
    if ('0' <= current && current <= '9')
    {
      goto s3;
    }
    else
    {
      goto sout;
    }
  s4:
    st.clear();
    st.push(4);
    next_char();
    lexeme += current;
    if ('0' <= current && current <= '9')
    {
      goto s4;
    }else if(current == '.'){
      goto s2;
    }else{
      goto sout;
    }
  s5:
    st.clear();
    st.push(5);
    next_char();
    lexeme += current;
    goto sout;
  s6:
    st.clear();
    st.push(6);
    next_char();
    lexeme += current;
    if(current == '='){
      goto s7;
    }else{
      goto sout;
    }
  s7:
    st.clear();
    st.push(7);
    next_char();
    lexeme += current;
    goto sout;
  s8:
    st.push(8);
    next_char();
    lexeme += current;
    if(current == '"'){
      goto s10;
    }else if(
      (current >= 'a' && current <= 'z') ||
      (current >= 'A' && current <= 'Z') ||
      (current >= '0' && current <= '9') ||
      current == '_' ||
      current == ' '
    ){
      goto s9;

    }
  s9:
    st.push(9);
    next_char();
    lexeme += current;
    if(
      (current >= 'a' && current <= 'z') ||
      (current >= 'A' && current <= 'Z') ||
      (current >= '0' && current <= '9') ||
      current == '_' ||
      current == ' '
    ){
      goto s9;
    }else if(current == '"'){
      goto s10;
    }else{
      goto sout;
    }
  s10:
    st.clear();
    st.push(10);
    next_char();
    lexeme += current;
    goto sout;
  s11:
    st.clear();
    st.push(11);
    next_char();
    lexeme += current;
    if(
      (current >= 'a' && current <= 'z') ||
      (current >= 'A' && current <= 'Z') ||
      (current >= '0' && current <= '9') ||
      current == '_'
    ){
      goto s11;
    }else{
      goto sout;
    }
  sout:
    st.push(-2);
    int sta = st.top();
    int truncate = lexeme.size();
    while (terminate.find(sta) == terminate.end() || sta != BAD)
    {
      st.pop();
      sta = st.top();
      if (pointer == fence)
      {
        cout << "lex error in roll back" << endl;
        exit(0);
      }
      truncate--;
      pointer = (pointer - 1) % buf_size;
    }
    if (sta == BAD)
    {
      cout << "lex error in line " << nu << " :" << lexeme << endl;
      exit(0);
    }
    else
    {
      string lexeme_t = lexeme.substr(truncate);
      switch (terminate[sta])
      {
      case ZERO:
        if (INT_C.find(0) == INT_C.end())
        {
          INT_C[0] = CONST_INT.size();
          CONST_INT.push_back(0);
        }
        res.push_back({ZERO, INT_C[0]});
      case INT:
      {
        long val;
        stringstream ss;
        ss << lexeme_t;
        ss >> val;
        if (INT_C.find(val) == INT_C.end())
        {
          INT_C[val] = CONST_INT.size();
          CONST_INT.push_back(val);
        }
        res.push_back({INT, INT_C[val]});
      }
      case FLOAT:
      {
        double val;
        stringstream ss;
        ss << lexeme_t;
        ss >> val;
        if (FLOAT_C.find(val) == FLOAT_C.end())
        {
          FLOAT_C[val] = CONST_FLOAT.size();
          CONST_FLOAT.push_back(val);
        }
        res.push_back({FLOAT, FLOAT_C[val]});
      }
      case STR:
      {
        string val = lexeme_t.substr(1, lexeme_t.size() - 1);
        if (STR_C.find(val) == STR_C.end())
        {
          STR_C[val] = CONST_STR.size();
          CONST_STR.push_back(val);
        }
        res.push_back({STR, STR_C[val]});
      }
      case IDENTIFIER:
      {
        string val = lexeme_t;
        if (ID_C.find(val) == ID_C.end())
        {
          ID_C[val] = CONST_ID.size();
          CONST_ID.push_back(val);
        }
        res.push_back({IDENTIFIER, ID_C[val]});
      }
      case EQ:
      {
        res.push_back({EQ, -1});
      }
      default: // equal -1
        assert(lexeme_t.size() == 1);
        res.push_back({int(lexeme_t[0]), -1});
      }
      goto s0;
    }
  }
};
} // namespace front_end
#endif
