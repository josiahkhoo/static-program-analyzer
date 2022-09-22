#ifndef SPA_QUERY_PARSER_H
#define SPA_QUERY_PARSER_H

#include "common/parser.h"
#include "query_string.h"
#include "query_string_builder.h"

class QueryParser : public Parser<QueryString> {
 public:
  QueryParser();

  QueryString Parse(std::vector<Token> tokens_) override;

 private:
  int token_pos_ = 0;
  std::vector<Token> tokens_;
  QueryStringBuilder query_string_builder_;

  Token Peek();

  bool MatchKind(Token::Kind kind);

  bool MatchString(const std::string& s);

  bool CheckEnd();

  void Expect(Token::Kind kind);

  void Expect(const std::string& s);

  void ParseDeclaration();

  void ParseSelect();

  bool ParseClause();

  void ParseFollows();

  void ParseFollowsT();

  void CheckFollowsParentRef(const StatementReference& stmtRef) const;

  void ParseParent();

  void ParseParentT();

  void ParseUses();

  void CheckUsesLhs();

  void CheckEntityRhs(const EntityReference& entRef) const;

  void ParseUsesS();

  void ParseUsesP();

  void ParseModifies();

  void CheckModifiesLhs();

  void ParseModifiesS();

  void ParseModifiesP();

  void ParseCalls();

  void ParseCallsT();

  void CheckProcedureEntity(const EntityReference& entRef) const;

  bool ParsePattern();

  void CheckPatternSyn(const Synonym& synonym) const;

  void ParseQueryOperation();

  void ParseCleanUpSyntax();

  StatementReference ExtractStmtRef();
  EntityReference ExtractEntityRef();
  Expression ExtractExpression();
  EntityType ExtractEntityType();
  std::string GetTerm();
  std::string GetExpression();
};

#endif  // SPA_QUERY_PARSER_H
