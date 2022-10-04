#include "attribute_select_parser.h"

#include "common/clause/synonym_select.h"
#include "qps/parser/query_parser_util.h"

bool AttributeSelectParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;

  if (!tokens->CheckEnd() && tokens->MatchKind(Token::IDENTIFIER)) {
    std::string syn_token = tokens->PeekValue();
    Synonym synonym = builder.GetSynonym(syn_token);
    tokens->Forward();
    if (!tokens->CheckEnd() && tokens->MatchKind(Token::PERIOD)) {
      tokens->Forward();
      if (!tokens->CheckEnd() && tokens->MatchKind(Token::IDENTIFIER)) {
        tokens->Back();
        tokens->Back();
        return true;
      }
      tokens->Back();
    }
    tokens->Back();
  }
  return false;
}

std::shared_ptr<Select> AttributeSelectParser::Parse(TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;

  std::string syn_token = tokens->PeekValue();
  tokens->Expect(Token::IDENTIFIER);
  Synonym synonym = builder.GetSynonym(syn_token);
  tokens->Expect(Token::PERIOD);
  Token attribute_token = tokens->Peek();
  tokens->Expect(Token::IDENTIFIER);

  Attribute::AttributeName attr_name =
      QueryParserUtil::GetAttrName(attribute_token);
  Select::SynonymWithMaybeAttribute synonym_with_maybe_attribute = {synonym,
                                                                    attr_name};
  std::shared_ptr<SynonymSelect> synSl = std::make_shared<SynonymSelect>(
      std::vector<Select::SynonymWithMaybeAttribute>{
          synonym_with_maybe_attribute});

  return synSl;
}
