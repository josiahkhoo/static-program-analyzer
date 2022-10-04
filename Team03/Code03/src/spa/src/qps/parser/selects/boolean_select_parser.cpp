#include "boolean_select_parser.h"

#include "common/clause/boolean_select.h"

bool BooleanSelectParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;

  if (!tokens->CheckEnd() && tokens->MatchString("BOOLEAN")) {
    return true;
  }
  return false;
}

std::shared_ptr<Select> BooleanSelectParser::Parse(TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  tokens->Expect("BOOLEAN");
  std::shared_ptr<BooleanSelect> boolSl = std::make_shared<BooleanSelect>();
  return boolSl;
}
