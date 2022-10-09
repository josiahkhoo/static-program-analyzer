#include "entity_extractor_result.h"

#include <utility>

EntityExtractorResult::EntityExtractorResult(
    std::vector<AssignEntity> assign_entities,
    std::vector<CallEntity> call_entities,
    std::vector<ConstantEntity> constant_entities,
    std::vector<IfEntity> if_entities, std::vector<PrintEntity> print_entities,
    std::vector<ProcedureEntity> procedure_entities,
    std::vector<ReadEntity> read_entities,
    std::vector<StatementEntity> statement_entities,
    std::vector<VariableEntity> variable_entities,
    std::vector<WhileEntity> while_entities)
    : assign_entities_(std::move(assign_entities)),
      call_entities_(std::move(call_entities)),
      constant_entities_(std::move(constant_entities)),
      if_entities_(std::move(if_entities)),
      print_entities_(std::move(print_entities)),
      procedure_entities_(std::move(procedure_entities)),
      read_entities_(std::move(read_entities)),
      statement_entities_(std::move(statement_entities)),
      variable_entities_(std::move(variable_entities)),
      while_entities_(std::move(while_entities)) {}

std::vector<AssignEntity> EntityExtractorResult::GetAssignEntities() const {
  return assign_entities_;
}

std::vector<CallEntity> EntityExtractorResult::GetCallEntities() const {
  return call_entities_;
}

std::vector<ConstantEntity> EntityExtractorResult::GetConstantEntities() const {
  return constant_entities_;
}

std::vector<IfEntity> EntityExtractorResult::GetIfEntities() const {
  return if_entities_;
}

std::vector<PrintEntity> EntityExtractorResult::GetPrintEntities() const {
  return print_entities_;
}

std::vector<ProcedureEntity> EntityExtractorResult::GetProcedureEntities()
    const {
  return procedure_entities_;
}

std::vector<ReadEntity> EntityExtractorResult::GetReadEntities() const {
  return read_entities_;
}

std::vector<StatementEntity> EntityExtractorResult::GetStatementEntities()
    const {
  return statement_entities_;
}

std::vector<VariableEntity> EntityExtractorResult::GetVariableEntities() const {
  return variable_entities_;
}

std::vector<WhileEntity> EntityExtractorResult::GetWhileEntities() const {
  return while_entities_;
}

bool EntityExtractorResult::operator==(const EntityExtractorResult &rhs) const {
  return assign_entities_ == rhs.assign_entities_ &&
         call_entities_ == rhs.call_entities_ &&
         constant_entities_ == rhs.constant_entities_ &&
         if_entities_ == rhs.if_entities_ &&
         print_entities_ == rhs.print_entities_ &&
         procedure_entities_ == rhs.procedure_entities_ &&
         read_entities_ == rhs.read_entities_ &&
         statement_entities_ == rhs.statement_entities_ &&
         variable_entities_ == rhs.variable_entities_ &&
         while_entities_ == rhs.while_entities_;
}

bool EntityExtractorResult::operator!=(const EntityExtractorResult &rhs) const {
  return !(rhs == *this);
}

EntityExtractorResult::Builder::Builder() = default;

EntityExtractorResult::Builder EntityExtractorResult::Builder::AssignEntities(
    std::vector<AssignEntity> *assign_entities) {
  assign_entities_ = assign_entities;
  return *this;
}

EntityExtractorResult::Builder EntityExtractorResult::Builder::CallEntities(
    std::vector<CallEntity> *call_entities) {
  call_entities_ = call_entities;
  return *this;
}

EntityExtractorResult::Builder EntityExtractorResult::Builder::ConstantEntities(
    std::vector<ConstantEntity> *constant_entities) {
  constant_entities_ = constant_entities;
  return *this;
}

EntityExtractorResult::Builder EntityExtractorResult::Builder::IfEntities(
    std::vector<IfEntity> *if_entities) {
  if_entities_ = if_entities;
  return *this;
}

EntityExtractorResult::Builder EntityExtractorResult::Builder::PrintEntities(
    std::vector<PrintEntity> *print_entities) {
  print_entities_ = print_entities;
  return *this;
}

EntityExtractorResult::Builder
EntityExtractorResult::Builder::ProcedureEntities(
    std::vector<ProcedureEntity> *procedure_entities) {
  procedure_entities_ = procedure_entities;
  return *this;
}

EntityExtractorResult::Builder EntityExtractorResult::Builder::ReadEntities(
    std::vector<ReadEntity> *read_entities) {
  read_entities_ = read_entities;
  return *this;
}

EntityExtractorResult::Builder
EntityExtractorResult::Builder::StatementEntities(
    std::vector<StatementEntity> *statement_entities) {
  statement_entities_ = statement_entities;
  return *this;
}

EntityExtractorResult::Builder EntityExtractorResult::Builder::VariableEntities(
    std::vector<VariableEntity> *variable_entities) {
  variable_entities_ = variable_entities;
  return *this;
}

EntityExtractorResult::Builder EntityExtractorResult::Builder::WhileEntities(
    std::vector<WhileEntity> *while_entities) {
  while_entities_ = while_entities;
  return *this;
}

EntityExtractorResult EntityExtractorResult::Builder::Build() {
  return {*assign_entities_, *call_entities_,      *constant_entities_,
          *if_entities_,     *print_entities_,     *procedure_entities_,
          *read_entities_,   *statement_entities_, *variable_entities_,
          *while_entities_};
}
