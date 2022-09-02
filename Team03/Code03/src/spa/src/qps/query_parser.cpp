#include "query_parser.h"

#include <iostream>
#include <stdexcept>

#include "common/clause/select.h"

QueryString QueryParser::Parse(std::vector<Token> tokens) {
  try {
    tokens_ = tokens;
    ParseSelect();
    ParseSuchThat();
  } catch (const std::runtime_error& e_) {
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

bool QueryParser::MatchString(const std::string& s) {
  return (Peek(token_pos_).GetValue() == s);
}

bool QueryParser::MatchStmtRef() {
  return MatchKind(Token::IDENTIFIER) || MatchKind(Token::UNDERSCORE) || MatchKind(Token::NUMBER);
}

void QueryParser::Expect(Token::Kind kind) {
  if (MatchKind(kind)) {
    token_pos_++;
  } else {
    throw std::runtime_error("Expected a different token kind");
  }
}

void QueryParser::Expect(const std::string& s) {
  if (MatchString(s)) {
    token_pos_++;
  } else {
    throw std::runtime_error("Expected a different token string");
  }
}

void QueryParser::ExpectStmtRef() {
  if (MatchStmtRef()) {
    token_pos_++;
  } else {
    throw std::runtime_error("Expected a stmtRef");
  }
}

void QueryParser::ParseSelect() {
  next_ = Peek(token_pos_);
  Expect("Select");
  next_ = Peek(token_pos_);
  Expect(Token::IDENTIFIER);

  EntityReference new_entity = EntityReference();
  new_entity.SetIdentifier(next_.GetValue());
  Select new_select = Select(new_entity);

  query_string_builder_.AddSelect(new_select);
}

void QueryParser::ParseSuchThat() {
  while (!MatchKind(Token::END)) {
    if (MatchString("such")) {
      token_pos_++;
      Expect("that");
      // Check for each clause type
      ParseFollow();
    } else {
      throw std::runtime_error("Unexpected token: " + Peek(token_pos_).GetValue());
    }
  }
}

void QueryParser::ParseFollow() {
  Expect("Follows");
  Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  std::string raw_stmtRef1 = Peek(token_pos_).GetValue();
  StatementReference stmtRef1 = ExtractStmtRef(raw_stmtRef1);

  // Get stmt2
  std::string raw_stmtRef2 = Peek(token_pos_).GetValue();
  StatementReference stmtRef2 = ExtractStmtRef(raw_stmtRef2);

  Expect(Token::RIGHT_ROUND_BRACKET);
  FollowsClause folCl = FollowsClause(stmtRef1, stmtRef2);
  query_string_builder_.AddFollows(folCl);
}

StatementReference QueryParser::ExtractStmtRef(const std::string&) {
  std::string raw_stmtRef = Peek(token_pos_).GetValue();
  ExpectStmtRef();

  StatementReference stmtRef = *new StatementReference();
  if (MatchKind(Token::IDENTIFIER)) {
    stmtRef.SetSynonym(raw_stmtRef);
  } else if (MatchKind(Token::UNDERSCORE)) {
    stmtRef.SetWildCard();
  } else {
    stmtRef.SetLineNumber(raw_stmtRef);
  }
  return stmtRef;
}
