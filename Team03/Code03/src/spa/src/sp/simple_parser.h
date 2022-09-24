#ifndef SPA_SIMPLE_PARSER_H
#define SPA_SIMPLE_PARSER_H

#include "common/lexer.h"
#include "common/parser.h"
#include "common/t_node.h"
#include "common/token.h"

#include <unordered_set>
#include <unordered_map>

class SimpleParser : public Parser<TNode, std::vector<Token>> {
 public:
  SimpleParser();

  TNode Parse(std::vector<Token> tokens_) override;

 private:
  int token_pos_ = 0;
  int statement_number_ = 0;
  int t_node_id_ = 0;
  std::vector<Token> tokens_;
  std::string curr_proc_;
  std::unordered_map<std::string, std::unordered_set<std::string>> proc_map_;

  Token Peek(int pos);

  bool MatchKind(Token::Kind kind);

  bool MatchString(const std::string &s);

  void Expect(Token::Kind kind);

  void Expect(const std::string &s);

  std::shared_ptr<TNode> ParseProcedure();

  std::shared_ptr<TNode> ParseStatementList();

  std::shared_ptr<TNode> ParseStatement();

  std::shared_ptr<TNode> ParseAssign();

  std::shared_ptr<TNode> ParseRead();

  std::shared_ptr<TNode> ParsePrint();

  std::shared_ptr<TNode> ParseCall();

  std::shared_ptr<TNode> ParseWhile();

  std::shared_ptr<TNode> ParseIf();

  std::shared_ptr<TNode> ParseCondExpr();

  std::shared_ptr<TNode> ParseRelExpr();

  std::shared_ptr<TNode> ParseRelFactor();

  std::shared_ptr<TNode> ParseExpr();

  std::shared_ptr<TNode> ParseTerm();

  std::shared_ptr<TNode> ParseFactor();

  std::shared_ptr<TNode> ParseVarName();

  std::shared_ptr<TNode> ParseConstValue();

  void AssignParentToChildren(
      std::shared_ptr<TNode> t_node,
      const std::vector<std::shared_ptr<TNode>> &children);

  void CheckValidProgram();

  void TraverseProcedureTree(std::unordered_set<std::string> &children, std::string &start, std::string &end);
};

#endif  // SPA_SIMPLE_PARSER_H
