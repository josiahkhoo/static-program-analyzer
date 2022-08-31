#include "select_clause.h"

SelectClause::SelectClause(std::string synonym) : synonym(synonym){}

std::string SelectClause::GetSynonym() const { return synonym; }
