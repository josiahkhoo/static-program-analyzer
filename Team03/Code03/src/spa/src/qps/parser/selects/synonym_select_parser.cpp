#include "synonym_select_parser.h"

#include "common/clause/synonym_select.h"

bool SynonymSelectParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;

  if (!tokens->CheckEnd() && tokens->MatchKind(Token::IDENTIFIER)) {
    std::string syn_token = tokens->PeekValue();
    Synonym synonym = builder.GetSynonym(syn_token);
    return true;
  }
  return false;
}

std::shared_ptr<Select> SynonymSelectParser::Parse(TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;

  std::string syn_token = tokens->PeekValue();
  tokens->Expect(Token::IDENTIFIER);
  Synonym synonym = builder.GetSynonym(syn_token);
  Select::SynonymWithMaybeAttribute synonym_with_maybe_attribute = {synonym};
  std::shared_ptr<SynonymSelect> synSl = std::make_shared<SynonymSelect>(
      std::vector<Select::SynonymWithMaybeAttribute>{
          synonym_with_maybe_attribute});

  return synSl;
}
