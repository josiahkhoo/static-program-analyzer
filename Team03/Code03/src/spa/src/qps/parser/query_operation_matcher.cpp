#include "query_operation_matcher.h"

#include "query_parser_util.h"

/// Checks if current tokens match clause/operation grammar word
/// \param tokens, word
/// \return If current tokens matches specified word
bool QueryOperationMatcher::MatchParser(
    const std::shared_ptr<TokenHandler>& tokens, const std::string& word) {
  if (!tokens->CheckEnd() && tokens->MatchString(word)) {
    return true;
  }
  return false;
}

/// Checks if current tokens match entity type and clause/operation grammar word
/// \param data, word, type
/// \return If current tokens matches specified type and word
bool QueryOperationMatcher::MatchParser(
    const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
        data,
    const EntityType& type) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  bool res = false;
  Synonym synonym =
      QueryParserUtil::ExtractSynonym(builder, tokens->PeekValue());
  // Check if ASSIGN, IF, WHILE
  QueryParserUtil::CheckPatternSyn(synonym);
  if (synonym.IsEntityType(type)) {
    res = true;
  }
  return res;
}

/// Checks if current tokens match T clause/operation grammar word
/// \param tokens, word
/// \return If current tokens matches specified '*' and word
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