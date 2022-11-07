#ifndef SPA_ENTITY_QUERYABLE_H
#define SPA_ENTITY_QUERYABLE_H

#include "common/entity/entity_type.h"
#include "common/reference/attribute_name.h"
#include "pkb/entity_store/entity_manager.h"

class EntityQueryable {
 public:
  explicit EntityQueryable(const EntityManager& entity_manager_);

  [[nodiscard]] std::unordered_set<std::string> QueryAll(EntityType type) const;

  [[nodiscard]] std::unordered_set<std::string> GetAssignStatements() const;

  [[nodiscard]] std::unordered_set<std::string> GetCallStatements() const;

  [[nodiscard]] std::unordered_set<std::string> GetReadStatements() const;

  // With Query Methods
  [[nodiscard]] std::string QueryWithAttributeFromStatement(
      EntityType type, int statement_number) const;

  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType type, AttributeName name, std::string identifier) const;

  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType type, AttributeName name, int number) const;

  [[nodiscard]] bool CheckValidAffectsStmtNo(int stmt_no) const;

  // For Affects Relationship
  [[nodiscard]] bool CheckNotAssignStmtNo(int stmt_no) const;

 protected:
  const EntityManager& entity_manager_;
};

#endif  // SPA_ENTITY_QUERYABLE_H
