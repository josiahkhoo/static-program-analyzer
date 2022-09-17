#include "semantic_exception.h"

SemanticException::SemanticException(std::string msg) : message(std::move(msg)) {}

const char* SemanticException::what() const noexcept { return what_.c_str(); }

std::string SemanticException::GetMessage() const { return message; }
