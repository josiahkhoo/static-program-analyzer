#include "abstraction_extractor.h"

AbstractionExtractorResult AbstractionExtractor::Extract(
    const std::vector<AssignEntity>& assign_entities,
    const std::vector<CallEntity>& call_entities,
    const std::vector<ConstantEntity>& constant_entities,
    const std::vector<IfEntity>& if_entities,
    const std::vector<PrintEntity>& print_entities,
    const std::vector<ProcedureEntity>& procedure_entities,
    const std::vector<ReadEntity>& read_entities,
    const std::vector<StatementEntity>& statement_entities,
    const std::vector<VariableEntity>& variable_entities,
    const std::vector<WhileEntity>& while_entities) const {
  std::unordered_map<TNode, StatementEntity*> t_node_stmt_ent_umap =
      GetTNodeStatementEntityMap(statement_entities);
  std::unordered_map<TNode, VariableEntity*> t_node_var_ent_umap =
      GetTNodeVariableEntityMap(variable_entities);
  std::unordered_map<TNode, ConstantEntity*> t_node_const_ent_umap =
      GetTNodeConstantEntityMap(constant_entities);
  return {{}, {}, {}, {}, {}, {}};
}

std::unordered_map<TNode, StatementEntity*>
AbstractionExtractor::GetTNodeStatementEntityMap(
    const std::vector<StatementEntity>& statement_entities) const {
  std::unordered_map<TNode, StatementEntity*> umap;
  for (auto statement_entity : statement_entities)
    umap.insert_or_assign(*statement_entity.GetNodePointer(),
                          &statement_entity);
  return umap;
}

std::unordered_map<TNode, VariableEntity*>
AbstractionExtractor::GetTNodeVariableEntityMap(
    const std::vector<VariableEntity>& variable_entities) const {
  std::unordered_map<TNode, VariableEntity*> umap;
  for (auto variable_entity : variable_entities)
    umap.insert_or_assign(*variable_entity.GetNodePointer(), &variable_entity);
  return umap;
}

std::unordered_map<TNode, ConstantEntity*>
AbstractionExtractor::GetTNodeConstantEntityMap(
    const std::vector<ConstantEntity>& constant_entities) const {
  std::unordered_map<TNode, ConstantEntity*> umap;
  for (auto constant_entity : constant_entities)
    umap.insert_or_assign(*constant_entity.GetNodePointer(), &constant_entity);
  return umap;
}
