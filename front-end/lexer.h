#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <string>

namespace front_end {
namespace lexer {
enum class Token {
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
  // Values.
  STRING,
  NUMBER,
  // Others.
  END,
  NEW_LINE,
  SHARP,
  COMMA,
  SEMICOLON,
  NumToken
};

std::map<Token, std::string> strTok{
    {Token::VOID, "VOID"},
    {Token::CHAR, "CHAR"},
    {Token::SHORT, "SHORT"},
    {Token::FLOAT, "FLOAT"},
    {Token::DOUBLE, "DOUBLE"},
    {Token::NUMBER, "NUMBER"},
    {Token::INT, "INT"},
    {Token::LONG, "LONG"},
    {Token::UNSIGNED, "UNSIGNED"},
    {Token::SIGNED, "SIGNED"},
    {Token::FOR, "FOR"},
    {Token::IF, "IF"},
    {Token::ELSE, "ELSE"},
    {Token::WHILE, "WHILE"},
    {Token::DO, "DO"},
    {Token::DOUBLE, "DOUBLE"},
    {Token::UNION, "UNION"},
    {Token::STRUCT, "STRUCT"},
    {Token::STRING, "STRING"},
    {Token::RETURN, "RETURN"},
    {Token::IDENTIFIER, "IDENTIFIER"},
    {Token::LT, "<"},
    {Token::LE, "<="},
    {Token::GT, ">"},
    {Token::GE, ">="},
    {Token::EQ, "=="},
    {Token::ASSIGN, "="},
    {Token::NOT, "!"},
    {Token::NEG, "~"},
    {Token::MUL, "*"},
    {Token::DIV, "/"},
    {Token::COMMENT, ""},
    {Token::SUB, "-"},
    {Token::ADD, "+"},
    {Token::AND, "&"},
    {Token::OR, "|"},
    {Token::SUB_SUB, "--"},
    {Token::AND_AND, "&&"},
    {Token::OR_OR, "||"},
    {Token::ADD_ADD, "++"},
    {Token::MEMBER, "->"},
    {Token::COMMA, ","},
    {Token::SEMICOLON, ";"},
    {Token::SHARP, "#"},
    {Token::OPEN_PAREN, "("},
    {Token::CLOSE_PAREN, ")"},
    {Token::OPEN_BRAKET, "["},
    {Token::CLOSE_BRAKET, "]"},
    {Token::OPEN_BRACE, "{"},
    {Token::CLOSE_BRACE, "}"},
    {Token::END, "EOF"},
};

typedef union TokVal {
  long LVal;
  size_t ULVal;
  double DVal;
} TokVal;

class Lexer {
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
  Lexer(const std::string &fileName);
  inline void getValue(int &value) {
    TokVal val = m_tokenValDB.front();
    m_tokenValDB.pop();
    value = (int)val.LVal;
  }
  inline void getValue(unsigned int &value) {
    TokVal val = m_tokenValDB.front();
    m_tokenValDB.pop();
    value = (unsigned)val.ULVal;
  }
  inline void getValue(float &value) {
    TokVal val = m_tokenValDB.front();
    m_tokenValDB.pop();
    value = (float)val.DVal;
  }
  inline void getValue(double &value) {
    TokVal val = m_tokenValDB.front();
    m_tokenValDB.pop();
    value = val.DVal;
  }
  inline void getValue(std::string &value) {
    TokVal val = m_tokenValDB.front();
    m_tokenValDB.pop();
    size_t index = val.ULVal;
    value = m_strValueDB[index];
  }
  std::vector<Token> lex();
};
} // namespace lexer
} // namespace front_end
