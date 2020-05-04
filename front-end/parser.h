#ifndef __PARSER_H__
#define __PARSER_H__

#include "parser_impl.h"

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

namespace front_end {
class AstProgram;
namespace lexer {
class LexerImpl;
}
} // namespace front_end

namespace front_end {
namespace parser {

template <class LexerPolicy, class ParserPolicy> class Parser {
  typename std::enable_if<std::is_base_of<lexer::LexerImpl, LexerPolicy>::value,
                          lexer::LexerImpl>::type *m_lexerImpl;
  typename std::enable_if<std::is_base_of<ParserImpl, ParserPolicy>::value,
                          ParserImpl>::type *m_parserImpl;

public:
  Parser(const std::string &filePath, std::ostream &errOut);
  const AstProgram *parse();
  virtual ~Parser();
};

} // namespace parser
} // namespace front_end
#endif
