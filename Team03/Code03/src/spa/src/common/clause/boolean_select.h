#ifndef SPA_BOOLEAN_SELECT_H
#define SPA_BOOLEAN_SELECT_H

#include "select.h"

class BooleanSelect : public Select {
 public:
  [[nodiscard]] std::vector<SynonymWithMaybeAttribute> GetSynonyms()
      const override;
  [[nodiscard]] std::unordered_set<std::string> GetResultSet(
      QResult q_result) const override;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_CLAUSE_BOOLEAN_SELECT_H_
