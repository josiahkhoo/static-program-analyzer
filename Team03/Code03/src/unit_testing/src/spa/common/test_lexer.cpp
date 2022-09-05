#include <sstream>

#include "catch.hpp"
#include "common/lexer.h"
#include "common/token.h"
#include "vector"

TEST_CASE("Extract all string tokens", "[Lexer]") {
    std::istringstream str_stream(
            "1\nh1\n(\n)\n{\n}\n==\n=\n<=\n<\n>=\n>\n+"
            "\n-\n*\n/\n,\n%\n;\n||\n&&\n!");
    Lexer lex;
    std::vector<Token> tokens = lex.Lex(str_stream);

    REQUIRE(tokens.size() == 23);

    REQUIRE(tokens[0].GetValue() == "1");
    REQUIRE(tokens[1].GetValue() == "h1");

    std::vector<Token::Kind> k = {Token::NUMBER,
                                  Token::IDENTIFIER,
                                  Token::LEFT_ROUND_BRACKET,
                                  Token::RIGHT_ROUND_BRACKET,
                                  Token::LEFT_CURLY_BRACKET,
                                  Token::RIGHT_CURLY_BRACKET,
                                  Token::DOUBLE_EQUAL,
                                  Token::EQUAL,
                                  Token::LESS_THAN_OR_EQUAL,
                                  Token::LESS_THAN,
                                  Token::GREATER_THAN_OR_EQUAL,
                                  Token::GREATER_THAN,
                                  Token::PLUS,
                                  Token::MINUS,
                                  Token::ASTERISK,
                                  Token::SLASH,
                                  Token::COMMA,
                                  Token::PERCENT,
                                  Token::SEMICOLON,
                                  Token::OR,
                                  Token::AND,
                                  Token::NOT,
                                  Token::END};

    for (int i = 0; i < tokens.size(); i++) {
        REQUIRE(tokens[i].Is(k[i]));
    }
}

TEST_CASE("Extract if block code tokens", "[Lexer]") {
    std::istringstream str_stream(
            "if (x==1) then {\n"
            "    z = x + 1; }");
    Lexer lex;
    std::vector<Token> tokens = lex.Lex(str_stream);

    REQUIRE(tokens.size() == 16);

    std::vector<Token::Kind> k = {Token::IDENTIFIER,
                                  Token::LEFT_ROUND_BRACKET,
                                  Token::IDENTIFIER,
                                  Token::DOUBLE_EQUAL,
                                  Token::NUMBER,
                                  Token::RIGHT_ROUND_BRACKET,
                                  Token::IDENTIFIER,
                                  Token::LEFT_CURLY_BRACKET,
                                  Token::IDENTIFIER,
                                  Token::EQUAL,
                                  Token::IDENTIFIER,
                                  Token::PLUS,
                                  Token::NUMBER,
                                  Token::SEMICOLON,
                                  Token::RIGHT_CURLY_BRACKET,
                                  Token::END};

    for (int i = 0; i < tokens.size(); i++) {
        REQUIRE(tokens[i].Is(k[i]));
    }
}
