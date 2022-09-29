#include "query_operation_matcher.h"

#include "query_parser_util.h"

bool QueryOperationMatcher::MatchParser(
    const std::shared_ptr<TokenHandler>& tokens, const std::string& word) {
  if (!tokens->CheckEnd() && tokens->MatchString(word)) {
    return true;
  }
  return false;
}

bool QueryOperationMatcher::MatchTParser(
    const std::shared_ptr<TokenHandler>& tokens, const std::string& word) {
  if (!tokens->CheckEnd() && tokens->MatchString(word)) {
    tokens->Forward();
    if (tokens->MatchKind(Token::ASTERISK)) {
      tokens->Back();
      return true;
    }
    tokens->Back();
  }
  return false;
}

bool QueryOperationMatcher::MatchEntityParser(
    const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
        data,
    const EntityType& type) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  bool res = false;
  Synonym synonym = builder.GetSynonym(tokens->PeekValue());
  // Check if ASSIGN, IF, WHILE
  QueryParserUtil::CheckPatternSyn(synonym);
  if (synonym.IsEntityType(type)) {
    res = true;
  }
  return res;
}
