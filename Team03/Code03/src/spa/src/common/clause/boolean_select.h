#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_CLAUSE_BOOLEAN_SELECT_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_CLAUSE_BOOLEAN_SELECT_H_

#include "select.h"

class BooleanSelect : public Select {
 public:
  [[nodiscard]] std::vector<Synonym> GetSynonyms() const override;
  [[nodiscard]] std::unordered_set<std::string> GetResultSet(
      QResult q_result) const override;

 public:
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_CLAUSE_BOOLEAN_SELECT_H_
