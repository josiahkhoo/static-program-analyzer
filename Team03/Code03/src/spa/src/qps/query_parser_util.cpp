//#include "query_parser_util.h"
//
//#include "qps/exceptions/syntax_exception.h"
//
//StatementReference QueryParserUtil::ExtractStmtRef() {
//  StatementReference statement_reference;
//
//  if (MatchKind(Token::IDENTIFIER)) {
//    // Checks current declared synonyms to do matching
//    Synonym synonym = query_string_builder_.GetSynonym(Peek().GetValue());
//    statement_reference = StatementReference(synonym);
//  } else if (MatchKind(Token::UNDERSCORE)) {
//    statement_reference = StatementReference();
//  } else if (MatchKind(Token::NUMBER)) {
//    statement_reference = StatementReference(stoi(Peek().GetValue()));
//  } else {
//    throw SyntaxException("Expected different stmtRef");
//  }
//  token_pos++;
//  return statement_reference;
//}
//
//EntityReference QueryParserUtil::ExtractEntityRef() {
//  EntityReference entity_reference;
//
//  // Wildcard
//  if (MatchKind(Token::UNDERSCORE)) {
//    token_pos++;
//    entity_reference = EntityReference();
//  }
//  // Identifier
//  else if (MatchKind(Token::INVERTED_COMMAS)) {
//    token_pos++;
//    entity_reference = EntityReference(Peek().GetValue());
//    token_pos++;
//    Expect(Token::INVERTED_COMMAS);
//  }
//  // Synonym
//  else if (MatchKind(Token::IDENTIFIER)) {
//    entity_reference =
//        EntityReference(query_string_builder_.GetSynonym(Peek().GetValue()));
//    token_pos++;
//  } else {
//    throw SyntaxException("Expected different entRef");
//  }
//
//  return entity_reference;
//}
//
//Expression QueryParserUtil::ExtractExpression() {
//  Expression exp;
//
//  // Wildcard front
//  if (MatchKind(Token::UNDERSCORE)) {
//    exp.has_front_wildcard = true;
//    token_pos++;
//  }
//  // Pattern to match
//  if (MatchKind(Token::INVERTED_COMMAS)) {
//    token_pos++;
//    exp.to_match = GetExpression();
//    Expect(Token::INVERTED_COMMAS);
//  }
//  // Wildcard back
//  if (MatchKind(Token::UNDERSCORE)) {
//    exp.has_back_wildcard = true;
//    token_pos++;
//  }
//
//  return exp;
//}
//
//std::string QueryParserUtil::GetExpression() {
//  std::string res;
//  Token next = Peek();
//  while (next.IsNot(Token::INVERTED_COMMAS) &&
//         next.IsNot(Token::RIGHT_ROUND_BRACKET)) {
//    res.append(GetTerm());
//    token_pos++;
//    next = Peek();
//  }
//  return res;
//}
//
//std::string QueryParserUtil::GetTerm() {
//  std::string res;
//  Token next = Peek();
//  // var_name, const_value, operator
//  if (next.Is(Token::IDENTIFIER) || next.Is(Token::NUMBER)) {
//    res.append(next.GetValue());
//  } else if (next.Is(Token::PLUS) || next.Is(Token::MINUS) ||
//             next.Is(Token::ASTERISK) || next.Is(Token::SLASH) ||
//             next.Is(Token::PERCENT)) {
//    res.append(next.GetValue());
//    token_pos++;
//    res.append(GetTerm());
//  }
//  // ( exp )
//  else if (next.Is(Token::LEFT_ROUND_BRACKET)) {
//    token_pos++;
//    res.append("(");
//
//    res.append(GetExpression());
//
//    Expect(Token::RIGHT_ROUND_BRACKET);
//    token_pos--;
//    res.append(")");
//  }
//
//  if (res.empty()) {
//    throw SyntaxException("Invalid expression");
//  }
//  return res;
//}
//void QueryParserUtil::CheckFollowsParentRef(
//    const StatementReference &stmtRef) const {
//  if (stmtRef.IsSynonym() &&
//      (stmtRef.IsEntityType(VARIABLE) || stmtRef.IsEntityType(CONSTANT) ||
//       stmtRef.IsEntityType(PROCEDURE))) {
//    throw SemanticException("Synonym is of a wrong entity type");
//  }
//}
//
//void QueryParserUtil::CheckPatternSyn(const Synonym &synonym) const {
//  if (!synonym.IsEntityType(ASSIGN)) {
//    throw SemanticException("Syn-assign not supported");
//  }
//}
//void QueryParserUtil::CheckEntityRhs(const EntityReference &entRef) const {
//  if (entRef.IsSynonym() && entRef.GetSynonym().GetEntityType() != VARIABLE) {
//    throw SemanticException("Synonym is not a variable entity");
//  }
//}
//
//void QueryParserUtil::CheckUsesLhs() {
//  Token next = Peek();
//  if (next.Is(Token::UNDERSCORE)) {
//    throw SemanticException("Synonym is of a wrong entity type");
//  }
//  if (next.Is(Token::IDENTIFIER)) {
//    Synonym syn = query_string_builder_.GetSynonym(next.GetValue());
//    if (syn.IsEntityType(PROCEDURE)) {
//      ParseUsesP();
//    } else {
//      ParseUsesS();
//    }
//  } else if (next.Is(Token::INVERTED_COMMAS)) {
//    ParseUsesP();
//  } else {
//    ParseUsesS();
//  }
//}