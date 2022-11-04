//
// Created by kohha on 3/11/2022.
//

#include "entity_storable_pkb_strategy.h"

/// Store Procedure Entities
/// \param ts List of entities
template <>
void EntityStorablePkb<ProcedureEntity>::Store(std::vector<ProcedureEntity> ts) {
  for (const ProcedureEntity& entity : ts) {
    entity_manager_.AddProcedure(entity);
  }
}

/// Store Variable Entities
/// \param ts List of entities
template <>
void EntityStorablePkb<VariableEntity>::Store(std::vector<VariableEntity> ts) {
  for (const VariableEntity& entity : ts) {
    entity_manager_.AddVariable(entity);
  }
}

/// Store Constant Entities
/// \param ts List of entities
template <>
void EntityStorablePkb<ConstantEntity>::Store(std::vector<ConstantEntity> ts) {
  for (const ConstantEntity& entity : ts) {
    entity_manager_.AddConstant(entity);
  }
}

/// Store Call Entities
/// \param ts List of entities
template <>
void EntityStorablePkb<CallEntity>::Store(std::vector<CallEntity> ts) {
  for (const CallEntity& entity : ts) {
    entity_manager_.AddCallStatement(entity);
  }
}

/// Store Read Entities
/// \param ts List of entities
template <>
void EntityStorablePkb<ReadEntity>::Store(std::vector<ReadEntity> ts) {
  for (const ReadEntity& entity : ts) {
    entity_manager_.AddReadStatement(entity);
  }
}

/// Store Print Entities
/// \param ts List of entities
template <>
void EntityStorablePkb<PrintEntity>::Store(std::vector<PrintEntity> ts) {
  for (const PrintEntity& entity : ts) {
    entity_manager_.AddPrintStatement(entity);
  }
}

/// Store Assign Entities
/// \param ts List of entities
template <>
void EntityStorablePkb<AssignEntity>::Store(std::vector<AssignEntity> ts) {
  for (const AssignEntity& entity : ts) {
    entity_manager_.AddAssignStatement(entity);
    pattern_manager_.AddAssignPattern(entity);
  }
}

/// Store If Entities
/// \param ts List of entities
template <>
void EntityStorablePkb<IfEntity>::Store(std::vector<IfEntity> ts) {
  for (const IfEntity& entity : ts) {
    entity_manager_.AddIfStatement(entity);
  }
}

/// Store While Entities
/// \param ts List of entities
template <>
void EntityStorablePkb<WhileEntity>::Store(std::vector<WhileEntity> ts) {
  for (const WhileEntity& entity : ts) {
    entity_manager_.AddWhileStatement(entity);
  }
}
