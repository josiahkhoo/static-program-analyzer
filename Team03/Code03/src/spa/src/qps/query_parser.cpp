#include "query_parser.h"

#include <iostream>
#include <stdexcept>

#include "common/clause/pattern.h"
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
    ParsePattern();
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
  Token next = Peek(token_pos_);
  if (next.IsNot(Token::IDENTIFIER)) {
    return false;
  }
  return (next.GetValue() == s);
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

EntityReference QueryParser::ExtractEntityRef() {
  EntityReference entity_reference;

  if (MatchKind(Token::UNDERSCORE)) {
    token_pos_++;
    entity_reference = EntityReference();
  } else if (MatchKind(Token::INVERTED_COMMAS)) {
    token_pos_++;
    Token next = Peek(token_pos_);
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
    exp.hasFrontWildcard = true;
    token_pos_++;
  }
  EntityReference matchRef = ExtractEntityRef();
  exp.toMatch = matchRef.GetIdentifier();

  if (MatchKind(Token::UNDERSCORE)) {
    exp.hasBackWildcard = true;
    token_pos_++;
  }

  return exp;
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
  if (!MatchString("such")) {
    return;
  }
  token_pos_++;
  Expect("that");
  ParseFollow();
  // Check for each clause type, append below new clauses
}

void QueryParser::ParseFollow() {
  if (!MatchString("Follows")) {
    return;
  }

  Expect("Follows");

  if (MatchKind(Token::ASTERISK)) {
    return ParseFollowT();
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
  query_string_builder_.AddClause(folCl);
}

void QueryParser::ParseFollowT() {
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
  query_string_builder_.AddClause(folCl);
}

void QueryParser::ParsePattern() {
  if (!MatchString("pattern")) {
    return;
  }

  Expect(Token::IDENTIFIER);

  // Validates if assign-entity was captured
  Token next = Peek(token_pos_);
  Expect(Token::IDENTIFIER);
  Synonym synonym = Synonym(EntityType::ASSIGN, next.GetValue());

  Expect(Token::LEFT_ROUND_BRACKET);

  EntityReference entityRef = ExtractEntityRef();

  Expect(Token::COMMA);

  Expression exp = ExtractExpression();

  Expect(Token::RIGHT_ROUND_BRACKET);

  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entityRef, exp);
  query_string_builder_.AddPattern(ptn);
}
