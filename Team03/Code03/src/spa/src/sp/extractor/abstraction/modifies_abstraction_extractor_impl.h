#ifndef SPA_MODIFIES_ABSTRACTION_EXTRACTOR_IMPL_H
#define SPA_MODIFIES_ABSTRACTION_EXTRACTOR_IMPL_H

#include "common/abstraction/modifies_p_abstraction.h"
#include "common/abstraction/modifies_s_abstraction.h"
#include "modifies_abstraction_extractor.h"
#include "sp/extractor/bi_sub_abstraction_extractor.h"

class ModifiesAbstractionExtractorImpl : public ModifiesAbstractionExtractor {
 public:
  std::pair<std::vector<ModifiesSAbstraction>,
            std::vector<ModifiesPAbstraction>>
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
      const override;
};

#endif  // SPA_MODIFIES_ABSTRACTION_EXTRACTOR_IMPL_H
