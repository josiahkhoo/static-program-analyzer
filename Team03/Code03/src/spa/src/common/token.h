//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_TOKEN_H
#define SPA_TOKEN_H

#include <optional>
#include <string>

// The token class is responsible for representing a single token.
// It holds the value for numbers and identifiers.
class Token {
 public:
  enum Kind {
    NUMBER,                 // E.g. "0", "10", "012"
    IDENTIFIER,             // E.g. "hi", "h2"
    LEFT_ROUND_BRACKET,     // (
    RIGHT_ROUND_BRACKET,    // )
    LEFT_CURLY_BRACKET,     // {
    RIGHT_CURLY_BRACKET,    // }
    DOUBLE_EQUAL,           // ==
    EQUAL,                  // =
    LESS_THAN,              // <
    LESS_THAN_OR_EQUAL,     // <=
    GREATER_THAN,           // >
    GREATER_THAN_OR_EQUAL,  // >=
    PLUS,                   // +
    MINUS,                  // -
    ASTERISK,               // *
    SLASH,                  // /
    COMMA,                  // ,
    PERCENT,                // %
    SEMICOLON,              // "
    OR,                     // ||
    AND,                    // &&
    NOT,                    // !
    NEXT_LINE,              // \n
    END                     // \0
  };

  // Constructs a token that does not hold a value.
  explicit Token(Kind kind);

  // Constructs a token holding a value.
  Token(Kind kind, std::string value);

  // Checks if the token is a specified kind.
  bool Is(Kind kind);

  // Check if the token is not a specified kind.
  bool IsNot(Kind kind);

  std::string GetValue() const;

 private:
  Kind kind_;
  std::optional<std::string> value_;

  // Checks if token can hold a value.
  static bool CanHoldValue(Kind kind);
};

#endif  // SPA_TOKEN_H