#ifndef SPA_BOOLEAN_SELECT_H
#define SPA_BOOLEAN_SELECT_H

#include "select.h"

class BooleanSelect : public Select {
 public:
  [[nodiscard]] std::vector<SynonymWithMaybeAttribute> GetSynonyms()
      const override;
  [[nodiscard]] std::unordered_set<std::string> GetResultSet(
      const QResult &q_result, const QueryablePkb &pkb) const override;
};

#endif  // SPA_BOOLEAN_SELECT_H
