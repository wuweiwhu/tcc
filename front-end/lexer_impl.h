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
  /// Used to indicate whether the next const number is minus.
  static bool g_isMinus;
  /// Current file.
  const std::string m_filePath;
  std::fstream m_codeStream;
  /// Indicate whether the whole file has been lexed.
  bool m_fileEnd;
  /// Current char to process.
  char m_currentCh;
  /// Current line to process.
  size_t m_currentLine;
  /// For simple tokens, such as ',', ";", use this map to
  /// get the Token.
  static std::map<char, Token> s_charToToken;
  /// DataBase for const string
  std::vector<std::string> m_strValueDB;
  /// For quickly check whether a string is aready in DB.
  std::set<std::string> m_strValueDBSet;
  /// Store the value of tokens.
  std::queue<TokVal> m_tokenValDB;
  /// Get next token.
  Token next();
  /// Read a char.
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
  /// For print human readable token steam.
  static std::string strTok(Token);
  /// Lex.
  std::vector<Token> lex() override;
};
} // namespace lexer
} // namespace front_end
#endif
