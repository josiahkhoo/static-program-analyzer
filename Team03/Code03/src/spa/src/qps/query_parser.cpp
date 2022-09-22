#include "query_parser.h"

#include <stdexcept>

#include "common/clause/calls_clause.h"
#include "common/clause/calls_t_clause.h"
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
  tokens_ = TokenHandler();
  query_string_builder_ = QueryStringBuilder();
}

QueryString QueryParser::Parse(std::vector<Token> tokens) {
  tokens_ = TokenHandler(tokens);
  ParseDeclaration();
  ParseSelect();
  ParseQueryOperation();
  ParseCleanUpSyntax();
  return query_string_builder_.GetQueryString();
}

StatementReference QueryParser::ExtractStmtRef() {
  StatementReference statement_reference;

  if (tokens_.MatchKind(Token::IDENTIFIER)) {
    // Checks current declared synonyms to do matching
    Synonym synonym = query_string_builder_.GetSynonym(tokens_.Peek().GetValue());
    statement_reference = StatementReference(synonym);
  } else if (tokens_.MatchKind(Token::UNDERSCORE)) {
    statement_reference = StatementReference();
  } else if (tokens_.MatchKind(Token::NUMBER)) {
    statement_reference = StatementReference(stoi(tokens_.Peek().GetValue()));
  } else {
    throw SyntaxException("tokens_.Expected different stmtRef");
  }
  tokens_.Forward();
  return statement_reference;
}

EntityReference QueryParser::ExtractEntityRef() {
  EntityReference entity_reference;

  // Wildcard
  if (tokens_.MatchKind(Token::UNDERSCORE)) {
    tokens_.Forward();
    entity_reference = EntityReference();
  }
  // Identifier
  else if (tokens_.MatchKind(Token::INVERTED_COMMAS)) {
    tokens_.Forward();
    entity_reference = EntityReference(tokens_.Peek().GetValue());
    tokens_.Forward();
    tokens_.Expect(Token::INVERTED_COMMAS);
  }
  // Synonym
  else if (tokens_.MatchKind(Token::IDENTIFIER)) {
    entity_reference =
        EntityReference(query_string_builder_.GetSynonym(tokens_.Peek().GetValue()));
    tokens_.Forward();
  } else {
    throw SyntaxException("tokens_.Expected different entRef");
  }

  return entity_reference;
}

Expression QueryParser::ExtractExpression() {
  Expression exp;

  // Wildcard front
  if (tokens_.MatchKind(Token::UNDERSCORE)) {
    exp.has_front_wildcard = true;
    tokens_.Forward();
  }
  // Pattern to match
  if (tokens_.MatchKind(Token::INVERTED_COMMAS)) {
    tokens_.Forward();
    exp.to_match = GetExpression();
    tokens_.Expect(Token::INVERTED_COMMAS);
  }
  // Wildcard back
  if (tokens_.MatchKind(Token::UNDERSCORE)) {
    exp.has_back_wildcard = true;
    tokens_.Forward();
  }

  return exp;
}

std::string QueryParser::GetExpression() {
  std::string res;
  Token next = tokens_.Peek();
  while (next.IsNot(Token::INVERTED_COMMAS) &&
         next.IsNot(Token::RIGHT_ROUND_BRACKET)) {
    res.append(GetTerm());
    tokens_.Forward();
    next = tokens_.Peek();
  }
  return res;
}

std::string QueryParser::GetTerm() {
  std::string res;
  Token next = tokens_.Peek();
  // var_name, const_value, operator
  if (next.Is(Token::IDENTIFIER) || next.Is(Token::NUMBER)) {
    res.append(next.GetValue());
  } else if (next.Is(Token::PLUS) || next.Is(Token::MINUS) ||
             next.Is(Token::ASTERISK) || next.Is(Token::SLASH) ||
             next.Is(Token::PERCENT)) {
    res.append(next.GetValue());
    tokens_.Forward();
    res.append(GetTerm());
  }
  // ( exp )
  else if (next.Is(Token::LEFT_ROUND_BRACKET)) {
    tokens_.Forward();
    res.append("(");

    res.append(GetExpression());

    tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
    tokens_.Back();
    res.append(")");
  }

  if (res.empty()) {
    throw SyntaxException("Invalid expression");
  }
  return res;
}

