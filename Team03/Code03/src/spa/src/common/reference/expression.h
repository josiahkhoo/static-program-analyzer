#ifndef SPA_EXPRESSION_H
#define SPA_EXPRESSION_H

#include <string>

struct Expression {
  bool has_front_wildcard = false;
  std::string to_match;
  bool has_back_wildcard = false;
};

#endif  // SPA_EXPRESSION_H
