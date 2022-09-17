#ifndef SPA_SEMANTIC_EXCEPTION_H
#define SPA_SEMANTIC_EXCEPTION_H

#include <exception>
#include <iostream>
#include <utility>

class SemanticException : public std::exception {
 private:
  const std::string what_ = "SemanticError";
  std::string message;

 public:
  explicit SemanticException(std::string msg);
  [[nodiscard]] const char *what() const noexcept override;
  [[nodiscard]] std::string GetMessage() const;
};

#endif  // SPA_SEMANTIC_EXCEPTION_H
