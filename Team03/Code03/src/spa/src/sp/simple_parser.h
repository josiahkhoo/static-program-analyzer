#ifndef SPA_SIMPLE_PARSER_H
#define SPA_SIMPLE_PARSER_H

#include "common/lexer.h"
#include "common/parser.h"
#include "common/t_node.h"
#include "common/token.h"

class SimpleParser : public Parser<TNode> {
 public:
  SimpleParser();
  TNode Parse(std::vector<Token> tokens_) override;

 private:
  int token_pos_ = 0;
  int statement_number_ = 0;
  int t_node_id_ = 0;
  std::vector<Token> tokens_;

  Token Peek(int pos);
  bool MatchKind(Token::Kind kind);
  bool MatchString(const std::string& s);
  void Expect(Token::Kind kind);
  void Expect(const std::string& s);

  TNode ParseProcedure();
  TNode ParseStatementList();
  TNode ParseStatement();

  TNode ParseAssign();
  TNode ParseRead();
  TNode ParsePrint();
  TNode ParseCall();
  TNode ParseWhile();
  TNode ParseIf();

  TNode ParseCondExpr();
  TNode ParseRelExpr();

  TNode ParseRelFactor();
  TNode ParseExpr();
  TNode ParseTerm();
  TNode ParseFactor();

  TNode ParseVarName();
  TNode ParseConstValue();
};

#endif  // SPA_SIMPLE_PARSER_H
