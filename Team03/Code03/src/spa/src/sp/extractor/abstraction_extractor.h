//
// Created by Josiah Khoo on 29/8/22.
//

#ifndef SPA_ABSTRACTION_EXTRACTOR_H
#define SPA_ABSTRACTION_EXTRACTOR_H

#include <unordered_map>

#include "abstraction_extractor_result.h"
#include "common/entity/constant_entity.h"
#include "common/entity/statement_entity.h"
#include "common/entity/variable_entity.h"
#include "entity_extractor_result.h"

class AbstractionExtractor {
 public:
  AbstractionExtractorResult Extract(
      EntityExtractorResult eer,
      std::unordered_map<TNode, StatementEntity> t_node_stmt_ent_umap,
      std::unordered_map<TNode, VariableEntity> t_node_var_ent_umap,
      std::unordered_map<TNode, ConstantEntity> t_node_const_ent_umap) const;
};

#endif  // SPA_ABSTRACTION_EXTRACTOR_H
