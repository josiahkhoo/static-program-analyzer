#include "call_entity.h"

CallEntity::CallEntity(const TNode &node, int line_number)
    : StatementEntity(node, line_number) {}

std::string CallEntity::GetProcedureName() const {
  return node_.GetStringValue();
}
