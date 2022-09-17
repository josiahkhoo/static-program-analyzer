#include "catch.hpp"
#include "qps/evaluator.h"
#include "qps/planner.h"
#include "qps/qnodes/entity_node.h"

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

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsRelations()
      const override {
    return {"11"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentsRelations()
      const override {
    return {"12"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesP() const override {
    return {"13"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesP(
      std::string procedure_name) const override {
    return {"14"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesPBy() const override {
    return {"15"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesPBy(
      std::string variable_name) const override {
    return {"16"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesS() const override {
    return {"17"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesS(
      int statement_number) const override {
    return {"18"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesSBy() const override {
    return {"19"};
  }

  [[nodiscard]] std::unordered_set<std::string> GetUsesSBy(
      std::string variable_name) const override {
    return {"20"};
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
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(syn, entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected = pkb.QueryAllPattern(exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(syn, entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(syn, entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {ptn, f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(syn, entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference();
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {ptn, f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::shared_ptr<Pattern> ptn =
      std::make_shared<Pattern>(syn, entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference();
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f, ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

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
  std::unordered_set<std::string> result = eval.Execute(pkb, root_3, s);
  std::unordered_set<std::string> expected = {"1", "1", "1"};
  REQUIRE(result == expected);
}