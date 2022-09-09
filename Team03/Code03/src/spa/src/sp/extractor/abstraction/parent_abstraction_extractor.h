#ifndef SPA_PARENT_ABSTRACTION_EXTRACTOR_H
#define SPA_PARENT_ABSTRACTION_EXTRACTOR_H

#include "common/abstraction/parent_abstraction.h"
#include "sp/extractor/sub_abstraction_extractor.h"

class ParentAbstractionExtractor
    : public SubAbstractionExtractor<ParentAbstraction> {
 public:
  std::vector<ParentAbstraction> Extract(
      const std::vector<AssignEntity> &assign_entities,
      const std::vector<CallEntity> &call_entities,
      const std::vector<ConstantEntity> &constant_entities,
      const std::vector<IfEntity> &if_entities,
      const std::vector<PrintEntity> &print_entities,
      const std::vector<ProcedureEntity> &procedure_entities,
      const std::vector<ReadEntity> &read_entities,
      const std::vector<StatementEntity> &statement_entities,
      const std::vector<VariableEntity> &variable_entities,
      const std::vector<WhileEntity> &while_entities,
      std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap,
      std::unordered_map<TNode, VariableEntity> &t_node_var_ent_umap,
      std::unordered_map<TNode, ConstantEntity> &t_node_const_ent_umap)
      const override;
};

#endif  // SPA_PARENT_ABSTRACTION_EXTRACTOR_H
