#include "entity_storable_pkb.h"

EntityStorablePkb::EntityStorablePkb(EntityManager& entity_manager_,
                                     PatternManager& pattern_manager_)
    : entity_manager_(entity_manager_), pattern_manager_(pattern_manager_) {}

/// Store Procedure Entities
/// \param ts List of entities
void EntityStorablePkb::Store(std::vector<ProcedureEntity> ts) {
  for (const ProcedureEntity& entity : ts) {
    entity_manager_.AddProcedure(entity);
  }
}

/// Store Variable Entities
/// \param ts List of entities
void EntityStorablePkb::Store(std::vector<VariableEntity> ts) {
  for (const VariableEntity& entity : ts) {
    entity_manager_.AddVariable(entity);
  }
}

/// Store Constant Entities
/// \param ts List of entities
void EntityStorablePkb::Store(std::vector<ConstantEntity> ts) {
  for (const ConstantEntity& entity : ts) {
    entity_manager_.AddConstant(entity);
  }
}

/// Store Call Entities
/// \param ts List of entities
void EntityStorablePkb::Store(std::vector<CallEntity> ts) {
  for (const CallEntity& entity : ts) {
    entity_manager_.AddCallStatement(entity);
  }
}

/// Store Read Entities
/// \param ts List of entities
void EntityStorablePkb::Store(std::vector<ReadEntity> ts) {
  for (const ReadEntity& entity : ts) {
    entity_manager_.AddReadStatement(entity);
  }
}

/// Store Print Entities
/// \param ts List of entities
void EntityStorablePkb::Store(std::vector<PrintEntity> ts) {
  for (const PrintEntity& entity : ts) {
    entity_manager_.AddPrintStatement(entity);
  }
}

/// Store Assign Entities
/// \param ts List of entities
void EntityStorablePkb::Store(std::vector<AssignEntity> ts) {
  for (const AssignEntity& entity : ts) {
    entity_manager_.AddAssignStatement(entity);
    pattern_manager_.AddAssignPattern(entity);
  }
}

/// Store If Entities
/// \param ts List of entities
void EntityStorablePkb::Store(std::vector<IfEntity> ts) {
  for (const IfEntity& entity : ts) {
    entity_manager_.AddIfStatement(entity);
  }
}

/// Store While Entities
/// \param ts List of entities
void EntityStorablePkb::Store(std::vector<WhileEntity> ts) {
  for (const WhileEntity& entity : ts) {
    entity_manager_.AddWhileStatement(entity);
  }
}