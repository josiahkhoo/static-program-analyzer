#ifndef SPA_SYNONYM_SELECT_H_
#define SPA_SYNONYM_SELECT_H_

#include <vector>

#include "common/reference/attribute.h"
#include "common/reference/synonym.h"
#include "select.h"

class SynonymSelect : public Select {
 public:
  explicit SynonymSelect(std::vector<SynonymWithMaybeAttribute> synonyms);

  [[nodiscard]] std::vector<SynonymWithMaybeAttribute> GetSynonyms()
      const override;

  [[nodiscard]] std::unordered_set<std::string> GetResultSet(
      QResult q_result) const override;

 private:
  std::vector<SynonymWithMaybeAttribute> synonyms_;
};
#endif  // SPA_SYNONYM_SELECT_H_
