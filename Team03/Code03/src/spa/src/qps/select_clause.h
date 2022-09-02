#ifndef SPA_SELECT_CLAUSE_H
#define SPA_SELECT_CLAUSE_H

#include <string>

class SelectClause : public QueryTail {
public:
	explicit SelectClause(std::string synonym);
	std::string GetSynonym() const;

private:
	std::string synonym;
};

#endif  // SPA_SELECT_CLAUSE_H

#include <vector>

#include "common/entity/entity.h"
#include "common/queryable_pkb.h"
#include "query_tail.h"

class SelectClause : public QueryTail {
 public:
  explicit SelectClause(std::string synonym);
  [[nodiscard]] std::string GetSynonym() const;
  std::vector<Entity> Filter(QueryablePkb &pkb) override;
  std::vector<Entity> Filter(QueryablePkb &pkb, std::vector<Entity> list_of_entity) override;
 private:
  std::string synonym;
};

#endif  // SPA_SELECT_CLAUSE_H