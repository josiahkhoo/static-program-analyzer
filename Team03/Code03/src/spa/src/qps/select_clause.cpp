#include "select_clause.h"

SelectClause::SelectClause(std::string synonym) : synonym(synonym){}

std::string SelectClause::GetSynonym() const { return synonym; }
#include "common/queryable_pkb.h"

SelectClause::SelectClause(std::string synonym) : synonym(synonym){}

std::string SelectClause::GetSynonym() const { return synonym; }

std::vector<Entity> SelectClause::Filter(QueryablePkb &pkb, std::vector<Entity> list_of_entity) {
  return list_of_entity;
}

std::vector<Entity> SelectClause::Filter(QueryablePkb &pkb) {
  pkb.query();
  return {};
}
