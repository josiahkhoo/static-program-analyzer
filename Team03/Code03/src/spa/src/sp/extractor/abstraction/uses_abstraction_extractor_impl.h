#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_IMPL_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_IMPL_H_

#include "common/abstraction/uses_p_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"
#include "sp/extractor/bi_sub_abstraction_extractor.h"
#include "uses_abstraction_extractor.h"

class UsesAbstractionExtractorImpl : public UsesAbstractionExtractor {
 public:
  std::pair<std::vector<UsesSAbstraction>, std::vector<UsesPAbstraction>>
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
          std::unordered_map<TNode, ProcedureEntity>& t_node_proc_ent_umap,
          std::unordered_map<const TNode*, std::unordered_set<const TNode*>>&
              proc_node_call_ent_umap,
          std::unordered_map<std::string, const TNode*>& proc_name_node_umap)
      const override;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_IMPL_H_
