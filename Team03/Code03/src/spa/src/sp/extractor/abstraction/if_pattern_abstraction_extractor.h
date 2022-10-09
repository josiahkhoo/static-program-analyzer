#ifndef SPA_IF_PATTERN_ABSTRACTION_EXTRACTOR_H_
#define SPA_IF_PATTERN_ABSTRACTION_EXTRACTOR_H_

#include "common/abstraction/if_pattern_abstraction.h"
#include "sp/extractor/sub_abstraction_extractor.h"

class IfPatternAbstractionExtractor
    : public SubAbstractionExtractor<IfPatternAbstraction> {
 public:
  std::vector<IfPatternAbstraction> Extract(
      const SubAbstractionExtractorContext &context) const override;

 private:
  void RecursivelyExtractFromChildren(
      std::vector<IfPatternAbstraction> *if_pattern_abstractions,
      const IfEntity &if_entity,
      const std::vector<std::shared_ptr<TNode>> &children,
      std::unordered_map<TNode, VariableEntity> &t_node_var_ent_umap) const;
};

#endif  // SPA_IF_PATTERN_ABSTRACTION_EXTRACTOR_H_
