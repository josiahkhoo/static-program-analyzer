#include "procedure_entity.h"

#include <utility>

ProcedureEntity::ProcedureEntity(const TNode &node, std::string name)
    : Entity(node), name_(std::move(name)) {}

std::string ProcedureEntity::GetName() const { return name_; }
