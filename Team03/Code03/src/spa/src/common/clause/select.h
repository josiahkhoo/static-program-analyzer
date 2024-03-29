#ifndef SPA_SELECT_H
#define SPA_SELECT_H

#include <optional>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/queryable_pkb.h"
#include "common/reference/attribute.h"
#include "common/reference/attribute_name.h"
#include "common/reference/synonym.h"
#include "qps/qnodes/q_result.h"

class Select {
 public:
  struct SynonymWithMaybeAttribute {
    explicit SynonymWithMaybeAttribute(Synonym synonym)
        : synonym(std::move(synonym)), maybe_attribute(std::nullopt) {}

    SynonymWithMaybeAttribute(Synonym synonym, AttributeName attribute)
        : synonym(std::move(synonym)), maybe_attribute(attribute) {}

    Synonym synonym;
    std::optional<AttributeName> maybe_attribute;
  };

  virtual ~Select() = default;

  [[nodiscard]] virtual std::vector<SynonymWithMaybeAttribute> GetSynonyms()
      const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetResultSet(
      const QResult &q_result, const QueryablePkb &pkb) const = 0;
};

#endif  // SPA_SELECT_H
