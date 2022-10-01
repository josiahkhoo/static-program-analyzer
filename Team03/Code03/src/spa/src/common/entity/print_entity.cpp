#include "print_entity.h"

PrintEntity::PrintEntity(const TNode &node, int line_number)
    : StatementEntity(node, line_number) {}

std::string PrintEntity::GetVariableName() const {
  return node_.GetChildren()[0]->GetStringValue();
}
