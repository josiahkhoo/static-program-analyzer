#ifndef SPA_FOLLOW_PARSER_H
#define SPA_FOLLOW_PARSER_H

#include "common/clause/follows_clause.h"
#include "common/parser.h"

/// Parser tokens and creates a new FollowsClause object
class FollowsParser : public Parser<FollowsClause> {
 public:
  FollowsClause Parse(std::vector<Token> tokens) override;
};

#endif  // SPA_FOLLOW_PARSER_H
