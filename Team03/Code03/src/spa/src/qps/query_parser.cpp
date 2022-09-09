#include "query_parser.h"

#include <stdexcept>

#include "common/clause/parent_clause.h"
#include "common/clause/parent_t_clause.h"
#include "common/clause/pattern.h"
#include "common/clause/select.h"
#include "common/entity/assign_entity.h"

QueryParser::QueryParser() {
  tokens_ = {};
  query_string_builder_ = QueryStringBuilder();
};

QueryString QueryParser::Parse(std::vector<Token> tokens) {
  tokens_ = tokens;
  ParseDeclaration();
  ParseSelect();
  ParseQueryOperation();
  return query_string_builder_.GetQueryString();
}

Token QueryParser::Peek() {
  if (token_pos_ >= tokens_.size()) {
    throw std::runtime_error("No more tokens left to Peek");
  }
  return tokens_[token_pos_];
}

bool QueryParser::MatchKind(Token::Kind kind) { return Peek().Is(kind); }

bool QueryParser::MatchString(const std::string &s) {
  Token next = Peek();
  if (next.IsNot(Token::IDENTIFIER)) {
    return false;
  }
  return (next.GetValue() == s);
}

bool QueryParser::CheckEnd() { return token_pos_ == tokens_.size(); }

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
    Synonym synonym = query_string_builder_.GetSynonym(Peek().GetValue());
    statement_reference = StatementReference(synonym);
  } else if (MatchKind(Token::UNDERSCORE)) {
    statement_reference = StatementReference();
  } else if (MatchKind(Token::NUMBER)) {
    statement_reference = StatementReference(stoi(Peek().GetValue()));
  } else {
    throw std::runtime_error("Expected a stmtRef");
  }
  token_pos_++;
  return statement_reference;
}

EntityReference QueryParser::ExtractEntityRef() {
  EntityReference entity_reference;

  if (MatchKind(Token::UNDERSCORE)) {
    token_pos_++;
    entity_reference = EntityReference();
  } else if (MatchKind(Token::INVERTED_COMMAS)) {
    token_pos_++;
    Token next = Peek();
    entity_reference = EntityReference(next.GetValue());
    token_pos_++;
    Expect(Token::INVERTED_COMMAS);
  } else {
    throw std::runtime_error("Expected a entityRef");
  }

  return entity_reference;
}

Expression QueryParser::ExtractExpression() {
  Expression exp;

  if (MatchKind(Token::UNDERSCORE)) {
    exp.has_front_wildcard = true;
    token_pos_++;
  }

  EntityReference matchRef = ExtractEntityRef();
  exp.to_match = matchRef.GetIdentifier();

  if (MatchKind(Token::UNDERSCORE)) {
    exp.has_back_wildcard = true;
    token_pos_++;
  }

  return exp;
}

void QueryParser::ParseDeclaration() {
  Token next = Peek();
  Expect("assign");
  next = Peek();
  Expect(Token::IDENTIFIER);
  Synonym synonym = Synonym(EntityType::ASSIGN, next.GetValue());
  Expect(Token::SEMICOLON);
  query_string_builder_.AddDeclaration(synonym);
}

void QueryParser::ParseSelect() {
  if (CheckEnd()) {
    return;
  }
  Token next = Peek();
  Expect("Select");
  next = Peek();
  Expect(Token::IDENTIFIER);

  Synonym synonym = Synonym(EntityType::ASSIGN, next.GetValue());
  Select new_select = Select(synonym);

  query_string_builder_.AddSelect(new_select);
}

void QueryParser::ParseClause() {
  if (CheckEnd() || !MatchString("such")) {
    return;
  }
  token_pos_++;
  Expect("that");
  ParseFollows();
  ParseParent();
  // Check for each clause type, append below new clauses

  if (query_string_builder_.IsEmpty()) {
    throw std::runtime_error("Expected clause");
  }
}

void QueryParser::ParseFollows() {
  if (CheckEnd() || !MatchString("Follows")) {
    return;
  }

  Expect("Follows");

  if (MatchKind(Token::ASTERISK)) {
    return ParseFollowsT();
  }

  Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 = ExtractStmtRef();

  Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<FollowsClause> folCl =
      std::make_shared<FollowsClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(folCl);
}

void QueryParser::ParseFollowsT() {
  Expect(Token::ASTERISK);

  Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 = ExtractStmtRef();

  Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  Expect(Token::RIGHT_ROUND_BRACKET);

  std::shared_ptr<FollowsTClause> folCl =
      std::make_shared<FollowsTClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(folCl);
}

void QueryParser::ParsePattern() {
  if (CheckEnd() || !MatchString("pattern")) {
    return;
  }

  Expect(Token::IDENTIFIER);

  // Validates if assign-entity was captured
  Token next = Peek();
  Expect(Token::IDENTIFIER);
  Synonym synonym = Synonym(EntityType::ASSIGN, next.GetValue());

  Expect(Token::LEFT_ROUND_BRACKET);

  EntityReference entity_ref = ExtractEntityRef();

  Expect(Token::COMMA);

  Expression exp = ExtractExpression();

  Expect(Token::RIGHT_ROUND_BRACKET);

  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entity_ref, exp);
  query_string_builder_.AddQueryOperation(ptn);
}

void QueryParser::ParseQueryOperation() {
  while (token_pos_ < tokens_.size() - 1) {
    ParseClause();
    ParsePattern();
  }
}

void QueryParser::ParseParent() {
  if (CheckEnd() || !MatchString("Parent")) {
      return;
  }
  
  Expect("Parent");
  
  if (MatchKind(Token::ASTERISK)) {
    return ParseParentT();
  }

  Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 = ExtractStmtRef();

  Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ParentClause> parCl =
      std::make_shared<ParentClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(parCl);
}

void QueryParser::ParseParentT() {
  Expect(Token::ASTERISK);

  Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 = ExtractStmtRef();

  Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ParentTClause> parCl =
      std::make_shared<ParentTClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(parCl);
}
