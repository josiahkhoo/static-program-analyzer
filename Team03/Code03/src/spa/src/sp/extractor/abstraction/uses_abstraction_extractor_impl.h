#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_IMPL_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_IMPL_H_

#include "common/abstraction/uses_p_abstraction.h"
#include "common/abstraction/uses_s_abstraction.h"
#include "sp/extractor/bi_sub_abstraction_extractor.h"
#include "uses_abstraction_extractor.h"

class UsesAbstractionExtractorImpl : public UsesAbstractionExtractor {
 public:
  std::pair<std::vector<UsesSAbstraction>, std::vector<UsesPAbstraction>>
  Extract(const SubAbstractionExtractorContext& context) const override;

 private:
  void TraverseProcedureTree(
      std::unordered_map<TNode, ProcedureEntity>& t_node_proc_ent_umap,
      std::unordered_map<std::string, const TNode*>& proc_name_node_umap,
      std::unordered_map<const TNode*, std::unordered_set<const TNode*>>&
          proc_node_call_ent_umap,
      std::unordered_map<const TNode*, std::unordered_set<const TNode*>>&
          proc_var_map,
      std::unordered_set<const TNode*>& children, const TNode* parent) const;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_SP_EXTRACTOR_ABSTRACTION_USES_ABSTRACTION_EXTRACTOR_IMPL_H_
