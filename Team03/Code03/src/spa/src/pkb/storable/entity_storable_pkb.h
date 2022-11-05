//
// Created by kohha on 3/11/2022.
//

#ifndef SPA_ENTITY_STORABLE_PKB_H
#define SPA_ENTITY_STORABLE_PKB_H

#include "pkb/storable/entity/assign_entity_storable.h"
#include "pkb/storable/entity/call_entity_storable.h"
#include "pkb/storable/entity/constant_entity_storable.h"
#include "pkb/storable/entity/if_entity_storable.h"
#include "pkb/storable/entity/print_entity_storable.h"
#include "pkb/storable/entity/procedure_entity_storable.h"
#include "pkb/storable/entity/read_entity_storable.h"
#include "pkb/storable/entity/variable_entity_storable.h"
#include "pkb/storable/entity/while_entity_storable.h"

class EntityStorablePkb {
 public:
  EntityStorablePkb();

  [[nodiscard]] AssignEntityStorable GetAssignEntityStorable() const;

  [[nodiscard]] CallEntityStorable GetCallEntityStorable() const;

  [[nodiscard]] ConstantEntityStorable GetConstantEntityStorable() const;

  [[nodiscard]] IfEntityStorable GetIfEntityStorable() const;

  [[nodiscard]] PrintEntityStorable GetPrintEntityStorable() const;

  [[nodiscard]] ProcedureEntityStorable GetProcedureEntityStorable() const;

  [[nodiscard]] ReadEntityStorable GetReadEntityStorable() const;

  [[nodiscard]] VariableEntityStorable GetVariableEntityStorable() const;

  [[nodiscard]] WhileEntityStorable GetWhileEntityStorable() const;

 private:
  AssignEntityStorable assign_entity_storable_;
  CallEntityStorable call_entity_storable_;
  ConstantEntityStorable constant_entity_storable_;
  IfEntityStorable if_entity_storable_;
  PrintEntityStorable print_entity_storable_;
  ProcedureEntityStorable procedure_entity_storable_;
  ReadEntityStorable read_entity_storable_;
  VariableEntityStorable variable_entity_storable_;
  WhileEntityStorable while_entity_storable_;
};

#endif  // SPA_ENTITY_STORABLE_PKB_H