void QueryParser::ParseDeclaration() {
  while (! tokens_.CheckEnd() && ! tokens_.MatchString("Select")) {
    Token next = tokens_.Peek();
    EntityType entType = ExtractEntityType();
    next = tokens_.Peek();
    tokens_.Expect(Token::IDENTIFIER);
    Synonym synonym = Synonym(entType, next.GetValue());
    query_string_builder_.AddDeclaration(synonym);
    while (tokens_.MatchKind(Token::COMMA)) {
      tokens_.Forward();
      next = tokens_.Peek();
      tokens_.Expect(Token::IDENTIFIER);
      synonym = Synonym(entType, next.GetValue());
      query_string_builder_.AddDeclaration(synonym);
    }
    tokens_.Expect(Token::SEMICOLON);
  }

  if (query_string_builder_.IsDeclarationsEmpty()) {
    throw SyntaxException("No declaration declared");
  }
}

EntityType QueryParser::ExtractEntityType() {
  EntityType result;
  if ( tokens_.MatchString("stmt")) {
    result = EntityType::STATEMENT;
  } else if ( tokens_.MatchString("read")) {
    result = EntityType::READ;
  } else if ( tokens_.MatchString("print")) {
    result = EntityType::PRINT;
  } else if ( tokens_.MatchString("call")) {
    result = EntityType::CALL;
  } else if ( tokens_.MatchString("while")) {
    result = EntityType::WHILE;
  } else if ( tokens_.MatchString("if")) {
    result = EntityType::IF;
  } else if ( tokens_.MatchString("assign")) {
    result = EntityType::ASSIGN;
  } else if ( tokens_.MatchString("variable")) {
    result = EntityType::VARIABLE;
  } else if ( tokens_.MatchString("constant")) {
    result = EntityType::CONSTANT;
  } else if ( tokens_.MatchString("procedure")) {
    result = EntityType::PROCEDURE;
  } else {
    throw SyntaxException("tokens_.Expected different declaration");
  }
  tokens_.Forward();
  return result;
}

void QueryParser::ParseSelect() {
  if ( tokens_.CheckEnd()) {
    return;
  }
  Token next = tokens_.Peek();
  tokens_.Expect("Select");
  next = tokens_.Peek();
  tokens_.Expect(Token::IDENTIFIER);

  Synonym synonym = query_string_builder_.GetSynonym(next.GetValue());
  Select new_select = Select(synonym);

  query_string_builder_.AddSelect(new_select);
}

bool QueryParser::ParseClause() {
  if ( tokens_.CheckEnd() || ! tokens_.MatchString("such")) {
    return false;
  }
  tokens_.Forward();
  tokens_.Expect("that");
  ParseFollows();
  ParseParent();
  ParseUses();
  ParseModifies();
  ParseCalls();
  // Check for each clause type, append below new clauses

  if (query_string_builder_.IsOperationsEmpty()) {
    throw SyntaxException("No operations or declarations declared");
  }
  return true;
}

