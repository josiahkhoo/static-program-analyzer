#include "statement_entity.h"

StatementEntity::StatementEntity(const TNode &node, int statement_number)
    : Entity(node), statement_number_(statement_number) {}

int StatementEntity::GetStatementNumber() const { return statement_number_; }

std::string StatementEntity::ToString() const {
  return std::to_string(statement_number_);
}
