#include "query_parser.h"

#include "common/clause/boolean_select.h"
#include "common/clause/select.h"
#include "common/clause/synonym_select.h"
#include "common/entity/assign_entity.h"
#include "qps/exceptions/syntax_exception.h"
#include "qps/parser/operations/calls_parser.h"
#include "qps/parser/operations/calls_t_parser.h"
#include "qps/parser/operations/follows_parser.h"
#include "qps/parser/operations/follows_t_parser.h"
#include "qps/parser/operations/modifies_p_parser.h"
#include "qps/parser/operations/modifies_s_parser.h"
#include "qps/parser/operations/parent_parser.h"
#include "qps/parser/operations/parent_t_parser.h"
#include "qps/parser/operations/pattern_assign_parser.h"
#include "qps/parser/operations/pattern_if_parser.h"
#include "qps/parser/operations/pattern_while_parser.h"
#include "qps/parser/operations/uses_p_parser.h"
#include "qps/parser/operations/uses_s_parser.h"
#include "qps/parser/operations/with_parser.h"
#include "qps/parser/query_parser_util.h"
#include "qps/parser/token_builder_pair.h"

QueryParser::QueryParser() = default;

QueryString QueryParser::Parse(std::vector<Token> tokens) {
  tokens_ = std::make_shared<TokenHandler>(TokenHandler(tokens));
  query_string_builder_ = QueryStringBuilder();
  ParseDeclaration();
  ParseSelect();
  ParseQueryOperation();
  CheckLeftoverTokens();
  return query_string_builder_.GetQueryString();
}

void QueryParser::ParseDeclaration() {
  while (!tokens_->CheckEnd() && !tokens_->MatchString("Select")) {
    Token next = tokens_->Peek();
    EntityType entType = QueryParserUtil::ExtractEntityType(tokens_);
    next = tokens_->Peek();
    tokens_->Expect(Token::IDENTIFIER);
    Synonym synonym = Synonym(entType, next.GetValue());
    query_string_builder_.AddDeclaration(synonym);
    while (tokens_->MatchKind(Token::COMMA)) {
      tokens_->Forward();
      next = tokens_->Peek();
      tokens_->Expect(Token::IDENTIFIER);
      synonym = Synonym(entType, next.GetValue());
      query_string_builder_.AddDeclaration(synonym);
    }
    tokens_->Expect(Token::SEMICOLON);
  }
}

void QueryParser::ParseSelect() {
  if (tokens_->CheckEnd()) {
    return;
  }
  tokens_->Expect("Select");
  std::string syn_token = tokens_->PeekValue();
  tokens_->Expect(Token::IDENTIFIER);
  if (syn_token == "BOOLEAN") {
    query_string_builder_.AddSelect(std::make_shared<BooleanSelect>());
  } else {
    Synonym synonym = query_string_builder_.GetSynonym(syn_token);
    query_string_builder_.AddSelect(
        std::make_shared<SynonymSelect>(std::vector{synonym}));
  }
}

void QueryParser::ParseQueryOperation() {
  // Check for each clause type, append below new clauses
  // Note: Order matters, place stricter clause first i.e. Follows* > Follows
  st_parsers_.push_back(std::make_shared<FollowsTParser>());
  st_parsers_.push_back(std::make_shared<FollowsParser>());
  st_parsers_.push_back(std::make_shared<ParentTParser>());
  st_parsers_.push_back(std::make_shared<ParentParser>());
  st_parsers_.push_back(std::make_shared<CallsTParser>());
  st_parsers_.push_back(std::make_shared<CallsParser>());
  st_parsers_.push_back(std::make_shared<UsesPParser>());
  st_parsers_.push_back(std::make_shared<UsesSParser>());
  st_parsers_.push_back(std::make_shared<ModifiesPParser>());
  st_parsers_.push_back(std::make_shared<ModifiesSParser>());

  pattern_parsers_.push_back(std::make_shared<PatternAssignParser>());
  pattern_parsers_.push_back(std::make_shared<PatternIfParser>());
  pattern_parsers_.push_back(std::make_shared<PatternWhileParser>());

  while (tokens_->IsNotEnd()) {
    bool found_clause = ParseClause();
    bool found_pattern = ParsePattern();
    bool found_with = ParseWith();
    // No operation detected, exit
    if (!(found_clause || found_pattern || found_with)) {
      break;
    }
  }
}

bool QueryParser::ParseClause() {
  if (tokens_->CheckEnd() || !tokens_->MatchString("such")) {
    return false;
  }
  tokens_->Forward();
  tokens_->Expect("that");
  ParseIndividualClause();
  // No clause found
  if (query_string_builder_.IsOperationsEmpty()) {
    throw SyntaxException("No operations or declarations declared");
  }
  return true;
}

void QueryParser::ParseIndividualClause() {
  TokenBuilderPair queryData = TokenBuilderPair(tokens_, query_string_builder_);

  std::shared_ptr<QueryOperation> op;
  for (const auto& clause_parser : st_parsers_) {
    if (clause_parser->MatchParser(queryData)) {
      op = clause_parser->Parse(queryData);
      break;
    }
  }
  if (op != nullptr) {
    query_string_builder_.AddQueryOperation(op);
  }
}

bool QueryParser::ParsePattern() {
  TokenBuilderPair queryData = TokenBuilderPair(tokens_, query_string_builder_);

  std::shared_ptr<QueryOperation> op;
  for (const auto& clause_parser : pattern_parsers_) {
    if (clause_parser->MatchParser(queryData)) {
      op = clause_parser->Parse(queryData);
      break;
    }
  }
  if (op != nullptr) {
    query_string_builder_.AddQueryOperation(op);
    return true;
  }
  return false;
}

bool QueryParser::ParseWith() {
  TokenBuilderPair queryData = TokenBuilderPair(tokens_, query_string_builder_);

  WithParser withP;
  std::shared_ptr<QueryOperation> op;
  if (withP.MatchParser(queryData)) {
    withP.Parse(queryData);
    return true;
  }
  return false;
}

void QueryParser::CheckLeftoverTokens() {
  if (!tokens_->CheckEnd() && tokens_->Peek().IsNot(Token::END)) {
    throw SyntaxException("Unexpected additional token(s)");
  }
}
