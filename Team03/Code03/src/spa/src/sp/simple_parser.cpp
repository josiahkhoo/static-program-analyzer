#include "simple_parser.h"

#include <stdexcept>
#include <vector>

SimpleParser::SimpleParser(std::vector<Token> tokens) : tokens(std::move(tokens)) {};

Token SimpleParser::peek(int pos) {
  if (pos >= tokens.size()) {
    throw std::runtime_error("No more tokens left to peek");
  }
  return tokens[pos];
}

bool SimpleParser::matchKind(Token::Kind kind) {
  if (peek(tokenPos).Is(kind))
  {
    return true;
  }
  return false;
}

bool SimpleParser::matchString(const std::string& s) {
  if (peek(tokenPos).GetValue() == s){
    return true;
  }
  return false;
}

bool SimpleParser::expect(Token::Kind kind) {
  if(matchKind(kind)) {
    tokenPos++;
    return true;
  }
  throw std::runtime_error("Expected a different token kind");
}

bool SimpleParser::expect(const std::string& s) {
  if(matchString(s)) {
    tokenPos++;
    return true;
  }
  throw std::runtime_error("Expected a different token string");
}


TNode SimpleParser::parse(std::vector<Token> tokens) {
  TNode programNode(TNode::Program, 0);
  do {
    programNode.GetChildren().emplace_back(parseProcedure());
  } while (!matchKind(Token::END));
  return programNode;
}

TNode SimpleParser::parseProcedure() {
  expect("procedure");
  TNode procedureNode(TNode::Procedure, 0, peek(tokenPos).GetValue());
  tokenPos++;

  expect(Token::LEFT_CURLY_BRACKET);
  procedureNode.GetChildren().emplace_back(parseStatementList());
  expect(Token::RIGHT_CURLY_BRACKET);

  return procedureNode;
}

TNode SimpleParser::parseStatementList() {
  TNode statementListNode(TNode::StatementList, 0);
  do {
    statementListNode.GetChildren().emplace_back(parseStatement());
  } while (!matchKind(Token::RIGHT_CURLY_BRACKET));
  return statementListNode;
}

TNode SimpleParser::parseStatement() {
  if(peek(tokenPos + 1).Is(Token::EQUAL)) {
    return parseAssign();
  }

  if (!matchKind(Token::IDENTIFIER)) {
    throw std::runtime_error ("Expected IDENTIFIER but got something else");
  }

  if (peek(tokenPos).GetValue() == "read") {
    return parseRead();
  } else if (peek(tokenPos).GetValue() == "print") {
    return parsePrint();
  } else if (peek(tokenPos).GetValue() == "call") {
    return parseCall();
  } else if (peek(tokenPos).GetValue() == "while") {
    return parseWhile();
  } else if (peek(tokenPos).GetValue() == "if") {
    return parseIf();
  } else {
    throw std::runtime_error ("Failed to parse statement with Token name " + peek(tokenPos).GetValue());
  }
}
