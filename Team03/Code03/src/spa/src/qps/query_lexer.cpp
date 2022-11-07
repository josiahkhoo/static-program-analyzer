#include "query_lexer.h"

// Lexer rules specific to QPS only
TokenRules QueryLexer::token_rules_ = {
    {Token::WHITESPACE, "^(\\s+)"},
    {Token::NUMBER, "^(\\d+)"},
    {Token::IDENTIFIER, "^([a-zA-Z]+[a-zA-Z0-9]*)"},
    {Token::LEFT_ROUND_BRACKET, "^(\\()"},
    {Token::RIGHT_ROUND_BRACKET, "^(\\))"},
    {Token::LEFT_CURLY_BRACKET, "^(\\{)"},
    {Token::RIGHT_CURLY_BRACKET, "^(\\})"},
    {Token::EQUAL, "^(=)"},
    {Token::LESS_THAN, "^(<)"},
    {Token::GREATER_THAN, "^(>)"},
    {Token::PLUS, "^(\\+)"},
    {Token::MINUS, "^(\\-)"},
    {Token::ASTERISK, "^(\\*)"},
    {Token::SLASH, "^(\\/)"},
    {Token::COMMA, "^(,)"},
    {Token::PERIOD, "^(\\.)"},
    {Token::PERCENT, "^(%)"},
    {Token::SEMICOLON, "^(;)"},
    {Token::INVERTED_COMMAS, "^(\")"},
    {Token::UNDERSCORE, "^(_)"},
    {Token::HASHTAG, "^(#)"},
    {Token::NEXT_LINE, "^(\n)"},
    {Token::END, "^(\0)"}};

QueryLexer::QueryLexer(const Lexer& lexer) : lexer_(lexer) {}

std::vector<Token> QueryLexer::Execute(std::string& query) const {
  return lexer_.Lex(query, token_rules_);
}
