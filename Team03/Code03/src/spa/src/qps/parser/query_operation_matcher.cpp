#include "query_operation_matcher.h"

bool QueryOperationMatcher::MatchParser(
    const std::shared_ptr<TokenHandler>& tokens, const std::string& word) {
  if (!tokens->CheckEnd() && tokens->MatchString(word)) {
    return true;
  }
  return false;
}