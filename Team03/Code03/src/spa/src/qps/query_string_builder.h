#ifndef SPA_QUERY_STRING_BUILDER_H
#define SPA_QUERY_STRING_BUILDER_H

#include "common/parser.h"
#include "common/t_node.h"
#include "query_string.h"

class QueryStringBuilder : public Parser<QueryString> {
public:
	QueryString parse(std::vector<Token> tokens_) override;

private:
  int token_pos_ = 0;
  std::vector<Token> tokens_;
  Token next;
  QueryString queryString;

};

#endif  // SPA_QUERY_STRING_BUILDER_H
