#ifndef SPA_SIMPLE_PARSER_H
#define SPA_SIMPLE_PARSER_H

#include "common/parser.h"
#include "common/t_node.h"
#include "common/lexer.h"
#include "common/token.h"

class SimpleParser : public Parser<TNode> {
 public:
  SimpleParser(std::vector<Token> tokens);
  TNode parse(std::vector<Token> tokens) override;

  bool matchKind(Token::Kind kind);
  bool matchString(const std::string& s);
  bool expect(Token::Kind kind);
  bool expect(const std::string& s);

  Token peek(int pos);
  TNode parseProcedure();

  TNode parseStatementList();
  TNode parseStatement();

  TNode parseRead ();
  TNode parsePrint ();
  TNode parseCall ();
  TNode parseWhile ();
  TNode parseIf ();
  TNode parseAssign ();

  TNode parseCondExpr ();
  TNode parseRelExpr ();
  TNode parseRelFactor ();
  TNode parseExpr ();
  TNode parseTerm ();
  TNode parseFactor ();
  TNode parseConstValue ();
  TNode parseName ();
 private:
  int tokenPos = 0;
  int lineNumber = 0;
  std::vector<Token> tokens;
};

#endif  // SPA_SIMPLE_PARSER_H
