#include "common/clause/follows_clause.h"
#include "follows_parser.h"

const std::string FollowsClause::CLAUSE_WORD = "Follows";

FollowsClause FollowsParser::Parse(std::vector<Token> tokens) {
  return FollowsClause(StatementReference(), StatementReference());
}