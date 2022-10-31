#ifndef SPA_CALLS_T_ABSTRACTION_EXTRACTOR_H
#define SPA_CALLS_T_ABSTRACTION_EXTRACTOR_H

#include "common/abstraction/calls_t_abstraction.h"
#include "sp/extractor/sub_abstraction_extractor.h"

class CallsTAbstractionExtractor
    : public SubAbstractionExtractor<CallsTAbstraction> {
 public:
  [[nodiscard]] std::vector<CallsTAbstraction> Extract(
      const SubAbstractionExtractorContext &context) const override;

  void TraverseProcedureTree(
      std::unordered_map<TNode, ProcedureEntity> &t_node_proc_ent_umap,
      std::vector<CallsTAbstraction> &calls_t_abstractions,
      std::unordered_map<std::string, const TNode *> &proc_name_mapping,
      std::unordered_map<const TNode *, std::unordered_set<const TNode *>>
          &procedure_mapping,
      const std::unordered_set<const TNode *> &children, ProcedureEntity &lhs,
      std::unordered_set<std::string> &unique_procedures) const;
};

#endif  // SPA_CALLS_T_ABSTRACTION_EXTRACTOR_H
