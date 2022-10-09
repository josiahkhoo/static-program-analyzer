#ifndef SPA_PARSER_H
#define SPA_PARSER_H

#include <vector>

#include "token.h"

template <class T, class V>
class Parser {
 public:
  virtual ~Parser() = default;
  virtual T Parse(V tokens) = 0;
};

#endif  // SPA_PARSER_H
