#include "SyntaxException.h"

SyntaxException::SyntaxException(std::string msg) : message(std::move(msg)) {}

const char* SyntaxException::what() const { return what_.c_str(); }

std::string SyntaxException::GetMessage() const { return message; }
