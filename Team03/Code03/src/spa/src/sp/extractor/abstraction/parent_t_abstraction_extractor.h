#ifndef SPA_PARENT_T_ABSTRACTION_EXTRACTOR_H
#define SPA_PARENT_T_ABSTRACTION_EXTRACTOR_H

#include "common/abstraction/parent_t_abstraction.h"
#include "sp/extractor/sub_abstraction_extractor.h"

class ParentTAbstractionExtractor
    : public SubAbstractionExtractor<ParentTAbstraction> {
 public:
  [[nodiscard]] std::vector<ParentTAbstraction> Extract(
      const SubAbstractionExtractorContext &context) const override;

 private:
  void RetrieveFromWhileChildren(
      std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap,
      std::vector<ParentTAbstraction> &parent_t_abstractions,
      StatementEntity &lhs,
      const std::vector<std::shared_ptr<TNode>> &children) const;
  void RetrieveFromIfChildren(
      std::unordered_map<TNode, StatementEntity> &t_node_stmt_ent_umap,
      std::vector<ParentTAbstraction> &parent_t_abstractions,
      StatementEntity &lhs,
      const std::vector<std::shared_ptr<TNode>> &then_statements,
      const std::vector<std::shared_ptr<TNode>> &else_statements) const;
};

#endif  // SPA_PARENT_T_ABSTRACTION_EXTRACTOR_H
