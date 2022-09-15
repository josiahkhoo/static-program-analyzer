#include "syntax_exception.h"

syntax_exception::syntax_exception(std::string msg) : message(std::move(msg)) {}

const char* syntax_exception::what() const { return what_.c_str(); }

std::string syntax_exception::GetMessage() const { return message; }
