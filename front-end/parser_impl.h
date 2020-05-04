#ifndef __PARSER_IMPL_H__
#define __PARSER_IMPL_H__

#include "lexer_impl.h"

#include <iostream>
#include <stack>
#include <vector>

namespace front_end {
class AstProgram;
}

namespace front_end {
namespace parser {
class ParserImpl {
protected:
  std::ostream &m_errOut;
  ParserImpl(std::ostream &errOut) : m_errOut(errOut) {}

public:
  virtual const AstProgram *parse(const std::vector<lexer::Token> &) = 0;
};

/// \brief A simple recursive desecent parser.
class LLParser : public ParserImpl {
public:
  LLParser(std::ostream &errOut) : ParserImpl(errOut) {}
  const AstProgram *parse(const std::vector<lexer::Token> &toks) override;
};

/// \brief A simple shift reduce parser.
class LRParser : public ParserImpl {
  std::stack<lexer::Token> m_reduceStack;
  void logMessage(const std::string &);
public:
  LRParser(std::ostream &errOut) : ParserImpl(errOut) {}
  const AstProgram *parse(const std::vector<lexer::Token> &toks) override;
};

} // namespace parser
} // namespace front_end

#endif
