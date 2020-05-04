#include "parser.h"

#include "lexer_impl.h"

namespace front_end {

class AstProgram;

namespace parser {
template <class LexerPolicy, class ParserPolicy>
Parser<LexerPolicy, ParserPolicy>::Parser(const std::string &filePath,
                                          std::ostream &errOut)
    : m_lexerImpl(new LexerPolicy(filePath)),
      m_parserImpl(new ParserPolicy(errOut)) {}

template <class LexerPolicy, class ParserPolicy>
const AstProgram *Parser<LexerPolicy, ParserPolicy>::parse() {
  std::vector<lexer::Token> toks = m_lexerImpl->lex();
  return m_parserImpl->parse(toks);
}

template <class LexerPolicy, class ParserPolicy>
Parser<LexerPolicy, ParserPolicy>::~Parser() {
  delete m_lexerImpl;
  delete m_parserImpl;
}

template class Parser<lexer::SimpleLexer, LRParser>;

} // namespace parser
} // namespace front_end
