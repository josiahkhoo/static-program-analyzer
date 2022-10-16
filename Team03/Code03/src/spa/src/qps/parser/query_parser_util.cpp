#include "query_parser_util.h"

#include "common/reference/attribute_name.h"
#include "common/reference/identifier.h"
#include "common/reference/integer.h"
#include "qps/exceptions/semantic_exception.h"
#include "qps/exceptions/syntax_exception.h"

/// Retrieve statement reference from tokens & builder
/// \param tokens
/// \param builder
/// \return StatementReference
StatementReference QueryParserUtil::ExtractStmtRef(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  StatementReference statement_reference;
  if (tokens->MatchKind(Token::IDENTIFIER)) {
    // Checks current declared synonyms to do matching
    Synonym synonym = builder.GetSynonym(tokens->PeekValue());
    statement_reference = StatementReference(synonym);
    tokens->Forward();
  } else if (tokens->MatchKind(Token::UNDERSCORE)) {
    statement_reference = StatementReference();
    tokens->Forward();
  } else if (tokens->MatchKind(Token::NUMBER)) {
    statement_reference = StatementReference(ExtractInteger(tokens));
  } else {
    throw SyntaxException("Expected different stmtRef");
  }
  return statement_reference;
}

/// Retrieve entity reference from tokens & builder
/// \param tokens
/// \param builder
/// \return EntityReference
EntityReference QueryParserUtil::ExtractEntityRef(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  EntityReference entity_reference;
  // Wildcard
  if (tokens->MatchKind(Token::UNDERSCORE)) {
    entity_reference = EntityReference();
    tokens->Forward();
  }
  // Identifier
  else if (tokens->MatchKind(Token::INVERTED_COMMAS)) {
    Identifier ident = ExtractIdentifier(tokens);
    entity_reference = EntityReference(ident);
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

/// Retrieve expression from tokens & builder
/// \param tokens
/// \param builder
/// \return Expression
Expression QueryParserUtil::ExtractExpression(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  Expression exp;
  // Wildcard front
  if (tokens->MatchKind(Token::UNDERSCORE)) {
    exp.has_front_wildcard = true;
    tokens->Forward();
  }
  // Pattern to match - Expression
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

/// Retrieve entity type of token
/// \param tokens
/// \return EntityType of token
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

/// Retrieve pattern expression: expression
/// \param tokens
/// \param builder
/// \return String Expression
std::string QueryParserUtil::GetExpression(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  // Start of expression must be term
  if (tokens->IsMathOperator()) {
    throw SyntaxException("Invalid expression");
  }
  std::string res;
  Token next = tokens->Peek();
  while (next.IsNot(Token::INVERTED_COMMAS) &&
         next.IsNot(Token::RIGHT_ROUND_BRACKET)) {
    res.append(GetTerm(tokens, builder));
    tokens->Forward();
    next = tokens->Peek();
  }
  return res;
}

/// Retrieve pattern expression: term
/// \param tokens
/// \param builder
/// \return String Term
std::string QueryParserUtil::GetTerm(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  std::string res;
  Token next = tokens->Peek();
  // var_name, const_value, operator
  if (next.Is(Token::IDENTIFIER) || next.Is(Token::NUMBER)) {
    res.append(next.GetValue());
  } else if (tokens->IsMathOperator()) {
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

/// Verifies statement reference
/// \param synonym
void QueryParserUtil::CheckFollowsParentRef(const StatementReference& stmtRef) {
  if (stmtRef.IsSynonym() &&
      (stmtRef.IsEntityType(VARIABLE) || stmtRef.IsEntityType(CONSTANT) ||
       stmtRef.IsEntityType(PROCEDURE))) {
    throw SemanticException("Synonym is of a wrong entity type");
  }
}

/// Verifies statement reference is an Assign synonym
/// \param stmtRef
void QueryParserUtil::CheckAffectsRef(const StatementReference& stmtRef) {
  if (stmtRef.IsSynonym() &&
      !(stmtRef.IsEntityType(ASSIGN) || stmtRef.IsEntityType(STATEMENT))) {
    throw SemanticException("Invalid statement reference for Affects clause");
  }
}

/// Verifies synonym is pattern-able
/// \param synonym
void QueryParserUtil::CheckPatternSyn(const Synonym& synonym) {
  if (!(synonym.IsEntityType(ASSIGN) || synonym.IsEntityType(IF) ||
        synonym.IsEntityType(WHILE))) {
    throw SemanticException("Syn-assign not supported");
  }
}

/// Verifies entity reference is a Procedure entity
/// \param entity_ref
void QueryParserUtil::CheckProcedureEntity(const EntityReference& entRef) {
  if (entRef.IsSynonym() && !entRef.IsEntityType(PROCEDURE)) {
    throw SemanticException("Expected procedure reference");
  }
}

/// Verifies entity reference is a Variable entity
/// \param entRef
void QueryParserUtil::CheckVariableEntity(const EntityReference& entRef) {
  if (entRef.IsSynonym() && entRef.GetSynonym().GetEntityType() != VARIABLE) {
    throw SemanticException("Synonym is not a variable entity");
  }
}

/// Checks if clause has a Procedure entity
/// \param tokens
/// \param builder
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

/// Extracts Attribute Reference object from given tokens & query string
/// \param tokens
/// \param builder
/// \return AttributeReference
AttributeReference QueryParserUtil::ExtractAttrRef(
    const std::shared_ptr<TokenHandler>& tokens,
    const QueryStringBuilder& builder) {
  Token next = tokens->Peek();
  // "Identifier"
  if (tokens->MatchKind(Token::INVERTED_COMMAS)) {
    Identifier identifier = ExtractIdentifier(tokens);
    return AttributeReference(identifier);
  }
  // Integer
  else if (tokens->MatchKind(Token::NUMBER)) {
    return AttributeReference(ExtractInteger(tokens));
  }
  // Attribute x.'procName'| 'varName' | 'value' | 'stmt#'
  else {
    tokens->Expect(Token::IDENTIFIER);
    Synonym syn = builder.GetSynonym(next.GetValue());
    tokens->Expect(Token::PERIOD);
    AttributeName attrName = ExtractAttrName(syn, tokens);
    Attribute attr = Attribute(syn, attrName);
    return AttributeReference(attr);
  }
}

/// Extracts Attribute Name object from given tokens
/// \param tokens
/// \return AttributeName
AttributeName QueryParserUtil::ExtractAttrName(
    Synonym syn, const std::shared_ptr<TokenHandler>& tokens) {
  Token next = tokens->Peek();
  tokens->Expect(Token::IDENTIFIER);
  std::string name = next.GetValue();
  // Check attribute name exist
  if (!Attribute::attrNameRepresentation.count(name)) {
    throw SyntaxException("No such attribute name");
  }
  AttributeName attrName = Attribute::attrNameRepresentation[name];
  // Checks stmt#
  if (attrName == AttributeName::STMT_NO) {
    tokens->Expect(Token::HASHTAG);
  }
  // Check if attribute and synonym match
  std::unordered_set<AttributeName> map =
      Attribute::entityAllowedAttributes[syn.GetEntityType()];
  if (!map.count(attrName)) {
    throw SemanticException("Synonym doesn't support this attribute");
  }
  return attrName;
}

/// Extracts Identifier object from given tokens
/// \param tokens
/// \return Identifier
Identifier QueryParserUtil::ExtractIdentifier(
    const std::shared_ptr<TokenHandler>& tokens) {
  tokens->Expect(Token::INVERTED_COMMAS);
  Identifier ident = tokens->PeekValue();
  tokens->Forward();
  tokens->Expect(Token::INVERTED_COMMAS);
  return ident;
}

/// Extracts Integer object from given tokens
/// \param tokens
/// \return Integer
Integer QueryParserUtil::ExtractInteger(
    const std::shared_ptr<TokenHandler>& tokens) {
  tokens->Expect(Token::NUMBER);
  tokens->Back();
  Integer integer = stoi(tokens->PeekValue());
  tokens->Forward();
  return integer;
}