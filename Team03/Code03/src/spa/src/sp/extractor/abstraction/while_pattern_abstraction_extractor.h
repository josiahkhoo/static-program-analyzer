#ifndef SPA_WHILE_PATTERN_ABSTRACTION_EXTRACTOR_H_
#define SPA_WHILE_PATTERN_ABSTRACTION_EXTRACTOR_H_

#include "common/abstraction/while_pattern_abstraction.h"
#include "sp/extractor/sub_abstraction_extractor.h"

class WhilePatternAbstractionExtractor
    : public SubAbstractionExtractor<WhilePatternAbstraction> {
 public:
  std::vector<WhilePatternAbstraction> Extract(
      const SubAbstractionExtractorContext &context) const override;

 private:
  void RecursivelyExtractFromChildren(
      std::vector<WhilePatternAbstraction> *while_pattern_abstractions,
      const WhileEntity &while_entity,
      const std::vector<std::shared_ptr<TNode>> &children,
      std::unordered_map<TNode, VariableEntity> &t_node_var_ent_umap) const;
};

#endif  // SPA_WHILE_PATTERN_ABSTRACTION_EXTRACTOR_H_
