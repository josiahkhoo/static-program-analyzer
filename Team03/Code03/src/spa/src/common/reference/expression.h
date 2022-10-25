#ifndef SPA_EXPRESSION_H
#define SPA_EXPRESSION_H

#include <string>

struct Expression {
  bool has_wildcard = false;
  std::string to_match;
};

#endif  // SPA_EXPRESSION_H
