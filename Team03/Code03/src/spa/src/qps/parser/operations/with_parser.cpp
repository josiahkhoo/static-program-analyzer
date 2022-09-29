#include "with_parser.h"

#include "common/clause/with.h"
#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/query_parser_util.h"

const std::string WithParser::CLAUSE_WORD = "with";

bool WithParser::MatchParser(const TokenBuilderPair& data) const {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  return QueryOperationMatcher::MatchParser(tokens, CLAUSE_WORD);
}

std::shared_ptr<QueryOperation> WithParser::Parse(TokenBuilderPair data) {
  // Get data
  std::shared_ptr<TokenHandler> tokens = data.first;
  QueryStringBuilder builder = data.second;
  Token next = tokens->Peek();
  AttributeReference aRef1 = QueryParserUtil::ExtractAttrRef(tokens, builder);
  tokens->Expect(Token::EQUAL);
  AttributeReference aRef2 = QueryParserUtil::ExtractAttrRef(tokens, builder);

  // For attrCompare, the two ref comparison must be of the same type
  // (both NAME, or both INTEGER)
  if ((aRef1.IsLineNumber() && aRef2.IsIdentifier()) ||
      (aRef2.IsLineNumber() && aRef1.IsIdentifier())) {
    throw SemanticException("Ref comparison much be of same type");
  } else if (aRef1.IsSynonym() && aRef2.IsSynonym()) {
    if (QueryParserUtil::CheckNameAttribute(aRef1) !=
        QueryParserUtil::CheckNameAttribute(aRef2))
      throw SemanticException("Ref comparison much be of same type");
  } else if (aRef1.IsSynonym() && !aRef2.IsSynonym()) {
    if (QueryParserUtil::CheckNameAttribute(aRef1) != aRef2.IsIdentifier())
      throw SemanticException("Ref comparison much be of same type");
  } else if (aRef2.IsSynonym() && !aRef1.IsSynonym()) {
    if (QueryParserUtil::CheckNameAttribute(aRef2) != aRef1.IsIdentifier())
      throw SemanticException("Ref comparison much be of same type");
  }

  std::shared_ptr<With> withCl = std::make_shared<With>(aRef1, aRef2);
  return withCl;
}
