// #include "catch.hpp"
// #include "common/queryable_pkb.h"
// #include "common/reference/expression.h"
// #include "qps/planner.h"
//
// TEST_CASE("Construct 1 node: Select", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   QueryString qs = QueryString(s, {syn}, {});
//
//   std::shared_ptr<QNode> root = p.Plan(qs);
//   REQUIRE(root->IsLeaf());
// }
//
// TEST_CASE("Construct 1 node: Select & Follows", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   StatementReference statement_ref_1 = StatementReference(syn);
//   StatementReference statement_ref_2 = StatementReference(1);
//   std::shared_ptr<FollowsClause> f =
//       std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);
//   QueryString qs = QueryString(s, {syn}, {f});
//
//   std::shared_ptr<QNode> root = p.Plan(qs);
//   REQUIRE(root->IsLeaf());
// }
//
// TEST_CASE("Construct 1 node: Select & Pattern", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   EntityReference entity_ref = EntityReference();
//   Expression exp;
//   exp.to_match = "b";
//   std::shared_ptr<Pattern> ptn =
//       std::make_shared<Pattern>(syn, entity_ref, exp);
//   QueryString qs = QueryString(s, {syn}, {ptn});
//
//   std::shared_ptr<QNode> root = p.Plan(qs);
//   REQUIRE(root->IsLeaf());
// }
//
// TEST_CASE("Construct 1 node: Select & FollowsBy", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   StatementReference statement_ref_1 = StatementReference(syn);
//   StatementReference statement_ref_2 = StatementReference(1);
//   std::shared_ptr<FollowsClause> f =
//       std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);
//
//   QueryString qs = QueryString(s, {syn}, {f});
//   std::shared_ptr<QNode> root = p.Plan(qs);
//
//   REQUIRE(root->IsLeaf());
// }
//
// TEST_CASE("Construct 1 node: Select & FollowsT", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   StatementReference statement_ref_1 = StatementReference(1);
//   StatementReference statement_ref_2 = StatementReference(syn);
//   std::shared_ptr<FollowsTClause> f =
//       std::make_shared<FollowsTClause>(statement_ref_1, statement_ref_2);
//
//   QueryString qs = QueryString(s, {syn}, {f});
//   std::shared_ptr<QNode> root = p.Plan(qs);
//
//   REQUIRE(root->IsLeaf());
// }
//
// TEST_CASE("Construct 1 node: Select & FollowsTBy", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   StatementReference statement_ref_1 = StatementReference(syn);
//   StatementReference statement_ref_2 = StatementReference(1);
//   std::shared_ptr<FollowsTClause> f =
//       std::make_shared<FollowsTClause>(statement_ref_1, statement_ref_2);
//
//   QueryString qs = QueryString(s, {syn}, {f});
//   std::shared_ptr<QNode> root = p.Plan(qs);
//
//   REQUIRE(root->IsLeaf());
// }
//
// TEST_CASE("Construct 1 node: Select & Pattern WILDCARD", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   EntityReference entity_ref = EntityReference();
//   Expression exp;
//   exp.to_match = "b";
//   std::shared_ptr<Pattern> ptn =
//       std::make_shared<Pattern>(syn, entity_ref, exp);
//
//   QueryString qs = QueryString(s, {syn}, {ptn});
//   std::shared_ptr<QNode> root = p.Plan(qs);
//
//   REQUIRE(root->IsLeaf());
// }
//
// TEST_CASE("Construct 1 node: Select & Pattern IDENTIFIER", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   EntityReference entity_ref = EntityReference("id");
//   Expression exp;
//   exp.to_match = "b";
//   std::shared_ptr<Pattern> ptn =
//       std::make_shared<Pattern>(syn, entity_ref, exp);
//
//   QueryString qs = QueryString(s, {syn}, {ptn});
//   std::shared_ptr<QNode> root = p.Plan(qs);
//
//   REQUIRE(root->IsLeaf());
// }
//
// TEST_CASE("Construct 2 node: Select & Pattern & Follows", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   EntityReference entity_ref = EntityReference("id");
//   Expression exp;
//   exp.to_match = "b";
//   std::shared_ptr<Pattern> ptn =
//       std::make_shared<Pattern>(syn, entity_ref, exp);
//
//   StatementReference statement_ref_1 = StatementReference(1);
//   StatementReference statement_ref_2 = StatementReference(syn);
//   std::shared_ptr<FollowsClause> f =
//       std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);
//
//   QueryString qs = QueryString(s, {syn}, {ptn, f});
//   std::shared_ptr<QNode> root = p.Plan(qs);
//
//   REQUIRE_FALSE(root->IsLeaf());
//   REQUIRE(root->GetLeftNode()->IsLeaf());
//   REQUIRE(root->GetRightNode() == nullptr);
// }
//
// TEST_CASE("Construct 2 node: Select & Follows & Pattern", "[Planner]") {
//   Planner p = Planner();
//
//   Synonym syn = Synonym(EntityType::ASSIGN, "a");
//   Select s = Select(syn);
//   EntityReference entity_ref = EntityReference("id");
//   Expression exp;
//   exp.to_match = "b";
//   std::shared_ptr<Pattern> ptn =
//       std::make_shared<Pattern>(syn, entity_ref, exp);
//
//   StatementReference statement_ref_1 = StatementReference(1);
//   StatementReference statement_ref_2 = StatementReference(syn);
//   std::shared_ptr<FollowsClause> f =
//       std::make_shared<FollowsClause>(statement_ref_1, statement_ref_2);
//
//   QueryString qs = QueryString(s, {syn}, {f, ptn});
//   std::shared_ptr<QNode> root = p.Plan(qs);
//
//   REQUIRE_FALSE(root->IsLeaf());
//   REQUIRE(root->GetLeftNode()->IsLeaf());
//   REQUIRE(root->GetRightNode() == nullptr);
// }