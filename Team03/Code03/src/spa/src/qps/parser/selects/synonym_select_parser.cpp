#include "synonym_select_parser.h"

#include "common/clause/synonym_select.h"
#include "qps/parser/query_parser_util.h"

bool SynonymSelectParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  if (tokens->CheckEnd()) {
    return false;
  }
  return true;
}

std::shared_ptr<Select> SynonymSelectParser::Parse(TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;

  std::vector<Select::SynonymWithMaybeAttribute> synonyms_found;

  // Check if tuple
  bool isTuple = false;
  if (tokens->MatchKind(Token::LESS_THAN)) {
    tokens->Expect(Token::LESS_THAN);
    isTuple = true;
  }
  while (!tokens->CheckEnd()) {
    synonyms_found.emplace_back(ParseSynonym(tokens, builder));
    if (!isTuple) {
      break;
    } else if (tokens->MatchKind(Token::GREATER_THAN)) {
      tokens->Expect(Token::GREATER_THAN);
      break;
    }
    tokens->Expect(Token::COMMA);
  }

  std::shared_ptr<SynonymSelect> synSl =
      std::make_shared<SynonymSelect>(synonyms_found);

  return synSl;
}

Select::SynonymWithMaybeAttribute SynonymSelectParser::ParseSynonym(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  std::string syn_token = tokens->PeekValue();
  tokens->Expect(Token::IDENTIFIER);
  Synonym synonym = builder.GetSynonym(syn_token);

  // Get attribute name if exist
  if (!tokens->CheckEnd() && tokens->MatchKind(Token::PERIOD)) {
    tokens->Expect(Token::PERIOD);
    AttributeName attr_name = QueryParserUtil::ExtractAttrName(synonym, tokens);
    return {synonym, attr_name};
  } else {
    return Select::SynonymWithMaybeAttribute(synonym);
  }
}
