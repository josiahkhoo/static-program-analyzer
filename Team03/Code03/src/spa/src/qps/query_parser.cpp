#include "query_parser.h"

#include <iostream>
#include <stdexcept>

#include "common/clause/select.h"
#include "common/entity/assign_entity.h"

QueryParser::QueryParser() {
  tokens_ = {};
  query_string_builder_ = QueryStringBuilder();
};

QueryString QueryParser::Parse(std::vector<Token> tokens) {
  try {
    tokens_ = tokens;
    ParseDeclaration();
    ParseSelect();
    ParseClause();
  } catch (const std::runtime_error &e_) {
    std::cout << e_.what();
  }
  return query_string_builder_.GetQueryString();
}

Token QueryParser::Peek(int pos) {
  if (pos >= tokens_.size()) {
    throw std::runtime_error("No more tokens left to Peek");
  }
  return tokens_[pos];
}

bool QueryParser::MatchKind(Token::Kind kind) {
  return Peek(token_pos_).Is(kind);
}

bool QueryParser::MatchString(const std::string &s) {
  return (Peek(token_pos_).GetValue() == s);
}

bool QueryParser::MatchStmtRef() {
  return MatchKind(Token::IDENTIFIER) || MatchKind(Token::UNDERSCORE) ||
         MatchKind(Token::NUMBER);
}

void QueryParser::Expect(Token::Kind kind) {
  if (MatchKind(kind)) {
    token_pos_++;
  } else {
    throw std::runtime_error("Expected a different token kind");
  }
}

void QueryParser::Expect(const std::string &s) {
  if (MatchString(s)) {
    token_pos_++;
  } else {
    throw std::runtime_error("Expected a different token string");
  }
}

StatementReference QueryParser::ExtractStmtRef() {
  StatementReference statement_reference;

  if (MatchKind(Token::IDENTIFIER)) {
    // Checks current declared synonyms to do matching
    Synonym synonym =
        query_string_builder_.GetSynonym(Peek(token_pos_).GetValue());
    statement_reference = StatementReference(synonym);
  } else if (MatchKind(Token::UNDERSCORE)) {
    statement_reference = StatementReference();
  } else if (MatchKind(Token::NUMBER)) {
    statement_reference = StatementReference(stoi(Peek(token_pos_).GetValue()));
  } else {
    throw std::runtime_error("Expected a stmtRef");
  }
  token_pos_++;
  return statement_reference;
}

void QueryParser::ParseDeclaration() {
  Token next = Peek(token_pos_);
  Expect("assign");
  next = Peek(token_pos_);
  Expect(Token::IDENTIFIER);
  Synonym synonym = Synonym(EntityType::ASSIGN, next.GetValue());
  Expect(Token::SEMICOLON);
  query_string_builder_.AddDeclaration(synonym);
}

void QueryParser::ParseSelect() {
  Token next = Peek(token_pos_);
  Expect("Select");
  next = Peek(token_pos_);
  Expect(Token::IDENTIFIER);

  Synonym synonym = Synonym(EntityType::ASSIGN, next.GetValue());
  Select new_select = Select(synonym);

  query_string_builder_.AddSelect(new_select);
}

void QueryParser::ParseClause() {
  while (!MatchKind(Token::END)) {
    if (MatchString("such")) {
      token_pos_++;
      Expect("that");
      // Check for each clause type
      ParseFollow();
    } else {
      throw std::runtime_error("Unexpected token: " +
                               Peek(token_pos_).GetValue());
    }
  }
}

void QueryParser::ParseFollow() {
  Expect("Follows");
  Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 = ExtractStmtRef();

  Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<FollowsClause> folCl =
      std::make_shared<FollowsClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddClause(folCl);
}
