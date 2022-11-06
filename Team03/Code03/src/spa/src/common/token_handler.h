#ifndef SPA_TOKEN_HANDLER_H
#define SPA_TOKEN_HANDLER_H

#include <vector>

#include "common/token.h"

class TokenHandler {
 private:
  int token_pos_ = 0;
  std::vector<Token> tokens_;

 public:
  explicit TokenHandler();
  explicit TokenHandler(std::vector<Token> tokens);
  Token Peek();
  std::string PeekValue();
  bool MatchKind(Token::Kind kind);
  bool MatchString(const std::string& s);
  bool CheckEnd();
  void Expect(Token::Kind kind);
  void Expect(const std::string& s);
  void Forward();
  void Back();
  bool IsNotEnd();
  bool IsMathOperator();
  int GetTokenPos();
  void SetTokenPos(int token_pos);
  bool IsVarOrConst();
  bool CheckAhead(Token::Kind kind);
};

#endif  // SPA_TOKEN_HANDLER_H
