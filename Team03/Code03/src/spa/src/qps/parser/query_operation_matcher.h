#ifndef SPA_QUERY_OPERATION_MATCHER_H
#define SPA_QUERY_OPERATION_MATCHER_H

#include <memory>

#include "common/entity/entity_type.h"
#include "common/token_handler.h"
#include "qps/query_string_builder.h"

/// Utility class for matching clause/operation starting grammar word(s)
class QueryOperationMatcher {
 public:
  /// Checks if current tokens match clause/operation grammar word
  [[nodiscard]] static bool MatchParser(
      const std::shared_ptr<TokenHandler>& tokens, const std::string& word);
  /// Checks if current tokens match entity type and clause/operation grammar
  /// word
  [[nodiscard]] static bool MatchParser(
      const std::pair<std::shared_ptr<TokenHandler>, const QueryStringBuilder&>&
          data,
      const EntityType& type);
  /// Checks if current tokens match T clause/operation grammar word
  [[nodiscard]] static bool MatchTParser(
      const std::shared_ptr<TokenHandler>& tokens, const std::string& word);
};

#endif  // SPA_QUERY_OPERATION_MATCHER_H
