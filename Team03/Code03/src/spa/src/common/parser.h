#ifndef SPA_PARSER_H
#define SPA_PARSER_H

#include <vector>

#include "token.h"

template<class T>
class Parser {
public:
    virtual T Parse(std::vector<Token> tokens) = 0;
};

#endif  // SPA_PARSER_H
