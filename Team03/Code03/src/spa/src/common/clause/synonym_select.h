#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_CLAUSE_SYNONYM_SELECT_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_CLAUSE_SYNONYM_SELECT_H_

#include <vector>

#include "common/reference/synonym.h"
#include "select.h"

class SynonymSelect : public Select {
 public:
  explicit SynonymSelect(std::vector<Synonym> synonyms);

  [[nodiscard]] std::vector<Synonym> GetSynonyms() const override;
  [[nodiscard]] std::unordered_set<std::string> GetResultSet(
      QResult q_result) const override;

 private:
  std::vector<Synonym> synonyms_;
};
#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_CLAUSE_SYNONYM_SELECT_H_
