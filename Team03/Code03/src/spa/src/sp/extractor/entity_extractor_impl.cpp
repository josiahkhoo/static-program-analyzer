#include "entity_extractor_impl.h"

EntityExtractorImpl::EntityExtractorImpl(
    const NodeExtractor<AssignEntity> &assign_entity_node_extractor,
    const NodeExtractor<CallEntity> &call_entity_node_extractor,
    const NodeExtractor<ConstantEntity> &constant_entity_node_extractor,
    const NodeExtractor<IfEntity> &if_entity_node_extractor,
    const NodeExtractor<PrintEntity> &print_entity_node_extractor,
    const NodeExtractor<ProcedureEntity> &procedure_entity_node_extractor,
    const NodeExtractor<ReadEntity> &read_entity_node_extractor,
    const NodeExtractor<StatementEntity> &statement_entity_node_extractor,
    const NodeExtractor<VariableEntity> &variable_entity_node_extractor,
    const NodeExtractor<WhileEntity> &while_entity_node_extractor)
    : assign_entity_node_extractor_(assign_entity_node_extractor),
      call_entity_node_extractor_(call_entity_node_extractor),
      constant_entity_node_extractor_(constant_entity_node_extractor),
      if_entity_node_extractor_(if_entity_node_extractor),
      print_entity_node_extractor_(print_entity_node_extractor),
      procedure_entity_node_extractor_(procedure_entity_node_extractor),
      read_entity_node_extractor_(read_entity_node_extractor),
      statement_entity_node_extractor_(statement_entity_node_extractor),
      variable_entity_node_extractor_(variable_entity_node_extractor),
      while_entity_node_extractor_(while_entity_node_extractor) {}

EntityExtractorResult EntityExtractorImpl::Extract(const TNode &ast) const {
  std::vector<AssignEntity> assign_entities;
  std::vector<CallEntity> call_entities;
  std::vector<ConstantEntity> constant_entities;
  std::vector<IfEntity> if_entities;
  std::vector<PrintEntity> print_entities;
  std::vector<ProcedureEntity> procedure_entities;
  std::vector<ReadEntity> read_entities;
  std::vector<StatementEntity> statement_entities;
  std::vector<VariableEntity> variable_entities;
  std::vector<WhileEntity> while_entities;

  RecursivelyExtractNode(
      ast, &assign_entities, &call_entities, &constant_entities, &if_entities,
      &print_entities, &procedure_entities, &read_entities, &statement_entities,
      &variable_entities, &while_entities);

  return {assign_entities, call_entities,      constant_entities,
          if_entities,     print_entities,     procedure_entities,
          read_entities,   statement_entities, variable_entities,
          while_entities};
}

void EntityExtractorImpl::ExtractNode(
    const TNode &node, std::vector<AssignEntity> *assign_entities,
    std::vector<CallEntity> *call_entities,
    std::vector<ConstantEntity> *constant_entities,
    std::vector<IfEntity> *if_entities,
    std::vector<PrintEntity> *print_entities,
    std::vector<ProcedureEntity> *procedure_entities,
    std::vector<ReadEntity> *read_entities,
    std::vector<StatementEntity> *statement_entities,
    std::vector<VariableEntity> *variable_entities,
    std::vector<WhileEntity> *while_entities) const {
  std::optional<AssignEntity> maybe_assign_entity =
      assign_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_assign_entity.has_value()) {
    assign_entities->push_back(maybe_assign_entity.value());
  }
  std::optional<CallEntity> maybe_call_entity =
      call_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_call_entity.has_value()) {
    call_entities->push_back(maybe_call_entity.value());
  }
  std::optional<ConstantEntity> maybe_constant_entity =
      constant_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_constant_entity.has_value()) {
    constant_entities->push_back(maybe_constant_entity.value());
  }
  std::optional<IfEntity> maybe_if_entity =
      if_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_if_entity.has_value()) {
    if_entities->push_back(maybe_if_entity.value());
  }
  std::optional<PrintEntity> maybe_print_entity =
      print_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_print_entity.has_value()) {
    print_entities->push_back(maybe_print_entity.value());
  }
  std::optional<ProcedureEntity> maybe_procedure_entity =
      procedure_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_procedure_entity.has_value()) {
    procedure_entities->push_back(maybe_procedure_entity.value());
  }
  std::optional<ReadEntity> maybe_read_entity =
      read_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_read_entity.has_value()) {
    read_entities->push_back(maybe_read_entity.value());
  }
  std::optional<StatementEntity> maybe_statement_entity =
      statement_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_statement_entity.has_value()) {
    statement_entities->push_back(maybe_statement_entity.value());
  }
  std::optional<VariableEntity> maybe_variable_entity =
      variable_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_variable_entity.has_value()) {
    variable_entities->push_back(maybe_variable_entity.value());
  }
  std::optional<WhileEntity> maybe_while_entity =
      while_entity_node_extractor_.TryExtractFromNode(node);
  if (maybe_while_entity.has_value()) {
    while_entities->push_back(maybe_while_entity.value());
  }
}

void EntityExtractorImpl::RecursivelyExtractNode(
    const TNode &node, std::vector<AssignEntity> *assign_entities,
    std::vector<CallEntity> *call_entities,
    std::vector<ConstantEntity> *constant_entities,
    std::vector<IfEntity> *if_entities,
    std::vector<PrintEntity> *print_entities,
    std::vector<ProcedureEntity> *procedure_entities,
    std::vector<ReadEntity> *read_entities,
    std::vector<StatementEntity> *statement_entities,
    std::vector<VariableEntity> *variable_entities,
    std::vector<WhileEntity> *while_entities) const {
  ExtractNode(node, assign_entities, call_entities, constant_entities,
              if_entities, print_entities, procedure_entities, read_entities,
              statement_entities, variable_entities, while_entities);
  if (!node.IsLeaf()) {
    for (const std::shared_ptr<TNode> &child : node.GetChildren()) {
      RecursivelyExtractNode(
          *child, assign_entities, call_entities, constant_entities,
          if_entities, print_entities, procedure_entities, read_entities,
          statement_entities, variable_entities, while_entities);
    }
  }
};
