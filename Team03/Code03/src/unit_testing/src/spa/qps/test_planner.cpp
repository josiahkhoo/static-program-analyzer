#include "catch.hpp"
#include "common/queryable_pkb.h"
#include "common/reference/expression.h"
#include "qps/planner.h"

class QueryablePkbStub : public QueryablePkb {
 public:
  [[nodiscard]] std::unordered_set<std::string> QueryAll(
      EntityType type) const override {
    return {"1"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const override {
    return {"2"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const override {
    return {"3"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollows(
      int statement_number, EntityType type) const override {
    return {"4"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const override {
    return {"5"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
      int statement_number, EntityType type) const override {
    return {"6"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const override {
    return {"7"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllPattern(
      Expression exp) const override {
    return {"8"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPattern(
      EntityType type, Expression exp) const override {
    return {"9"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPattern(
      std::string lhs, Expression exp) const override {
    return {"10"};
  }
};

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

TEST_CASE("Test construct 1 node: Select & Pattern", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  EntityReference entity_ref = EntityReference();
  Expression exp;
  exp.toMatch = "b";
  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entity_ref, exp);
  QueryString qs = QueryString(s, {syn}, {ptn});

  std::shared_ptr<QNode> root = p.Plan(qs);
  REQUIRE(root->IsLeaf());
}

TEST_CASE("Test query 1 node: Select & Follows", "[Planner]") {
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
  REQUIRE(*(root->Fetch(pkb).begin()) == "4");
}

TEST_CASE("Test query 1 node: Select & FollowsBy", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference(1);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  REQUIRE(*(root->Fetch(pkb).begin()) == "5");
}

TEST_CASE("Test query 1 node: Select & FollowsT", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  std::shared_ptr<FollowsTClause> f =
      std::make_shared<FollowsTClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  REQUIRE(*(root->Fetch(pkb).begin()) == "6");
}

TEST_CASE("Test query 1 node: Select & FollowsTBy", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference(1);
  std::shared_ptr<FollowsTClause> f =
      std::make_shared<FollowsTClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  REQUIRE(*(root->Fetch(pkb).begin()) == "7");
}

TEST_CASE("Test query 1 node: Select & Pattern WILDCARD", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  EntityReference entity_ref = EntityReference();
  Expression exp;
  exp.toMatch = "b";
  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  REQUIRE(*(root->Fetch(pkb).begin()) == "8");
}

TEST_CASE("Test query 1 node: Select & Pattern IDENTIFIER", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.toMatch = "b";
  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  REQUIRE(*(root->Fetch(pkb).begin()) == "10");
}
