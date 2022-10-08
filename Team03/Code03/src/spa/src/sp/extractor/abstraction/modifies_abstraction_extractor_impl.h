#ifndef SPA_MODIFIES_ABSTRACTION_EXTRACTOR_IMPL_H
#define SPA_MODIFIES_ABSTRACTION_EXTRACTOR_IMPL_H

#include "common/abstraction/modifies_p_abstraction.h"
#include "common/abstraction/modifies_s_abstraction.h"
#include "modifies_abstraction_extractor.h"
#include "sp/extractor/bi_sub_abstraction_extractor.h"

class ModifiesAbstractionExtractorImpl : public ModifiesAbstractionExtractor {
 public:
  [[nodiscard]] std::pair<std::vector<ModifiesSAbstraction>,
                          std::vector<ModifiesPAbstraction>>
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

#endif  // SPA_MODIFIES_ABSTRACTION_EXTRACTOR_IMPL_H