void QueryParser::ParseFollows() {
  if ( tokens_.CheckEnd() || ! tokens_.MatchString("Follows")) {
    return;
  }

  tokens_.Expect("Follows");

  if (tokens_.MatchKind(Token::ASTERISK)) {
    return ParseFollowsT();
  }

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 = ExtractStmtRef();

  CheckFollowsParentRef(stmtRef1);

  tokens_.Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  CheckFollowsParentRef(stmtRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<FollowsClause> folCl =
      std::make_shared<FollowsClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(folCl);
}

void QueryParser::ParseFollowsT() {
  tokens_.Expect(Token::ASTERISK);

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 = ExtractStmtRef();

  CheckFollowsParentRef(stmtRef1);

  tokens_.Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  CheckFollowsParentRef(stmtRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);

  std::shared_ptr<FollowsTClause> folCl =
      std::make_shared<FollowsTClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(folCl);
}

void QueryParser::CheckFollowsParentRef(
    const StatementReference &stmtRef) const {
  if (stmtRef.IsSynonym() &&
      (stmtRef.IsEntityType(VARIABLE) || stmtRef.IsEntityType(CONSTANT) ||
       stmtRef.IsEntityType(PROCEDURE))) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
}

bool QueryParser::ParsePattern() {
  if ( tokens_.CheckEnd() || ! tokens_.MatchString("pattern")) {
    return false;
  }

  tokens_.Expect(Token::IDENTIFIER);

  // Validates if assign-entity was captured
  Token next = tokens_.Peek();
  tokens_.Expect(Token::IDENTIFIER);
  Synonym synonym = query_string_builder_.GetSynonym(next.GetValue());
  CheckPatternSyn(synonym);

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  EntityReference entity_ref = ExtractEntityRef();

  if (entity_ref.IsSynonym() &&
      entity_ref.GetSynonym().GetEntityType() != EntityType::VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }

  tokens_.Expect(Token::COMMA);

  Expression exp = ExtractExpression();

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);

  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(synonym, entity_ref, exp);
  query_string_builder_.AddQueryOperation(ptn);
  return true;
}

void QueryParser::CheckPatternSyn(const Synonym &synonym) const {
  if (!synonym.IsEntityType(ASSIGN)) {
    throw SemanticException("Syn-assign not supported");
  }
}

void QueryParser::ParseQueryOperation() {
  while (tokens_.IsNotEnd()) {
    bool found_clause = ParseClause();
    bool found_pattern = ParsePattern();
    if (!(found_clause || found_pattern)) {
      break;
    }
  }
}

