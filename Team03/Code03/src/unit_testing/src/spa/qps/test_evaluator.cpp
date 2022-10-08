#include "catch.hpp"
#include "common/clause/boolean_select.h"
#include "common/clause/pattern_if.h"
#include "common/clause/pattern_while.h"
#include "common/clause/synonym_select.h"
#include "common/clause/with.h"
#include "common/reference/attribute_name.h"
#include "common/reference/attribute_reference.h"
#include "fakeit.hpp"
#include "qps/evaluator.h"
#include "qps/planner.h"
#include "qps/qnodes/entity_node.h"

using namespace fakeit;

class QueryablePkbStub : public QueryablePkb {
 public:
  [[nodiscard]] std::unordered_set<std::string> QueryAll(
      EntityType) const override {
    return {"QueryAll"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollows(
      EntityType) const override {
    return {"QueryAllFollows"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllFollowsBy(
      EntityType) const override {
    return {"QueryAllFollowsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollows(
      int, EntityType) const override {
    return {"QueryFollows"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsBy(
      int, EntityType) const override {
    return {"QueryFollowsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsT(
      int, EntityType) const override {
    return {"QueryFollowsT"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryFollowsTBy(
      int, EntityType) const override {
    return {"QueryFollowsTBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParent(
      EntityType) const override {
    return {"QueryAllParent"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllParentBy(
      EntityType) const override {
    return {"QueryAllParentBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParent(
      int, EntityType) const override {
    return {"QueryParent"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentBy(
      int, EntityType) const override {
    return {"QueryParentBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentT(
      int, EntityType) const override {
    return {"QueryParentT"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryParentTBy(
      int, EntityType) const override {
    return {"QueryParentTBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllUses(
      EntityType) const override {
    return {"QueryAllUses"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllUsesBy(
      EntityType) const override {
    return {"QueryAllUsesBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesS(
      int, EntityType) const override {
    return {"QueryUsesS"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesSBy(
      std::string, EntityType) const override {
    return {"QueryUsesSBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesP(
      std::string, EntityType) const override {
    return {"QueryUsesP"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryUsesPBy(
      std::string, EntityType) const override {
    return {"QueryUsesPBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifies(
      EntityType) const override {
    return {"QueryAllModifies"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifiesBy(
      EntityType) const override {
    return {"QueryAllModifiesBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesS(
      int) const override {
    return {"QueryModifiesS"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesSBy(
      std::string, EntityType) const override {
    return {"QueryModifiesSBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesP(
      std::string) const override {
    return {"QueryModifiesP"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryModifiesPBy(
      std::string) const override {
    return {"QueryModifiesPBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllCalls() const override {
    return {"QueryAllCalls"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsBy()
      const override {
    return {"QueryAllCallsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCalls(
      std::string) const override {
    return {"QueryCalls"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCallsBy(
      std::string) const override {
    return {"QueryCallsBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCallsT(
      std::string) const override {
    return {"QueryCallsT"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryCallsTBy(
      std::string) const override {
    return {"QueryCallsTBy"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllAssignPattern(
      Expression) const override {
    return {"QueryAllAssignPattern"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAssignPattern(
      std::string, Expression) const override {
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

  [[nodiscard]] std::unordered_set<std::string> QueryAllModifiesRelations()
      const override {
    return {"QueryAllModifiesRelations"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryAllCallsRelations()
      const override {
    return {"QueryAllCallsRelations"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllWhilePattern()
      const override {
    return {"QueryAllWhilePattern"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryWhilePattern(
      std::string) const override {
    return {"QueryWhilePattern"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryAllIfPattern()
      const override {
    return {"QueryAllIfPattern"};
  }

  [[nodiscard]] virtual std::unordered_set<std::string> QueryIfPattern(
      std::string) const override {
    return {"QueryIfPattern"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromAssign(
      int) const override {
    return {"QueryPatternVariablesFromAssign"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromWhile(
      int) const override {
    return {"QueryPatternVariablesFromWhile"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryPatternVariablesFromIf(
      int) const override {
    return {"QueryPatternVariablesFromIf"};
  }

  [[nodiscard]] std::string QueryWithAttributeFromStatement(
      EntityType, int) const override {
    return {"QueryWithAttributeFromStatement"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType, AttributeName, std::string) const override {
    return {"QueryWithAttributeIdentifier"};
  }

  [[nodiscard]] std::unordered_set<std::string> QueryWithAttribute(
      EntityType, AttributeName, int) const override {
    return {"QueryWithAttributeNumber"};
  }
};

TEST_CASE("Query 'Select'", "[Evaluator]") {
  Evaluator eval = Evaluator();

  Planner p = Planner();
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
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
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
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
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
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
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
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
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
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

TEST_CASE("Query 'Select AllPatternAssign'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  EntityReference entity_ref = EntityReference();
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(syn, entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected = pkb.QueryAllAssignPattern(exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select Pattern(String)Assign'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(syn, entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryAssignPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select Pattern(String)If'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::IF, "i");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  EntityReference entity_ref = EntityReference("id");
  std::shared_ptr<PatternIf> ptn = std::make_shared<PatternIf>(syn, entity_ref);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryIfPattern(entity_ref.GetIdentifier());
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select Pattern(String)While'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::WHILE, "w");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  EntityReference entity_ref = EntityReference("id");
  std::shared_ptr<PatternWhile> ptn =
      std::make_shared<PatternWhile>(syn, entity_ref);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryWhilePattern(entity_ref.GetIdentifier());
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select Pattern(String)Assign Follows'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(syn, entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {ptn, f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected =
      pkb.QueryAssignPattern(entity_ref.GetIdentifier(), exp);
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

  REQUIRE(result.empty());
}

TEST_CASE("Query 'Select With Name'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  Attribute attr = Attribute(syn, AttributeName::PROC_NAME);
  AttributeReference attrRef1 = AttributeReference(attr);
  AttributeReference attrRef2 = AttributeReference("name");

  std::shared_ptr<With> withCl = std::make_shared<With>(attrRef1, attrRef2);

  QueryString qs = QueryString(s, {syn}, {withCl});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected = pkb.QueryWithAttribute(
      attrRef1.GetSynonym().GetEntityType(), attrRef1.GetAttributeName(),
      attrRef2.GetIdentifier());
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

  REQUIRE(result == expected);
}

TEST_CASE("Query 'Select With Integer'", "[Evaluator]") {
  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  Attribute attr = Attribute(syn, AttributeName::VALUE);
  AttributeReference attrRef1 = AttributeReference(attr);
  AttributeReference attrRef2 = AttributeReference(1);

  std::shared_ptr<With> withCl = std::make_shared<With>(attrRef1, attrRef2);

  QueryString qs = QueryString(s, {syn}, {withCl});
  std::shared_ptr<QNode> root = p.Plan(qs);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> expected = pkb.QueryWithAttribute(
      attrRef1.GetSynonym().GetEntityType(), attrRef1.GetAttributeName(),
      attrRef2.GetLineNumber());
  std::unordered_set<std::string> result = eval.Execute(pkb, root, s);

  REQUIRE(result == expected);
}

TEST_CASE("Intersect check 'Select Pattern(String)Assign AllFollows'",
          "[Evaluator]") {
  Mock<QueryablePkb> queryable_pkb_stub;
  When(Method(queryable_pkb_stub, QueryAllFollows))
      .AlwaysReturn({"1", "2", "4"});
  When(Method(queryable_pkb_stub, QueryAssignPattern)).AlwaysReturn({"4", "2"});

  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(syn, entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference();
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {ptn, f});
  std::shared_ptr<QNode> root = p.Plan(qs);

  std::unordered_set<std::string> expected =
      queryable_pkb_stub.get().QueryAssignPattern(entity_ref.GetIdentifier(),
                                                  exp);
  std::unordered_set<std::string> result =
      eval.Execute(queryable_pkb_stub.get(), root, s);

  result.begin();
  REQUIRE_FALSE(result.empty());
  REQUIRE(result.find("4")->size() == 1);
  REQUIRE(result.find("2")->size() == 1);
}

TEST_CASE("Intersect check 'Select AllFollows Pattern(String)Assign'",
          "[Evaluator]") {
  Mock<QueryablePkb> queryable_pkb_stub;
  When(Method(queryable_pkb_stub, QueryAllFollows))
      .AlwaysReturn({"1", "2", "4"});
  When(Method(queryable_pkb_stub, QueryAssignPattern)).AlwaysReturn({"4", "2"});

  Evaluator eval = Evaluator();
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(syn, entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference();
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f, ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);

  std::unordered_set<std::string> expected =
      queryable_pkb_stub.get().QueryAssignPattern(entity_ref.GetIdentifier(),
                                                  exp);
  std::unordered_set<std::string> result =
      eval.Execute(queryable_pkb_stub.get(), root, s);

  REQUIRE_FALSE(result.empty());
  result.begin();
  REQUIRE_FALSE(result.empty());
  REQUIRE(result.find("4")->size() == 1);
  REQUIRE(result.find("2")->size() == 1);
}

TEST_CASE("Union check'", "[Evaluator]") {
  Evaluator eval = Evaluator();

  Planner p = Planner();
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s = std::make_shared<SynonymSelect>(
      std::vector{Select::SynonymWithMaybeAttribute(syn)});
  QueryString qs = QueryString(s, {syn}, {});
  std::shared_ptr<QNode> root_1 = p.Plan(qs);
  std::shared_ptr<QNode> root_2 = p.Plan(qs);
  std::shared_ptr<QNode> root_3 = p.Plan(qs);

  root_3->SetLeftNode(root_1);
  root_3->SetRightNode(root_2);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> result = eval.Execute(pkb, root_3, s);
  std::unordered_set<std::string> expected = {"QueryAll", "QueryAll",
                                              "QueryAll"};
  REQUIRE(result == expected);
}

TEST_CASE("BOOLEAN check'", "[Evaluator]") {
  Evaluator eval = Evaluator();

  Planner p = Planner();
  std::shared_ptr<Select> s = std::make_shared<BooleanSelect>();
  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  QueryString qs = QueryString(s, {syn}, {});
  std::shared_ptr<QNode> root_1 = p.Plan(qs);
  std::shared_ptr<QNode> root_2 = p.Plan(qs);
  std::shared_ptr<QNode> root_3 = p.Plan(qs);

  root_3->SetLeftNode(root_1);
  root_3->SetRightNode(root_2);

  QueryablePkbStub pkb = QueryablePkbStub();
  std::unordered_set<std::string> result = eval.Execute(pkb, root_3, s);
  std::unordered_set<std::string> expected = {"TRUE"};
  REQUIRE(result == expected);
}
