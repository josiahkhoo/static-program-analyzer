//
// Created by kohha on 3/11/2022.
//

#include "entity_storable_pkb.h"

EntityStorablePkb::EntityStorablePkb() = default;

/// Get AssignEntityStorable
/// \return AssignEntityStorable 
AssignEntityStorable EntityStorablePkb::GetAssignEntityStorable() const {
  return assign_entity_storable_;
}

/// Get CallEntityStorable
/// \return CallEntityStorable 
CallEntityStorable EntityStorablePkb::GetCallEntityStorable() const {
  return call_entity_storable_;
}

/// Get ConstantEntityStorable
/// \return ConstantEntityStorable 
ConstantEntityStorable EntityStorablePkb::GetConstantEntityStorable() const {
  return constant_entity_storable_;
}

/// Get IfEntityStorable
/// \return IfEntityStorable 
IfEntityStorable EntityStorablePkb::GetIfEntityStorable() const {
  return if_entity_storable_;
}

/// Get PrintEntityStorable
/// \return PrintEntityStorable 
PrintEntityStorable EntityStorablePkb::GetPrintEntityStorable() const {
  return print_entity_storable_;
}

/// Get ProcedureEntityStorable
/// \return ProcedureEntityStorable 
ProcedureEntityStorable EntityStorablePkb::GetProcedureEntityStorable() const {
  return procedure_entity_storable_;
}

/// Get ReadEntityStorable
/// \return ReadEntityStorable 
ReadEntityStorable EntityStorablePkb::GetReadEntityStorable() const {
  return read_entity_storable_;
}

/// Get VariableEntityStorable
/// \return VariableEntityStorable 
VariableEntityStorable EntityStorablePkb::GetVariableEntityStorable() const {
  return variable_entity_storable_;
}

/// Get WhileEntityStorable
/// \return WhileEntityStorable 
WhileEntityStorable EntityStorablePkb::GetWhileEntityStorable() const {
  return while_entity_storable_;
}
