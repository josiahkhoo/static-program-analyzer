#ifndef SPA_PARSER_H
#define SPA_PARSER_H

#include "token.h"

template <class T>
class Parser {
  virtual T parse(std::vector<Token> tokens) = 0;
};

#endif  // SPA_PARSER_H
