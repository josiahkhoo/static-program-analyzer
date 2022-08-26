#include "procedure_entity.h"

#include <utility>

ProcedureEntity::ProcedureEntity(const TNode* node_ptr, std::string name)
    : Entity(node_ptr), name_(std::move(name)) {}

std::string ProcedureEntity::GetName() const { return name_; }
