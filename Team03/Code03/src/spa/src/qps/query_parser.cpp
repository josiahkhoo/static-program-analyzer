#include "query_parser.h"

#include <stdexcept>

#include "common/clause/modifies_p_clause.h"
#include "common/clause/modifies_s_clause.h"
#include "common/clause/parent_clause.h"
#include "common/clause/parent_t_clause.h"
#include "common/clause/pattern.h"
#include "common/clause/select.h"
#include "common/clause/uses_p_clause.h"
#include "common/clause/uses_s_clause.h"
#include "common/entity/assign_entity.h"
#include "qps/exceptions/semantic_exception.h"
#include "qps/exceptions/syntax_exception.h"

QueryParser::QueryParser() {
  tokens_ = {};
  query_string_builder_ = QueryStringBuilder();
}

QueryString QueryParser::Parse(std::vector<Token> tokens) {
  tokens_ = tokens;
  ParseDeclaration();
  ParseSelect();
  ParseQueryOperation();
  ParseCleanUpSyntax();
  return query_string_builder_.GetQueryString();
}

Token QueryParser::Peek() {
  if (token_pos_ >= tokens_.size()) {
    throw SyntaxException("No more tokens");
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

void QueryParser::Expect(Token::Kind kind) {
  if (MatchKind(kind)) {
    token_pos_++;
  } else {
    throw SyntaxException("Expected different token");
  }
}

void QueryParser::Expect(const std::string &s) {
  if (MatchString(s)) {
    token_pos_++;
  } else {
    throw SyntaxException("Expected different string");
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
    throw SyntaxException("Expected different stmtRef");
  }
  token_pos_++;
  return statement_reference;
}

EntityReference QueryParser::ExtractEntityRef() {
  EntityReference entity_reference;

  // Wildcard
  if (MatchKind(Token::UNDERSCORE)) {
    token_pos_++;
    entity_reference = EntityReference();
  }
  // Identifier
  else if (MatchKind(Token::INVERTED_COMMAS)) {
    token_pos_++;
    entity_reference = EntityReference(Peek().GetValue());
    token_pos_++;
    Expect(Token::INVERTED_COMMAS);
  }
  // Synonym
  else if (MatchKind(Token::IDENTIFIER)) {
    entity_reference =
        EntityReference(query_string_builder_.GetSynonym(Peek().GetValue()));
    token_pos_++;
  } else {
    throw SyntaxException("Expected different entRef");
  }

  return entity_reference;
}

Expression QueryParser::ExtractExpression() {
  Expression exp;

  // Wildcard front
  if (MatchKind(Token::UNDERSCORE)) {
    exp.has_front_wildcard = true;
    token_pos_++;
  }
  // Pattern to match
  if (MatchKind(Token::INVERTED_COMMAS)) {
    token_pos_++;
    std::string pattern;
    while (Peek().IsNot(Token::INVERTED_COMMAS)) {
      Token next = Peek();
      token_pos_++;
      pattern.append(next.GetValue());
    }
    exp.to_match = pattern;
    Expect(Token::INVERTED_COMMAS);
  }
  // Wildcard back
  if (MatchKind(Token::UNDERSCORE)) {
    exp.has_back_wildcard = true;
    token_pos_++;
  }

  return exp;
}

void QueryParser::ParseDeclaration() {
  while (!CheckEnd() && !MatchString("Select")) {
    Token next = Peek();
    EntityType entType = ExpectEntityType();
    next = Peek();
    Expect(Token::IDENTIFIER);
    Synonym synonym = Synonym(entType, next.GetValue());
    query_string_builder_.AddDeclaration(synonym);
    while (MatchKind(Token::COMMA)) {
      token_pos_++;
      next = Peek();
      Expect(Token::IDENTIFIER);
      synonym = Synonym(entType, next.GetValue());
      query_string_builder_.AddDeclaration(synonym);
    }
    Expect(Token::SEMICOLON);
  }

  if (query_string_builder_.IsDeclarationsEmpty()) {
    throw SyntaxException("No declaration declared");
  }
}

bool QueryParser::IsNextEntityType() {
  try {
    ExpectEntityType();
    token_pos_--;
    return true;
  } catch (const SyntaxException &ex) {
    return false;
  }
}

EntityType QueryParser::ExpectEntityType() {
  if (MatchString("stmt")) {
    token_pos_++;
    return EntityType::STATEMENT;
  } else if (MatchString("read")) {
    token_pos_++;
    return EntityType::READ;
  } else if (MatchString("print")) {
    token_pos_++;
    return EntityType::PRINT;
  } else if (MatchString("call")) {
    token_pos_++;
    return EntityType::CALL;
  } else if (MatchString("while")) {
    token_pos_++;
    return EntityType::WHILE;
  } else if (MatchString("if")) {
    token_pos_++;
    return EntityType::IF;
  } else if (MatchString("assign")) {
    token_pos_++;
    return EntityType::ASSIGN;
  } else if (MatchString("variable")) {
    token_pos_++;
    return EntityType::VARIABLE;
  } else if (MatchString("constant")) {
    token_pos_++;
    return EntityType::CONSTANT;
  } else if (MatchString("procedure")) {
    token_pos_++;
    return EntityType::PROCEDURE;
  } else {
    throw SyntaxException("Expected different declaration");
  }
}

void QueryParser::ParseSelect() {
  if (CheckEnd()) {
    return;
  }
  Token next = Peek();
  Expect("Select");
  next = Peek();
  Expect(Token::IDENTIFIER);

  Synonym synonym = query_string_builder_.GetSynonym(next.GetValue());
  Select new_select = Select(synonym);

  query_string_builder_.AddSelect(new_select);
}

bool QueryParser::ParseClause() {
  if (CheckEnd() || !MatchString("such")) {
    return false;
  }
  token_pos_++;
  Expect("that");
  ParseFollows();
  ParseParent();
  ParseUsesS();
  ParseModifiesS();
  // Check for each clause type, append below new clauses

  if (query_string_builder_.IsOperationsEmpty()) {
    throw SyntaxException("No operations or declarations declared");
  }
  return true;
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

  if (stmtRef1.IsSynonym() &&
      (stmtRef1.GetSynonym().GetEntityType() == EntityType::VARIABLE ||
       stmtRef1.GetSynonym().GetEntityType() == EntityType::CONSTANT ||
       stmtRef1.GetSynonym().GetEntityType() == EntityType::PROCEDURE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  if (stmtRef2.IsSynonym() &&
      (stmtRef2.GetSynonym().GetEntityType() == EntityType::VARIABLE ||
       stmtRef2.GetSynonym().GetEntityType() == EntityType::CONSTANT ||
       stmtRef2.GetSynonym().GetEntityType() == EntityType::PROCEDURE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

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

  if (stmtRef1.IsSynonym() &&
      (stmtRef1.GetSynonym().GetEntityType() == EntityType::VARIABLE ||
       stmtRef1.GetSynonym().GetEntityType() == EntityType::CONSTANT ||
       stmtRef1.GetSynonym().GetEntityType() == EntityType::PROCEDURE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  if (stmtRef2.IsSynonym() &&
      (stmtRef2.GetSynonym().GetEntityType() == EntityType::VARIABLE ||
       stmtRef2.GetSynonym().GetEntityType() == EntityType::CONSTANT ||
       stmtRef2.GetSynonym().GetEntityType() == EntityType::PROCEDURE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  Expect(Token::RIGHT_ROUND_BRACKET);

  std::shared_ptr<FollowsTClause> folCl =
      std::make_shared<FollowsTClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(folCl);
}

bool QueryParser::ParsePattern() {
  if (CheckEnd() || !MatchString("pattern")) {
    return false;
  }

  Expect(Token::IDENTIFIER);

  // Validates if assign-entity was captured
  Token next = Peek();
  Expect(Token::IDENTIFIER);
  Synonym synonym = Synonym(EntityType::ASSIGN, next.GetValue());

  Expect(Token::LEFT_ROUND_BRACKET);

  EntityReference entity_ref = ExtractEntityRef();

  if (entity_ref.IsSynonym() &&
      entity_ref.GetSynonym().GetEntityType() != EntityType::VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }

  Expect(Token::COMMA);

  Expression exp = ExtractExpression();

  Expect(Token::RIGHT_ROUND_BRACKET);

  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(synonym, entity_ref, exp);
  query_string_builder_.AddQueryOperation(ptn);
  return true;
}

void QueryParser::ParseQueryOperation() {
  while (token_pos_ < tokens_.size() - 1) {
    bool found_clause = ParseClause();
    bool found_pattern = ParsePattern();
    if (!(found_clause || found_pattern)) {
      break;
    }
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

  if (stmtRef1.IsSynonym() &&
      (stmtRef1.GetSynonym().GetEntityType() == EntityType::VARIABLE ||
       stmtRef1.GetSynonym().GetEntityType() == EntityType::CONSTANT ||
       stmtRef1.GetSynonym().GetEntityType() == EntityType::PROCEDURE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  if (stmtRef2.IsSynonym() &&
      (stmtRef2.GetSynonym().GetEntityType() == EntityType::VARIABLE ||
       stmtRef2.GetSynonym().GetEntityType() == EntityType::CONSTANT ||
       stmtRef2.GetSynonym().GetEntityType() == EntityType::PROCEDURE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

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

  if (stmtRef1.IsSynonym() &&
      (stmtRef1.GetSynonym().GetEntityType() == EntityType::VARIABLE ||
       stmtRef1.GetSynonym().GetEntityType() == EntityType::CONSTANT ||
       stmtRef1.GetSynonym().GetEntityType() == EntityType::PROCEDURE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  if (stmtRef2.IsSynonym() &&
      (stmtRef2.GetSynonym().GetEntityType() == EntityType::VARIABLE ||
       stmtRef2.GetSynonym().GetEntityType() == EntityType::CONSTANT ||
       stmtRef2.GetSynonym().GetEntityType() == EntityType::PROCEDURE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ParentTClause> parCl =
      std::make_shared<ParentTClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(parCl);
}

void QueryParser::ParseUsesS() {
  if (CheckEnd() || !MatchString("Uses")) {
    return;
  }

  Expect("Uses");

  if (MatchKind(Token::ASTERISK)) {
    return ParseUsesP();
  }

  Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt
  StatementReference stmtRef = ExtractStmtRef();

  if (stmtRef.IsSynonym() &&
      !(stmtRef.GetSynonym().GetEntityType() == EntityType::ASSIGN ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::PRINT ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::IF ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::WHILE ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::PROCEDURE ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::CALL)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  Expect(Token::COMMA);

  // Get ent
  EntityReference entRef = ExtractEntityRef();

  if (entRef.IsSynonym() &&
      entRef.GetSynonym().GetEntityType() != EntityType::VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }

  Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<UsesSClause> usesCl =
      std::make_shared<UsesSClause>(stmtRef, entRef);
  query_string_builder_.AddQueryOperation(usesCl);
}

void QueryParser::ParseUsesP() {
  Expect(Token::ASTERISK);

  Expect(Token::LEFT_ROUND_BRACKET);

  // Get ent1
  EntityReference entRef1 = ExtractEntityRef();

  if (!(entRef1.IsWildCard() || entRef1.IsIdentifier())) {
    throw SemanticException("Expected identifier entity reference");
  }

  Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 = ExtractEntityRef();

  if (entRef2.IsSynonym() &&
      entRef2.GetSynonym().GetEntityType() != EntityType::VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }

  Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<UsesPClause> usesCl =
      std::make_shared<UsesPClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(usesCl);
}

void QueryParser::ParseModifiesS() {
  if (CheckEnd() || !MatchString("Modifies")) {
    return;
  }

  Expect("Modifies");

  if (MatchKind(Token::ASTERISK)) {
    return ParseModifiesP();
  }

  Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt
  StatementReference stmtRef = ExtractStmtRef();

  if (stmtRef.IsSynonym() &&
      !(stmtRef.GetSynonym().GetEntityType() == EntityType::ASSIGN ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::READ ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::IF ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::WHILE ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::PROCEDURE ||
        stmtRef.GetSynonym().GetEntityType() == EntityType::CALL)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  Expect(Token::COMMA);

  // Get ent
  EntityReference entRef = ExtractEntityRef();

  if (entRef.IsSynonym() &&
      entRef.GetSynonym().GetEntityType() != EntityType::VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }

  Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ModifiesSClause> modCl =
      std::make_shared<ModifiesSClause>(stmtRef, entRef);
  query_string_builder_.AddQueryOperation(modCl);
}

void QueryParser::ParseModifiesP() {
  Expect(Token::ASTERISK);

  Expect(Token::LEFT_ROUND_BRACKET);

  // Get ent1
  EntityReference entRef1 = ExtractEntityRef();

  if (!(entRef1.IsWildCard() || entRef1.IsIdentifier())) {
    throw SemanticException("Expected identifier entity reference");
  }

  Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 = ExtractEntityRef();

  if (entRef2.IsSynonym() &&
      entRef2.GetSynonym().GetEntityType() != EntityType::VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }

  Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ModifiesPClause> modCl =
      std::make_shared<ModifiesPClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(modCl);
}

void QueryParser::ParseCleanUpSyntax() {
  if (!CheckEnd() && Peek().IsNot(Token::END)) {
    throw SyntaxException("Unexpected additional token(s)");
  }
}
