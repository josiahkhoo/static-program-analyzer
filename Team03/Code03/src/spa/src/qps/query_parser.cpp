#include "query_parser.h"

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
#include "qps/query_parser_util.h"

QueryParser::QueryParser() = default;

QueryString QueryParser::Parse(std::vector<Token> tokens) {
  tokens_ = TokenHandler(tokens);
  query_string_builder_ = QueryStringBuilder();
  ParseDeclaration();
  ParseSelect();
  ParseQueryOperation();
  ParseCleanUpSyntax();
  return query_string_builder_.GetQueryString();
}

void QueryParser::ParseDeclaration() {
  while (!tokens_.CheckEnd() && !tokens_.MatchString("Select")) {
    Token next = tokens_.Peek();
    EntityType entType = QueryParserUtil::ExtractEntityType(tokens_);
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

void QueryParser::ParseSelect() {
  if (tokens_.CheckEnd()) {
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
  if (tokens_.CheckEnd() || !tokens_.MatchString("such")) {
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
  if (tokens_.CheckEnd() || !tokens_.MatchString("Follows")) {
    return;
  }

  tokens_.Expect("Follows");

  if (tokens_.MatchKind(Token::ASTERISK)) {
    return ParseFollowsT();
  }

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckFollowsParentRef(stmtRef1);

  tokens_.Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckFollowsParentRef(stmtRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<FollowsClause> folCl =
      std::make_shared<FollowsClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(folCl);
}

void QueryParser::ParseFollowsT() {
  tokens_.Expect(Token::ASTERISK);

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckFollowsParentRef(stmtRef1);

  tokens_.Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckFollowsParentRef(stmtRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);

  std::shared_ptr<FollowsTClause> folCl =
      std::make_shared<FollowsTClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(folCl);
}

bool QueryParser::ParsePattern() {
  if (tokens_.CheckEnd() || !tokens_.MatchString("pattern")) {
    return false;
  }

  tokens_.Expect(Token::IDENTIFIER);

  // Validates if assign-entity was captured
  Token next = tokens_.Peek();
  tokens_.Expect(Token::IDENTIFIER);
  Synonym synonym = query_string_builder_.GetSynonym(next.GetValue());
  QueryParserUtil::CheckPatternSyn(synonym);

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  EntityReference entity_ref =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  if (entity_ref.IsSynonym() &&
      entity_ref.GetSynonym().GetEntityType() != EntityType::VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }

  tokens_.Expect(Token::COMMA);

  Expression exp =
      QueryParserUtil::ExtractExpression(tokens_, query_string_builder_);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);

  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(synonym, entity_ref, exp);
  query_string_builder_.AddQueryOperation(ptn);
  return true;
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
  if (tokens_.CheckEnd() || !tokens_.MatchString("Parent")) {
    return;
  }

  tokens_.Expect("Parent");

  if (tokens_.MatchKind(Token::ASTERISK)) {
    return ParseParentT();
  }

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckFollowsParentRef(stmtRef1);

  tokens_.Expect(Token::COMMA);

  // Get stmt2
  StatementReference stmtRef2 =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckFollowsParentRef(stmtRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ParentClause> parCl =
      std::make_shared<ParentClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(parCl);
}

void QueryParser::ParseParentT() {
  tokens_.Expect(Token::ASTERISK);

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  // Get stmt1
  StatementReference stmtRef1 =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  tokens_.Expect(Token::COMMA);

  QueryParserUtil::CheckFollowsParentRef(stmtRef1);

  // Get stmt2
  StatementReference stmtRef2 =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckFollowsParentRef(stmtRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ParentTClause> parCl =
      std::make_shared<ParentTClause>(stmtRef1, stmtRef2);
  query_string_builder_.AddQueryOperation(parCl);
}

void QueryParser::ParseUses() {
  if (tokens_.CheckEnd() || !tokens_.MatchString("Uses")) {
    return;
  }

  tokens_.Expect("Uses");

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  CheckUsesLhs(tokens_, query_string_builder_);
}

void QueryParser::ParseUsesS() {
  StatementReference stmtRef =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  if (stmtRef.IsSynonym() &&
      !(stmtRef.IsEntityType(ASSIGN) || stmtRef.IsEntityType(PRINT) ||
        stmtRef.IsEntityType(STATEMENT) || stmtRef.IsEntityType(IF) ||
        stmtRef.IsEntityType(WHILE) || stmtRef.IsEntityType(CALL))) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  tokens_.Expect(Token::COMMA);

  // Get ent
  EntityReference entRef =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckEntityRhs(entRef);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<UsesSClause> usesCl =
      std::make_shared<UsesSClause>(stmtRef, entRef);
  query_string_builder_.AddQueryOperation(usesCl);
}

void QueryParser::ParseUsesP() {
  EntityReference entRef1 =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  if (!(entRef1.IsIdentifier() || entRef1.IsEntityType(PROCEDURE))) {
    throw SemanticException("tokens_.Expected identifier entity reference");
  }

  tokens_.Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckEntityRhs(entRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<UsesPClause> usesCl =
      std::make_shared<UsesPClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(usesCl);
}

void QueryParser::ParseModifies() {
  if (tokens_.CheckEnd() || !tokens_.MatchString("Modifies")) {
    return;
  }

  tokens_.Expect("Modifies");

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  CheckModifiesLhs(tokens_, query_string_builder_);
}

void QueryParser::ParseModifiesS() {
  StatementReference stmtRef =
      QueryParserUtil::ExtractStmtRef(tokens_, query_string_builder_);

  if (stmtRef.IsSynonym() &&
      !(stmtRef.IsEntityType(ASSIGN) || stmtRef.IsEntityType(READ) ||
        stmtRef.IsEntityType(STATEMENT) || stmtRef.IsEntityType(IF) ||
        stmtRef.IsEntityType(WHILE) || stmtRef.IsEntityType(CALL))) {
    throw SemanticException("Synonym is of a wrong entity type");
  }

  tokens_.Expect(Token::COMMA);

  // Get ent
  EntityReference entRef =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckEntityRhs(entRef);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ModifiesSClause> modCl =
      std::make_shared<ModifiesSClause>(stmtRef, entRef);
  query_string_builder_.AddQueryOperation(modCl);
}

void QueryParser::ParseModifiesP() {
  EntityReference entRef1 =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  if (!(entRef1.IsIdentifier() || entRef1.IsEntityType(PROCEDURE))) {
    throw SemanticException("tokens_.Expected identifier entity reference");
  }

  tokens_.Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckEntityRhs(entRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<ModifiesPClause> modCl =
      std::make_shared<ModifiesPClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(modCl);
}

void QueryParser::ParseCalls() {
  if (tokens_.CheckEnd() || !tokens_.MatchString("Calls")) {
    return;
  }

  tokens_.Expect("Calls");

  if (tokens_.MatchKind(Token::ASTERISK)) {
    return ParseCallsT();
  }

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  EntityReference entRef1 =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckProcedureEntity(entRef1);

  tokens_.Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckProcedureEntity(entRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<CallsClause> callsCl =
      std::make_shared<CallsClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(callsCl);
}

void QueryParser::ParseCallsT() {
  tokens_.Expect(Token::ASTERISK);

  tokens_.Expect(Token::LEFT_ROUND_BRACKET);

  EntityReference entRef1 =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckProcedureEntity(entRef1);

  tokens_.Expect(Token::COMMA);

  // Get ent2
  EntityReference entRef2 =
      QueryParserUtil::ExtractEntityRef(tokens_, query_string_builder_);

  QueryParserUtil::CheckProcedureEntity(entRef2);

  tokens_.Expect(Token::RIGHT_ROUND_BRACKET);
  std::shared_ptr<CallsTClause> callsTCl =
      std::make_shared<CallsTClause>(entRef1, entRef2);
  query_string_builder_.AddQueryOperation(callsTCl);
}

void QueryParser::ParseCleanUpSyntax() {
  if (!tokens_.CheckEnd() && tokens_.Peek().IsNot(Token::END)) {
    throw SyntaxException("Expected additional token(s)");
  }
}

void QueryParser::CheckUsesLhs(TokenHandler tokens,
                                   const QueryStringBuilder& builder) {
  Token next = tokens.Peek();
  if (next.Is(Token::UNDERSCORE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
  if (next.Is(Token::IDENTIFIER)) {
    Synonym syn = builder.GetSynonym(next.GetValue());
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

void QueryParser::CheckModifiesLhs(TokenHandler tokens,
                                       const QueryStringBuilder& builder) {
  Token next = tokens.Peek();
  if (next.Is(Token::UNDERSCORE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
  if (next.Is(Token::IDENTIFIER)) {
    Synonym syn = builder.GetSynonym(next.GetValue());
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
