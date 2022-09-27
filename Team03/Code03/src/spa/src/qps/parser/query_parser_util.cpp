#include "query_parser_util.h"

#include "qps/exceptions/semantic_exception.h"
#include "qps/exceptions/syntax_exception.h"

StatementReference QueryParserUtil::ExtractStmtRef(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  StatementReference statement_reference;
  if (tokens->MatchKind(Token::IDENTIFIER)) {
    // Checks current declared synonyms to do matching
    Synonym synonym = builder.GetSynonym(tokens->PeekValue());
    statement_reference = StatementReference(synonym);
  } else if (tokens->MatchKind(Token::UNDERSCORE)) {
    statement_reference = StatementReference();
  } else if (tokens->MatchKind(Token::NUMBER)) {
    statement_reference = StatementReference(stoi(tokens->PeekValue()));
  } else {
    throw SyntaxException("Expected different stmtRef");
  }
  tokens->Forward();
  return statement_reference;
}

EntityReference QueryParserUtil::ExtractEntityRef(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  EntityReference entity_reference;
  // Wildcard
  if (tokens->MatchKind(Token::UNDERSCORE)) {
    tokens->Forward();
    entity_reference = EntityReference();
  }
  // Identifier
  else if (tokens->MatchKind(Token::INVERTED_COMMAS)) {
    tokens->Forward();
    entity_reference = EntityReference(tokens->PeekValue());
    tokens->Forward();
    tokens->Expect(Token::INVERTED_COMMAS);
  }
  // Synonym
  else if (tokens->MatchKind(Token::IDENTIFIER)) {
    entity_reference = EntityReference(builder.GetSynonym(tokens->PeekValue()));
    tokens->Forward();
  } else {
    throw SyntaxException("Expected different entRef");
  }
  return entity_reference;
}

Expression QueryParserUtil::ExtractExpression(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  Expression exp;
  // Wildcard front
  if (tokens->MatchKind(Token::UNDERSCORE)) {
    exp.has_front_wildcard = true;
    tokens->Forward();
  }
  // Pattern to match
  if (tokens->MatchKind(Token::INVERTED_COMMAS)) {
    tokens->Forward();
    exp.to_match = GetExpression(tokens, builder);
    tokens->Expect(Token::INVERTED_COMMAS);
  }
  // Wildcard back
  if (tokens->MatchKind(Token::UNDERSCORE)) {
    exp.has_back_wildcard = true;
    tokens->Forward();
  }
  return exp;
}

EntityType QueryParserUtil::ExtractEntityType(
    const std::shared_ptr<TokenHandler>& tokens) {
  EntityType result;
  if (tokens->MatchString("stmt")) {
    result = EntityType::STATEMENT;
  } else if (tokens->MatchString("read")) {
    result = EntityType::READ;
  } else if (tokens->MatchString("print")) {
    result = EntityType::PRINT;
  } else if (tokens->MatchString("call")) {
    result = EntityType::CALL;
  } else if (tokens->MatchString("while")) {
    result = EntityType::WHILE;
  } else if (tokens->MatchString("if")) {
    result = EntityType::IF;
  } else if (tokens->MatchString("assign")) {
    result = EntityType::ASSIGN;
  } else if (tokens->MatchString("variable")) {
    result = EntityType::VARIABLE;
  } else if (tokens->MatchString("constant")) {
    result = EntityType::CONSTANT;
  } else if (tokens->MatchString("procedure")) {
    result = EntityType::PROCEDURE;
  } else {
    throw SyntaxException("tokens->Expected different declaration");
  }
  tokens->Forward();
  return result;
}

std::string QueryParserUtil::GetExpression(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  std::string res;
  Token next = tokens->Peek();
  // Start of expression must be term
  if (isMathOperator(next)) {
    throw SyntaxException("Invalid expression");
  }
  while (next.IsNot(Token::INVERTED_COMMAS) &&
         next.IsNot(Token::RIGHT_ROUND_BRACKET)) {
    res.append(GetTerm(tokens, builder));
    tokens->Forward();
    next = tokens->Peek();
  }
  return res;
}

std::string QueryParserUtil::GetTerm(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  std::string res;
  Token next = tokens->Peek();
  // var_name, const_value, operator
  if (next.Is(Token::IDENTIFIER) || next.Is(Token::NUMBER)) {
    res.append(next.GetValue());
  } else if (isMathOperator(next)) {
    res.append(next.GetValue());
    tokens->Forward();
    res.append(GetTerm(tokens, builder));
  }
  // ( exp )
  else if (next.Is(Token::LEFT_ROUND_BRACKET)) {
    tokens->Forward();
    res.append("(");

    res.append(GetExpression(tokens, builder));

    tokens->Expect(Token::RIGHT_ROUND_BRACKET);
    tokens->Back();
    res.append(")");
  }
  // No term, const, exp detected
  if (res.empty()) {
    throw SyntaxException("Invalid expression");
  }
  return res;
}

bool QueryParserUtil::isMathOperator(Token& next) {
  return next.Is(Token::PLUS) || next.Is(Token::MINUS) ||
         next.Is(Token::ASTERISK) || next.Is(Token::SLASH) ||
         next.Is(Token::PERCENT);
}

void QueryParserUtil::CheckFollowsParentRef(const StatementReference& stmtRef) {
  if (stmtRef.IsSynonym() &&
      (stmtRef.IsEntityType(VARIABLE) || stmtRef.IsEntityType(CONSTANT) ||
       stmtRef.IsEntityType(PROCEDURE))) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
}

void QueryParserUtil::CheckPatternSyn(const Synonym& synonym) {
  if (!(synonym.IsEntityType(ASSIGN) || synonym.IsEntityType(IF) ||
        synonym.IsEntityType(WHILE))) {
    throw SemanticException("Syn-assign not supported");
  }
}

void QueryParserUtil::CheckEntityRhs(const EntityReference& entRef) {
  if (entRef.IsSynonym() && entRef.GetSynonym().GetEntityType() != VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }
}

void QueryParserUtil::CheckProcedureEntity(const EntityReference& entRef) {
  if (!entRef.IsEntityType(PROCEDURE)) {
    throw SemanticException("Expected procedure reference");
  }
}

void QueryParserUtil::CheckVariableEntity(const EntityReference& entity_ref) {
  if (entity_ref.IsSynonym() &&
      entity_ref.GetSynonym().GetEntityType() != VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }
}

bool QueryParserUtil::CheckProcedureClause(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  tokens->Forward();  // skip WORD
  tokens->Forward();  // skip BRACKET
  Token next = tokens->Peek();
  if (next.Is(Token::UNDERSCORE)) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
  bool result = false;
  if (next.Is(Token::IDENTIFIER)) {
    Synonym syn = builder.GetSynonym(next.GetValue());
    if (syn.IsEntityType(PROCEDURE)) {
      result = true;
    }
  } else if (next.Is(Token::INVERTED_COMMAS)) {
    result = true;
  }
  tokens->Back();  // go back to BRACKET
  tokens->Back();  // go back to WORD
  return result;
}