#ifndef SPA_SYNTAX_EXCEPTION_H
#define SPA_SYNTAX_EXCEPTION_H

#include <exception>
#include <iostream>
#include <utility>

class SyntaxException : public std::exception {
 private:
  const std::string what_ = "SyntaxError";
  std::string message;

 public:
  explicit SyntaxException(std::string msg);
  [[nodiscard]] const char *what() const noexcept override;
  [[nodiscard]] std::string GetMessage() const;
};

#endif  // SPA_SYNTAX_EXCEPTION_H
