#include "catch.hpp"
#include "common/clause/pattern_if.h"
#include "common/clause/pattern_while.h"
#include "common/clause/synonym_select.h"
#include "common/queryable_pkb.h"
#include "common/reference/expression.h"
#include "qps/planner.h"

TEST_CASE("Construct 1 node: Select", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  QueryString qs = QueryString(s, {syn}, {});

  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 1 node: Select & Follows", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference(1);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);
  QueryString qs = QueryString(s, {syn}, {f});

  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 1 node: Select & PatternAssign", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  EntityReference entity_ref = EntityReference();
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(syn, entity_ref, exp);
  QueryString qs = QueryString(s, {syn}, {ptn});

  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 1 node: Select & PatternIf", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::IF, "i");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  EntityReference entity_ref = EntityReference();
  std::shared_ptr<PatternIf> ptn = std::make_shared<PatternIf>(syn, entity_ref);
  QueryString qs = QueryString(s, {syn}, {ptn});

  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 1 node: Select & PatternWhile", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::WHILE, "w");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  EntityReference entity_ref = EntityReference();
  std::shared_ptr<PatternWhile> ptn =
      std::make_shared<PatternWhile>(syn, entity_ref);
  QueryString qs = QueryString(s, {syn}, {ptn});

  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 1 node: Select & FollowsBy", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference(1);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f});
  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 1 node: Select & FollowsT", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  std::shared_ptr<FollowsTClause> f =
      std::make_shared<FollowsTClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f});
  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 1 node: Select & FollowsTBy", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  StatementReference statement_ref_1 = StatementReference(syn);
  StatementReference statement_ref_2 = StatementReference(1);
  std::shared_ptr<FollowsTClause> f =
      std::make_shared<FollowsTClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f});
  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 1 node: Select & PatternAssign WILDCARD", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  EntityReference entity_ref = EntityReference();
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(syn, entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 1 node: Select & PatternAssign IDENTIFIER", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(syn, entity_ref, exp);

  QueryString qs = QueryString(s, {syn}, {ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);
}

TEST_CASE("Construct 2 node: Select & PatternAssign & Follows", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
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
}

TEST_CASE("Construct 2 node: Select & Follows & PatternAssign", "[Planner]") {
  Planner p = Planner();

  Synonym syn = Synonym(EntityType::ASSIGN, "a");
  std::shared_ptr<SynonymSelect> s =
      std::make_shared<SynonymSelect>(std::vector{syn});
  EntityReference entity_ref = EntityReference("id");
  Expression exp;
  exp.to_match = "b";
  std::shared_ptr<PatternAssign> ptn =
      std::make_shared<PatternAssign>(syn, entity_ref, exp);

  StatementReference statement_ref_1 = StatementReference(1);
  StatementReference statement_ref_2 = StatementReference(syn);
  std::shared_ptr<FollowsClause> f =
      std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);

  QueryString qs = QueryString(s, {syn}, {f, ptn});
  std::shared_ptr<QNode> root = p.Plan(qs);
}