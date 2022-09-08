#include "assign_entity.h"

AssignEntity::AssignEntity(const TNode& node, int line_number)
    : PatternStatementEntity(node, line_number) {}

const TNode& AssignEntity::GetPatternSourceNode() const { return node_; }
