#ifndef __LEXER_H__
#define __LEXER_H__
#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <string>

namespace front_end
{
namespace lexer
{
enum class Token
{
  // builtin types.
  VOID,
  CHAR,
  SHORT,
  INT,
  LONG,
  FLOAT,
  SIGNED,
  UNSIGNED,
  DOUBLE,
  // Idenifier.
  IDENTIFIER,
  // Keywords.
  IF,
  ELSE,
  FOR,
  DO,
  WHILE,
  RETURN,
  UNION,
  STRUCT,
  // Operator.
  ADD,
  SUB,
  MUL,
  DIV,
  MOD,
  ADD_ADD,
  SUB_SUB,
  MEMBER,
  AND,
  AND_AND,
  OR,
  OR_OR,
  LT,
  LE,
  GT,
  GE,
  EQ,
  NOT,
  NEG,
  ASSIGN,
  NOT_EQ,
  // Comment.
  COMMENT,
  // Brakets
  OPEN_PAREN,
  CLOSE_PAREN,
  OPEN_BRAKET,
  CLOSE_BRAKET,
  OPEN_BRACE,
  CLOSE_BRACE,
  // Constants.
  STRINGCONST,
  NUMBERCONST,
  // Others.
  END,
  NEW_LINE,
  SHARP,
  COMMA,
  SEMICOLON,
  NumToken
};

typedef union TokVal {
  long LVal;
  double DVal;
} TokVal;

class LexerImpl
{
public:
  virtual std::vector<Token> lex() = 0;
};

class SimpleLexer : public LexerImpl
{
  static bool g_isMinus;
  const std::string m_filePath;
  std::fstream m_codeStream;
  bool m_fileEnd;
  char m_currentCh;
  size_t m_currentLine;
  static std::map<char, Token> s_charToToken;
  std::vector<std::string> m_strValueDB;
  // For quickly look for m_strValueDB.
  std::set<std::string> m_strValueDBSet;
  std::queue<TokVal> m_tokenValDB;
  Token next();
  void readChar();

public:
  SimpleLexer(const std::string &fileName);

  // For int, uint, char, uchar, short, ushort, long, ulong.
  template <class T>
  inline void getUnsignedValue(T &value)
  {
    TokVal val = m_tokenValDB.front();
    m_tokenValDB.pop();
    value = val.LVal;
  }

  inline void getValue(float &value)
  {
    double val = 0;
    getValue(val);
    value = (float)val;
  }
  inline void getValue(double &value)
  {
    TokVal val = m_tokenValDB.front();
    m_tokenValDB.pop();
    value = val.DVal;
  }
  inline void getValue(std::string &value)
  {
    TokVal val = m_tokenValDB.front();
    m_tokenValDB.pop();
    size_t index = val.LVal;
    value = m_strValueDB[index];
  }

  static std::string strTok(Token);

  std::vector<Token> lex() override;
};
} // namespace lexer
} // namespace front_end
#endif
