#ifndef SPA_SIMPLE_PARSER_H
#define SPA_SIMPLE_PARSER_H

#include "common/parser.h"
#include "common/t_node.h"

class SimpleParser : public Parser<TNode> {
  TNode parse(std::vector<Token> tokens) override;
};

#endif  // SPA_SIMPLE_PARSER_H
