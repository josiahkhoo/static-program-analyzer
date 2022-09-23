#include "query_operation_matcher_t.h"

bool QueryOperationMatcherT::MatchParser(
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
