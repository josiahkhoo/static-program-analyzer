#include "catch.hpp"
#include "qps/evaluator.h"
#include "qps/planner.h"
#include "qps/qnodes/entity_node.h"

class QueryablePkbStub : public QueryablePkb {
 public:
  [[nodiscard]] std::unordered_set<std::string> QueryAll(
      EntityType type) const override {
    return {"QueryAll"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
      EntityType type) const override {
    return {"QueryAllFollows"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType type) const override {
    return {"QueryAllFollowsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollows(
      int statement_number, EntityType type) const override {
    return {"QueryFollows"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
      int statement_number, EntityType type) const override {
    return {"QueryFollowsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
      int statement_number, EntityType type) const override {
    return {"QueryFollowsT"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
      int statement_number, EntityType type) const override {
    return {"QueryFollowsTBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParent(
      EntityType type) const override {
    return {"QueryAllParent"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentBy(
      EntityType type) const override {
    return {"QueryAllParentBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParent(
      int statement_number, EntityType type) const override {
    return {"QueryParent"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentBy(
      int statement_number, EntityType type) const override {
    return {"QueryParentBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentT(
      int statement_number, EntityType type) const override {
    return {"QueryParentT"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentTBy(
      int statement_number, EntityType type) const override {
    return {"QueryParentTBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllUses(
      EntityType type) const override {
    return {"QueryAllUses"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllUsesBy(
      EntityType type) const override {
    return {"QueryAllUsesBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesS(
      int statement_number, EntityType type) const override {
    return {"QueryUsesS"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesSBy(
      std::string identifier, EntityType type) const override {
    return {"QueryUsesSBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesP(
      std::string identifier, EntityType type) const override {
    return {"QueryUsesP"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesPBy(
      std::string identifier, EntityType type) const override {
    return {"QueryUsesPBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllPattern(
      Expression exp) const override {
    return {"QueryAllPattern"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPattern(
      EntityType type, Expression exp) const override {
    return {"QueryPatternEnt"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPattern(
      std::string lhs, Expression exp) const override {
    return {"QueryPatternStr"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsRelations()
      const override {
    return {"QueryAllFollowsRelations"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentsRelations()
      const override {
    return {"QueryAllParentsRelations"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllUsesRelations()
      const override {
    return {"QueryAllUsesRelations"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesP() const override {
    return {"GetUsesP"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesP(
      std::string procedure_name) const override {
    return {"GetUsesPProd"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesPBy() const override {
    return {"GetUsesPBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesPBy(
      std::string variable_name) const override {
    return {"GetUsesPByVar"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesS() const override {
    return {"GetUsesS"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesS(
      int statement_number) const override {
    return {"GetUsesSStmt"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesSBy() const override {
    return {"GetUsesSBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesSBy(
      std::string variable_name) const override {
    return {"GetUsesSByVar"};
  }
};

TEST_CASE("Query 'Select'", "[Evaluator]") {
  Evaluator eval = Evaluator();

  Planner p = Planner();
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  QueryString qs = QueryString(s, {syn}, {});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected = pkb.QueryAll(syn.GetEntityType());
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select Follows'", "[Evaluator]") {
  Evaluator eval = Evaluator();
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
  std::unordered_set<std::string> expected =
      pkb.QueryFollows(1, syn.GetEntityType());
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select FollowsBy'", "[Evaluator]") {
  Evaluator eval = Evaluator();
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
  std::unordered_set<std::string> expected =
      pkb.QueryFollowsBy(1, syn.GetEntityType());
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select FollowsT'", "[Evaluator]") {
  Evaluator eval = Evaluator();
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
  std::unordered_set<std::string> expected =
      pkb.QueryFollowsT(1, syn.GetEntityType());
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select FollowsTBy'", "[Evaluator]") {
  Evaluator eval = Evaluator();
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
  std::unordered_set<std::string> expected =
      pkb.QueryFollowsTBy(1, syn.GetEntityType());
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select AllPattern'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  EntityReference entity_ref = EntityReference();
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected = pkb.QueryAllPattern(exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select Pattern(String)'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select Pattern(String) Follows'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {ptn, f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE(result.empty());
}

TEST_CASE("Intersect check 'Select Pattern(String) AllFollows'",
          "[Evaluator]") {
  class QueryablePkbStub : public QueryablePkb {
   public:
    [[nodiscard]] std::unordered_set<std::string> QueryAll(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
        EntityType type) const override {
      return {"1", "2", "4"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollows(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllParent(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllParentBy(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryParent(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryParentBy(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryParentT(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryParentTBy(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllUses(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllUsesBy(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryUsesS(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryUsesSBy(
        std::string identifier, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryUsesP(
        std::string identifier, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryUsesPBy(
        std::string identifier, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllPattern(
        Expression exp) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryPattern(
        EntityType type, Expression exp) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryPattern(
        std::string lhs, Expression exp) const override {
      return {"4", "2"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsRelations()
        const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllParentsRelations()
        const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllUsesRelations()
        const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesP() const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesP(
        std::string procedure_name) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesPBy() const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesPBy(
        std::string variable_name) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesS() const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesS(
        int statement_number) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesSBy() const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesSBy(
        std::string variable_name) const override {
      return {};
    }
  };

  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference();
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {ptn, f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  auto it = result.begin();
  REQUIRE_FALSE(result.empty());
  REQUIRE(result.find("4")->size() == 1);
  REQUIRE(result.find("2")->size() == 1);
}

TEST_CASE("Intersect check 'Select AllFollows Pattern(String)'",
          "[Evaluator]") {
  class QueryablePkbStub : public QueryablePkb {
   public:
    [[nodiscard]] std::unordered_set<std::string> QueryAll(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
        EntityType type) const override {
      return {"1", "2", "4"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollows(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllParent(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllParentBy(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryParent(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryParentBy(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryParentT(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryParentTBy(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllUses(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllUsesBy(
        EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryUsesS(
        int statement_number, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryUsesSBy(
        std::string identifier, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryUsesP(
        std::string identifier, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryUsesPBy(
        std::string identifier, EntityType type) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllPattern(
        Expression exp) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryPattern(
        EntityType type, Expression exp) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryPattern(
        std::string lhs, Expression exp) const override {
      return {"2", "4"};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsRelations()
        const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllParentsRelations()
        const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> QueryAllUsesRelations()
        const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesP() const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesP(
        std::string procedure_name) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesPBy() const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesPBy(
        std::string variable_name) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesS() const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesS(
        int statement_number) const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesSBy() const override {
      return {};
    }

    [[nodiscard]] std::unordered_set<std::string> GetUsesSBy(
        std::string variable_name) const override {
      return {};
    }
  };

  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<Pattern> ptn = std::make_shared<Pattern>(entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference();
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f, ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root);

  REQUIRE_FALSE(result.empty());
  auto it = result.begin();
  REQUIRE_FALSE(result.empty());
  REQUIRE(result.find("4")->size() == 1);
  REQUIRE(result.find("2")->size() == 1);
}

TEST_CASE("Union check'", "[Evaluator]") {
  Evaluator eval = Evaluator();

  Planner p = Planner();
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  Select s = Select(syn);
  QueryString qs = QueryString(s, {syn}, {});
  std::shared_ptr<QNode> root_1 = p.Plan(qs);
  std::shared_ptr<QNode> root_2 = p.Plan(qs);
  std::shared_ptr<QNode> root_3 = p.Plan(qs);

  root_3->SetLeftNode(root_1);
  root_3->SetRightNode(root_2);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> result = eval.Execute(pkb, root_3);
  std::unordered_set<std::string> expected = {"QueryAll", "QueryAll",
                                              "QueryAll"};
  REQUIRE(result == expected);
}
