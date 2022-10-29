#ifndef SPA_PLANNER_H
#define SPA_PLANNER_H

#include <unordered_map>

#include "qps/qnodes/q_node.h"
#include "query_string.h"

class Planner {
 public:
  explicit Planner();

  /// Generates an executable query tree from a given query string.
  /// \param q_string Query string.
  /// \return Executable query tree.
  [[nodiscard]] std::shared_ptr<QNode> Plan(const QueryString &q_string) const;

 private:
  /// Sorts a given vector of query operation based on speed, from fastest to
  /// slowest.
  ///
  /// \param v Vector to sort.
  void SortQueryOperationVector(
      std::vector<std::shared_ptr<QueryOperation>> &v) const;

  [[nodiscard]] std::shared_ptr<QNode> BuildIntersectTree(
      const std::vector<std::shared_ptr<QueryOperation>> &operations) const;

  /// Looks through all the single syn operations and double syn operations and
  /// links them together. <br/> For example: Follows(1, s) and Follows(2, s)
  /// are linked together, but Follows(1, k) and Follows(2, k1) are not as they
  /// don't share common synonyms.
  /// <br/> These single synonym abstractions are then linked to the double
  /// synonym abstractions. <br/> Example: Follows(1, s) and Follows(2, s) are
  /// connected to Follows(s, s1).
  ///
  /// \param single_syn_ops Vector of single syn operations.
  /// \param double_syn_ops Vector of double syn operations.
  /// \param abstraction_nodes Vector of abstraction nodes to write into.
  /// \param abstraction_node_to_query_op_map Map of abstraction nodes to
  /// corresponding query operation to write into.
  void CreateAbstractionNodes(
      const std::vector<std::shared_ptr<QueryOperation>> &single_syn_ops,
      const std::vector<std::shared_ptr<QueryOperation>> &double_syn_ops,
      std::vector<std::shared_ptr<QNode>> &abstraction_nodes,
      std::unordered_map<std::shared_ptr<QNode>,
                         std::shared_ptr<QueryOperation>>
          &abstraction_node_to_query_op_map) const;

  /// Looks through all the given abstraction nodes and groups them together
  /// based on common values within the double synonym operations.
  ///
  /// \param abstraction_nodes Vector of abstraction nodes.
  /// \param abstraction_node_to_query_op_map Map of abstraction nodes to
  /// corresponding query operation.
  /// \param disjoint_join_nodes Vector of disjoint join nodes to write into.
  void CreateDisjointJoinNodes(
      const std::vector<std::shared_ptr<QNode>> &abstraction_nodes,
      std::unordered_map<std::shared_ptr<QNode>,
                         std::shared_ptr<QueryOperation>>
          &abstraction_node_to_query_op_map,
      std::unordered_set<std::shared_ptr<QNode>> &disjoint_join_nodes) const;

  /// Connects given disjoint nodes together a left skewed tree.
  ///
  /// \param disjoint_join_nodes Disjoint join nodes to connect.
  /// \param head Existing head.
  /// \return New tree.
  std::shared_ptr<QNode> ConnectDisjointNodes(
      std::unordered_set<std::shared_ptr<QNode>> &disjoint_join_nodes,
      std::shared_ptr<QNode> &head) const;

  /// Adds unused synonyms (i.e. synonyms not used in a abstractions but are
  /// part of the select clause) to existing head, in a left skewed tree.
  ///
  /// \param q_string Query string.
  /// \param single_syn_ops Single synonym operations.
  /// \param double_syn_ops Double synonym operations.
  /// \param head Existing head.
  /// \return New tree.
  std::shared_ptr<QNode> ConnectUnusedSynonyms(
      const QueryString &q_string,
      const std::vector<std::shared_ptr<QueryOperation>> &single_syn_ops,
      const std::vector<std::shared_ptr<QueryOperation>> &double_syn_ops,
      std::shared_ptr<QNode> &head) const;

  /// Adds no synonym operations to the existing head in the form of boolean
  /// nodes in a left skewed tree.
  ///
  /// \param no_syn_ops No synonym operations.
  /// \param head  Existing head.
  /// \return New tree.
  std::shared_ptr<QNode> ConnectBooleanNodes(
      const std::vector<std::shared_ptr<QueryOperation>> &no_syn_ops,
      std::shared_ptr<QNode> &head) const;
};

#endif  // SPA_PLANNER_H
