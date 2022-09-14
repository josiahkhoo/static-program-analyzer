#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_H_

#include "common/abstraction/uses_p_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"
#include "sp/extractor/bi_sub_abstraction_extractor.h"

class UsesAbstractionExtractor
    : public BiSubAbstractionExtractor<UsesSAbstraction, UsesPAbstraction> {
 public:
  virtual std::pair<std::vector<UsesSAbstraction>,
                    std::vector<UsesPAbstraction>>
  Extract(const std::vector<AssignEntity>& assign_entities,
          const std::vector<CallEntity>& call_entities,
          const std::vector<ConstantEntity>& constant_entities,
          const std::vector<IfEntity>& if_entities,
          const std::vector<PrintEntity>& print_entities,
          const std::vector<ProcedureEntity>& procedure_entities,
          const std::vector<ReadEntity>& read_entities,
          const std::vector<StatementEntity>& statement_entities,
          const std::vector<VariableEntity>& variable_entities,
          const std::vector<WhileEntity>& while_entities,
          std::unordered_map<TNode, StatementEntity>& t_node_stmt_ent_umap,
          std::unordered_map<TNode, VariableEntity>& t_node_var_ent_umap,
          std::unordered_map<TNode, ConstantEntity>& t_node_const_ent_umap,
          std::unordered_map<TNode, ProcedureEntity>& t_node_proc_ent_umap)
      const = 0;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_H_
