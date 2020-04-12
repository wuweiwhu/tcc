#include "parser.h"
#include <iostream>

using namespace front_end::lexer;
using namespace front_end::parser;
int main() {
  Parser<SimpleLexer, LRParser> par("test.c", std::cout);
  par.parse();
  std::cout << std::endl;
  return 0;
}
