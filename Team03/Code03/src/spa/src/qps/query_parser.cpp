#include "query_parser.h"

#include "common/clause/select.h"
#include "common/entity/assign_entity.h"
#include "common/exceptions/syntax_exception.h"
#include "qps/exceptions/semantic_exception.h"
#include "qps/parser/operations/affects_parser.h"
#include "qps/parser/operations/affects_t_parser.h"
#include "qps/parser/operations/calls_parser.h"
#include "qps/parser/operations/calls_t_parser.h"
#include "qps/parser/operations/follows_parser.h"
#include "qps/parser/operations/follows_t_parser.h"
#include "qps/parser/operations/modifies_p_parser.h"
#include "qps/parser/operations/modifies_s_parser.h"
#include "qps/parser/operations/next_parser.h"
#include "qps/parser/operations/next_t_parser.h"
#include "qps/parser/operations/parent_parser.h"
#include "qps/parser/operations/parent_t_parser.h"
#include "qps/parser/operations/pattern_assign_parser.h"
#include "qps/parser/operations/pattern_if_parser.h"
#include "qps/parser/operations/pattern_while_parser.h"
#include "qps/parser/operations/uses_p_parser.h"
#include "qps/parser/operations/uses_s_parser.h"
#include "qps/parser/operations/with_parser.h"
#include "qps/parser/query_parser_util.h"
#include "qps/parser/selects/boolean_select_parser.h"
#include "qps/parser/selects/synonym_select_parser.h"
#include "qps/parser/token_builder_pair.h"

QueryParser::QueryParser() = default;

QueryString QueryParser::Parse(std::vector<Token> tokens) {
  tokens_ = std::make_shared<TokenHandler>(TokenHandler(tokens));
  query_string_builder_ = QueryStringBuilder();
  last_query_operation_ = std::optional<Token>();
  ParseDeclaration();
  ParseSelect();
  ParseQueryOperation();
  CheckLeftoverTokens();
  return RetrieveQueryString();
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
  TokenBuilderPair queryData = TokenBuilderPair(tokens_, query_string_builder_);

  select_parsers_.push_back(std::make_shared<BooleanSelectParser>());
  select_parsers_.push_back(std::make_shared<SynonymSelectParser>());

  std::shared_ptr<Select> op;
  for (const auto& clause_parser : select_parsers_) {
    if (clause_parser->MatchParser(queryData)) {
      op = clause_parser->Parse(queryData);
      break;
    }
  }
  if (op != nullptr) {
    query_string_builder_.AddSelect(op);
  } else {
    throw SyntaxException("Expected a Select clause");
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
  st_parsers_.push_back(std::make_shared<NextTParser>());
  st_parsers_.push_back(std::make_shared<NextParser>());
  st_parsers_.push_back(std::make_shared<AffectsTParser>());
  st_parsers_.push_back(std::make_shared<AffectsParser>());

  pattern_parsers_.push_back(std::make_shared<PatternAssignParser>());
  pattern_parsers_.push_back(std::make_shared<PatternIfParser>());
  pattern_parsers_.push_back(std::make_shared<PatternWhileParser>());

  while (tokens_->IsNotEnd()) {
    bool found_clause = false;
    bool found_pattern = false;
    bool found_with = false;
    if (tokens_->MatchString("and")) {
      if (last_query_operation_) {
        std::string last_query_op_str =
            last_query_operation_.value().GetValue();
        tokens_->Forward();
        if (last_query_op_str == "such") {
          found_clause = ParseClause(true);
        } else if (last_query_op_str == "pattern") {
          found_pattern = ParsePattern(true);
        } else if (last_query_op_str == "with") {
          found_pattern = ParseWith(true);
        }
      } else {
        throw SyntaxException("Unexpected 'and' as first query operation");
      }
    } else {
      found_clause = ParseClause();
      found_pattern = ParsePattern();
      found_with = ParseWith();
    }
    if (!(found_clause || found_pattern || found_with)) {
      // No operation detected, exit
      break;
    }
  }
}

bool QueryParser::CheckClauseKeyWord(bool isAnd, const std::string& keyword) {
  if (!isAnd) {
    if (tokens_->CheckEnd() || !tokens_->MatchString(keyword)) {
      return false;
    }
    tokens_->Forward();
  }
  return true;
}

bool QueryParser::ParseClause(bool isAnd) {
  if (!CheckClauseKeyWord(isAnd, "such")) {
    return false;
  }
  if (!isAnd) {
    tokens_->Expect("that");
  }
  ParseIndividualClause();
  // No clause found
  if (query_string_builder_.IsOperationsEmpty()) {
    throw SyntaxException("No operations or declarations declared");
  }
  last_query_operation_ = Token(Token::Kind::IDENTIFIER, "such");
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
  } else {
    throw SyntaxException("Expected a such-that clause");
  }
}

bool QueryParser::ParsePattern(bool isAnd) {
  if (!CheckClauseKeyWord(isAnd, "pattern")) {
    return false;
  }
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
    last_query_operation_ = Token(Token::Kind::IDENTIFIER, "pattern");
    return true;
  } else {
    throw SyntaxException("Expected a pattern clause");
  }
}

bool QueryParser::ParseWith(bool isAnd) {
  if (!CheckClauseKeyWord(isAnd, "with")) {
    return false;
  }
  TokenBuilderPair queryData = TokenBuilderPair(tokens_, query_string_builder_);

  WithParser withP;
  std::shared_ptr<QueryOperation> op;
  op = withP.Parse(queryData);
  if (op != nullptr) {
    query_string_builder_.AddQueryOperation(op);
    last_query_operation_ = Token(Token::Kind::IDENTIFIER, "with");
    return true;
  } else {
    throw SyntaxException("Expected a with clause");
  }
}

void QueryParser::CheckLeftoverTokens() {
  if (!tokens_->CheckEnd() && tokens_->Peek().IsNot(Token::END)) {
    throw SyntaxException("Unexpected additional token(s)");
  }
}

QueryString QueryParser::RetrieveQueryString() {
  if (query_string_builder_.HasNoSelect()) {
    throw SemanticException("Empty select");
  }
  return query_string_builder_.GetQueryString();
}
