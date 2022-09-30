#include "read_entity.h"

ReadEntity::ReadEntity(const TNode &node, int line_number)
    : StatementEntity(node, line_number) {}

std::string ReadEntity::GetVariableName() const {
  return node_.GetChildren()[0]->GetStringValue();
}
