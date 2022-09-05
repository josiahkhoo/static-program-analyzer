#include "catch.hpp"
#include "common/queryable_pkb.h"
#include "qps/planner.h"



TEST_CASE("Test construct 1 node: Select", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  QueryString qs = QueryString(s, {syn}, {});

  std::shared_ptr<QNode> root = p.Plan(qs);
  REQUIRE(root->IsLeaf());
}

TEST_CASE("Test construct 1 node: Select & Follows", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference(1);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);
  QueryString qs = QueryString(s, {syn}, {f});

  std::shared_ptr<QNode> root = p.Plan(qs);
  REQUIRE(root->IsLeaf());
}

TEST_CASE("Test query 1 node: Select & Follows", "[Planner]") {
  class QueryablePkbStub : public QueryablePkb {
   public:
    [[nodiscard]] std::unordered_set<std::string> QueryAll(
        EntityType type) const override {
      return {"1"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollow(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollowBy(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollow(
        int statement_number, EntityType type) const override {
      return {"1"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowBy(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowT(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowTBy(
        int statement_number, EntityType type) const override {
      return {};
    }
  };

  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  REQUIRE(root->Fetch(pkb).size() == 1);
}
