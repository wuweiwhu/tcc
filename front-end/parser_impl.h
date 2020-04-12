#ifndef __PARSER_IMPL_H__
#define __PARSER_IMPL_H__

#include "lexer_impl.h"

#include <iostream>
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

class LRParser : public ParserImpl {
public:
  LRParser(std::ostream &errOut) : ParserImpl(errOut) {}
  const AstProgram *parse(const std::vector<lexer::Token> &toks) override {
    std::cout << "Parser" << std::endl;
  }
};

} // namespace parser
} // namespace front_end

#endif
