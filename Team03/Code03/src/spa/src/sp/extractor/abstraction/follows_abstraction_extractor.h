#ifndef SPA_FOLLOWS_ABSTRACTION_EXTRACTOR_H
#define SPA_FOLLOWS_ABSTRACTION_EXTRACTOR_H

#include "common/abstraction/follows_abstraction.h"
#include "sp/extractor/sub_abstraction_extractor.h"

class FollowsAbstractionExtractor
    : public SubAbstractionExtractor<FollowsAbstraction> {
 public:
  [[nodiscard]] std::vector<FollowsAbstraction> Extract(
      const SubAbstractionExtractorContext &context) const override;

 private:
  static void RetrieveFromChildren(
      std::vector<FollowsAbstraction> *follows_abstractions,
      const std::vector<std::shared_ptr<TNode>> &children,
      std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap);
};

#endif  // SPA_FOLLOWS_ABSTRACTION_EXTRACTOR_H
