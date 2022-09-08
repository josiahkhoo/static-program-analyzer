#ifndef SPA_EXPRESSION_H
#define SPA_EXPRESSION_H

#include <string>

struct Expression {
  bool hasFrontWildcard = false;
  std::string toMatch;
  bool hasBackWildcard = false;
};

#endif  // SPA_EXPRESSION_H
