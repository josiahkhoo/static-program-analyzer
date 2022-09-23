#ifndef SPA_SELECT_H
#define SPA_SELECT_H

#include <unordered_set>
#include <vector>

#include "common/reference/synonym.h"
#include "qps/qnodes/q_result.h"

class Select {
 public:
  [[nodiscard]] virtual std::vector<Synonym> GetSynonyms() const = 0;

  [[nodiscard]] virtual std::unordered_set<std::string> GetResultSet(
      QResult q_result) const = 0;
};

#endif  // SPA_SELECT_H
