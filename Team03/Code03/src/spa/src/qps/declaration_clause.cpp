#include "declaration_clause.h"

DeclarationClause::DeclarationClause(QPEnums::DesignEntity type, std::string synonym) : type(type), synonym(synonym){}

QPEnums::DesignEntity DeclarationClause::GetType() const { return type; }

std::string DeclarationClause::GetSynonym() const { return synonym; }
