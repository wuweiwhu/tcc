#include "parser_impl.h"

#include "ast.h"

using namespace front_end::lexer;

namespace front_end
{
namespace parser
{
static inline bool isTypeSpecifier(Token tok)
{
  return tok == Token::INT ||
         tok == Token::FLOAT ||
         tok == Token::DOUBLE ||
         tok == Token::CHAR ||
         tok == Token::SHORT ||
         tok == Token::LONG;
}
const AstProgram *LRParser::parse(const std::vector<Token> &toks)
{
  for (Token tok : toks)
  {
    if (isTypeSpecifier(tok))
    {
        }
  }
}
} // namespace parser
} // namespace front_end
