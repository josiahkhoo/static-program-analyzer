#ifndef SPA_QUERYABLE_PKB_H
#define SPA_QUERYABLE_PKB_H

#include "common/entity/entity_type.h"
#include "string"
#include "unordered_set"

#include "common/entity/entity_type.h"

class QueryablePkb {
public:
    [[nodiscard]] virtual std::unordered_set<std::string> QueryAll(
            EntityType type) const = 0;

    [[nodiscard]] virtual std::unordered_set<std::string> QueryAllFollow(
            EntityType type) const = 0;

    [[nodiscard]] virtual std::unordered_set<std::string> QueryAllFollowBy(
            EntityType type) const = 0;

    [[nodiscard]] virtual std::unordered_set<std::string> QueryFollow(
            int statement_number, EntityType type) const = 0;

    [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowBy(
            int statement_number, EntityType type) const = 0;

    [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowT(
            int statement_number, EntityType type) const = 0;

    [[nodiscard]] virtual std::unordered_set<std::string> QueryFollowTBy(
            int statement_number, EntityType type) const = 0;
};

#endif  // SPA_QUERYABLE_PKB_H