void QueryParser::ParseParent() {
  if ( tokens_.CheckEnd() || ! tokens_.MatchString("Parent")) {
    return;
  }

  tokens_.Expect("Parent");

  if (tokens_.MatchKind(Token::ASTERISK)) {
    return ParseParentT();
  }

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 = ExtractStmtRef();

  CheckFollowsParentRef(stmtRef1);

  tokens_.Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  CheckFollowsParentRef(stmtRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ParentClause> parCl =
      std::make_shared<ParentClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(parCl);
}

void QueryParser::ParseParentT() {
  tokens_.Expect(Token::ASTERISK);

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 = ExtractStmtRef();

  tokens_.Expect(Token::COMMA);

  CheckFollowsParentRef(stmtRef1);

  // Get stmt2
  StatementReference stmtRef2 = ExtractStmtRef();

  CheckFollowsParentRef(stmtRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ParentTClause> parCl =
      std::make_shared<ParentTClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(parCl);
}

void QueryParser::ParseUses() {
  if ( tokens_.CheckEnd() || ! tokens_.MatchString("Uses")) {
    return;
  }

  tokens_.Expect("Uses");

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  CheckUsesLhs();
}

void QueryParser::CheckUsesLhs() {
  Token next = tokens_.Peek();
  if (next.Is(Token::UNDERSCORE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
  if (next.Is(Token::IDENTIFIER)) {
    Synonym syn = query_string_builder_.GetSynonym(next.GetValue());
    if (syn.IsEntityType(PROCEDURE)) {
      ParseUsesP();
    } else {
      ParseUsesS();
    }
  } else if (next.Is(Token::INVERTED_COMMAS)) {
    ParseUsesP();
  } else {
    ParseUsesS();
  }
}

void QueryParser::CheckEntityRhs(const EntityReference &entRef) const {
  if (entRef.IsSynonym() && entRef.GetSynonym().GetEntityType() != VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }
}

void QueryParser::ParseUsesS() {
  StatementReference stmtRef = ExtractStmtRef();

  if (stmtRef.IsSynonym() &&
      !(stmtRef.IsEntityType(ASSIGN) || stmtRef.IsEntityType(PRINT) ||
        stmtRef.IsEntityType(STATEMENT) || stmtRef.IsEntityType(IF) ||
        stmtRef.IsEntityType(WHILE) || stmtRef.IsEntityType(CALL))) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  tokens_.Expect(Token::COMMA);

  // Get ent
  EntityReference entRef = ExtractEntityRef();

  CheckEntityRhs(entRef);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<UsesSClause> usesCl =
      std::make_shared<UsesSClause>(stmtRef, entRef);
  query_string_builder_.AddQueryOperation(usesCl);
}

void QueryParser::ParseUsesP() {
  EntityReference entRef1 = ExtractEntityRef();

  if (!(entRef1.IsIdentifier() || entRef1.IsEntityType(PROCEDURE))) {
    throw SemanticException("tokens_.Expected identifier entity reference");
  }

  tokens_.Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 = ExtractEntityRef();

  CheckEntityRhs(entRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<UsesPClause> usesCl =
      std::make_shared<UsesPClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(usesCl);
}

void QueryParser::ParseModifies() {
  if ( tokens_.CheckEnd() || ! tokens_.MatchString("Modifies")) {
    return;
  }

  tokens_.Expect("Modifies");

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  CheckModifiesLhs();
}

void QueryParser::CheckModifiesLhs() {
  Token next = tokens_.Peek();
  if (next.Is(Token::UNDERSCORE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
  if (next.Is(Token::IDENTIFIER)) {
    Synonym syn = query_string_builder_.GetSynonym(next.GetValue());
    if (syn.IsEntityType(PROCEDURE)) {
      ParseModifiesP();
    } else {
      ParseModifiesS();
    }
  } else if (next.Is(Token::INVERTED_COMMAS)) {
    ParseModifiesP();
  } else {
    ParseModifiesS();
  }
}

void QueryParser::ParseModifiesS() {
  StatementReference stmtRef = ExtractStmtRef();

  if (stmtRef.IsSynonym() &&
      !(stmtRef.IsEntityType(ASSIGN) || stmtRef.IsEntityType(READ) ||
        stmtRef.IsEntityType(STATEMENT) || stmtRef.IsEntityType(IF) ||
        stmtRef.IsEntityType(WHILE) || stmtRef.IsEntityType(CALL))) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  tokens_.Expect(Token::COMMA);

  // Get ent
  EntityReference entRef = ExtractEntityRef();

  CheckEntityRhs(entRef);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ModifiesSClause> modCl =
      std::make_shared<ModifiesSClause>(stmtRef, entRef);
  query_string_builder_.AddQueryOperation(modCl);
}

void QueryParser::ParseModifiesP() {
  EntityReference entRef1 = ExtractEntityRef();

  if (!(entRef1.IsIdentifier() || entRef1.IsEntityType(PROCEDURE))) {
    throw SemanticException("tokens_.Expected identifier entity reference");
  }

  tokens_.Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 = ExtractEntityRef();

  CheckEntityRhs(entRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ModifiesPClause> modCl =
      std::make_shared<ModifiesPClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(modCl);
}

void QueryParser::ParseCalls() {
  if ( tokens_.CheckEnd() || ! tokens_.MatchString("Calls")) {
    return;
  }

  tokens_.Expect("Calls");

  if (tokens_.MatchKind(Token::ASTERISK)) {
    return ParseCallsT();
  }

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  EntityReference entRef1 = ExtractEntityRef();

  CheckProcedureEntity(entRef1);

  tokens_.Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 = ExtractEntityRef();

  CheckProcedureEntity(entRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<CallsClause> callsCl =
      std::make_shared<CallsClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(callsCl);
}

void QueryParser::ParseCallsT() {
  tokens_.Expect(Token::ASTERISK);

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  EntityReference entRef1 = ExtractEntityRef();

  CheckProcedureEntity(entRef1);

  tokens_.Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 = ExtractEntityRef();

  CheckProcedureEntity(entRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<CallsTClause> callsTCl =
      std::make_shared<CallsTClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(callsTCl);
}

void QueryParser::CheckProcedureEntity(const EntityReference &entRef) const {
  if (!entRef.IsEntityType(PROCEDURE)) {
    throw SemanticException("tokens_.Expected procedure reference");
  }
}

void QueryParser::ParseCleanUpSyntax() {
  if (! tokens_.CheckEnd() && tokens_.Peek().IsNot(Token::END)) {
    throw SyntaxException("Untokens_.Expected additional token(s)");
  }
}
