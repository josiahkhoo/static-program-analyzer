#ifndef SPA_FOLLOWS_T_ABSTRACTION_EXTRACTOR_H
#define SPA_FOLLOWS_T_ABSTRACTION_EXTRACTOR_H

#include "common/abstraction/follows_t_abstraction.h"
#include "sp/extractor/sub_abstraction_extractor.h"

class FollowsTAbstractionExtractor
    : public SubAbstractionExtractor<FollowsTAbstraction> {
 public:
  [[nodiscard]] std::vector<FollowsTAbstraction> Extract(
      const SubAbstractionExtractorContext &context) const override;

 private:
  static void RetrieveFromChildren(
      std::vector<FollowsTAbstraction> *follows_t_abstractions,
      const std::vector<std::shared_ptr<TNode>> &children,
      std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap);
};

#endif  // SPA_FOLLOWS_T_ABSTRACTION_EXTRACTOR_H
